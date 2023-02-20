#pragma once

#include <memory>
#include <string>

#include "../ast/procedure_node.h"
#include "../ast/statement_node.h"
#include "PKBStorageClasses/EntityClasses/Entity.h"

namespace rel {
enum RelationshipType {
  USES_PROC_VAR,
  USES_STMT_VAR,
  MODIFIES_PROC_VAR,
  MODIFIES_STMT_VAR,
  FOLLOWS_STMT_STMT,
  PARENT_STMT_STMT,
  ASSIGN_STMT,
  CALL_STMT,
  IF_STMT,
  WHILE_STMT,
  PRINT_STMT,
  READ_STMT,
  CONST,
  PROC,
  VAR,
  ASSIGN_EXP,
};

class Relationship {
 public:
  virtual ~Relationship() = default;
  virtual RelationshipType relationshipType() = 0;
};

class StmtVarRelationship : public Relationship {
 public:
  virtual int statementNumber() = 0;
  // TODO: return PKBStorageClasses/EntityClasses/Entity.h?
  virtual std::string variableName() = 0;
  // static StmtVarRelationship CreateRelationship(
  //     std::shared_ptr<ast::StatementNode> statement, std::string
  //     variableName);

 private:
  std::shared_ptr<ast::StatementNode> statementNode_;
  std::string variableName_;
};

class ProcVarRelationship : public Relationship {
 public:
  virtual std::string procedureName() = 0;
  virtual std::string variableName() = 0;
  // static ProcVarRelationship CreateRelationship(
  //     std::string procedureName, std::string variableName);

 private:
  std::string procedureName_;
  std::string variableName_;
};

class StmtStmtRelationship : public Relationship {
 public:
  virtual int firstStatementNumber() = 0;
  virtual int secondStatementNumber() = 0;
  // static StmtStmtRelationship CreateRelationship(
  //     std::shared_ptr<ast::StatementNode> firstStatement,
  //     std::shared_ptr<ast::StatementNode> secondStatement);

 private:
  std::shared_ptr<ast::StatementNode> firstStatementNode_;
  std::shared_ptr<ast::StatementNode> secondStatementNode_;
};

class StmtRelationship : public Relationship {
 public:
  virtual int statementNumber() = 0;

 private:
  std::shared_ptr<ast::StatementNode> statementNode_;
};
}  // namespace rel
