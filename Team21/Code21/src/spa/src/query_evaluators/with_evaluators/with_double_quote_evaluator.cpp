#include "with_double_quote_evaluator.h"
#include "PKBStorageClasses/EntityClasses/Entity.h"
#include "query/quoted_identifier.h"
#include <vector>

namespace qps {
auto WithDoubleQuoteEvaluator::CallPkb(QueryFacade &pkb) -> std::vector<std::vector<Entity *>> {
  std::vector<std::vector<Entity *>> equalResult = {};
  std::vector<Entity *> trueResult = {};
  const auto &ref1 = getClause().getRef1();
  const auto &ref2 = getClause().getRef2();
  const auto &ref1Quote = std::get<QuotedIdentifier>(ref1.ref);
  const auto &ref2Quote = std::get<QuotedIdentifier>(ref2.ref);

  if (ref1Quote.getQuotedId() == ref2Quote.getQuotedId()) {
    equalResult.push_back(trueResult);
    return equalResult;
  }
  return equalResult;
}
}  // namespace qps
