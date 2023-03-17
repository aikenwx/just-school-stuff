#include "equal_token.h"

#include <assert.h>

#include <string>

namespace token {
const std::unique_ptr<Token> EqualToken::CreateToken(std::string str) {
  assert(str == "=="); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  return std::unique_ptr<EqualToken>(new EqualToken());
};

EqualToken::EqualToken(){};

const std::string EqualToken::GetValue() { return "=="; };
}  // namespace token
