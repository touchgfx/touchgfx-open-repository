#ifndef FRONTENDHEAP_HPP
#define FRONTENDHEAP_HPP

#include <common/Meta.hpp>
#include <common/Partition.hpp>
#include <mvp/MVPHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/common/FrontendApplication.hpp>
#include <gui/model/Model.hpp>
#include <gui/template_screen/TemplateView.hpp>
#include <gui/template_screen/TemplatePresenter.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/transitions/SlideTransition.hpp>

/**
 * This class provides the memory that shall be used for memory allocations
 * in the frontend. A single instance of the FrontendHeap is allocated once (in heap
 * memory), and all other frontend objects such as views, presenters and data model are
 * allocated within the scope of this FrontendHeap. As such, the RAM usage of the entire
 * user interface is sizeof(FrontendHeap).
 *
 * @note The FrontendHeap reserves memory for the most memory-consuming presenter and
 * view only. The largest of these classes are determined at compile-time using template
 * magic. As such, it is important to add all presenters, views and transitions to the
 * type lists in this class.
 *
 */
class FrontendHeap : public MVPHeap
{
public:
    /**
     * A list of all view types. Must end with meta::Nil.
     * @note All view types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< TemplateView,
            meta::TypeList< MainView,
                            meta::Nil
                          > > ViewTypes;

    /**
     * Determine (compile time) the View type of largest size.
     */
    typedef meta::select_type_maxsize< ViewTypes >::type MaxViewType;

    /**
     * A list of all presenter types. Must end with meta::Nil.
     * @note All presenter types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< TemplatePresenter,
            meta::TypeList< MainPresenter,
                            meta::Nil
                          > > PresenterTypes;

    /**
     * Determine (compile time) the Presenter type of largest size.
     */
    typedef meta::select_type_maxsize< PresenterTypes >::type MaxPresenterType;

    /**
     * A list of all transition types. Must end with meta::Nil.
     * @note All transition types used in the application MUST be added to this list!
     */
    typedef meta::TypeList< NoTransition,
            meta::TypeList< SlideTransition<WEST>,
            meta::TypeList< SlideTransition<EAST>,
                            meta::Nil
                          > > > TransitionTypes;

    /**
     * Determine (compile time) the Transition type of largest size.
     */
    typedef meta::select_type_maxsize< TransitionTypes >::type MaxTransitionType;

    static FrontendHeap& getInstance()
    {
        static FrontendHeap instance;
        return instance;
    }

    Partition< PresenterTypes, 1 > presenters;
    Partition< ViewTypes, 1 > views;
    Partition< TransitionTypes, 1 > transitions;
    FrontendApplication app;
    Model model;
private:
    FrontendHeap()
        : MVPHeap(presenters, views, transitions, app),
          presenters(),
          views(),
          transitions(),
          app(model, *this)
        {
            // Goto start screen
            app.gotoMainScreenNoTransition();
        }
};

#endif
