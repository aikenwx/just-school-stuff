#pragma once

#include <string>
#include <vector>

namespace qps {

// QueryTokenizer represents Query Tokenizer consuming the PQL String to produce list of String tokens
class QueryTokenizer {
 private:
	std::string queryString;
	int currentIndex;
	std::string currentString; //Current String for QueryTokenizer
	std::vector<std::string> tokens;

	auto peek() -> char;
	auto next() -> char;
	auto isEnd() -> bool;
	void readPhrase();
	void readNumber();

 public:
	explicit QueryTokenizer(std::string source);
	auto tokenize() -> std::vector<std::string>;
};

}  // namespace qps
