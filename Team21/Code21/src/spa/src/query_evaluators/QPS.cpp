#include "QPS.h"

#include "query_preprocess/query_tokenizer.h"
#include "query_preprocess/query_parser.h"
#include "query_evaluator.h"
#include "query_validation/SemanticValidator.h"
#include "query_validation/SyntacticValidator.h"

namespace qps {
void QPS::evaluate(std::string &query_str, std::list<std::string> &results, QueryFacade &pkb) {
  try {
    QueryTokenizer tokenizer(query_str);
    QueryParser parser(tokenizer.tokenize());
    Query query(parser.parse());
    SemanticValidator validatorSemantic(query);
    SyntacticValidator validatorSyntactic(query);
    QueryEvaluator evaluator(query);

    validatorSyntactic.validateQuery();
    validatorSemantic.validateQuery();
    for (const auto &str : evaluator.EvaluateQuery(pkb)) {
      results.push_back(str);
    }
  } catch (qps::QueryException &e) {
    if (e.getType() == ErrorType::Syntactic) {
      results.emplace_back("SyntaxError");
    } else {
      results.emplace_back("SemanticError");
    }
    return;
  }
}
}  // namespace qps
