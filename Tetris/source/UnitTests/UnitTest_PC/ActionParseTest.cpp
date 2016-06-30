/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_ActionParseTestSuite_init = false;
#include "ActionParseTest.h"

static ActionParseTestSuite suite_ActionParseTestSuite;

static CxxTest::List Tests_ActionParseTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ActionParseTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ActionParseTest.h", 7, "ActionParseTestSuite", suite_ActionParseTestSuite, Tests_ActionParseTestSuite );

static class TestDescription_suite_ActionParseTestSuite_TestParseActionList : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestParseActionList() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 34, "TestParseActionList" ) {}
 void runTest() { suite_ActionParseTestSuite.TestParseActionList(); }
} testDescription_suite_ActionParseTestSuite_TestParseActionList;

static class TestDescription_suite_ActionParseTestSuite_TestParseNestedActionList : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestParseNestedActionList() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 72, "TestParseNestedActionList" ) {}
 void runTest() { suite_ActionParseTestSuite.TestParseNestedActionList(); }
} testDescription_suite_ActionParseTestSuite_TestParseNestedActionList;

static class TestDescription_suite_ActionParseTestSuite_TestActionCreateActionParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestActionCreateActionParse() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 111, "TestActionCreateActionParse" ) {}
 void runTest() { suite_ActionParseTestSuite.TestActionCreateActionParse(); }
} testDescription_suite_ActionParseTestSuite_TestActionCreateActionParse;

static class TestDescription_suite_ActionParseTestSuite_TestActionDestroyActionParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestActionDestroyActionParse() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 157, "TestActionDestroyActionParse" ) {}
 void runTest() { suite_ActionParseTestSuite.TestActionDestroyActionParse(); }
} testDescription_suite_ActionParseTestSuite_TestActionDestroyActionParse;

static class TestDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInEntity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInEntity() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 198, "TestEmptyActionExpressionInEntity" ) {}
 void runTest() { suite_ActionParseTestSuite.TestEmptyActionExpressionInEntity(); }
} testDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInEntity;

static class TestDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInActionList : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInActionList() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 235, "TestEmptyActionExpressionInActionList" ) {}
 void runTest() { suite_ActionParseTestSuite.TestEmptyActionExpressionInActionList(); }
} testDescription_suite_ActionParseTestSuite_TestEmptyActionExpressionInActionList;

static class TestDescription_suite_ActionParseTestSuite_TestIntegerActionExpression : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestIntegerActionExpression() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 276, "TestIntegerActionExpression" ) {}
 void runTest() { suite_ActionParseTestSuite.TestIntegerActionExpression(); }
} testDescription_suite_ActionParseTestSuite_TestIntegerActionExpression;

static class TestDescription_suite_ActionParseTestSuite_TestFloatActionExpression : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestFloatActionExpression() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 384, "TestFloatActionExpression" ) {}
 void runTest() { suite_ActionParseTestSuite.TestFloatActionExpression(); }
} testDescription_suite_ActionParseTestSuite_TestFloatActionExpression;

static class TestDescription_suite_ActionParseTestSuite_TestNestedExpressions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ActionParseTestSuite_TestNestedExpressions() : CxxTest::RealTestDescription( Tests_ActionParseTestSuite, suiteDescription_ActionParseTestSuite, 456, "TestNestedExpressions" ) {}
 void runTest() { suite_ActionParseTestSuite.TestNestedExpressions(); }
} testDescription_suite_ActionParseTestSuite_TestNestedExpressions;

