#include "not_node.h"

namespace ast {
NotNode::NotNode(std::shared_ptr<INode> operand) {
  this->operand = operand;
}

std::shared_ptr<INode> NotNode::GetOperand() {
  return operand;
}

std::string NotNode::ToString() const {
  return "not:\n{\n" + operand->ToString() + "}\n";
}
}
