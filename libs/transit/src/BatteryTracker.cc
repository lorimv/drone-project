#include "BatteryTracker.h"
BatteryTracker* BatteryTracker::instance = NULL;

BatteryTracker::BatteryTracker() {
}

BatteryTracker* BatteryTracker::getInstance() {
  if (instance == NULL) {
      instance = new BatteryTracker();
      return instance;
  } else {
      return instance;
  }
}

void BatteryTracker::updateDepletion(IEntity* drone, float batteryLevel) {
  batteryLevelsMap[drone] = batteryLevel;
}

void BatteryTracker::updateDistance(IEntity* drone, double newDistance) {
  distancesMap[drone] = newDistance;
}

void BatteryTracker::updateTripCount(IEntity* drone) {
  numberOfTrips[drone] = (numberOfTrips[drone] + 1);
}

void BatteryTracker::updateStationVisitCount(IEntity* drone) {
  rechargeStationVisits[drone] = (rechargeStationVisits[drone] + 1);
}
void BatteryTracker::writeToCSV() {
    cout << "calling writeToCSV" << endl;
    ofstream DataLogger;
    DataLogger.open("DataLog.csv");
    DataLogger << "Drone Name" << "," << "Distance" << ","
    << "Battery level" << "," << "Number of Trips"
    << "," << "Recharge Station Visits" << endl;
    for (auto it = distancesMap.begin(); it != distancesMap.end(); ++it) {
      std::string name = it->first->GetDetails()["name"];
      int distance = it->second;
      float batteryLevel = batteryLevelsMap[it->first];
      int tripCount = numberOfTrips[it->first];
      DataLogger << name << "," << distance << "," <<
      batteryLevel << "," << tripCount << "," << endl;
    }
}
