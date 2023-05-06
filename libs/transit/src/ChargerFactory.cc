#include "ChargerFactory.h"

IEntity* ChargerFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("charger") == 0) {
    std::cout << "Charger Created" << std::endl;
    return new Charger(entity);
  }
  return nullptr;
}
