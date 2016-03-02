#!/usr/bin/env ruby

# Script to generate a TouchGFX View and Presenter pair.
# The script will generate new header and source files for these and 
# update the FrontendHeap and FrontendApplication accordingly.
# Visual Studio project files will be updated to include the new files
# 
# USAGE: 
#   ./screen.rb SCREEN_NAME
#
# The script comes "as is". Use with caution.
# Check https://github.com/draupnergraphics/touchgfx-open-repository/blob/master/license.txt for license terms

require 'erb'
require 'fileutils'
require 'securerandom'

# Extend the String class to have methods for snake, camel casing and sanitizing
class String
    def snake_case
        return downcase if match(/\A[A-Z]+\z/)
        gsub(/([A-Z]+)([A-Z][a-z])/, '\1_\2').
        gsub(/([a-z])([A-Z])/, '\1_\2').
        downcase
    end
    def camel_case
        return self if self !~ /_/ && self =~ /[A-Z]+.*/
        split('_').map{|e| e.capitalize}.join
    end
    def substitute(pattern, replacement)
        if(self.match(pattern).nil?)
            puts "WARNING: could not match #{pattern.to_s}"
        end
        self.sub(pattern, replacement)
    end
end

# Helper method for writing a file using a template from the templates directory
def write_file(file_name, template_name, mode = 'w')
    puts "* #{file_name}"
    File.open(file_name, mode) do |f|
        f.write(ERB.new(File.read("#{HERE}/templates/#{template_name}")).result)
    end
end

# Helper method to open a file and write modified contents
def change_file(file_name, output = true)
    puts "* #{file_name}" if output
    contents = File.read(file_name)
    modified_contents = yield contents
    File.open(file_name, 'w') { |f| f.write(modified_contents) }
end

# Check args
if(ARGV.length != 1)
    puts "Usage: ./screen.rb ScreenName"
    puts "Create View, Presenter, update FrontendHeap, FrontendApplicaton, ..."
    exit
end

name = ARGV.shift

if name.match(/[^A-Za-z]/)
    puts "screen name must consist of characters A-Z and a-z only"; exit
end

the_name = name.snake_case
TheName = name.camel_case

HERE = File.expand_path(File.dirname(__FILE__))
APP_PATH = File.dirname(HERE)

