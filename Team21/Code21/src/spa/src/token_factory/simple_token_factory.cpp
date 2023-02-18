#include "simple_token_factory.h"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "../token/and_token.h"
#include "../token/assign_token.h"
#include "../token/divide_token.h"
#include "../token/equal_token.h"
#include "../token/greater_equal_token.h"
#include "../token/greater_than_token.h"
#include "../token/identifier_token.h"
#include "../token/integer_token.h"
#include "../token/left_brace_token.h"
#include "../token/left_paren_token.h"
#include "../token/less_equal_token.h"
#include "../token/less_than_token.h"
#include "../token/minus_token.h"
#include "../token/modulo_token.h"
#include "../token/multiply_token.h"
#include "../token/not_equal_token.h"
#include "../token/not_token.h"
#include "../token/or_token.h"
#include "../token/plus_token.h"
#include "../token/right_brace_token.h"
#include "../token/right_paren_token.h"
#include "../token/semicolon_token.h"
#include "../token/token.h"
#include "util/is_integer.h"

namespace token_factory {
std::unique_ptr<token::Token> SimpleTokenFactory::createToken(std::string value) {
  if (value == "{") {
    return token::LeftBraceToken::createToken(value);
  } else if (value == "}") {
    return token::RightBraceToken::createToken(value);
  } else if (value == "(") {
    return token::LeftParenToken::createToken(value);
  } else if (value == ")") {
    return token::RightParenToken::createToken(value);
  } else if (value == ";") {
    return token::SemicolonToken::createToken(value);
  } else if (value == "+") {
    return token::PlusToken::createToken(value);
  } else if (value == "-") {
    return token::MinusToken::createToken(value);
  } else if (value == "*") {
    return token::MultiplyToken::createToken(value);
  } else if (value == "/") {
    return token::DivideToken::createToken(value);
  } else if (value == "%") {
    return token::ModuloToken::createToken(value);
  } else if (value == "==") {
    return token::EqualToken::createToken(value);
  } else if (value == "!=") {
    return token::NotEqualToken::createToken(value);
  } else if (value == "<") {
    return token::LessThanToken::createToken(value);
  } else if (value == "<=") {
    return token::LessEqualToken::createToken(value);
  } else if (value == ">") {
    return token::GreaterThanToken::createToken(value);
  } else if (value == ">=") {
    return token::GreaterEqualToken::createToken(value);
  } else if (value == "!") {
    return token::NotToken::createToken(value);
  } else if (value == "=") {
    return token::AssignToken::createToken(value);
  } else if (value == "&&") {
    return token::AndToken::createToken(value);
  } else if (value == "||") {
    return token::OrToken::createToken(value);
  } else if (util::is_integer(value)) {
    return token::IntegerToken::createToken(value);
  } else {
    return token::IdentifierToken::createToken(value);
  }
};

bool SimpleTokenFactory::isWhitespace(const char& c) {
  return (kWhitespaceTokens.find(c) != kWhitespaceTokens.end());
}

bool SimpleTokenFactory::isSymbolPrefixChar(const char& c) {
  return (kSymbolTokens.find(c) != kSymbolTokens.end());
}

CheckSymbolResult SimpleTokenFactory::checkSymbol(const std::string& value) {
  auto it = kSymbolTokens.find(value[0]);
  if (it == kSymbolTokens.end()) {
    return {false, false};
  }
  std::vector<std::string> candidates = it->second;
  bool isValidPrefix = false;
  for (std::string candidate : candidates) {
    if (candidate.size() < value.size()) {
      continue;
    }

    auto res = std::mismatch(value.begin(), value.end(), candidate.begin());
    if (res.first == value.end()) { // prefix match
      isValidPrefix = true;
      if (res.second == candidate.end()) { // exact match
        return {isValidPrefix, true}; // {isValidPrefix, isValidSymbol}
      }
    }
  }
  return {isValidPrefix, false};
}

SimpleTokenFactory::SimpleTokenFactory() {}

const std::unordered_map<char, std::vector<std::string>>
    SimpleTokenFactory::kSymbolTokens{
        {'+', {"++", "+"}}, {'-', {"--", "-"}}, {'*', {"*"}},
        {'/', {"/"}},       {'%', {"%"}},       {'(', {"("}},
        {')', {")"}},       {'{', {"{"}},       {'}', {"}"}},
        {';', {";"}},       {'=', {"==", "="}}, {'!', {"!=", "!"}},
        {'<', {"<=", "<"}}, {'>', {">=", ">"}}, {'&', {"&&"}},
        {'|', {"||"}},
    };

const std::unordered_set<char> SimpleTokenFactory::kWhitespaceTokens{' ', '\t',
                                                                    '\n', '\r'};
}  // namespace token_factory
