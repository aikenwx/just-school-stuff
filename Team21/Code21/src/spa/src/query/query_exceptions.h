#pragma once

#include <iostream>
#include <stdexcept>
#include <string>

namespace qps {

// Types of error introduced in PQL rules
enum class ErrorType { Semantic, Syntactic };

// QueryException represents Query Exception when PQL query got Syntactic or Semantic error
class QueryException : public std::runtime_error {
 private:
	ErrorType type_;

 public:
	explicit QueryException(ErrorType type_, const std::string& msg = "") : type_(type_), std::runtime_error(msg) {}

	auto getType() -> ErrorType {
		return type_;
	}
};

}  // namespace qps
