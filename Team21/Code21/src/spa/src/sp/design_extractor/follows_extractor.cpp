#include "follows_extractor.h"

#include <vector>

#include "../ast/statement_list_node.h"
#include "../ast/statement_node.h"
#include "../rel/follows_stmt_stmt_relationship.h"
#include "../rel/relationship.h"

namespace design_extractor {
void FollowsExtractor::HandleStatementListNode(
    const std::shared_ptr<ast::StatementListNode>& node, int depth) {
  std::vector<std::shared_ptr<ast::StatementNode>> statements =
      node->GetStatements();
  if (statements.size() <= 1) {
    // no Follows relationship possible in this statement list
    return;
  };

  // nb: `StatementListNode` stores statements in reverse order
  auto it = statements.crbegin();
  std::shared_ptr<ast::StatementNode> first = *it;
  it++;

  for (; it != statements.crend(); it++) {
    const std::shared_ptr<ast::StatementNode>& second = *it;
    relns_.push_back(
        rel::FollowsStmtStmtRelationship::CreateRelationship(first, second));
    first = second;
  };
};

auto
FollowsExtractor::GetRelationships() const -> std::vector<std::shared_ptr<rel::FollowsStmtStmtRelationship>> {
  return relns_;
};
}  // namespace design_extractor
