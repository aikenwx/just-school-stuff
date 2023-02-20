#pragma once

#include <memory>
#include <vector>

#include "procedure_node.h"

namespace ast {
class ProgramNode : public INode {
public:
  void AddProcedure(std::shared_ptr<ProcedureNode> procedure);
  std::vector<std::shared_ptr<ProcedureNode>> GetProcedures();
  std::string ToString() const override;
  int GetTotalStatementCount();

private:
  std::vector<std::shared_ptr<ProcedureNode> > procedures;
};
}