FileUtils.cd(APP_PATH) do 

    if(File.exists?("gui/include/gui/#{the_name}_screen/#{TheName}Presenter.hpp") || 
        File.exists?("gui/src/#{the_name}_screen/#{TheName}Presenter.cpp"))
        puts "#{TheName} already exists, bailing out."; exit
    end

    FileUtils.mkdir_p("gui/include/gui/#{the_name}_screen")
    FileUtils.mkdir_p("gui/src/#{the_name}_screen")

    write_file("gui/include/gui/#{the_name}_screen/#{TheName}Presenter.hpp", 'Presenter.hpp.template')
    write_file("gui/include/gui/#{the_name}_screen/#{TheName}View.hpp", 'View.hpp.template')
    write_file("gui/src/#{the_name}_screen/#{TheName}Presenter.cpp", 'Presenter.cpp.template')
    write_file("gui/src/#{the_name}_screen/#{TheName}View.cpp", 'View.cpp.template')

    change_file("gui/include/gui/common/FrontendApplication.hpp") do |contents|
        contents.
            substitute(/(class FrontendApplication.*?public:)/m, "\\1\n    void goto#{TheName}();").
            substitute(/(class FrontendApplication.*?private:)/m, "\\1\n    void goto#{TheName}Impl();")
    end

    change_file("gui/include/gui/common/FrontendHeap.hpp") do |contents| 
        includes = "\#include <gui/#{the_name}_screen/#{TheName}View.hpp>\n"\
                   "\#include <gui/#{the_name}_screen/#{TheName}Presenter.hpp>"
        contents.
            substitute(/(#include <gui\/common\/FrontendApplication\.hpp>)/m, "\\1\n#{includes}").
            substitute( /([[:blank:]]*)meta::Nil([\s,>]+?)ViewTypes/m, "\\1meta::TypeList< #{TheName}View,\n\\1meta::Nil \\2> ViewTypes").
            substitute( /([[:blank:]]*)meta::Nil([\s,>]+?)PresenterTypes/m, "\\1meta::TypeList< #{TheName}Presenter,\n\\1meta::Nil \\2> PresenterTypes") 
    end

    change_file("gui/src/common/FrontendApplication.cpp", false) do |contents| 
        includes = "\#include <gui/#{the_name}_screen/#{TheName}View.hpp>\n"\
                   "\#include <gui/#{the_name}_screen/#{TheName}Presenter.hpp>"
        contents.substitute(/(#include <gui\/common\/FrontendApplication\.hpp>)/m, "\\1\n#{includes}") 
    end
    write_file("gui/src/common/FrontendApplication.cpp", 'FrontendApplication.goto.cpp.template', 'a')

    change_file("simulator/msvs/Application.vcxproj") do |contents| 
        compiles = "    <ClCompile Include=\"..\\..\\gui\\src\\#{the_name}_screen\\#{TheName}Presenter.cpp\" />\n"\
                   "    <ClCompile Include=\"..\\..\\gui\\src\\#{the_name}_screen\\#{TheName}View.cpp\" />"
        includes = "    <ClInclude Include=\"..\\..\\gui\\include\\gui\\#{the_name}_screen\\#{TheName}Presenter.hpp\" />\n"\
                   "    <ClInclude Include=\"..\\..\\gui\\include\\gui\\#{the_name}_screen\\#{TheName}View.hpp\" />"
        contents.
            substitute(/(<ItemGroup>.+?<ClCompile Include="..\\..\\gui\\src\\common\\FrontendApplication.cpp" \/>)/m, "\\1\n#{compiles}").
            substitute(/(<ItemGroup>.+?<ClInclude Include="..\\..\\gui\\include\\gui\\common\\FrontendApplication.hpp" \/>)/m, "\\1\n#{includes}")
    end

    change_file("simulator/msvs/Application.vcxproj.filters") do |contents| 
        filters  = "    <Filter Include=\"Source Files\\#{the_name}_screen\">\n"\
                   "      <UniqueIdentifier>{#{SecureRandom.uuid}}</UniqueIdentifier>\n"\
                   "    </Filter>\n"\
                   "    <Filter Include=\"Header Files\\#{the_name}_screen\">\n"\
                   "      <UniqueIdentifier>{#{SecureRandom.uuid}}</UniqueIdentifier>\n"\
                   "    </Filter>"
        compiles = "    <ClCompile Include=\"..\\..\\gui\\src\\#{the_name}_screen\\#{TheName}View.cpp\">\n"\
                   "      <Filter>Source Files\\#{the_name}_screen</Filter>\n"\
                   "    </ClCompile>\n"\
                   "    <ClCompile Include=\"..\\..\\gui\\src\\#{the_name}_screen\\#{TheName}Presenter.cpp\">\n"\
                   "      <Filter>Source Files\\#{the_name}_screen</Filter>\n"\
                   "    </ClCompile>"
        includes = "    <ClInclude Include=\"..\\..\\gui\\include\\gui\\#{the_name}_screen\\#{TheName}View.hpp\">\n"\
                   "      <Filter>Header Files\\#{the_name}_screen<\/Filter>\n"\
                   "    </ClInclude>\n"\
                   "    <ClInclude Include=\"..\\..\\gui\\include\\gui\\#{the_name}_screen\\#{TheName}Presenter.hpp\">\n"\
                   "      <Filter>Header Files\\#{the_name}_screen</Filter>\n"\
                   "    </ClInclude>"
        contents.
            substitute(/(<Filter Include="Source Files\\simulator">\s+<UniqueIdentifier>\{.*?\}<\/UniqueIdentifier>\s+<\/Filter>)/m, "\\1\n#{filters}").
            substitute(/(<ClCompile Include="..\\..\\gui\\src\\common\\FrontendApplication.cpp">\s+<Filter>Source Files\\common<\/Filter>\s+<\/ClCompile>)/m, "\\1\n#{compiles}").
            substitute(/(<ClInclude Include="..\\..\\gui\\include\\gui\\common\\FrontendApplication.hpp">\s+<Filter>Header Files\\common<\/Filter>\s+<\/ClInclude>)/m, "\\1\n#{includes}")
    end
end