#pragma once

#include "query/with_clause.h"
#include "with_evaluator.h"
#include "PKB/QueryFacade.h"

namespace qps {

  class WithQuoteAttrEvaluator : public WithEvaluator {
  public:
    WithQuoteAttrEvaluator(WithClause clause, std::vector<Declaration> declarations)
      : WithEvaluator(std::move(clause), std::move(declarations)) {}
    auto CallPkb(QueryFacade& pkb) -> std::vector<std::vector<Entity *>*> override;
  };

} // namespace qps
