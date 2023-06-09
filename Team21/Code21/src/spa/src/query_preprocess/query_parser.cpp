#include "query_preprocess/query_parser.h"

#include <stack>
#include <cctype>
#include <algorithm>
#include <utility>
#include <ostream>

namespace qps {

QueryParser::QueryParser(std::vector<std::string> tokens_)
    : tokens{std::move(tokens_)}, currentIndex{0}, selectClause{Boolean()} {}

// See next PQL string token
auto QueryParser::peek() -> std::string {
  if (currentIndex < tokens.size()) {
    return tokens[currentIndex];
  }
  return "";
}

// Consume next PQL string token
auto QueryParser::next() -> std::string {
  std::string currentToken{peek()};
  currentIndex++;
  return currentToken;
}

// Check list of tokens reaching end
auto QueryParser::isEnd() -> bool {
  return (peek().empty());
}

// Helper function to check whether interger token is valid
auto QueryParser::isTokenValidInteger(std::string str) -> bool {
  for (char digit : str) {
    if (std::isdigit(digit) == 0) {
      return false;
    }
  }
  if (str.length() > 1 && str[0] == '0') {
    return false;
  }
  return str.length() != 0;
}

// Check whether next token is identical
auto QueryParser::isSameToken(const std::string& str) -> bool {
  return (peek() == str);
}

// Assert that the next token should be the specified string
auto QueryParser::assertNextToken(const std::string& str) -> bool {
  if (isSameToken(str)) {
    return true;
  }
  throw QueryException(ErrorType::Syntactic, "Syntactic error. Invalid Query Syntax. Expect (" + str + ") got (" + peek() + ")");
}

auto QueryParser::parseRef() -> Ref {
  if (isSameToken("\"")) {
    next();
    std::string iden = next();
    assertNextToken("\"");
    next();
    return QuotedIdentifier(iden);
  } if (Synonym::isValidSynonym(peek())) {
    return Synonym(next());
  } if (isSameToken("_")) {
    next();
    return Underscore();
  } if (isTokenValidInteger(peek())) {
    return std::stoi(next());
  }     throw QueryException(ErrorType::Syntactic, "Invalid representation for Ref: (" + peek() + ")");

}

auto QueryParser::parseExpressionSpec() -> ExpressionSpec {
  bool isPartial{};
  std::string expression{};

  if (isSameToken("\"")) {
    next();
    expression = validateExpression(next());
    expression = makePostfix(expression);
    isPartial = false;
    assertNextToken("\"");
    next();
  } else {
    assertNextToken("_");
    next();
    if (isSameToken("\"")) {
      next();
      expression = validateExpression(next());
      expression = makePostfix(expression);
      isPartial = true;
      assertNextToken("\"");
      next();
      assertNextToken("_");
      next();
    } else {
      return Underscore();
    }
  }
  return Expression(isPartial, expression);
}

// check for syntax error in expression together with helper functions
auto QueryParser::validateExpression(std::string str) -> std::string {
  str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
  int idx = 0;
  int firstidx = idx;
  int last = static_cast<int>(str.length()) - 1;
  int openBracketCount = 0;
  int closeBracketCount = 0;
  while (idx < str.length()) {
    int next = idx + 1;
    int prev = idx - 1;
    checkAlphanumericHelper(str, idx, next, prev);
    checkNumberHelper(str, idx, last, next, prev);
    checkLeftBracketHelper(str, idx, last, prev, next, openBracketCount);
    checkRightBracketHelper(str, idx, last, prev, next, closeBracketCount, openBracketCount);
    checkOperatorHelper(str, idx, last, next, prev);
    if (firstidx == idx) {
      throw QueryException(ErrorType::Syntactic,
        "Syntactic error. Expression spec contains unallowed characters inside or ends with wrong character");
    }
    firstidx = idx;
  }
  if (openBracketCount != closeBracketCount) {
    throw QueryException(ErrorType::Syntactic, "Syntactic error. Closing brackets are insufficient");
  }
  return str;
}

void QueryParser::checkAlphanumericHelper(std::string str, int &idx, int &next, int &prev) {
  if (isalpha(str[idx]) != 0) {
    ++idx;
    while (idx < str.length() && (isalnum(str[idx]) != 0)) {
      ++idx;
    }
  }
  next = idx + 1;
  prev = idx - 1;
}

void QueryParser::checkNumberHelper(std::string str, int &idx, int last, int &next, int &prev) {
    if (isdigit(str[idx]) != 0) {
      ++idx;
      prev = idx - 1;
      if (str[prev] == '0' && idx < str.length() && (isdigit(str[idx]) != 0)) {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. Expression spec contains leading zero");
      }
      while (idx < str.length() && (isdigit(str[idx]) != 0)) {
        ++idx;
      }
      if (idx <= last && (isalpha(str[idx]) != 0)) {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. Integer has a letter in it");
      }
    }
    next = idx + 1;
    prev = idx - 1;
}

void QueryParser::checkLeftBracketHelper(std::string str, int &idx, int last, int &prev, int &next, int &openBracketCount) {
    if (str[idx] == '(' && idx < last) {
      if (idx > 0 && operatorHelper(str[prev]) < 0 && str[prev] != '(') {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. ( is preceded by neither an operator or (");
      }
      if ((isalnum(str[next]) == 0) && str[next] != '(') {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. ( is followed by neither an alphanumeric char or (");
      }
      openBracketCount += 1;
      ++idx;
    }
    next = idx + 1;
    prev = idx - 1;
}

void QueryParser::checkRightBracketHelper(std::string str, int &idx, int last, int &prev, int &next, int &closeBracketCount, int &openBracketCount) {
      if (str[idx] == ')') {
        if (idx == 0) {
          throw QueryException(ErrorType::Syntactic, "Syntactic error. ) cannot be first char");
        }
        if ((isalnum(str[prev]) == 0) && str[prev] != ')') {
          throw QueryException(ErrorType::Syntactic, "Syntactic error. ) is preceded by neither an alphanumeric char or )");
        }
        if (idx != last && operatorHelper(str[next]) < 0 && str[next] != ')') {
          throw QueryException(ErrorType::Syntactic, "Syntactic error. ) is followed by neither an operator or )");
        }
        closeBracketCount += 1;
        if (closeBracketCount > openBracketCount) {
          throw QueryException(ErrorType::Syntactic, "Syntactic error. ) is not supposed to be allowed without a opening bracket");
        }
      ++idx;
    }
    next = idx + 1;
    prev = idx - 1;
}

void QueryParser::checkOperatorHelper(std::string str, int &idx, int last, int &next, int& prev) {
    if (operatorHelper(str[idx]) >= 0 && idx < last) {
      if (idx == 0) {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. Operator cannot be first char");
      }
      if (operatorHelper(str[next]) >= 0) {
        throw QueryException(ErrorType::Syntactic, "Syntactic error. operator cannot be followed by operator");
      }
      ++idx;
    }
    next = idx + 1;
    prev = idx - 1;
}

auto QueryParser::parseElement() -> Element {
  Synonym synonym = Synonym(next());
  if (isSameToken(".")) {
    next();
    AttrName attrName = getAttrNameFromString(next());
    return AttrRef(synonym, attrName);
  }     return synonym;

}

auto QueryParser::parseWithRef() -> WithRef {
  if (isSameToken("\"")) {
    next();
    std::string iden = next();
    assertNextToken("\"");
    next();
    return WithRef(QuotedIdentifier(iden));
  } if (isTokenValidInteger(peek())) {
    return WithRef(std::stoi(next()));
  } if (Synonym::isValidSynonym(peek())) {
    Synonym synonym = Synonym(next());
    assertNextToken(".");
    next();
    AttrName attrName = getAttrNameFromString(next());
    return WithRef(AttrRef(synonym, attrName));
  }     throw QueryException(ErrorType::Syntactic, "Invalid representation for WithRef: (" + peek() + ")");

}

auto QueryParser::parseTupleSelect() -> std::vector<Element> {
  std::vector<Element> tuple{};
  if (isSameToken("<")) {
    next();
    tuple.push_back(parseElement());
    while (isSameToken(",")) {
      next();
      tuple.push_back(parseElement());
    }
    assertNextToken(">");
    next();
  } else {
    tuple.push_back(parseElement());
  }
  return tuple;
}

void QueryParser::parseSuchThat() {
  Relationship relationship{getRelationshipFromString(next())};
  assertNextToken("(");
  next();
  Ref arg1{parseRef()};
  assertNextToken(",");
  next();
  Ref arg2{parseRef()};
  assertNextToken(")");
  next();

  suchThatClause.emplace_back(relationship, arg1, arg2, declarations);
}

void QueryParser::parsePattern() {
  Synonym synonym{Synonym(next())};
  if (!Declaration::findDeclarationWithSynonym(declarations, synonym).has_value()) {
    throw QueryException(ErrorType::Semantic,
      "Semantic error. There is missing declaration in pattern clause for synonym " + synonym.getSynonym());
  }
  auto declaration{Declaration::findDeclarationWithSynonym(declarations, synonym)};
  DesignEntity synDE{ declaration.value().getDesignEntity() };

  assertNextToken("(");
  next();
  Ref arg1{parseRef()};
  assertNextToken(",");
  next();
  ExpressionSpec arg2{parseExpressionSpec()};
  if (synDE == DesignEntity::IF) {
    assertNextToken(",");
    next();
    assertNextToken("_");
    next();
  }
  assertNextToken(")");
  next();

  patternClause.emplace_back(synonym, arg1, arg2);
}

void QueryParser::parseWith() {
  WithRef ref1{parseWithRef()};
  assertNextToken("=");
  next();
  WithRef ref2{parseWithRef()};

  withClause.emplace_back(ref1, ref2);
}

auto QueryParser::parseDeclaration() -> bool {
  try {
    getDesignEntityFromString(peek());
  } catch (QueryException &e) {
    return false;
  }
  DesignEntity design_entity{getDesignEntityFromString(next())};
  std::vector<Synonym> synonym_list;

  synonym_list.emplace_back(next());

  while (!isSameToken(";")) {
    assertNextToken(",");
    next();
    synonym_list.emplace_back(next());
  }
  next();
  for (const Synonym& synonym : synonym_list) {
    declarations.emplace_back(design_entity, synonym);
  }
  return true;
}

void QueryParser::parseSelectClause() {
  assertNextToken("Select");
  next();
  std::string select = peek();
  if (select == "BOOLEAN") {
    Synonym test_synonym{select};
    if (Declaration::findDeclarationWithSynonym(declarations, test_synonym) == std::nullopt) {
      selectClause = Boolean();
      next();
    } else {
      selectClause = parseTupleSelect();
    }
  } else {
    selectClause = parseTupleSelect();
  }
}

auto QueryParser::parseSuchThatClause() -> bool {
  if (!isSameToken("such")) {
    return false;
  }
  next();
  assertNextToken("that");
  next();

  parseSuchThat();
  while (isSameToken("and")) {
    next();
    parseSuchThat();
  }
  return true;
}

auto QueryParser::parsePatternClause() -> bool {
  if (!isSameToken("pattern")) {
    return false;
  }
  next();

  parsePattern();
  while (isSameToken("and")) {
    next();
    parsePattern();
  }
  return true;
}

auto QueryParser::parseWithClause() -> bool {
  if (!isSameToken("with")) {
    return false;
  }
  next();

  parseWith();
  while (isSameToken("and")) {
    next();
    parseWith();
  }
  return true;
}

// Parse the list of string tokens and generate the Query object
auto QueryParser::parse() -> Query {
  while (!isEnd()) {
    if (!parseDeclaration()) {
      break;
    }
  }
  parseSelectClause();
  while (!isEnd()) {
    if (parseSuchThatClause()) {
      continue;
    } if (parsePatternClause()) {
      continue;
    } if (parseWithClause()) {
      continue;
    }       throw QueryException(ErrorType::Syntactic, "Invalid clause, not such-that or pattern");

  }
  return {declarations, suchThatClause, patternClause, withClause, selectClause};
}

//helper to tell precedence of operators
auto QueryParser::operatorHelper(char character) -> int {
  switch (character) {
  case '%':
  case '*':
  case '/':return 1;
  case '+':
  case '-':return 0;
  default:return -1;
  }
}

// Helper function to translate Expression string to post-fix form
auto QueryParser::makePostfix(std::string str) -> std::string {
  std::stack<char> stck;
  std::string postfixed;
  int idx = 0;
  auto last = str.length() - 1;
  while (idx < str.length()) {
    //check for alphanumeric
    if (isalpha(str[idx]) != 0) {
      postfixed += "\"";
      postfixed += str[idx];
      idx++;
      while (idx < str.length() && (isalnum(str[idx]) != 0)) {
        postfixed += str[idx];
        idx++;
      }
      postfixed += "\"";
    }
    //check for number
    else if (isdigit(str[idx]) != 0) {
      postfixed += "\"";
      postfixed += str[idx];
      idx++;
      while (idx < str.length() && (isdigit(str[idx]) != 0)) {
        postfixed += str[idx];
        idx++;
      }
      postfixed += "\"";
    }
    //check for '('
    else if (str[idx] == '(') {
      stck.push(str[idx]);
      idx++;
    }
    //check for ')'
    else if (str[idx] == ')') {
      while (stck.top() != '(') {
        postfixed += stck.top();
        stck.pop();
      }
      stck.pop();
      idx++;
    }
    //check for operators
    else if (operatorHelper(str[idx]) >= 0 && idx < last) {
      while (!stck.empty() && (operatorHelper(str[idx]) <= operatorHelper(stck.top()))) {
        postfixed += stck.top();
        stck.pop();
      }
      stck.push(str[idx]);
      idx++;
    }
  }
  while (!stck.empty()) {
    postfixed += stck.top();
    stck.pop();
  }
  return postfixed;
}

}  // namespace qps
