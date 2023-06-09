//
// Created by Aiken Wong on 29/3/23.
//

#ifndef SPA_AFFECTSSTARCFGEVALUATOR_H
#define SPA_AFFECTSSTARCFGEVALUATOR_H

#include "AffectsRelatedCFGEvaluator.h"
class AffectsStarCFGEvaluator : public AffectsRelatedCFGEvaluator {
 public:
  AffectsStarCFGEvaluator(cfg::CFG *cfg, RelationshipStorage *relationshipStorage,
                          RelationshipCache *relationshipCache, EntityManager *entityManager);

  [[nodiscard]] auto getRelationshipType() const
      -> const RelationshipType& override;

  auto createNewRelationship(Entity* leftStatement, Entity* rightStatement)
      -> std::unique_ptr<Relationship> override;

  auto getRelatedStatements(Statement* sourceStatement, bool isReverse)
      -> std::unique_ptr<std::vector<Entity*>> override;

 protected:
  auto shouldSortForDoubleEnityTypeEvaluation() -> bool override;
};

#endif  // SPA_AFFECTSSTARCFGEVALUATOR_H
