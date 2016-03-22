#include <gui/template_screen/TemplatePresenter.hpp>
#include <gui/template_screen/TemplateView.hpp>
#include <gui/model/Model.hpp>

TemplatePresenter::TemplatePresenter(TemplateView& v)
    : view(v)
{
}

void TemplatePresenter::activate()
{
    view.setPoolTemperature(model->getPoolTemperature());
    view.setResetValue(model->getPoolTemperature());
}

void TemplatePresenter::deactivate()
{

}

void TemplatePresenter::poolTemperatureUpdated(int value)
{
    model->setPoolTemperature(value);
}
