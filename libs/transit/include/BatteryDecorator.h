#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "DroneDecorator.h"
#include "IStrategy.h"
#include "BatteryDecorator.h"

/**
 * @brief this class inhertis from the DroneDecorator class and is represents
 * battery.
 */
  class BatteryDecorator : public DroneDecorator {
   private:
    int charge;
    BatteryTracker::BatteryTracker *tracker;

  
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

    /**
     * @brief Getter for accessing battery level
     */
    int GetBatteryLevel() { return charge; }

    /**
     * @brief Checks if drone has enough charge to complete the trip
     * and get to the nearest recharge station after the trip.
     */
    bool NeedsCharge(double dt, std::vector<IEntity*> scheduler);

    /**
     * @brief Returns the nearest available recharge station
     */
    IEntity* GetNearestCharger(IEntity* d, std::vector<IEntity*> scheduler);
  };

#endif
