#ifndef DRONE_DECORATOR_H_
#define DRONE_DECORATOR_H_

#include "IEntity.h"
#include "Drone.h"

/**
 * @brief this class inhertis from the IEntity class and is represents
 * an abstract drone decorator template.
 */
class DroneDecorator : public IEntity {
 protected:
  IEntity* drone;

 public:
  /**
   * @brief Construct a new Drone Decorator object
   *
   * @param drone the drone to decorate onto
   */
  DroneDecorator(IEntity* drone);
  /**
   * @brief Drone Decorator Destructor
   */
  ~DroneDecorator();
   /**
    * @brief Gets the speed of the drone
    * @return The speed of the drone
    */
  float GetSpeed() const { return drone->GetSpeed(); }
  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return drone->GetPosition(); }
  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return drone->GetDirection(); }
  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return drone->GetDestination(); }
  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { return drone->GetColor(); }
  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return drone->GetDetails(); }
  /**
   * @brief Gets the availability of the drone
   * @return The availability of the drone
   */
  bool GetAvailability() const { return drone->GetAvailability(); }
  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { drone->SetPosition(pos_); }
  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { drone->SetDirection(dir_); }
  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { drone->SetDestination(des_); }
  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_) { drone->SetColor(col_); }
  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle) { drone->Rotate(angle); }
  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height) { drone->Jump(height); }
  /**
   * @brief Removing the copy constructor and assignment operator
   * so that drones cannot be copied.
   */
  DroneDecorator(const DroneDecorator& drone) = delete;
  DroneDecorator& operator=(const DroneDecorator& drone) = delete;
  /**
   * @brief update function to be overwritten, calls drone's update when needed
   * 
   * @param dt Delta Time
   * @param scheduler List of all entities in the system
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) = 0;

  void SetGraph(const IGraph* graph);
};

#endif
