#pragma once

#include <string>

#include "token.h"

namespace token {
class IntegerToken : public Token {
 public:
  static const std::unique_ptr<Token> createToken(std::string);
  const std::string getValue() override;

 private:
  IntegerToken(std::string value);
  std::string value;
};
}  // namespace token
