//
// Created by Aiken Wong on 3/2/23.
//

#include "Entity.h"
#include <stdexcept>


EntityType::EntityType() : StorageKey(EntityType::entityTypeKeyCounter++){}

// NOLINTNEXTLINE (cppcoreguidelines-avoid-non-const-global-variables)
std::size_t EntityType::entityTypeKeyCounter = 0;

auto std::hash<EntityType>::operator()(const EntityType &entityType) const
    -> std::size_t {
  return entityType.getKey();
}

EntityKey::EntityKey(const EntityType *entityType, std::string *entityValue)
    : StorageKey(entityType->getKey() ^ std::hash<std::string>()(*entityValue)),
      entityType(entityType),
      entityValue(entityValue), entityIntValue(-1) {}

EntityKey::EntityKey(const EntityType *entityType, int entityIntValue)
    : StorageKey(entityType->getKey() ^
                 std::hash<std::string>()(std::to_string(entityIntValue))),
      entityType(entityType), entityIntValue(entityIntValue) {

  this->entityValueStore = std::to_string(entityIntValue);
  this->entityValue = &entityValueStore;
}

auto EntityKey::getOptionalInt() -> int* {
    if (entityIntValue == -1) {
        try {
            entityIntValue = std::stoi(entityValueStore);
        } catch (std::invalid_argument) {
            entityIntValue = 0;
            return nullptr;
        }
    } else if (entityIntValue == 0) {
        // already evaluated
        return nullptr;
    }

    return &entityIntValue;
}


auto EntityKey::operator==(const EntityKey &entityKey) const -> bool {
  return *this->entityType == *entityKey.entityType &&
         *this->entityValue == *entityKey.entityValue;
}

auto std::hash<EntityKey>::operator()(const EntityKey &entityKey) const
    -> std::size_t {
  return entityKey.getKey();
}

auto Entity::getEntityValue() const -> std::string * {
  return this->entityValue.get();
}

Entity::Entity(const EntityType *entityType,
               const std::shared_ptr<std::string> &entityValue)
    : entityKey(EntityKey(entityType, entityValue.get())) {
  this->entityValue = std::shared_ptr<std::string>(entityValue);
}

Entity::Entity(const EntityType *entityType,
               const std::shared_ptr<std::string> &entityValue, int entityIntValue)
        : entityKey(EntityKey(entityType, entityIntValue)) {
    this->entityValue = std::shared_ptr<std::string>(entityValue);
}

auto Entity::getEntityKey() -> EntityKey & { return this->entityKey; }

auto Entity::equals(Entity *otherEntity) -> bool {
  return this->entityKey == otherEntity->entityKey;
}

auto EntityType::operator==(const EntityType &entityType) const -> bool {
  return this->getKey() == entityType.getKey();
}
