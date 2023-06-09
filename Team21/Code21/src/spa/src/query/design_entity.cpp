#include "query/design_entity.h"
#include "query/query_exceptions.h"

#include <stdexcept>
#include <map>

namespace qps {

// Look up table from Design Entity to string representation
const std::map<DesignEntity, std::string> designEntityStringMap{ {
	{DesignEntity::STMT, "stmt"},
	{DesignEntity::READ, "read"},
	{DesignEntity::PRINT, "print"},
	{DesignEntity::CALL, "call"},
	{DesignEntity::WHILE, "while"},
	{DesignEntity::IF, "if"},
	{DesignEntity::ASSIGN, "assign"},
	{DesignEntity::VARIABLE, "variable"},
	{DesignEntity::CONSTANT, "constant"},
	{DesignEntity::PROCEDURE, "procedure"},
} };

// Look up table from query substring to Design Entity
const std::map<std::string, DesignEntity> designEntityMap{ {
	{"stmt", DesignEntity::STMT},
	{"read", DesignEntity::READ},
	{"print", DesignEntity::PRINT},
	{"call", DesignEntity::CALL},
	{"while", DesignEntity::WHILE},
	{"if", DesignEntity::IF},
	{"assign", DesignEntity::ASSIGN},
	{"variable", DesignEntity::VARIABLE},
	{"constant", DesignEntity::CONSTANT},
	{"procedure", DesignEntity::PROCEDURE},
} };

// Get corresponding design entity of a given string when parsing
auto getDesignEntityFromString(const std::string& deString) -> DesignEntity {
	try {
		return designEntityMap.at(deString);
	}
	catch (const std::out_of_range& err) {
		throw QueryException(ErrorType::Syntactic, "Invalid Design Entity " + deString);
	}
}

// Get corresponding string representation of a design entity (used for debugging)
auto getStringFromDE(DesignEntity designEntity) -> std::string {
	return designEntityStringMap.at(designEntity);
}

}  // namespace qps
