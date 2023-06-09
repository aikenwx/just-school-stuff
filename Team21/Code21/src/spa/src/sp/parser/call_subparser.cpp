#include "sp/ast/astlib.h"
#include "call_subparser.h"
#include "util/instance_of.h"
#include "util/is_identifier_node_value.h"

namespace parser {
auto CallSubparser::Parse(std::shared_ptr<Context> context) -> bool {
  auto stack = context->GetStack();
  auto iter = stack->rbegin();
  if (context->IsLookaheadSymbolValue(";")) {
    // call: 'call' iden ';'
    if (stack->size() >= 2
      && util::instance_of<ast::IdentifierNode>(*iter)
      && IsIdentifierNodeValue(*std::next(iter, 1), "call")) {
      // References name node for procedure name
      std::shared_ptr<ast::IdentifierNode> nam =
          std::static_pointer_cast<ast::IdentifierNode>(stack->back());
      // Pops name node
      stack->pop_back();
      // Pops 'call' identifier node
      stack->pop_back();
      // Creates call node
      std::shared_ptr<ast::CallNode> sta =
          std::make_shared<ast::CallNode>(nam);
      context->GetStatementCounter()++;
      // Pushes call node to parse stack
      stack->push_back(sta);
      return true;
    }
  }
  return Subparser::Parse(context);
}
}  // namespace parser
