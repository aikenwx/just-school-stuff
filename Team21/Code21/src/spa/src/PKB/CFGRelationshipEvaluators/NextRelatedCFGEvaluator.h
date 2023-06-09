//
// Created by Aiken Wong on 6/4/23.
//

#ifndef SPA_NEXTRELATEDCFGEVALUATOR_H
#define SPA_NEXTRELATEDCFGEVALUATOR_H

#include "CFGRelationshipEvaluator.h"

class NextRelatedCFGEvaluator : public CFGRelationshipEvaluator {
 public:
  NextRelatedCFGEvaluator(cfg::CFG *cfg, RelationshipStorage *relationshipStorage,
                          RelationshipCache *relationshipCache,
                          EntityManager *entityManager);

 protected:
  auto shouldEvaluateRelationshipsByEntityTypesInReverse(
      std::vector<Entity *> *leftEntityVector,
      std::vector<Entity *> *rightEntityVector) -> bool override;
};

#endif  // SPA_NEXTRELATEDCFGEVALUATOR_H
