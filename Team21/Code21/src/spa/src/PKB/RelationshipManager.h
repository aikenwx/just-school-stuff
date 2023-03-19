//
// Created by Aiken Wong on 4/2/23.
//

#ifndef SPA_RELATIONSHIPMANAGER_H
#define SPA_RELATIONSHIPMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../PKBStorageClasses/EntityClasses/Entity.h"
#include "PKBStorageClasses/RelationshipClasses/Relationship.h"

struct RelationshipDoubleSynonymKey : public StorageKey {
   private:
    const RelationshipType *relationshipType;
    const EntityType *leftHandEntityType;
    const EntityType *rightHandEntityType;

   public:
    RelationshipDoubleSynonymKey(const RelationshipType *relationshipType, const EntityType *leftHandEntityType, const EntityType *rightHandEntityType);
    auto operator==(
        const RelationshipDoubleSynonymKey &otherRelationshipSynonymKey) const
        -> bool;
};

template <>
struct std::hash<RelationshipDoubleSynonymKey> {
  auto operator()(const RelationshipDoubleSynonymKey &relationshipSynonymKey)
      const -> std::size_t;
};

struct RelationshipSynonymLiteralKey : public StorageKey {
   private:
    const RelationshipType *relationshipType;
    const EntityType *leftHandEntityType;
    EntityKey *rightHandEntityKey;

   public:
    RelationshipSynonymLiteralKey(const RelationshipType *relationshipType, const EntityType *entityType, EntityKey *entityKey);
    auto operator==(const RelationshipSynonymLiteralKey
                        &otherRelationshipLiteralSynonymKey) const -> bool;
};

template <>
struct std::hash<RelationshipSynonymLiteralKey> {
  auto operator()(
      const RelationshipSynonymLiteralKey &relationshipLiteralSynonymKey) const
      -> std::size_t;
};

struct RelationshipLiteralSynonymKey : public StorageKey {
   private:
    const RelationshipType *relationshipType;
    EntityKey *leftHandEntityKey;
    const EntityType *rightHandEntityType;

   public:
    RelationshipLiteralSynonymKey(const RelationshipType *relationshipType, EntityKey *entityKey, const EntityType *entityType);
    auto operator==(const RelationshipLiteralSynonymKey
                        &otherRelationshipLiteralSynonymKey) const -> bool;
};

template <>
struct std::hash<RelationshipLiteralSynonymKey> {
  auto operator()(
      const RelationshipLiteralSynonymKey &relationshipLiteralSynonymKey) const
      -> std::size_t;
};

class RelationshipManager {
   private:
    std::unordered_map<RelationshipDoubleSynonymKey, std::shared_ptr<std::vector<Relationship *>>> relationshipDoubleSynonymStore;

    std::unordered_map<RelationshipSynonymLiteralKey, std::shared_ptr<std::vector<Entity *>>> relationshipSynonymLiteralStore;

    std::unordered_map<RelationshipSynonymLiteralKey, std::shared_ptr<std::vector<Entity *>>> relationshipSynonymLiteralVectorStore;

    std::unordered_map<RelationshipLiteralSynonymKey, std::shared_ptr<std::vector<Entity *>>> relationshipLiteralSynonymStore;

    std::unordered_map<RelationshipKey, std::shared_ptr<Relationship>> relationshipStore;

   public:
    RelationshipManager();

    void storeRelationship(const std::shared_ptr<Relationship>& relationship);

    auto getRelationship(RelationshipKey &key) -> Relationship *;

    auto getRelationshipsByTypes(const RelationshipType &relationshipType,
                                 const EntityType &leftHandEntityType,
                                 const EntityType &rightHandEntityType)
        -> std::vector<Relationship *> *;

    auto getEntitiesForGivenRelationshipTypeAndLeftHandEntityType(
        RelationshipType &relationshipType, const EntityType &leftHandEntityType,
        EntityKey &rightHandEntityKey) -> std::vector<Entity *> *;
    auto getEntitiesForGivenRelationshipTypeAndRightHandEntityType(
        RelationshipType &relationshipType, EntityKey &leftHandEntityKey,
        const EntityType &rightHandEntityType) -> std::vector<Entity *> *;

   private:
    void storeInRelationshipDoubleSynonymStore(Relationship *relationship);

    void storeInRelationshipSynonymLiteralStore(Relationship *relationship);

    void storeInRelationshipLiteralSynonymStore(Relationship *relationship);

    void initialiseVectorForRelationshipDoubleSynonymStoreIfNotExist(RelationshipDoubleSynonymKey relationshipSynonymKey);

    void initialiseVectorForRelationshipLiteralSynonymStoreIfNotExist(RelationshipLiteralSynonymKey relationshipLiteralSynonymKey);

    void initialiseVectorForRelationshipSynonymLiteralStoreIfNotExist(RelationshipSynonymLiteralKey relationshipSynonymLiteralKey);
};

#endif  // SPA_RELATIONSHIPMANAGER_H
