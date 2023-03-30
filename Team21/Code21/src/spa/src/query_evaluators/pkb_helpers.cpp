#include "pkb_helpers.h"

#include "PKBStorageClasses/EntityClasses/Statement.h"
#include "PKBStorageClasses/EntityClasses/ReadStatement.h"
#include "PKBStorageClasses/EntityClasses/PrintStatement.h"
#include "PKBStorageClasses/EntityClasses/CallStatement.h"
#include "PKBStorageClasses/EntityClasses/WhileStatement.h"
#include "PKBStorageClasses/EntityClasses/IfStatement.h"
#include "PKBStorageClasses/EntityClasses/AssignStatement.h"
#include "PKBStorageClasses/EntityClasses/Variable.h"
#include "PKBStorageClasses/EntityClasses/Constant.h"
#include "PKBStorageClasses/EntityClasses/Procedure.h"
#include "PKBStorageClasses/RelationshipClasses/ParentRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/ParentStarRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/FollowsRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/FollowsStarRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/UsesRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/ModifiesRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/CallsRelationship.h"
#include "PKBStorageClasses/RelationshipClasses/CallsStarRelationship.h"

namespace qps {

auto DesignEntityToEntityType(DesignEntity entity) -> EntityType {
  switch (entity) {
    case DesignEntity::STMT:return Statement::getEntityTypeStatic();
    case DesignEntity::READ:return ReadStatement::getEntityTypeStatic();
    case DesignEntity::PRINT:return PrintStatement::getEntityTypeStatic();
    case DesignEntity::CALL:return CallStatement::getEntityTypeStatic();
    case DesignEntity::WHILE:return WhileStatement::getEntityTypeStatic();
    case DesignEntity::IF:return IfStatement::getEntityTypeStatic();
    case DesignEntity::ASSIGN:return AssignStatement::getEntityTypeStatic();
    case DesignEntity::VARIABLE:return Variable::getEntityTypeStatic();
    case DesignEntity::CONSTANT:return Constant::getEntityTypeStatic();
    case DesignEntity::PROCEDURE:return Procedure::getEntityTypeStatic();
  }
}

auto RelationshipToRelationshipType(Relationship relationship) -> RelationshipType {
  switch (relationship) {
    case Relationship::Parent: return ParentRelationship::getRelationshipTypeStatic();
    case Relationship::ParentT: return ParentStarRelationship::getRelationshipTypeStatic();
    case Relationship::Follows: return FollowsRelationship::getRelationshipTypeStatic();
    case Relationship::FollowsT: return FollowsStarRelationship::getRelationshipTypeStatic();
    case Relationship::Uses:
    case Relationship::UsesS:
    case Relationship::UsesP: return UsesRelationship::getRelationshipTypeStatic();
    case Relationship::Modifies:
    case Relationship::ModifiesS:
    case Relationship::ModifiesP: return ModifiesRelationship::getRelationshipTypeStatic();
    case Relationship::Calls: return CallsRelationship::getRelationshipTypeStatic();
    case Relationship::CallsT: return CallsStarRelationship::getRelationshipTypeStatic();
    case Relationship::Next:;
    case Relationship::NextT:;
    case Relationship::Affects:;
    case Relationship::AffectsT:throw std::invalid_argument("Not supported yet");
  }
}

auto ExtractEntities(const std::vector<::Relationship *> &relationships) -> std::vector<std::vector<Entity *>> {
  std::vector<std::vector<Entity *>> entities;
  entities.reserve(relationships.size());
  for (const auto &entity : relationships) {
    entities.push_back({entity->getLeftHandEntity(), entity->getRightHandEntity()});
  }
  return entities;
}
}  // namespace qps
