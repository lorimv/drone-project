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
        static BatteryTracker* getInstance();
        // called for every update()
        // void getBatteryLevel(); 
        // write to a map with (IEntity, depletion)
        // only call
        void updateDepletion(IEntity* drone, int newBatteryLevel);

        // update Drone's total distance travelled to the value of newDistance
        void updateDistance(IEntity* drone, double newDistance);

        void updateTripCount(IEntity* drone, int newCount);
 
        void writeToCSV();

        void updateStationVisitCount(IEntity* drone, int newCount);
       

    private:
        BatteryTracker();
        static BatteryTracker* instance;
        map<IEntity*, double> distancesMap;
        map<IEntity*, int> batteryLevelsMap; // updated in BatteryDecorator
        map<IEntity*, int> numberOfTrips;
        map<IEntity*, int> rechargeStationVisits; // updated in BatteryDecorator

};

#endif // BATTERY_TRACKER_H 