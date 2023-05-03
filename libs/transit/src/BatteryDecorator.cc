#include "BatteryDecorator.h"

BatteryDecorator::~BatteryDecorator() {
  delete drone;
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
  //if drone has no destination...
  //drone->Update(dt, scheduler) like normal
  
  //else if drone->toRobot
  //Calculate charge needed to get there
  //If charge < requiredCharge...
  //route to a Charger (they're kept track of in scheduler)
  //else...
  //drone->Move(dt, scheduler)
  //but also reduce charge, too
}
