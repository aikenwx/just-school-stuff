#include <string>
#include <utility>

#include "modifies_stmt_var_relationship.h"

namespace rel {
auto ModifiesStmtVarRelationship::CreateRelationship(
    std::shared_ptr<ast::StatementNode> statementNode,
    const std::string &variableName)
    -> std::unique_ptr<ModifiesStmtVarRelationship> {
  return std::unique_ptr<ModifiesStmtVarRelationship>(
      new ModifiesStmtVarRelationship(std::move(statementNode), variableName));
};
} // namespace rel
