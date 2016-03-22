#include <gui/main_screen/MainPresenter.hpp>
#include <gui/main_screen/MainView.hpp>
#include <gui/model/Model.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{
}

void MainPresenter::activate()
{
    view.setPoolTemperature(model->getPoolTemperature());
    view.setOutdoorTemperature(model->getOutdoorTemperature());
}

void MainPresenter::deactivate()
{

}

void MainPresenter::outdoorTemperatureUpdated(int newTemperature)
{
    view.setOutdoorTemperature(newTemperature);
}
