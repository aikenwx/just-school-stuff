#pragma once

#include <string>

#include "relationship.h"

namespace rel {
class ModifiesProcVarRelationship : public ProcVarRelationship {
public:
  static auto CreateRelationship(const std::string &procedureName,
                                 const std::string &variableName)
      -> std::unique_ptr<ModifiesProcVarRelationship>;
  [[nodiscard]] auto relationshipType() const -> RelationshipType override {
    return RelationshipType::MODIFIES_PROC_VAR;
  };

private:
  ModifiesProcVarRelationship(std::string_view procedureName,
                              std::string_view variableName)
      : ProcVarRelationship(procedureName, variableName){};
};
} // namespace rel
