//
// Created by Aiken Wong on 5/2/23.
//
#include <catch2/catch_test_macros.hpp>

#include "PKB/PKB.h"
#include "PKBStorageClasses/EntityClasses/ReadStatement.h"
#include "PKBStorageClasses/RelationshipClasses/UsesInParentConditionRelationship.h"
#include "PKBtestHelpers.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

TEST_CASE("Facades available") {
  PKB pkb;
  REQUIRE(pkb.getPopulateFacade() != nullptr);
  REQUIRE(pkb.getQueryFacade() != nullptr);
}

TEST_CASE(
    "PKB can store read statement and QueryFacade can retrieve read "
    "statement") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeReadStatement(1);
  auto *entities = queryFacade->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 1);
  auto expectedStatement = ReadStatement(1);
  REQUIRE(entities->at(0)->equals(&expectedStatement));
}

TEST_CASE(
    "PKB can store multiple read statements and QueryFacade can retrieve read "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeReadStatement(1);
  populateFacade->storeReadStatement(2);
  auto *entities = queryFacade->getEntitiesByType(ReadStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  auto expectedStatement1 = ReadStatement(1);
  auto expectedStatement2 = ReadStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedStatement1));
  REQUIRE(entities->at(1)->equals(&expectedStatement2));
}

TEST_CASE(
    "PKB can store read relationship and QueryFacade can read retrieve "
    "relationship") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeReadStatement(1);
  populateFacade->storeReadStatement(2);
  populateFacade->storeFollowsRelationship(1, 2);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           ReadStatement::getEntityTypeStatic(),
                                           ReadStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 1);

  auto rs1 = ReadStatement(1);
  auto rs2 = ReadStatement(2);
  auto expectedRelationship = FollowsRelationship(&rs1, &rs2);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship));
}

TEST_CASE(
    "PKB can store multiple read follow read relationships and QueryFacade can "
    "retrieve the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeReadStatement(1);
  populateFacade->storeReadStatement(2);
  populateFacade->storeReadStatement(3);
  populateFacade->storeFollowsRelationship(1, 2);
  populateFacade->storeFollowsRelationship(2, 3);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           ReadStatement::getEntityTypeStatic(),
                                           ReadStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto rs1 = ReadStatement(1);
  auto rs2_1 = ReadStatement(2);
  auto expectedRelationship1 = FollowsRelationship(&rs1, &rs2_1);
  auto rs2_2 = ReadStatement(2);
  auto rs3 = ReadStatement(3);
  auto expectedRelationship2 = FollowsRelationship(&rs2_2, &rs3);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple print statements and retrieve mulitple print "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storePrintStatement(1);
  populateFacade->storePrintStatement(2);
  auto *entities = queryFacade->getEntitiesByType(PrintStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  auto expectedPrintStatement1 = PrintStatement(1);
  auto expectedPrintStatement2 = PrintStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedPrintStatement1));
  REQUIRE(entities->at(1)->equals(&expectedPrintStatement2));
}

TEST_CASE(
    "PKB can store multiple print follow print relationships and retrieve the "
    "relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storePrintStatement(1);
  populateFacade->storePrintStatement(2);
  populateFacade->storePrintStatement(3);
  populateFacade->storeFollowsRelationship(1, 2);
  populateFacade->storeFollowsRelationship(2, 3);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           PrintStatement::getEntityTypeStatic(),
                                           PrintStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto rs1 = PrintStatement(1);
  auto rs2_1 = PrintStatement(2);
  auto expectedRelationship1 = FollowsRelationship(&rs1, &rs2_1);
  auto rs2_2 = PrintStatement(2);
  auto rs3 = PrintStatement(3);
  auto expectedRelationship2 = FollowsRelationship(&rs2_2, &rs3);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple call statements and retrieve multiple call "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeCallStatement(1);
  populateFacade->storeCallStatement(2);
  auto *entities = queryFacade->getEntitiesByType(CallStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  auto expectedCallStatement1 = CallStatement(1);
  auto expectedCallStatement2 = CallStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedCallStatement1));
  REQUIRE(entities->at(1)->equals(&expectedCallStatement2));
}

TEST_CASE(
    "PKB can store multiple assign statements and retrieve multiple assign "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeAssignmentStatement(2);
  auto *entities = queryFacade->getEntitiesByType(AssignStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  auto expectedAssignStatement1 = AssignStatement(1);
  auto expectedAssignStatement2 = AssignStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedAssignStatement1));
  REQUIRE(entities->at(1)->equals(&expectedAssignStatement2));
}

