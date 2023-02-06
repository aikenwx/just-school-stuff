#pragma once

#include <string>

#include "../ast/procedure_node.h"
#include "../ast/statement_node.h"

namespace rel {
class Relationship {
  public:
    virtual ~Relationship() = default;
};

class StmtVarRelationship : public Relationship {
 public:
  virtual int statementNumber() = 0;
  // TODO: return PKBStorageClasses/EntityClasses/Entity.h?
  virtual int entityType() = 0;
  virtual std::string variableName() = 0;
  // static StmtVarRelationship CreateRelationship(
  //     ast::StatementNode* statement, std::string variableName);

 private:
  ast::StatementNode* statementNode_;
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
  virtual int firstEntityType() = 0;
  virtual int secondEntityType() = 0;
  // static StmtStmtRelationship CreateRelationship(
  //     ast::StatementNode* firstStatement, ast::StatementNode*
  //     secondStatement);

 private:
  ast::StatementNode* firstStatementNode_;
  ast::StatementNode* secondStatementNode_;
};

class StmtRelationship : public Relationship {
 public:
  virtual int statementNumber() = 0;
  virtual int entityType() = 0;
  // static StmtRelationship CreateRelationship(ast::StatementNode* statement);

 private:
  ast::StatementNode* statementNode_;
};
}  // namespace rel
