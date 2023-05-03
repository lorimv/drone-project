#include "BatteryDecorator.h"

BatteryDecorator::~BatteryDecorator() {
  delete drone;
}

bool BatteryDecorator::NeedsCharge(double dt) {
  IEntity* simDrone = drone;
  int simCharge = charge;
  
  while (!(simDrone->GetAvailable())) {
    simDrone->Update();
    simCharge -= (dt * .001);      //TODO edit battery decrease based on tests
    if (simCharge <= 0) {
      return true;
    }
  }
  new BeelineStrategy(simDrone->GetPosition(), GetNearestCharger()->GetPosition());
  
  while (//simDrone to charger incomplete)}
    
    simCharge -= (dt * .001);
    if (simCharge <= 0) {
      return true;
    }
  }
  return false;
}

BatteryDecorator::GetNearestCharger(){

}



void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
  bool charging;//here
  bool needCharge;
  
  if (charging) { //if at a charger
    charge += (dt* .1);
    if (battery >= 100) {
      charge = 100        
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

