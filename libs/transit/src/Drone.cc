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
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
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
  if (available) {
    cout << "1" << endl;
    GetNearestEntity(scheduler);
  }
  if (toRobot) {
    cout << "2" << endl;
    toRobot->Move(this, dt);
    cout << toRobot->IsCompleted() << endl;
    if (toRobot->IsCompleted()) {
      cout << "here under completed" << endl;
      delete toRobot;
      toRobot = nullptr;
      pickedUp = true;
    }
  }
    else if (toFinalDestination) {
    cout << "3" << endl;
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      cout << "4" << endl;
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      cout << "5" << endl;
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
    }
  }
  cout << "End of drone update" << endl;
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
  this->nearestEntity = drone.nearestEntity;
  this->toRobot = drone.toRobot;
  this->toFinalDestination = drone.toFinalDestination;

  // this->graph = drone.graph;
  this->SetGraph(drone.graph);
  this->id = drone.id;
  this->name = drone.name;

  return *this;
    
}
