#include "DroneDecorator.h"

DroneDecorator::DroneDecorator(IEntity* drone){
  this->drone = drone;
}

DroneDecorator::~DroneDecorator() {
  // Delete dynamically allocated variables
  delete drone;
}
