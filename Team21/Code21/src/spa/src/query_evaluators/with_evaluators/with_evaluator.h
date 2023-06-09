#pragma once

#include "query/declaration.h"
#include "query/with_clause.h"
#include "query_evaluators/clause_evaluator.h"
#include "query_evaluators/select_evaluators/attr_ref_eval.h"
#include "PKBStorageClasses/EntityClasses/Entity.h"
#include "PKBStorageClasses/RelationshipClasses/Relationship.h"

namespace qps {

class WithEvaluator : public ClauseEvaluator {
 public:
  WithEvaluator(const WithClause &clause, const std::vector<Declaration> &declarations);

  auto getClause() -> const WithClause &;

  auto getDeclarations() -> const std::vector<Declaration> &;

  auto Evaluate(QueryFacade &pkb) -> ClauseResult override;

  virtual auto CallPkb(QueryFacade &pkb) -> std::vector<std::vector<Entity *>> = 0;

 private:
  const WithClause &clause_;

  //nullPtr means false result while empty vector means true result
  auto ConstructResult(const std::vector<std::vector<Entity *>> &) -> ClauseResult;

  const std::vector<Declaration> &declarations_;

};

}  // namespace qps
