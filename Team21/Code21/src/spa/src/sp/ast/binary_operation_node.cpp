#include "binary_operation_node.h"

#include <utility>

namespace ast {
BinaryOperationNode::BinaryOperationNode(std::shared_ptr<INode> left,
                                         std::shared_ptr<INode> right)
    : left_(std::move(left)), right_(std::move(right)) {}

auto BinaryOperationNode::GetLeft() const -> std::shared_ptr<INode> {
  return left_;
}

auto BinaryOperationNode::GetRight() const -> std::shared_ptr<INode> {
  return right_;
}

auto BinaryOperationNode::ToString() const -> std::string {
  return "{\nleft:" + left_->ToString() + "right:" + right_->ToString() + "}\n";
}

void BinaryOperationNode::AcceptVisitor(design_extractor::Extractor &extractor,
                                        int depth) {
  // nb: no HandleBinaryOperationNode() in Extractor
  // call HandleOtherNode() to let extractor update state
  // e.g. node parents
  extractor.HandleOtherNode(shared_from_this(), depth);

  left_->AcceptVisitor(extractor, depth + 1);
  right_->AcceptVisitor(extractor, depth + 1);
}
} // namespace ast
