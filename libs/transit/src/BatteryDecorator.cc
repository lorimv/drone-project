#include "BatteryDecorator.h"

BatteryDecorator::~BatteryDecorator() {
  delete drone;
}

bool BatteryDecorator::NeedsCharge() {
  IEntity* simDrone = drone;
  int simCharge = charge;
  
  while (//simDrone trip incomplete) {
    if (simCharge <= 0) {
      return true;
    }
  }
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
    return;
  }
  
  else if (drone->GetAvailable()) { //If Drone waiting for trip
    drone->GetNearestEntity(scheduler);
    if (!(drone->GetAvailable())//if it found a trip...
      if (NeedsCharge())
        needCharge = true;
        return;
      }
    }
  }
  
  if (needCharge) {
    drone
  } else {
    drone->Update();
  }
  
  
  
  
  //else if drone->toRobot
  //Calculate charge needed to get there
  //If charge < requiredCharge...
  //route to a Charger (they're kept track of in scheduler)
  //else...
  //drone->Move(dt, scheduler)
  //but also reduce charge, too
}

