#include <catch2/catch_test_macros.hpp>
#include <memory>

#include "PKB/EntityManager.h"
#include "PKBStorageClasses/EntityClasses/AssignStatement.h"
#include "PKBStorageClasses/EntityClasses/CallStatement.h"
#include "PKBStorageClasses/EntityClasses/IfStatement.h"
#include "PKBStorageClasses/EntityClasses/PrintStatement.h"
#include "PKBStorageClasses/EntityClasses/Procedure.h"
#include "PKBStorageClasses/EntityClasses/ReadStatement.h"
#include "PKBStorageClasses/EntityClasses/WhileStatement.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

TEST_CASE("EntityManager Instantiates") {
  auto entityManager = std::make_unique<EntityManager>();
}

TEST_CASE("EntityManager can store entity") {
  auto entityManager = std::make_unique<EntityManager>();

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
}

TEST_CASE("EntityManager can retrieve entity") {
  auto entityManager = std::make_unique<EntityManager>();
  std::shared_ptr<ReadStatement> readStatement =
      std::make_unique<ReadStatement>(1);

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 1);
  REQUIRE(entities->at(0)->equals(readStatement.get()));
}

TEST_CASE("EntityManager can retrieve mulitple entries") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement1 =
      std::make_unique<ReadStatement>(1);
  std::shared_ptr<ReadStatement> readStatement2 =
      std::make_unique<ReadStatement>(2);

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
  entityManager->storeEntity(std::make_unique<ReadStatement>(2));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  REQUIRE(entities->at(0)->equals(readStatement1.get()));
  REQUIRE(entities->at(1)->equals(readStatement2.get()));
}

TEST_CASE("EntityManager returns empty vector if no entries") {
  auto entityManager = std::make_unique<EntityManager>();

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->empty());
}

TEST_CASE("EntityManager can retrieve multiple types") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement =
      std::make_unique<ReadStatement>(1);
  std::shared_ptr<AssignStatement> assignStatement =
      std::make_unique<AssignStatement>(2);

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
  entityManager->storeEntity(std::make_unique<AssignStatement>(2));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 1);
  REQUIRE(entities->at(0)->equals(readStatement.get()));

  entities =
      entityManager->getEntitiesByType(AssignStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 1);
  REQUIRE(entities->at(0)->equals(assignStatement.get()));
}

TEST_CASE("EntityManager can retrieve multiple entities of multiple types") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement1 =
      std::make_unique<ReadStatement>(1);
  std::shared_ptr<ReadStatement> readStatement2 =
      std::make_unique<ReadStatement>(2);
  std::shared_ptr<AssignStatement> assignStatement1 =
      std::make_unique<AssignStatement>(3);
  std::shared_ptr<AssignStatement> assignStatement2 =
      std::make_unique<AssignStatement>(4);

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
  entityManager->storeEntity(std::make_unique<ReadStatement>(2));
  entityManager->storeEntity(std::make_unique<AssignStatement>(3));
  entityManager->storeEntity(std::make_unique<AssignStatement>(4));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  REQUIRE(entities->at(0)->equals(readStatement1.get()));
  REQUIRE(entities->at(1)->equals(readStatement2.get()));

  entities =
      entityManager->getEntitiesByType(AssignStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  REQUIRE(entities->at(0)->equals(assignStatement1.get()));
  REQUIRE(entities->at(1)->equals(assignStatement2.get()));
}

