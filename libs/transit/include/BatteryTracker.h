#ifndef BATTERY_TRACKER_H
#define BATTERY_TRACKER_H
#include <map>
#include "IEntity.h"
#include "Drone.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class BatteryTracker {
 public:
    /**
    * @brief Get the instance of the Singleton BatteryTracker class
    */
        static BatteryTracker* getInstance();
        /**
        * @brief Will update DepletionMap to store current batteryLevel of a drone
        * @param drone The particular drone that will have its BatteryLevel updated
        * @param newBatteryLevel new Battery Level of drone
        */
        void updateDepletion(IEntity* drone, float newBatteryLevel);

        /** 
        * @brief update Drone's total distance travelled to the value of newDistance
        * @param drone The particular drone that will have its distance updated
        * @param newDistance new total distance of Drone
        */
        void updateDistance(IEntity* drone, double newDistance);
        /**
        * @brief Will increment tripCount for a particular drone
        * @param drone The particular drone that will have its BatteryLevel updated
        */
        void updateTripCount(IEntity* drone);
        /**
        * @brief Will write the contents of the Maps to a CSV file
        */
        void writeToCSV();

        /**
        * @brief Will increment the number of visits to a RechargeStation for a drone
        * @param drone The drone to have its count incremented
        */
        void updateStationVisitCount(IEntity* drone);

 private:
        BatteryTracker();
        static BatteryTracker* instance;
        map<IEntity*, double> distancesMap;
        map<IEntity*, float> batteryLevelsMap;
        map<IEntity*, int> numberOfTrips;
        map<IEntity*, int> rechargeStationVisits;
};

#endif  // BATTERY_TRACKER_H
