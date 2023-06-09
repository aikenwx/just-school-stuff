#include <memory>
#include <vector>

#include "sp/token/token.h"

namespace tokenizer {
bool verifyTokenizerOutput(std::vector<std::unique_ptr<token::Token>> const& tokens,
                           std::vector<std::string> expected);
}  // namespace tokenizer
