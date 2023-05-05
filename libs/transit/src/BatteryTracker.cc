#include "BatteryTracker.h"
BatteryTracker* BatteryTracker::instance = NULL;

BatteryTracker::BatteryTracker(){
    // initialize vars
}

BatteryTracker* BatteryTracker::getInstance(){
  if (instance == NULL){
      instance = new BatteryTracker();
      return instance;
  }
  else {
      return instance;
  }
}

void BatteryTracker::updateDepletion(IEntity* drone, float batteryLevel){
  batteryLevelsMap[drone] = batteryLevel;
}

void BatteryTracker::updateDistance(IEntity* drone, double newDistance) {
  // cout << "Entered updateDistance" << endl;
  // Drone* new_drone = dynamic_cast<Drone*>(drone);
  // new_drone->setDistance(newDistance);
  //batteryLevelsMap.insert_or_assign(new_drone, newDistance);
  // std::cout << newDistance << std::endl;
  distancesMap[drone] = newDistance;
  // cout << "Left updateDistance" << endl;
  //std::cout << distancesMap[new_drone] << std::endl;
  
  //  batteryLevelsMap[drone] = newDistance;
}

void BatteryTracker::updateTripCount(IEntity* drone, int newCount) {
  numberOfTrips[drone] = newCount;
}

void BatteryTracker::updateStationVisitCount(IEntity* drone, int newCount) {
  rechargeStationVisits[drone] = newCount;
}

void BatteryTracker::writeToCSV(){
    cout << "calling writeToCSV" << endl;
    ofstream DataLogger;
    DataLogger.open("DataLog.csv");

    DataLogger << "Drone Name" << "," << "Distance" << "," << "Battery level" << "," << "Number of Trips" << "," << "Recharge Station Visits" << endl;
    for(auto it = distancesMap.begin(); it != distancesMap.end(); ++it) {
      // cout << "inside loop" << endl;
      std::string name = it->first->GetDetails()["name"];
      // cout << "name: " << name << endl;
      int distance = it->second;
      float batteryLevel = batteryLevelsMap[it->first];
      //DataLogger << name << "," << distance << "," << batteryLevel << endl; 
      DataLogger << name << "," << distance << "," << batteryLevel << "," << endl; 
      
      // batteryLevelMap["Drone1"]
      // DataLogger << "Drone1" << 
      // auto i = it->first;
      // ...
    }
}