#include "DroneDecorator.h"

DroneDecorator::DroneDecorator(IEntity* drone){
  this->drone = drone;
// this->drone = new Drone((drone->GetDetails()));
}

DroneDecorator::~DroneDecorator() {
  // Delete dynamically allocated variables
  delete drone;
}

void DroneDecorator::SetGraph(const IGraph* graph) {
    this->drone->SetGraph(graph);
}
