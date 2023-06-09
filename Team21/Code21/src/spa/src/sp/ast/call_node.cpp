#include "call_node.h"

#include "exceptions/parser_error.h"

namespace ast {
CallNode::CallNode(const std::shared_ptr<IdentifierNode> &name) : name_(name->GetValue()) {}

auto CallNode::GetProcedureName() -> std::string { return name_; }

auto CallNode::GetProcedure() -> std::shared_ptr<ProcedureNode> {
  std::shared_ptr<ProcedureNode> procedure = this->procedure_.lock();
  return procedure;
}

void CallNode::SetProcedure(const std::shared_ptr<ProcedureNode> &procedure) {
  this->procedure_ = std::weak_ptr<ProcedureNode>(procedure);
}

auto CallNode::ToString() const -> std::string {
  return "call:\n{\n" + name_ + "}\n";
}

void CallNode::AcceptVisitor(design_extractor::Extractor &extractor,
                             int depth) {
  auto currentNode = shared_from_this();
  extractor.HandleStatementNode(
      std::static_pointer_cast<StatementNode>(currentNode), depth);
  extractor.HandleCallNode(std::static_pointer_cast<CallNode>(currentNode),
                           depth);
}
} // namespace ast
