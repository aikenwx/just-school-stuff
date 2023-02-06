#pragma once
#include <vector>
#include "i_node.h"

namespace ast {
class ProgramNode : public INode {
public:
  void AddProcedure(INode *procedure);
  std::vector<INode *> *GetProcedures();

private:
  std::vector<INode *> procedures;
};
}
