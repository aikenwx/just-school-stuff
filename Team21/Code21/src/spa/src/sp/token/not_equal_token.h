#pragma once

#include <string>

#include "token.h"

namespace token {
class NotEqualToken : public Token {
 public:
  static auto CreateToken(std::string_view) -> std::unique_ptr<Token>;
  [[nodiscard]] auto GetType() const -> TokenType override { return TokenType::NOT_EQUAL; }
  [[nodiscard]] auto GetValue() const -> std::string override;

 private:
  NotEqualToken() = default;
};
}  // namespace token
