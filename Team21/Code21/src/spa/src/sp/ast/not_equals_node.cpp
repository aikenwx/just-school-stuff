#include "not_equals_node.h"

namespace ast {
auto NotEqualsNode::ToString() const -> std::string {
  return "not_equals:\n{\nleft:" + left->ToString() + "right:" + right->ToString() + "}\n";
}
}
