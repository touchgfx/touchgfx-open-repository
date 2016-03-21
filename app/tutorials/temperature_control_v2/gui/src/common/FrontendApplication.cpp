#include <new>
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/template_screen/TemplateView.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <gui/common/FrontendHeap.hpp>

using namespace touchgfx;


FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : touchgfx::MVPApplication(),
      transitionCallback(),
      frontendHeap(heap),
      model(m)
{
}

void FrontendApplication::gotoTemplateScreen()
{
    transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoTemplateScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoTemplateScreenImpl()
{
    makeTransition< TemplateView, TemplatePresenter, touchgfx::SlideTransition<EAST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreen()
{
    transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenImpl()
{
    makeTransition< MainView, MainPresenter, touchgfx::SlideTransition<WEST>, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMainScreenNoTransition()
{
    transitionCallback = touchgfx::Callback< FrontendApplication >(this, &FrontendApplication::gotoMainScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &transitionCallback;
}

void FrontendApplication::gotoMainScreenNoTransitionImpl()
{
    makeTransition< MainView, MainPresenter, touchgfx::NoTransition, Model >(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}