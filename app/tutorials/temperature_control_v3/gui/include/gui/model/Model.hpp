#ifndef MODEL_HPP
#define MODEL_HPP

#include <gui/model/ModelListener.hpp>
#include <touchgfx/Utils.hpp>

class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */
class Model
{
public:
    Model() :
        modelListener(0),
        poolTemperature(22),
        outdoorTemperature(28),
        tickCounter(0)
    {}

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener) { modelListener = listener; }

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick() 
    {
        if (++tickCounter % 250 == 0)
        {
            uint32_t rnd = randomNumber();
            if (rnd < 20)
            {
                updateOutdoorTemperature(outdoorTemperature + 1);
            }
            else if (rnd < 40)
            {
                updateOutdoorTemperature(outdoorTemperature - 1);
            }
        }

    }

    void setPoolTemperature(int value)  {  poolTemperature = value; }
    int getPoolTemperature() {  return poolTemperature; }

    void updateOutdoorTemperature(int value)
    {
        outdoorTemperature = value;
        modelListener->outdoorTemperatureUpdated(outdoorTemperature);
    }

    int getOutdoorTemperature() { return outdoorTemperature; }

protected:
    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

    int poolTemperature;
    int outdoorTemperature;

    int tickCounter;

    // Returns a pseudo random number between 0 and 100
    uint32_t randomNumber()
    {
        static uint32_t seed = 5323;
        seed = 8253729 * seed + 2396403;
        return seed % 100;
    }
};


#endif /* MODEL_HPP */
