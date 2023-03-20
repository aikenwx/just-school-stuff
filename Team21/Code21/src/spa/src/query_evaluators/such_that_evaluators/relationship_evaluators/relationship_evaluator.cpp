#include "relationship_evaluator.h"
#include "query/ref.h"
#include "query/query_exceptions.h"
#include "query_evaluators/pkb_helpers.h"

namespace qps {
const std::vector<EntityType>
    RelationshipEvaluator::CONTAINER_TYPES =
    {WhileStatement::getEntityTypeStatic(), IfStatement::getEntityTypeStatic()};

auto RelationshipEvaluator::Evaluate(QueryFacade &pkb) -> ClauseResult {
  std::vector<::Relationship *> filtered_relationships;
  Ref ref1 = clause_.getArg1();
  Ref ref2 = clause_.getArg2();
  auto left_hand = ResolveLeftTypes(ref1);
  auto right_hand = ResolveRightTypes(ref2);
  for (auto left : left_hand) {
    for (auto right : right_hand) {
      auto res = CallPkb(pkb, left, right);
      for (auto *relationship : res) {
        if (!Filter(*relationship)) {
          filtered_relationships.push_back(relationship);
        }
      }
    }
  }
  return qps::RelationshipEvaluator::ConstructResult(filtered_relationships);
}

auto RelationshipEvaluator::ConstructResult(const std::vector<::Relationship *> &relationships) -> ClauseResult {
  Ref ref1 = clause_.getArg1();
  Ref ref2 = clause_.getArg2();
  std::vector<Synonym> syns;
  bool left_syn = false;
  bool right_syn = false;
  if (Synonym *syn = std::get_if<Synonym>(&ref1)) {
    left_syn = true;
    syns.push_back(*syn);
  }
  if (Synonym *syn = std::get_if<Synonym>(&ref2)) {
    right_syn = true;
    syns.push_back(*syn);
  }

  if (left_syn && right_syn && syns[0] == syns[1]) {
    return false;
  }

  if (!left_syn && !right_syn) {
    return !relationships.empty();
  }

  SynonymTable result(syns);
  for (auto *relation : relationships) {
    SynonymTable::Row row;
    if (left_syn) {
      row.push_back(relation->getLeftHandEntity());
    }
    if (right_syn) {
      row.push_back(relation->getRightHandEntity());
    }
    result.AddRow(std::move(row));
  }
  return result;
}

auto RelationshipEvaluator::Filter(::Relationship &relationship) -> bool {
  Ref ref1 = clause_.getArg1();
  Ref ref2 = clause_.getArg2();
  if (StatementNumber *stmt_num = std::get_if<StatementNumber>(&ref1)) {
    if (*(relationship.getLeftHandEntity()->getEntityValue()) != std::to_string(*stmt_num)) {
      return true;
    }
  }

  if (StatementNumber *stmt_num = std::get_if<StatementNumber>(&ref2)) {
    if (*(relationship.getRightHandEntity()->getEntityValue()) != std::to_string(*stmt_num)) {
      return true;
    }
  }

  if (QuotedIdentifier *quoted_identifier = std::get_if<QuotedIdentifier>(&ref1)) {
    if (*(relationship.getLeftHandEntity()->getEntityValue()) != quoted_identifier->getQuotedId()) {
      return true;
    }
  }

  if (QuotedIdentifier *quoted_identifier = std::get_if<QuotedIdentifier>(&ref2)) {
    if (*(relationship.getRightHandEntity()->getEntityValue()) != quoted_identifier->getQuotedId()) {
      return true;
    }
  }
  return false;
}
auto RelationshipEvaluator::ResolveLeftTypes(Ref &left_arg) -> std::vector<EntityType> {
  if (Synonym *syn = std::get_if<Synonym>(&left_arg)) {
    return {GetEntityType(*syn, declarations_)};
  }
  return GetLeftHandTypes(left_arg);

}

auto RelationshipEvaluator::ResolveRightTypes(Ref &right_arg) -> std::vector<EntityType> {
  if (Synonym *syn = std::get_if<Synonym>(&right_arg)) {
    return {GetEntityType(*syn, declarations_)};
  }
  return GetRightHandTypes(right_arg);
}
}  // namespace qps