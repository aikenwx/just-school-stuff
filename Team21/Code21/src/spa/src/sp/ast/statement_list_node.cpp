#include "statement_list_node.h"

namespace ast {
void StatementListNode::AddStatement(INode *node) {
  statements.push_back(node);
}
}
