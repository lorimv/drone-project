#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
using namespace std;

Drone::Drone() {
  position = {0, 0, 0};
  direction = {0, 0, 0};
  speed = 0;
  available = true;
}

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
//   tracker = tracker->getInstance();
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  if (graph) {
    delete graph;
  }
  if (nearestEntity) {
    delete nearestEntity;
  }
  if (toRobot) {
    delete toRobot;
  }
  if (toFinalDestination) {
    delete toFinalDestination;
  }
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  // cout << "1" << endl;
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    // cout << "2" << endl;
    if (entity->GetAvailability()) {
      // cout << "3" << endl;
      float disToEntity = this->position.Distance(entity->GetPosition());
      // cout << "4" << endl;

      if (disToEntity <= minDis) {
        // cout << "5" << endl;

        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
    // cout << "A" << endl;

  }

  if (nearestEntity) {
      // set availability to the nearest robot
    // cout << "6" << endl;
    
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    // cout << "7" << endl;

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    // cout << "8" << endl;
    toRobot = new BeelineStrategy(position, destination);

    // std::vector< std::vector<float> > graphNodes = 

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar"){
      // cout << "9" << endl;

      toFinalDestination =
        new JumpDecorator(new AstarStrategy(destination, finalDestination, graph));
    }
    else if (strat == "dfs"){
      toFinalDestination =
        new SpinDecorator(new JumpDecorator(new DfsStrategy(destination, finalDestination, graph)));
    }
    else if (strat == "dijkstra"){
      toFinalDestination =
        new JumpDecorator(new SpinDecorator(new DijkstraStrategy(destination, finalDestination, graph)));
    }
    else {
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
    }
  }
}


void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  BatteryTracker *tracker = BatteryTracker::getInstance();
  if (available) {
    cout << "calling getne" << endl;
    GetNearestEntity(scheduler);
  }
  if (toRobot) {
    cout << "2robot" << endl;
    toRobot->Move(this, dt);
    cout << "moved" << endl;
    this->distance += dt;

    tracker->updateDistance(this, this->distance);
    // cout << toRobot->IsCompleted() << endl;
    if (toRobot->IsCompleted()) {
      cout << "here under completed" << endl;
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
    // cout << "available: " << available << endl;
  }
  else if (toFinalDestination) {
    // cout << "3" << endl;
    // cout << (this->GetDetails())["type"] << endl;
    toFinalDestination->Move(this, dt);
    this->distance += dt;
    tracker->updateDistance(this, this->distance);

    if (nearestEntity && pickedUp) {
      // cout << "4" << endl;
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      tracker->updateTripCount(this);
      cout << "end of trip" << endl;
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;

    //   this->distance = 0.0;
    }
  }
}

void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}

Drone& Drone::operator=(const Drone& drone) {
  IEntity::operator=(drone);

  this->details = drone.details;
  this->position = drone.position;
  this->direction = drone.direction;
  this->color = drone.color;
  this->jumpHeight = drone.jumpHeight;
  this->goUp = drone.goUp;
  this->destination = drone.destination;
  this->speed = drone.speed;
  this->available = drone.available;
  this->pickedUp = drone.pickedUp;
  this->nearestEntity = nullptr;
  *(dynamic_cast<PathStrategy*>(this->toRobot)) = *(dynamic_cast<PathStrategy*>(drone.toRobot));
  *(dynamic_cast<PathStrategy*>(this->toFinalDestination)) = *(dynamic_cast<PathStrategy*>(drone.toFinalDestination));

  // this->graph = drone.graph;
  this->SetGraph(drone.graph);
  
  cout << "DEEP COPY!!!" << endl;

  return *this;
    
}


