#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "BatteryDecorator.h"


BatteryDecorator::~BatteryDecorator() {
  delete drone;
  delete toCharger;
}

bool BatteryDecorator::NeedsCharge(double dt, std::vector<IEntity*> scheduler) {
  IEntity* simDrone = new Drone;
  simDrone = drone;
  int simCharge = charge;
  
  while (!(simDrone->GetAvailability())) {
    simDrone->Update(dt, scheduler);
    simCharge -= (dt * .001);      // TODO edit battery decrease based on tests
    if (simCharge <= 0) {
      return true;
    }
  }
  IStrategy* BeeLine = new BeelineStrategy(simDrone->GetPosition(), 
                                                 GetNearestCharger(simDrone, scheduler)->GetPosition());
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

IEntity* BatteryDecorator::GetNearestCharger(IEntity* d, std::vector<IEntity*> scheduler){
  float minDis = std::numeric_limits<float>::max();
  IEntity* closest_charger;
  for (auto entity: scheduler){
    JsonObject details = entity->GetDetails();
    std::string type = details["type"];
    if (type.compare("charger") == 0){
      float dis = d->GetPosition().Distance(entity->GetPosition());
      if (dis < minDis){
        minDis = dis;
        closest_charger = entity;
      }
    }
  }
  return closest_charger;

}



void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
//here
//  bool needCharge;
  
  if (charging) { //if at a charger
    charge += (dt* .1);
    if (charge >= 100) {
      charge = 100;      
      charging = false;
    }
    return;
  }
  
  else if (drone->GetAvailability()) { //If Drone waiting for trip
    drone->GetNearestEntity(scheduler);
    if (!(drone->GetAvailability())){//if it found a trip...
      if (NeedsCharge(dt, scheduler)){
        toCharger = new BeelineStrategy(drone->GetPosition(), 
                                        GetNearestCharger(drone, scheduler)->GetPosition());
      }  
      return;
    }
  }
  
  if (toCharger) {
    if (toCharger->IsCompleted()) {
      delete toCharger;
      toCharger = nullptr;
      charging = true;
      return;
    } else {
      toCharger->Move(drone, dt);
      return;
    }
  }
  
  else {
    drone->Update(dt, scheduler);
    // BatteryTracker *tracker;
    // tracker = tracker->GetInstance();
    // tracker->updateDepletion(drone, charge);
  }
  
  
  
  
  //else if drone->toRobot
  //Calculate charge needed to get there
  //If charge < requiredCharge...
  //route to a Charger (they're kept track of in scheduler)
  //else...
  //drone->Move(dt, scheduler)
  //but also reduce charge, too
}

