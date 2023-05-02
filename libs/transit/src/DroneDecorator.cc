#include "DroneDecorator.h"

DroneDecorator::DroneDecorator(IEntity drone){
  this->drone = drone;
}

CelebrationDecorator::~CelebrationDecorator() {
  // Delete dynamically allocated variables
  delete drone;
}