TEST_CASE(
    "PKB can store multiple if statements and retrieve multiple if "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeIfStatement(1);
  populateFacade->storeIfStatement(2);
  auto *entities = queryFacade->getEntitiesByType(IfStatement::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);
  auto expectedIfStatement1 = IfStatement(1);
  auto expectedIfStatement2 = IfStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedIfStatement1));
  REQUIRE(entities->at(1)->equals(&expectedIfStatement2));
}

TEST_CASE(
    "PKB can store multiple while statements and retrieve multiple while "
    "statements") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeWhileStatement(2);
  auto *entities = queryFacade->getEntitiesByType(WhileStatement::getEntityTypeStatic());
  REQUIRE(entities->size() == 2);
  auto expectedWhileStatement1 = WhileStatement(1);
  auto expectedWhileStatement2 = WhileStatement(2);
  REQUIRE(entities->at(0)->equals(&expectedWhileStatement1));
  REQUIRE(entities->at(1)->equals(&expectedWhileStatement2));
}

TEST_CASE(
    "PKB can store multiple while parent read relationships and retrieve the "
    "relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeReadStatement(2);
  populateFacade->storeReadStatement(3);
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeParentRelationship(1, 3);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(ParentRelationship::getRelationshipTypeStatic(),
                                           WhileStatement::getEntityTypeStatic(),
                                           ReadStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto ws1_1 = WhileStatement(1);
  auto rs2 = ReadStatement(2);
  auto expectedRelationship1 = ParentRelationship(&ws1_1, &rs2);
  auto ws1_2 = WhileStatement(1);
  auto rs3 = ReadStatement(3);
  auto expectedRelationship2 = ParentRelationship(&ws1_2, &rs3);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple while parent assign relationships and retrieve the "
    "relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeWhileStatement(3);
  populateFacade->storeAssignmentStatement(4);
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeParentRelationship(3, 4);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(ParentRelationship::getRelationshipTypeStatic(),
                                           WhileStatement::getEntityTypeStatic(),
                                           AssignStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto ws1 = WhileStatement(1);
  auto as2 = AssignStatement(2);
  auto expectedRelationship1 = ParentRelationship(&ws1, &as2);
  auto ws3 = WhileStatement(3);
  auto as4 = AssignStatement(4);
  auto expectedRelationship2 = ParentRelationship(&ws3, &as4);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store mulitple assignment follows read relationships and retrieve "
    "the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeReadStatement(2);
  populateFacade->storeAssignmentStatement(3);
  populateFacade->storeReadStatement(4);
  populateFacade->storeFollowsRelationship(1, 2);
  populateFacade->storeFollowsRelationship(3, 4);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           AssignStatement::getEntityTypeStatic(),
                                           ReadStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto as1 = AssignStatement(1);
  auto rs2 = ReadStatement(2);
  auto expectedRelationship1 = FollowsRelationship(&as1, &rs2);
  auto as3 = AssignStatement(3);
  auto rs4 = ReadStatement(4);
  auto expectedRelationship2 = FollowsRelationship(&as3, &rs4);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple assignment follows assignment relationships and "
    "retrieve the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeAssignmentStatement(3);
  populateFacade->storeFollowsRelationship(1, 2);
  populateFacade->storeFollowsRelationship(2, 3);
  auto *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           AssignStatement::getEntityTypeStatic(),
                                           AssignStatement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto as1 = AssignStatement(1);
  auto as2_1 = AssignStatement(2);
  auto expectedRelationship1 = FollowsRelationship(&as1, &as2_1);
  auto as2_2 = AssignStatement(2);
  auto as3 = AssignStatement(3);
  auto expectedRelationship2 = FollowsRelationship(&as2_2, &as3);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple assignment uses variable relationships and "
    "retrieve the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeStatementUsesVariableRelationship(1, "x");
  populateFacade->storeStatementUsesVariableRelationship(2, "y");
  auto *relationships = queryFacade->getRelationshipsByTypes(UsesRelationship::getRelationshipTypeStatic(), AssignStatement::getEntityTypeStatic(), Variable::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto as1 = AssignStatement(1);
  // will be stored in a shared_ptr internally then dealloc'd automatically
  auto v_x = Variable(std::make_unique<std::string>("x"));
  auto expectedRelationship1 = UsesRelationship(&as1, &v_x);

  auto as2 = AssignStatement(2);
  // will be stored in a shared_ptr internally then dealloc'd automatically
  auto v_y = Variable(std::make_unique<std::string>("y"));
  auto expectedRelationship2 = UsesRelationship(&as2, &v_y);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple procedure uses variable relationships and retrieve "
    "the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeProcedureUsesVariableRelationship("Procedure1", "x");
  populateFacade->storeProcedureUsesVariableRelationship("Procedure2", "y");
  auto *relationships =
      queryFacade->getRelationshipsByTypes(UsesRelationship::getRelationshipTypeStatic(), Procedure::getEntityTypeStatic(), Variable::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto p_Procedure1 = Procedure(std::make_unique<std::string>("Procedure1"));
  auto v_x = Variable(std::make_unique<std::string>("x"));
  auto expectedRelationship1 = UsesRelationship(&p_Procedure1, &v_x);
  auto p_Procedure2 = Procedure(std::make_unique<std::string>("Procedure2"));
  auto v_y = Variable(std::make_unique<std::string>("y"));
  auto expectedRelationship2 = UsesRelationship(&p_Procedure2, &v_y);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple call modifies variable relationships and retrieve "
    "the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeCallStatement(1);
  populateFacade->storeCallStatement(2);
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeStatementModifiesVariableRelationship(1, "x");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  auto *relationships =
      queryFacade->getRelationshipsByTypes(ModifiesRelationship::getRelationshipTypeStatic(),
                                           CallStatement::getEntityTypeStatic(),
                                           Variable::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto cs1 = CallStatement(1);
  auto v_x = Variable(std::make_unique<std::string>("x"));
  auto expectedRelationship1 = ModifiesRelationship(&cs1, &v_x);
  auto cs2 = CallStatement(2);
  auto v_y = Variable(std::make_unique<std::string>("y"));
  auto expectedRelationship2 = ModifiesRelationship(&cs2, &v_y);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE(
    "PKB can store multiple procedure modifies variable relationships and "
    "retrieve the relationships") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure2", "y");
  auto *relationships =
      queryFacade->getRelationshipsByTypes(ModifiesRelationship::getRelationshipTypeStatic(),
                                           Procedure::getEntityTypeStatic(), Variable::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  auto p_Procedure1 = Procedure(std::make_unique<std::string>("Procedure1"));
  auto v_x = Variable(std::make_unique<std::string>("x"));
  auto expectedRelationship1 = ModifiesRelationship(&p_Procedure1, &v_x);
  auto p_Procedure2 = Procedure(std::make_unique<std::string>("Procedure2"));
  auto v_y = Variable(std::make_unique<std::string>("y"));
  auto expectedRelationship2 = ModifiesRelationship(&p_Procedure2, &v_y);

  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(0), &expectedRelationship1));
  REQUIRE(PKBtestHelpers::relationshipEqualsRelationship(
      relationships->at(1), &expectedRelationship2));
}

TEST_CASE("PKB can store mulitple types of statements and retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeCallStatement(2);
  populateFacade->storeIfStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeReadStatement(5);
  populateFacade->storeWhileStatement(6);
  populateFacade->storeAssignmentStatement(7);

  // should not be returned
  populateFacade->storeConstant(1);
  populateFacade->storeVariable("x");
  populateFacade->storeProcedure("Procedure1");

  auto const *statements = queryFacade->getEntitiesByType(Statement::getEntityTypeStatic());

  REQUIRE(statements->size() == 7);

  auto expectedStatement1 = AssignStatement(1);
  auto expectedStatement2 = CallStatement(2);
  auto expectedStatement3 = IfStatement(3);
  auto expectedStatement4 = PrintStatement(4);
  auto expectedStatement5 = ReadStatement(5);
  auto expectedStatement6 = WhileStatement(6);
  auto expectedStatement7 = AssignStatement(7);

  std::vector<Statement *> expectedStatements = {
      &expectedStatement1, &expectedStatement2, &expectedStatement3,
      &expectedStatement4, &expectedStatement5, &expectedStatement6,
      &expectedStatement7};

  // for loop finds the statement in the vector and compares it to the expected
  // statement
  for (auto *statement : *statements) {
    REQUIRE(std::find_if(expectedStatements.begin(), expectedStatements.end(),
                         [&statement](Statement *expectedStatement) {
                           return statement->equals(expectedStatement);
                         }) != expectedStatements.end());
  }
}

TEST_CASE(
    "PKB can store mulitple types of statement follows statements "
    "relationships and retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeAssignmentStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storeIfStatement(4);
  populateFacade->storePrintStatement(5);
  populateFacade->storeReadStatement(6);
  populateFacade->storeWhileStatement(7);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeProcedure("Procedure1");

  populateFacade->storeFollowsRelationship(1, 2);
  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeFollowsRelationship(3, 4);
  populateFacade->storeFollowsRelationship(4, 5);
  populateFacade->storeFollowsRelationship(5, 6);
  populateFacade->storeFollowsRelationship(6, 7);

  // should not be returned
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeStatementUsesVariableRelationship(1, "x");
  populateFacade->storeStatementModifiesVariableRelationship(1, "y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");

  auto const *relationships =
      queryFacade->getRelationshipsByTypes(FollowsRelationship::getRelationshipTypeStatic(),
                                           Statement::getEntityTypeStatic(), Statement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 6);

  auto as1 = AssignStatement(1);
  auto as2_1 = AssignStatement(2);
  auto expectedRelationship1 = FollowsRelationship(&as1, &as2_1);

  auto as2_2 = AssignStatement(2);
  auto cs3_1 = CallStatement(3);
  auto expectedRelationship2 = FollowsRelationship(&as2_2, &cs3_1);

  auto cs3_2 = CallStatement(3);
  auto is4_1 = IfStatement(4);
  auto expectedRelationship3 = FollowsRelationship(&cs3_2, &is4_1);

  auto is4_2 = IfStatement(4);
  auto ps5_1 = PrintStatement(5);
  auto expectedRelationship4 = FollowsRelationship(&is4_2, &ps5_1);

  auto ps5_2 = PrintStatement(5);
  auto rs6_1 = ReadStatement(6);
  auto expectedRelationship5 = FollowsRelationship(&ps5_2, &rs6_1);

  auto rs6_2 = ReadStatement(6);
  auto ws7 = WhileStatement(7);
  auto expectedRelationship6 = FollowsRelationship(&rs6_2, &ws7);

  std::vector<FollowsRelationship *> expectedRelationships = {
      &expectedRelationship1, &expectedRelationship2, &expectedRelationship3,
      &expectedRelationship4, &expectedRelationship5, &expectedRelationship6};

  // for loop finds the relationship in the vector and compares it to the
  // expected relationship
  for (auto *relationship : *relationships) {
    bool found = false;
    for (auto *expectedRelationship : expectedRelationships) {
      found = found || PKBtestHelpers::relationshipEqualsRelationship(
                           relationship, expectedRelationship);
    }
    REQUIRE(found);
  }
}

TEST_CASE(
    "PKB can store multitple while parent statements relationships and "
    "retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeReadStatement(5);
  populateFacade->storeIfStatement(6);
  populateFacade->storeWhileStatement(7);

  populateFacade->storeIfStatement(8);
  populateFacade->storeAssignmentStatement(9);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeProcedure("Procedure1");

  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeParentRelationship(1, 3);
  populateFacade->storeParentRelationship(1, 4);
  populateFacade->storeParentRelationship(1, 5);
  populateFacade->storeParentRelationship(1, 6);
  populateFacade->storeParentRelationship(1, 7);

  // should not be returned
  populateFacade->storeParentRelationship(8, 9);
  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeStatementUsesVariableRelationship(2, "x");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");
  populateFacade->storeParentStarRelationship(1, 2);
  populateFacade->storeFollowsStarRelationship(2, 3);

  auto const *relationships =
      queryFacade->getRelationshipsByTypes(ParentRelationship::getRelationshipTypeStatic(),
                                           WhileStatement::getEntityTypeStatic(),
                                           Statement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 6);

  auto ws1_1 = WhileStatement(1);
  auto as2 = AssignStatement(2);
  auto expectedRelationship1 = ParentRelationship(&ws1_1, &as2);

  auto ws1_2 = WhileStatement(1);
  auto cs3 = CallStatement(3);
  auto expectedRelationship2 = ParentRelationship(&ws1_2, &cs3);

  auto ws1_3 = WhileStatement(1);
  auto ps4 = PrintStatement(4);
  auto expectedRelationship3 = ParentRelationship(&ws1_3, &ps4);

  auto ws1_4 = WhileStatement(1);
  auto rs5 = ReadStatement(5);
  auto expectedRelationship4 = ParentRelationship(&ws1_4, &rs5);

  auto ws1_5 = WhileStatement(1);
  auto is6 = IfStatement(6);
  auto expectedRelationship5 = ParentRelationship(&ws1_5, &is6);

  auto ws1_6 = WhileStatement(1);
  auto ws7 = WhileStatement(7);
  auto expectedRelationship6 = ParentRelationship(&ws1_6, &ws7);

  std::vector<ParentRelationship *> expectedRelationships = {
      &expectedRelationship1, &expectedRelationship2, &expectedRelationship3,
      &expectedRelationship4, &expectedRelationship5, &expectedRelationship6};

  // for loop finds the relationship in the vector and compares it to the
  // expected relationship

  for (auto *relationship : *relationships) {
    bool found = false;
    for (ParentRelationship *expectedRelationship : expectedRelationships) {
      found = found || PKBtestHelpers::relationshipEqualsRelationship(
                           relationship, expectedRelationship);
    }
    REQUIRE(found);
  }
}

TEST_CASE(
    "PKB can store multitple while parentStar statements relationships and "
    "retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeReadStatement(5);
  populateFacade->storeIfStatement(6);
  populateFacade->storeWhileStatement(7);

  populateFacade->storeIfStatement(8);
  populateFacade->storeAssignmentStatement(9);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeProcedure("Procedure1");

  populateFacade->storeParentStarRelationship(1, 2);
  populateFacade->storeParentStarRelationship(1, 3);
  populateFacade->storeParentStarRelationship(1, 4);
  populateFacade->storeParentStarRelationship(1, 5);
  populateFacade->storeParentStarRelationship(1, 6);
  populateFacade->storeParentStarRelationship(1, 7);

  // should not be returned
  populateFacade->storeParentRelationship(8, 9);
  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeStatementUsesVariableRelationship(2, "x");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeFollowsStarRelationship(2, 3);

  auto const *relationships =
      queryFacade->getRelationshipsByTypes(ParentStarRelationship::getRelationshipTypeStatic(),
                                           WhileStatement::getEntityTypeStatic(),
                                           Statement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 6);

  auto ws1_1 = WhileStatement(1);
  auto as2 = AssignStatement(2);
  auto expectedRelationship1 = ParentStarRelationship(&ws1_1, &as2);

  auto ws1_2 = WhileStatement(1);
  auto cs3 = CallStatement(3);
  auto expectedRelationship2 = ParentStarRelationship(&ws1_2, &cs3);

  auto ws1_3 = WhileStatement(1);
  auto ps4 = PrintStatement(4);
  auto expectedRelationship3 = ParentStarRelationship(&ws1_3, &ps4);

  auto ws1_4 = WhileStatement(1);
  auto rs5 = ReadStatement(5);
  auto expectedRelationship4 = ParentStarRelationship(&ws1_4, &rs5);

  auto ws1_5 = WhileStatement(1);
  auto is6 = IfStatement(6);
  auto expectedRelationship5 = ParentStarRelationship(&ws1_5, &is6);

  auto ws1_6 = WhileStatement(1);
  auto ws7 = WhileStatement(7);
  auto expectedRelationship6 = ParentStarRelationship(&ws1_6, &ws7);

  std::vector<ParentStarRelationship *> expectedRelationships = {
      &expectedRelationship1, &expectedRelationship2, &expectedRelationship3,
      &expectedRelationship4, &expectedRelationship5, &expectedRelationship6};

  // for loop finds the relationship in the vector and compares it to the
  // expected relationship

  for (auto *relationship : *relationships) {
    bool found = false;
    for (ParentStarRelationship *expectedRelationship : expectedRelationships) {
      found = found || PKBtestHelpers::relationshipEqualsRelationship(
                           relationship, expectedRelationship);
    }
    REQUIRE(found);
  }
}

TEST_CASE("PKB can store multiple Calls relationships and retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeReadStatement(5);
  populateFacade->storeIfStatement(6);
  populateFacade->storeWhileStatement(7);

  populateFacade->storeIfStatement(8);
  populateFacade->storeAssignmentStatement(9);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");

  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeProcedure("Procedure3");
  populateFacade->storeProcedure("Procedure4");
  populateFacade->storeProcedure("Procedure5");

  populateFacade->storeCallsRelationship("Procedure1", "Procedure2");
  populateFacade->storeCallsRelationship("Procedure1", "Procedure3");
  populateFacade->storeCallsRelationship("Procedure1", "Procedure4");
  populateFacade->storeCallsRelationship("Procedure1", "Procedure5");

  // should not be returned
  populateFacade->storeParentRelationship(8, 9);
  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeStatementUsesVariableRelationship(2, "x");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeFollowsStarRelationship(2, 3);
  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure2");

  auto const *relationships = queryFacade->getRelationshipsByTypes(CallsRelationship::getRelationshipTypeStatic(), Procedure::getEntityTypeStatic(), Procedure::getEntityTypeStatic());

  REQUIRE(relationships->size() == 4);

  auto proc_Procedure1_1 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure2 = Procedure(std::make_unique<std::string>("Procedure2"));
  auto expectedRelationship1 =
      CallsRelationship(&proc_Procedure1_1, &proc_Procedure2);

  auto proc_Procedure1_2 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure3 = Procedure(std::make_unique<std::string>("Procedure3"));
  auto expectedRelationship2 =
      CallsRelationship(&proc_Procedure1_2, &proc_Procedure3);

  auto proc_Procedure1_3 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure4 = Procedure(std::make_unique<std::string>("Procedure4"));
  auto expectedRelationship3 =
      CallsRelationship(&proc_Procedure1_3, &proc_Procedure4);

  auto proc_Procedure1_4 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure5 = Procedure(std::make_unique<std::string>("Procedure5"));
  auto expectedRelationship4 =
      CallsRelationship(&proc_Procedure1_4, &proc_Procedure5);

  std::vector<CallsRelationship *> expectedRelationships = {
      &expectedRelationship1, &expectedRelationship2, &expectedRelationship3,
      &expectedRelationship4};

  // for loop finds the relationship in the vector and compares it to the
  // expected relationship

  for (auto *relationship : *relationships) {
    bool found = false;
    for (CallsRelationship *expectedRelationship : expectedRelationships) {
      found = found || PKBtestHelpers::relationshipEqualsRelationship(
                           relationship, expectedRelationship);
    }
    REQUIRE(found);
  }
}

TEST_CASE(
    "PKB can store multiple CallsStar relationships and retrieve them all") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeReadStatement(5);
  populateFacade->storeIfStatement(6);
  populateFacade->storeWhileStatement(7);

  populateFacade->storeIfStatement(8);
  populateFacade->storeAssignmentStatement(9);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");

  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeProcedure("Procedure3");
  populateFacade->storeProcedure("Procedure4");
  populateFacade->storeProcedure("Procedure5");

  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure2");
  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure3");
  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure4");
  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure5");

  // should not be returned
  populateFacade->storeParentRelationship(8, 9);
  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeStatementUsesVariableRelationship(2, "x");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");
  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeFollowsStarRelationship(2, 3);
  populateFacade->storeCallsRelationship("Procedure1", "Procedure2");

  auto const *relationships = queryFacade->getRelationshipsByTypes(CallsStarRelationship::getRelationshipTypeStatic(), Procedure::getEntityTypeStatic(), Procedure::getEntityTypeStatic());

  REQUIRE(relationships->size() == 4);

  auto proc_Procedure1_1 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure2 = Procedure(std::make_unique<std::string>("Procedure2"));
  auto expectedRelationship1 =
      CallsStarRelationship(&proc_Procedure1_1, &proc_Procedure2);

  auto proc_Procedure1_2 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure3 = Procedure(std::make_unique<std::string>("Procedure3"));
  auto expectedRelationship2 =
      CallsStarRelationship(&proc_Procedure1_2, &proc_Procedure3);

  auto proc_Procedure1_3 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure4 = Procedure(std::make_unique<std::string>("Procedure4"));
  auto expectedRelationship3 =
      CallsStarRelationship(&proc_Procedure1_3, &proc_Procedure4);

  auto proc_Procedure1_4 =
      Procedure(std::make_unique<std::string>("Procedure1"));
  auto proc_Procedure5 = Procedure(std::make_unique<std::string>("Procedure5"));
  auto expectedRelationship4 =
      CallsStarRelationship(&proc_Procedure1_4, &proc_Procedure5);

  std::vector<CallsStarRelationship *> expectedRelationships = {
      &expectedRelationship1, &expectedRelationship2, &expectedRelationship3,
      &expectedRelationship4};

  // for loop finds the relationship in the vector and compares it to the
  // expected relationship

  for (auto *relationship : *relationships) {
    bool found = false;
    for (CallsStarRelationship *expectedRelationship : expectedRelationships) {
      found = found || PKBtestHelpers::relationshipEqualsRelationship(
                           relationship, expectedRelationship);
    }
    REQUIRE(found);
  }
}

TEST_CASE("PKB can store while and if statememt pattern information") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeIfStatement(2);
  populateFacade->storeWhileStatement(3);
  populateFacade->storeIfStatement(4);
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");

  populateFacade->storeUsesInParentConditionRelationship(1, "x");
  populateFacade->storeUsesInParentConditionRelationship(1, "x");

  populateFacade->storeUsesInParentConditionRelationship(3, "x");

  populateFacade->storeUsesInParentConditionRelationship(2, "y");
  populateFacade->storeUsesInParentConditionRelationship(2, "y");

  populateFacade->storeUsesInParentConditionRelationship(4, "y");
  populateFacade->storeUsesInParentConditionRelationship(4, "x");

  auto *whileStatements =
      queryFacade->getLeftEntitiesRelatedToGivenRightEntity(
          UsesInParentConditionRelationship::getRelationshipTypeStatic(), WhileStatement::getEntityTypeStatic(),
          Variable::getEntityTypeStatic(),
          "x");

  REQUIRE(whileStatements->size() == 2);

  // convert to array
  whileStatements->at(0)->equals(std::make_unique<WhileStatement>(1).get());
  whileStatements->at(1)->equals(std::make_unique<WhileStatement>(3).get());

  whileStatements =
      queryFacade->getLeftEntitiesRelatedToGivenRightEntity(
          UsesInParentConditionRelationship::getRelationshipTypeStatic(), WhileStatement::getEntityTypeStatic(),
          Variable::getEntityTypeStatic(),
          "y");

  REQUIRE(whileStatements->empty());

  auto *ifStatements =
      queryFacade->getLeftEntitiesRelatedToGivenRightEntity(
          UsesInParentConditionRelationship::getRelationshipTypeStatic(), IfStatement::getEntityTypeStatic(),
          Variable::getEntityTypeStatic(), "y");

  REQUIRE(ifStatements->size() == 2);
  // convert to array

  auto expectedIfStatement2 = std::make_unique<IfStatement>(2);
  auto expectedIfStatement4 = std::make_unique<IfStatement>(4);

  for (auto *ifStatement : *ifStatements) {
    bool found = false;
    found = found || ifStatement->equals(expectedIfStatement2.get());
    found = found || ifStatement->equals(expectedIfStatement4.get());
    REQUIRE(found);
  }

  ifStatements = queryFacade->getLeftEntitiesRelatedToGivenRightEntity(
      UsesInParentConditionRelationship::getRelationshipTypeStatic(), IfStatement::getEntityTypeStatic(),
      Variable::getEntityTypeStatic(), "x");

  REQUIRE(ifStatements->size() == 1);

  REQUIRE(ifStatements->at(0)->equals(expectedIfStatement4.get()));

  auto expectedVariableX =
      std::make_unique<Variable>(std::make_unique<std::string>("x"));
  auto expectedVariableY =
      std::make_unique<Variable>(std::make_unique<std::string>("y"));
  auto *ifVariables2 = queryFacade->getRightEntitiesRelatedToGivenLeftEntity(
      UsesInParentConditionRelationship::getRelationshipTypeStatic(), IfStatement::getEntityTypeStatic(), 2,
      Variable::getEntityTypeStatic());
  REQUIRE(ifVariables2->size() == 1);

  REQUIRE(ifVariables2->at(0)->equals(expectedVariableY.get()));

  auto *whileVariableSet1 =
      queryFacade->getRightEntitiesRelatedToGivenLeftEntity(
          UsesInParentConditionRelationship::getRelationshipTypeStatic(), WhileStatement::getEntityTypeStatic(),
          1, Variable::getEntityTypeStatic());
  REQUIRE(whileVariableSet1->size() == 1);

  REQUIRE(whileVariableSet1->at(0)->equals(expectedVariableX.get()));

  auto *ifVariables4 = queryFacade->getRightEntitiesRelatedToGivenLeftEntity(
      UsesInParentConditionRelationship::getRelationshipTypeStatic(), IfStatement::getEntityTypeStatic(), 4,
      Variable::getEntityTypeStatic());
  REQUIRE(ifVariables4->size() == 2);

  for (auto *variable : *ifVariables4) {
    bool found = false;
    found = found || variable->equals(expectedVariableX.get());
    found = found || variable->equals(expectedVariableY.get());
    REQUIRE(found);
  }

  auto *whileVariables3 =
      queryFacade->getRightEntitiesRelatedToGivenLeftEntity(
          UsesInParentConditionRelationship::getRelationshipTypeStatic(), WhileStatement::getEntityTypeStatic(),
          3, Variable::getEntityTypeStatic());

  REQUIRE(whileVariables3->size() == 1);

  REQUIRE(whileVariables3->at(0)->equals(expectedVariableX.get()));
}

TEST_CASE("Can add procedure name to calls") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  // Procedure1 calls Procedure2
  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeCallStatement(1);
  populateFacade->storeAssignmentStatement(2);

  populateFacade->storeAssignStatementPostfixExpression(2, "ab-");

  populateFacade->storeCallStatementProcedureName(1, "Procedure2");

  populateFacade->storeAssignStatementPostfixExpression(2, "ab-");

  populateFacade->storeCallStatementProcedureName(1, "Procedure2");

  populateFacade->storeCallsRelationship("Procedure1", "Procedure2");

  auto *callStatement = dynamic_cast<CallStatement *>(
      queryFacade->getEntity(CallStatement::getEntityTypeStatic(), 1));
  REQUIRE(*callStatement->getProcedureName() == "Procedure2");

  auto *assignStatement = dynamic_cast<AssignStatement *>(
      queryFacade->getEntity(AssignStatement::getEntityTypeStatic(), 2));

  REQUIRE(*assignStatement->getPostFixExpression() == "ab-");
}

TEST_CASE("PKB general query API works") {
  PKB pkb;
  PopulateFacade *populateFacade = pkb.getPopulateFacade();
  QueryFacade *queryFacade = pkb.getQueryFacade();

  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);
  populateFacade->storeWhileStatement(1);
  populateFacade->storeAssignmentStatement(2);
  populateFacade->storeCallStatement(3);
  populateFacade->storePrintStatement(4);

  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");
  populateFacade->storeVariable("x");
  populateFacade->storeVariable("y");

  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");
  populateFacade->storeProcedure("Procedure1");
  populateFacade->storeProcedure("Procedure2");

  populateFacade->storeParentRelationship(1, 2);
  populateFacade->storeParentRelationship(1, 3);
  populateFacade->storeParentRelationship(1, 4);

  populateFacade->storeFollowsRelationship(2, 3);
  populateFacade->storeFollowsRelationship(3, 4);

  populateFacade->storeFollowsStarRelationship(2, 3);

  populateFacade->storeStatementUsesVariableRelationship(2, "x");
  populateFacade->storeStatementUsesVariableRelationship(3, "y");
  populateFacade->storeStatementUsesVariableRelationship(3, "y");

  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeStatementModifiesVariableRelationship(2, "y");
  populateFacade->storeStatementModifiesVariableRelationship(3, "x");
  populateFacade->storeStatementModifiesVariableRelationship(3, "y");

  populateFacade->storeProcedureModifiesVariableRelationship("Procedure1", "x");

  populateFacade->storeCallsRelationship("Procedure1", "Procedure2");

  populateFacade->storeCallsStarRelationship("Procedure1", "Procedure2");

  std::vector<Entity *> *entities =
      queryFacade->getEntitiesByType(Statement::getEntityTypeStatic());

  REQUIRE(entities->size() == 4);

  auto *statement1 =
      queryFacade->getEntity(Statement::getEntityTypeStatic(), 1);
  auto *statement3 =
      queryFacade->getEntity(CallStatement::getEntityTypeStatic(), 3);
  REQUIRE(entities->at(0)->equals(statement1));
  REQUIRE(entities->at(1)->equals(std::make_unique<AssignStatement>(2).get()));
  REQUIRE(entities->at(2)->equals(statement3));
  REQUIRE(entities->at(3)->equals(std::make_unique<PrintStatement>(4).get()));

  entities = queryFacade->getEntitiesByType(Variable::getEntityTypeStatic());

  REQUIRE(entities->size() == 2);

  auto *variable1 =
      queryFacade->getEntity(Variable::getEntityTypeStatic(), "x");
  auto *variable2 =
      queryFacade->getEntity(Variable::getEntityTypeStatic(), "y");

  REQUIRE(entities->at(0)->equals(variable1));
  REQUIRE(entities->at(1)->equals(variable2));

  std::vector<Relationship *> *relationships =
      queryFacade->getRelationshipsByTypes(
          FollowsRelationship::getRelationshipTypeStatic(),
          Statement::getEntityTypeStatic(), Statement::getEntityTypeStatic());

  REQUIRE(relationships->size() == 2);

  REQUIRE(relationships->at(0)->equals(
      std::make_unique<FollowsRelationship>(
          std::make_unique<AssignStatement>(2).get(),
          std::make_unique<CallStatement>(3).get())
          .get()));
  REQUIRE(relationships->at(1)->equals(
      std::make_unique<FollowsRelationship>(
          std::make_unique<CallStatement>(3).get(),
          std::make_unique<PrintStatement>(4).get())
          .get()));

  std::vector<Relationship *> *relationships2 =
      queryFacade->getRelationshipsByTypes(
          UsesRelationship::getRelationshipTypeStatic(),
          Statement::getEntityTypeStatic(), Variable::getEntityTypeStatic());

  REQUIRE(relationships2->size() == 2);

  auto v_x = Variable(std::make_unique<std::string>("x"));
  REQUIRE(relationships2->at(0)->equals(
      std::make_unique<UsesRelationship>(
          std::make_unique<AssignStatement>(2).get(), &v_x)
          .get()));

  auto v_y = Variable(std::make_unique<std::string>("y"));
  REQUIRE(relationships2->at(1)->equals(
      std::make_unique<UsesRelationship>(
          std::make_unique<CallStatement>(3).get(), &v_y)
          .get()));

  std::vector<Relationship *> *relationships3 =
      queryFacade->getRelationshipsByTypes(
          ModifiesRelationship::getRelationshipTypeStatic(),
          CallStatement::getEntityTypeStatic(),
          Variable::getEntityTypeStatic());

  REQUIRE(relationships3->size() == 2);

  REQUIRE(relationships3->at(0)->equals(
      std::make_unique<ModifiesRelationship>(
          std::make_unique<CallStatement>(3).get(), &v_x)
          .get()));

  std::vector<Entity *> *entities2 =
      queryFacade->getRightEntitiesRelatedToGivenLeftEntity(
          ModifiesRelationship::getRelationshipTypeStatic(),
          Statement::getEntityTypeStatic(), 3, Variable::getEntityTypeStatic());

  REQUIRE(entities2->size() == 2);

  REQUIRE(entities2->at(0)->equals(&v_x));
  REQUIRE(entities2->at(1)->equals(&v_y));

  std::vector<Entity *> *entities3 =
      queryFacade->getLeftEntitiesRelatedToGivenRightEntity(
          UsesRelationship::getRelationshipTypeStatic(),
          Statement::getEntityTypeStatic(), Variable::getEntityTypeStatic(),
          "x");

  REQUIRE(entities3->size() == 1);
  REQUIRE(entities3->at(0)->equals(std::make_unique<AssignStatement>(2).get()));
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
