#ifndef SPA_IFSTATEMENT_H
#define SPA_IFSTATEMENT_H

#include "ParentStatement.h"

class IfStatement : public ParentStatement {
   private:
    static const StatementType ifStatementType;

   public:
    explicit IfStatement(int statementNumber);

    static auto getEntityTypeStatic() -> const EntityType &;

    [[nodiscard]] auto getEntityType() const -> const EntityType & override;
};

#endif
