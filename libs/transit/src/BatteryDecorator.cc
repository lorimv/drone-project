#include "BatteryDecorator.h"
#include "BeelineStrategy.h"

BatteryDecorator::~BatteryDecorator() {
  delete drone;
}

bool BatteryDecorator::NeedsCharge(double dt) {
  IEntity* simDrone = drone;
  int simCharge = charge;
  
  while (!(simDrone->GetAvailability())) {
    simDrone->Update();
    simCharge -= (dt * .001);      //TODO edit battery decrease based on tests
    if (simCharge <= 0) {
      return true;
    }
  }
  BeelineStrategy* BeeLine = new BeelineStrategy(simDrone->GetPosition(), GetNearestCharger()->GetPosition());
  // simDrone to charger incomplete
  while (!BeeLine->IsCompleted()){
    BeeLine->Move(simDrone, dt);
    simCharge -= (dt * .001);
    if (simCharge <= 0) {
      return true;
    }
  }
  return false;
}

IEntity* BatteryDecorator::GetNearestCharger(){
  float minDis = std::numeric_limits<float>::max();
  IEntity* closest_charger;
  for (auto entity: scheduler){
    JsonObject details = entity->GetDetails();
    std::string type = details["type"];
    if (type.compare("charger") == 0){
      float dis = this->GetPosition().Distance(entity->GetPosition());
      if (dis < minDis){
        minDis = dis;
        closest_charger = entity;
      }
    }
  }
  return closest_charger;

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
  
  else if (drone->GetAvailability()) { //If Drone waiting for trip
    drone->GetNearestEntity(scheduler);
    if (!(drone->GetAvailability()){//if it found a trip...
      if (NeedsCharge()){
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

