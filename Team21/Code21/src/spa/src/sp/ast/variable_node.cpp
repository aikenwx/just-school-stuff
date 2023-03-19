#include "variable_node.h"

namespace ast {
auto VariableNode::ToString() const -> std::string {
  return "variable:" + NamedNode::ToString();
}

void VariableNode::AcceptVisitor(design_extractor::Extractor &extractor,
                                 int depth) {
  extractor.HandleVariableNode(
      std::static_pointer_cast<VariableNode>(shared_from_this()), depth);
}
} // namespace ast
