#include "BatteryDecorator.h"

BatteryDecorator::~BatteryDecorator() {
  delete drone;
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
  bool charging;//here
  bool needCharge;
  
  if (charging) { //if at a charger
    battery += (dt* .1);
    if (battery >= 100) {
      battery = 100        
      charging = false;
    }
  }
  
  else if (drone->GetAvailable()) { //If Drone waiting for trip
    drone->GetNearestEntity(scheduler);
  }
  
  if (!drone->GetAvailable()) {
    
  }
  
  
  
  
  //else if drone->toRobot
  //Calculate charge needed to get there
  //If charge < requiredCharge...
  //route to a Charger (they're kept track of in scheduler)
  //else...
  //drone->Move(dt, scheduler)
  //but also reduce charge, too
}

