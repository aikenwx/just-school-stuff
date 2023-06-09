#pragma once

#include <iostream>

namespace qps {

// Expression represents an expression used in pattern clause
class Expression {
 private:
  bool isPartial;
  std::string expression;

 public:
  Expression(bool isPartial_, std::string expression_);
  [[nodiscard]] auto isExpressionPartial() const -> bool;
  [[nodiscard]] auto getExpression() const -> const std::string &;

  auto operator==(const Expression &expr) const -> bool {
    return isPartial == expr.isPartial && expression == expr.expression;
  }

  friend auto operator<<(std::ostream &ostream, Expression &expr)
  -> std::ostream & {
    ostream << expr.expression;
    return ostream;
  }
};

} // namespace qps
