#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "BatteryDecorator.h"
using namespace std;

BatteryDecorator::~BatteryDecorator() {
  delete drone;
  delete toCharger;
}

bool BatteryDecorator::NeedsCharge(double dt, std::vector<IEntity*> scheduler) {
  // cout << "needscharge" << endl;
  IEntity* simDrone = new Drone();
  *(dynamic_cast<Drone*>(simDrone)) = *(dynamic_cast<Drone*>(drone));
  float simCharge = charge;
  
  cout << "Drone availability pre-sim: " << drone->GetAvailability() << endl;
//  simDrone->GetNearestEntity(scheduler);
  while (!(simDrone->GetAvailability())) {
//    cout << simCharge << " here" << endl;
    simDrone->Update(dt, scheduler);
    simCharge -= (dt * .1);      // TODO edit battery decrease based on tests
    if (simCharge <= 0) {
      delete simDrone;
      cout << "SD DELETED" << endl;
      return true;
    }
  }
  cout << "Drone availability pre-toCHarger: " << drone->GetAvailability() << endl;
  IStrategy* BeeLine = new BeelineStrategy(simDrone->GetPosition(), 
                                                 GetNearestCharger(simDrone, scheduler)->GetPosition());
  // simDrone to charger incomplete
  while (!BeeLine->IsCompleted()){
    BeeLine->Move(simDrone, dt);
    simCharge -= (dt * 0.1);
//    cout << simCharge << " here" << endl;
    if (simCharge <= 0) {
      delete simDrone;
      cout << "SD DELETED" << endl;
      return true;
    }
  }
  cout << "Drone availability post-charger: " << drone->GetAvailability() << endl;
  delete simDrone;
  cout << "SD DELETED" << endl;
  return false;
}

IEntity* BatteryDecorator::GetNearestCharger(IEntity* d, std::vector<IEntity*> scheduler){
  cout << "getnearestcharger" << endl;
  float minDis = std::numeric_limits<float>::max();
  cout << "11" << endl;
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
  cout << "22" << endl;
  return closest_charger;

}



void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
  BatteryTracker *tracker = BatteryTracker::getInstance();
  //cout << "decupdate" << endl;
  if (charging) { //if at a charger
    cout << "Now charging" << endl;
    charge += (dt * 5);
    cout << "CHarge : " << charge << endl; 
    if (charge >= 100) {
      charge = 100;      
      charging = false;
    }
    return;
  }
  
  else if (drone->GetAvailability()) { //If Drone waiting for trip
//    cout << "drone is Available" << endl;
    // cout << "2" << endl;
    // cout << (drone->GetDetails())["type"] << endl;
    drone->GetNearestEntity(scheduler);
    // cout << 
    // cout << "2a" << endl;
    if (!(drone->GetAvailability())){//if it found a trip...
      if (NeedsCharge(dt, scheduler)){
       
        toCharger = new BeelineStrategy(drone->GetPosition(), 
                                        GetNearestCharger(drone, scheduler)->GetPosition());
        cout << "we need charge:" << endl;
      }  
      cout << "Under needs charge()" << endl;
      return;
    }
//    cout << "drone still available" << endl;
    // drone->Update(dt, scheduler);
  }
  
  else if (toCharger) {
//    cout << "To charger" << endl;
    // cout << "3" << endl;
    if (toCharger->IsCompleted()) {
      cout << "Tocharger completed" << endl;
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
     cout << "drone update" << endl;
    // cout << "4" << endl;
    if(charge > 0) {
       cout << "charge before update: " << charge << endl;
    }
    drone->Update(dt, scheduler);
//    Drone* new_drone = dynamic_cast<Drone*>(drone);
    // cout << "distance: " << new_drone->getDistance() << endl;
    // cout << "dt: " << dt  << endl;
    // cout << "after divide: " << (new_drone->getDistance() / dt) << endl;
    // cout << "new charge: " << charge - ((new_drone->getDistance() / dt) * 0.00000001) << endl;
    charge -= (dt * 0.1);
    // cout << "4a" << endl;
    //BatteryTracker *tracker;
    //tracker = tracker->getInstance();
    cout << "charge after update: " << charge << endl;
    tracker->updateDepletion(drone, charge);
  }

  
  
  
  
  //else if drone->toRobot
  //Calculate charge needed to get there
  //If charge < requiredCharge...
  //route to a Charger (they're kept track of in scheduler)
  //else...
  //drone->Move(dt, scheduler)
  //but also reduce charge, too
}

