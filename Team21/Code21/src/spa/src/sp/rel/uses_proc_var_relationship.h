#pragma once

#include <string>

#include "relationship.h"

namespace rel {
class UsesProcVarRelationship : public ProcVarRelationship {
 public:
  static auto CreateRelationship(
      const std::string& procedureName, const std::string& variableName) -> std::unique_ptr<UsesProcVarRelationship>;
  [[nodiscard]] auto procedureName() const -> std::string override;
  [[nodiscard]] auto variableName() const -> std::string override;
  [[nodiscard]] auto relationshipType() const -> RelationshipType override { return RelationshipType::USES_PROC_VAR; };

 private:
  UsesProcVarRelationship(std::string_view procedureName, std::string_view variableName) : procedureName_(procedureName), variableName_(variableName) {};
  std::string procedureName_;
  std::string variableName_;
};
}  // namespace rel
