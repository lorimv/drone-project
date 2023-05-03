#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "DroneDecorator.h"

/**
 * @brief this class inhertis from the DroneDecorator class and is represents
 * battery.
 */
  class BatteryDecorator : public DroneDecorator {
   private:
    int charge;
  
   public:
    /**
     * @brief Construct a new Spin Decorator object
     *
     * @param strategy the strategy to decorate onto
     */
    BatteryDecorator(IEntity* drone) : DroneDecorator(drone) {charge = 100;};
    
    /**
     * @brief BatteryDecorator Destructor
     */
    ~BatteryDecorator();
    
    /**
     * @brief Update the drone factoring in battery logic
     */
    virtual void Update(double dt, std::vector<IEntity*> scheduler);
  };

#endif