TEST_CASE("EntityManager can retrieve all Statements") {
  // store all statements
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement1 =
      std::make_unique<ReadStatement>(1);
  std::shared_ptr<ReadStatement> readStatement2 =
      std::make_unique<ReadStatement>(2);
  std::shared_ptr<PrintStatement> printStatement1 =
      std::make_unique<PrintStatement>(3);
  std::shared_ptr<PrintStatement> printStatement2 =
      std::make_unique<PrintStatement>(4);
  std::shared_ptr<AssignStatement> assignStatement1 =
      std::make_unique<AssignStatement>(5);
  std::shared_ptr<AssignStatement> assignStatement2 =
      std::make_unique<AssignStatement>(6);
  std::shared_ptr<CallStatement> callStatement1 =
      std::make_unique<CallStatement>(7);
  std::shared_ptr<CallStatement> callStatement2 =
      std::make_unique<CallStatement>(8);
  std::shared_ptr<WhileStatement> whileStatement1 =
      std::make_unique<WhileStatement>(9);
  std::shared_ptr<WhileStatement> whileStatement2 =
      std::make_unique<WhileStatement>(10);
  std::shared_ptr<IfStatement> ifStatement1 =
      std::make_unique<IfStatement>(11);
  std::shared_ptr<IfStatement> ifStatement2 =
      std::make_unique<IfStatement>(12);
  std::shared_ptr<Variable> variable =
      std::make_unique<Variable>(std::make_unique<std::string>("x"));
  std::shared_ptr<Procedure> procedure =
      std::make_unique<Procedure>(std::make_unique<std::string>("main"));

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
  entityManager->storeEntity(std::make_unique<ReadStatement>(2));
  entityManager->storeEntity(std::make_unique<PrintStatement>(3));
  entityManager->storeEntity(std::make_unique<PrintStatement>(4));
  entityManager->storeEntity(std::make_unique<AssignStatement>(5));
  entityManager->storeEntity(std::make_unique<AssignStatement>(6));
  entityManager->storeEntity(std::make_unique<CallStatement>(7));
  entityManager->storeEntity(std::make_unique<CallStatement>(8));
  entityManager->storeEntity(std::make_unique<WhileStatement>(9));
  entityManager->storeEntity(std::make_unique<WhileStatement>(10));
  entityManager->storeEntity(std::make_unique<IfStatement>(11));
  entityManager->storeEntity(std::make_unique<IfStatement>(12));
  entityManager->storeEntity(
      std::make_unique<Variable>(std::make_unique<std::string>("x")));
  entityManager->storeEntity(
      std::make_unique<Procedure>(std::make_unique<std::string>("main")));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(Statement::getEntityTypeStatic());

  REQUIRE(entities->size() == 12);

  for (Entity *entity : *entities) {
    bool isStatement =
        entity->getEntityType() == ReadStatement::getEntityTypeStatic() ||
        entity->getEntityType() == PrintStatement::getEntityTypeStatic() ||
        entity->getEntityType() == AssignStatement::getEntityTypeStatic() ||
        entity->getEntityType() == CallStatement::getEntityTypeStatic() ||
        entity->getEntityType() == WhileStatement::getEntityTypeStatic() ||
        entity->getEntityType() == IfStatement::getEntityTypeStatic();

    REQUIRE(isStatement);
  }
}

TEST_CASE(
    "Retrieving statements from empty EntityManager returns empty vector") {
  auto entityManager = std::make_unique<EntityManager>();

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(Statement::getEntityTypeStatic());

  REQUIRE(entities->empty());
}

TEST_CASE("Storing duplicate entity handled correctly") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement =
      std::make_unique<ReadStatement>(1);

  entityManager->storeEntity(std::make_unique<ReadStatement>(1));
  entityManager->storeEntity(std::make_unique<ReadStatement>(1));

  std::vector<Entity *> *entities =
      entityManager->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 1);
  REQUIRE(entities->at(0)->equals(readStatement.get()));
}

TEST_CASE("Can store and retrieve constant by constant value") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<Constant> constant = std::make_unique<Constant>(1);

  entityManager->storeEntity(std::make_unique<Constant>(1));

  auto key = EntityKey(&Constant::getEntityTypeStatic(), 1);

  auto *retrievedConstant =
      dynamic_cast<Constant *>(entityManager->getEntity(key));

  REQUIRE(retrievedConstant->equals(constant.get()));
}

TEST_CASE("Can store and retrieve variable by variable name") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<Variable> variable =
      std::make_unique<Variable>(std::make_unique<std::string>("x"));

  entityManager->storeEntity(
      std::make_unique<Variable>(std::make_unique<std::string>("x")));

  std::string word = "x";
  auto key = EntityKey(&Variable::getEntityTypeStatic(), &word);

  auto *retrievedVariable =
      dynamic_cast<Variable *>(entityManager->getEntity(key));

  REQUIRE(retrievedVariable->equals(variable.get()));
}

TEST_CASE("Can store and retrieve procedure by procedure name") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<Procedure> procedure =
      std::make_unique<Procedure>(std::make_unique<std::string>("main"));
  entityManager->storeEntity(
      std::make_unique<Procedure>(std::make_unique<std::string>("main")));

  std::string word = "main";
  auto key = EntityKey(&Procedure::getEntityTypeStatic(), &word);

  auto *retrievedProcedure =
      dynamic_cast<Procedure *>(entityManager->getEntity(key));

  REQUIRE(retrievedProcedure->equals(procedure.get()));
}

TEST_CASE("Can store and retrieve statement by statement number") {
  auto entityManager = std::make_unique<EntityManager>();

  std::shared_ptr<ReadStatement> readStatement =
      std::make_unique<ReadStatement>(1);
  entityManager->storeEntity(std::make_unique<ReadStatement>(1));

  auto key = EntityKey(&Statement::getEntityTypeStatic(), 1);

  auto *retrievedReadStatement =
      dynamic_cast<ReadStatement *>(entityManager->getEntity(key));

  REQUIRE(retrievedReadStatement->equals(readStatement.get()));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
