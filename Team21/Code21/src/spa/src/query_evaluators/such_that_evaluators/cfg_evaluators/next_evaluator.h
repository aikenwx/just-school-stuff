#pragma once

#include "cfg_evaluator.h"

namespace qps {

class NextEvaluator : public Cfg_Evaluator {
 public:
  NextEvaluator(SuchThatClause clause, std::vector<Declaration> declarations) :
      Cfg_Evaluator(std::move(clause), std::move(declarations)) {}
      
  ClauseResult Evaluate(QueryFacade &pkb) override;

};

} // qps
