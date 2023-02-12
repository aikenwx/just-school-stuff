//
// Created by Aiken Wong on 3/2/23.
//

#ifndef SPA_PARENTRELATIONSHIP_H
#define SPA_PARENTRELATIONSHIP_H

#include <memory>

#include "../EntityClasses/Statement.h"
#include "Relationship.h"

class ParentStarRelationship : public Relationship {
   private:
    Statement* parentStatement;
    Statement* childStatement;

   public:
    ParentStarRelationship(Statement *parentStatement, Statement *childStatement);
    bool containsEntityOnLeftHand(Entity *entity) override;
    bool containsEntityOnRightHand(Entity *entity) override;

    RelationshipType getRelationshipType() override;

    Entity *getLeftHandEntity() override;

    Entity *getRightHandEntity() override;
};

#endif  // SPA_PARENTRELATIONSHIP_H
