#pragma once
#include "i_node.h"

namespace ast {
class BinaryOperationNode : public INode {
public:
  BinaryOperationNode(INode *left, INode *right);

  INode *GetLeft();
  INode *GetRight();
  std::ostream &Write(std::ostream &out) const override;

private:
  INode *left;
  INode *right;
};
}