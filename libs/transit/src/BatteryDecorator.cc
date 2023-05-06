#include "BatteryDecorator.h"
#include "BeelineStrategy.h"
#include "BatteryDecorator.h"
using namespace std;

BatteryDecorator::~BatteryDecorator() {
  delete drone;
  delete toCharger;
  delete toOrigin;
}

bool BatteryDecorator::NeedsCharge(double dt, std::vector<IEntity*> scheduler) {
  *(dynamic_cast<Drone*>(simDrone)) = *(dynamic_cast<Drone*>(drone));
  float simCharge = charge;
  while (!(simDrone->GetAvailability())) {
    simDrone->Update(dt, scheduler);
    simCharge -= (dt * .1);
    if (simCharge <= 0) {
      return true;
    }
  }
  IStrategy* BeeLine = new BeelineStrategy(simDrone->GetPosition(),
        GetNearestCharger(simDrone, scheduler)->GetPosition());
  while (!BeeLine->IsCompleted()) {
    BeeLine->Move(simDrone, dt);
    simCharge -= (dt * 0.1);
    if (simCharge <= 0) {
      return true;
    }
  }
  return false;
}

IEntity* BatteryDecorator::GetNearestCharger(IEntity* d,
 std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  IEntity* closest_charger;
  for (auto entity : scheduler) {
    JsonObject details = entity->GetDetails();
    std::string type = details["type"];
    if (type.compare("charger") == 0) {
      float dis = d->GetPosition().Distance(entity->GetPosition());
      if (dis < minDis) {
        minDis = dis;
        closest_charger = entity;
      }
    }
  }
  return closest_charger;
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler) {
  BatteryTracker *tracker = BatteryTracker::getInstance();
  if (charging) {
    charge += (dt * 5);
    if (charge >= 100) {
      charge = 100;
      charging = false;
    }
    return;
  } else if (drone->GetAvailability()) {
    drone->GetNearestEntity(scheduler);
    if (!(drone->GetAvailability())) {
      if (charge < 20) {
        toCharger = new BeelineStrategy(drone->GetPosition(),
        GetNearestCharger(drone, scheduler)->GetPosition());
        toOrigin = new BeelineStrategy(GetNearestCharger(
          drone, scheduler)->GetPosition(),
            drone->GetPosition());
      }
      return;
    }
  } else if (toCharger) {
    if (toCharger->IsCompleted()) {
      tracker->updateStationVisitCount(drone);
      delete toCharger;
      toCharger = nullptr;
      charging = true;
      return;
    } else {
      toCharger->Move(drone, dt);
      return;
    }
  } else if (toOrigin) {
    if (toOrigin->IsCompleted()) {
      delete toOrigin;
      toOrigin = nullptr;
      return;
    } else {
      toOrigin->Move(drone, dt);
      return;
    }
  } else {
    drone->Update(dt, scheduler);
    charge -= (dt * 0.8);
    tracker->updateDepletion(drone, charge);
  }
}

