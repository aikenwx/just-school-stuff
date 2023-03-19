#include "assign_token.h"

#include <cassert>
#include <string>

namespace token {
auto AssignToken::CreateToken(std::string_view str)
    -> std::unique_ptr<Token> {
  assert(str == "="); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
  return std::unique_ptr<AssignToken>(new AssignToken());
};

auto AssignToken::GetValue() const -> std::string { return "="; };
}  // namespace token
