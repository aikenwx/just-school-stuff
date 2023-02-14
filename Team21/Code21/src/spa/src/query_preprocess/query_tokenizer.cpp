#include "query_preprocess/query_tokenizer.h"
#include "query/query_exceptions.h"

#include <cctype>
#include <set>

namespace qps {

	std::set<std::string> special_phrase={ "Follows", "Parent" };
	std::set<char> single_tokens{'(', ')', '*', ',', ';', '.', '_', '<', '>', '='};


	QueryTokenizer::QueryTokenizer(std::string source)
		: queryString{ source }, currentIndex{ 0 } {}

	char QueryTokenizer::peek() {
		char nextChar{};
		if (currentIndex < queryString.length()) {
			nextChar = queryString[currentIndex];
		} else {
			nextChar = EOF;
		}
		return nextChar;
	}
	char QueryTokenizer::next() {
		char nextChar{ peek() };
		currentIndex++;
		return nextChar;
	}
	bool QueryTokenizer::isEnd() {
		return currentIndex == queryString.length();
	}
	void QueryTokenizer::readPhrase() {
		while (isalnum(peek())) {
			currentString += next();
		}
		//Deals with special phrase with extra single token *
		if (special_phrase.count(currentString) && peek() == '*') {
			currentString += next();
		}
	}
	void QueryTokenizer::readNumber() {
		while (isdigit(peek())) {
			currentString += next();
		}
	}

	std::vector<std::string> QueryTokenizer::tokenize() {
		while (currentIndex < queryString.length()) {
			if (peek() == EOF) {
				break;
			} else if (isalpha(peek())) {
				readPhrase();
				tokens.push_back(currentString);
			} else if (isdigit(peek())) {
				readNumber();
				tokens.push_back(currentString);
			} else if (peek() == '"') {
				next();
				tokens.push_back("\"");
				while (peek() != '"') {
					currentString += next();
				}
				tokens.push_back(currentString);
				next();
				tokens.push_back("\"");
			} else if (isspace(peek())) {
				next();
			} else if (single_tokens.count(peek())) {
				currentString += next();
				tokens.push_back(currentString);
			} else {
				throw QueryException(ErrorType::Syntactic, "Unexpected character in query string: " + std::string(1, peek()));
			}
			currentString = "";
		}
		return tokens;
	}
}