#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include "IEntity.h"

/**
 * @brief this class inhertis from the IEntity class and is represents
 * an abstract drone decorator template.
 */
class DroneDecorator : public IEntity {
 protected:
  IEntity* drone;
  
 public:
  /**
   * @brief Construct a new Drone Decorator object
   *
   * @param drone the drone to decorate onto
   */
  DroneDecorator(IEntity* drone);
  
  /**
   * @brief Drone Decorator Destructor
   */
  ~DroneDecorator();
  
  /**
   * @brief update function to be overwritten, calls drone's update when needed
   * 
   * @param dt Delta Time
   * @param scheduler List of all entities in the system
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) = 0;
};

#endif
