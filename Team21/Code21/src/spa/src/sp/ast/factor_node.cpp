#include "factor_node.h"

namespace ast {
FactorNode::FactorNode(INode *operand) {
  this->operand = operand;
}

INode *FactorNode::GetOperand() {
  return operand;
}

std::ostream &FactorNode::Write(std::ostream &out) const {
  return out;
}
}
