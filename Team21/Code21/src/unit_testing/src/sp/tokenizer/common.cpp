#include <memory>
#include <string>
#include <vector>

#include "sp/token/token.h"

namespace tokenizer {
bool verifyTokenizerOutput(
    std::vector<std::unique_ptr<token::Token>> const& tokens,
    std::vector<std::string> expected) {
  if (tokens.size() != expected.size()) return false;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i]->GetValue() != expected[i]) return false;
  }
  return true;
};
}  // namespace tokenizer
