#pragma once
#include "binary_operation_node.h"

namespace ast {
class LesserEqualsNode : public BinaryOperationNode {
public:
  using BinaryOperationNode::BinaryOperationNode;

  virtual std::string ToString() const override;
};
}