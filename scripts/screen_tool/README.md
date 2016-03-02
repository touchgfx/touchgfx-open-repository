# screen.rb

Script to generate a TouchGFX View and Presenter pair.
The script will generate new header and source files for these and 
update the FrontendHeap and FrontendApplication accordingly.
Visual Studio project files will be updated to include the new files.
 
# Usage

Copy the screen_tool folder to your application root.
Run the tool from touchgfx-env by invoking the command
  
```
./screen_tool/screen.rb ScreenName
```

Replace ScreenName with the desired name of your screen.

# Example

```
cd app/template/EmptyApplication
./screen_tool/screen.rb Temperature
```

This will result in the following files being added and changed

* gui/include/gui/temperature_screen/TemperaturePresenter.hpp
* gui/include/gui/temperature_screen/TemperatureView.hpp
* gui/src/temperature_screen/TemperaturePresenter.cpp
* gui/src/temperature_screen/TemperatureView.cpp
* gui/include/gui/common/FrontendApplication.hpp
* gui/include/gui/common/FrontendHeap.hpp
* gui/src/common/FrontendApplication.cpp
* simulator/msvs/Application.vcxproj
* simulator/msvs/Application.vcxproj.filters
