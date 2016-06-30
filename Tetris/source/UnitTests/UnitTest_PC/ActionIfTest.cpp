/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_ActionIfTestSuite_init = false;
#include "ActionIfTest.h"

static ActionIfTestSuite suite_ActionIfTestSuite;

static CxxTest::List Tests_ActionIfTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionIfTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ActionIfTest.h", 13, "ActionIfTestSuite", suite_ActionIfTestSuite, Tests_ActionIfTestSuite );

static class TestDescription_suite_ActionIfTestSuite_TestName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestName() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 40, "TestName" ) {}
 void runTest() { suite_ActionIfTestSuite.TestName(); }
} testDescription_suite_ActionIfTestSuite_TestName;

static class TestDescription_suite_ActionIfTestSuite_TestGetActions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestGetActions() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 49, "TestGetActions" ) {}
 void runTest() { suite_ActionIfTestSuite.TestGetActions(); }
} testDescription_suite_ActionIfTestSuite_TestGetActions;

static class TestDescription_suite_ActionIfTestSuite_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestUpdate() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 56, "TestUpdate" ) {}
 void runTest() { suite_ActionIfTestSuite.TestUpdate(); }
} testDescription_suite_ActionIfTestSuite_TestUpdate;

static class TestDescription_suite_ActionIfTestSuite_TestActionInEntity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestActionInEntity() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 64, "TestActionInEntity" ) {}
 void runTest() { suite_ActionIfTestSuite.TestActionInEntity(); }
} testDescription_suite_ActionIfTestSuite_TestActionInEntity;

static class TestDescription_suite_ActionIfTestSuite_TestActionFactory : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestActionFactory() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 75, "TestActionFactory" ) {}
 void runTest() { suite_ActionIfTestSuite.TestActionFactory(); }
} testDescription_suite_ActionIfTestSuite_TestActionFactory;

static class TestDescription_suite_ActionIfTestSuite_TestEntityCreateAction : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestEntityCreateAction() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 89, "TestEntityCreateAction" ) {}
 void runTest() { suite_ActionIfTestSuite.TestEntityCreateAction(); }
} testDescription_suite_ActionIfTestSuite_TestEntityCreateAction;

static class TestDescription_suite_ActionIfTestSuite_TestActionIf : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestActionIf() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 105, "TestActionIf" ) {}
 void runTest() { suite_ActionIfTestSuite.TestActionIf(); }
} testDescription_suite_ActionIfTestSuite_TestActionIf;

static class TestDescription_suite_ActionIfTestSuite_TestXMLParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionIfTestSuite_TestXMLParse() : CxxTest::RealTestDescription( Tests_ActionIfTestSuite, suiteDescription_ActionIfTestSuite, 118, "TestXMLParse" ) {}
 void runTest() { suite_ActionIfTestSuite.TestXMLParse(); }
} testDescription_suite_ActionIfTestSuite_TestXMLParse;

