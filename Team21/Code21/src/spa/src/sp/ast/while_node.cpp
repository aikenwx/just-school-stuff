#include "while_node.h"

namespace ast {
WhileNode::WhileNode(INode *condition, StatementListNode *body) {
  this->condition = condition;
  this->body = body;
}

INode *WhileNode::GetCondition() {
  return condition;
}

StatementListNode *WhileNode::GetBody() {
  return body;
}

std::string WhileNode::ToString() const {
  return "while:\n{\ncondition:" + condition->ToString() + "body:" + body->ToString() + "}\n";
}
}
