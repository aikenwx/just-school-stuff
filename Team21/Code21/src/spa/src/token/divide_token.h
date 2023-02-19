#pragma once

#include <string>

#include "token.h"

namespace token {
class DivideToken : public Token {
 public:
  static const std::unique_ptr<Token> CreateToken(std::string);
  const TokenType GetType() override { return TokenType::DIVIDE; }
  const std::string GetValue() override;

 private:
  DivideToken();
};
}  // namespace token
