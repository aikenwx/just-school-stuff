#pragma once

#include <memory>

#include "expression_node.h"
#include "statement_node.h"
#include "variable_node.h"

namespace ast {
class AssignNode : public StatementNode {
public:
  AssignNode(std::shared_ptr<VariableNode> var, std::shared_ptr<ExpressionNode> exp);

  std::shared_ptr<VariableNode> GetVariable();
  std::shared_ptr<INode> GetAssignment();
  std::string ToString() const override;

private:
  std::shared_ptr<VariableNode> var;
  std::shared_ptr<INode> assignment;
};
}