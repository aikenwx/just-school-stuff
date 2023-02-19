#pragma once

#include <string>

#include "token.h"

namespace token {
class NotEqualToken : public Token {
 public:
  static const std::unique_ptr<Token> CreateToken(std::string);
  const TokenType GetType() override { return TokenType::NOT_EQUAL; }
  const std::string GetValue() override;

 private:
  NotEqualToken();
};
}  // namespace token
