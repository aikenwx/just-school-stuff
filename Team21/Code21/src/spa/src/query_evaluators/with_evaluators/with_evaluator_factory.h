#pragma once

#include "memory"

#include "query/with_clause.h"
#include "with_evaluator.h"

namespace qps {

class WithEvaluatorFactory {
 public:
  static auto Create(const WithClause &clause, const std::vector<Declaration> &decl_lst) -> std::unique_ptr<
      WithEvaluator>;
};

} // namespace qps
