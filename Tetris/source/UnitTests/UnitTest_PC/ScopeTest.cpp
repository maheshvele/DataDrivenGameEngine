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
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>

bool suite_ScopeTestSuite_init = false;
#include "ScopeTest.h"

static ScopeTestSuite suite_ScopeTestSuite;

static CxxTest::List Tests_ScopeTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ScopeTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ScopeTest.h", 9, "ScopeTestSuite", suite_ScopeTestSuite, Tests_ScopeTestSuite );

static class TestDescription_suite_ScopeTestSuite_TestOrphan : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestOrphan() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 36, "TestOrphan" ) {}
 void runTest() { suite_ScopeTestSuite.TestOrphan(); }
} testDescription_suite_ScopeTestSuite_TestOrphan;

static class TestDescription_suite_ScopeTestSuite_TestAppend : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestAppend() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 61, "TestAppend" ) {}
 void runTest() { suite_ScopeTestSuite.TestAppend(); }
} testDescription_suite_ScopeTestSuite_TestAppend;

static class TestDescription_suite_ScopeTestSuite_TestFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestFind() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 72, "TestFind" ) {}
 void runTest() { suite_ScopeTestSuite.TestFind(); }
} testDescription_suite_ScopeTestSuite_TestFind;

static class TestDescription_suite_ScopeTestSuite_TestBrackets : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestBrackets() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 82, "TestBrackets" ) {}
 void runTest() { suite_ScopeTestSuite.TestBrackets(); }
} testDescription_suite_ScopeTestSuite_TestBrackets;

static class TestDescription_suite_ScopeTestSuite_TestDatumOfScope : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestDatumOfScope() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 92, "TestDatumOfScope" ) {}
 void runTest() { suite_ScopeTestSuite.TestDatumOfScope(); }
} testDescription_suite_ScopeTestSuite_TestDatumOfScope;

static class TestDescription_suite_ScopeTestSuite_TestAdopt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestAdopt() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 109, "TestAdopt" ) {}
 void runTest() { suite_ScopeTestSuite.TestAdopt(); }
} testDescription_suite_ScopeTestSuite_TestAdopt;

static class TestDescription_suite_ScopeTestSuite_TestAppendScope : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestAppendScope() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 127, "TestAppendScope" ) {}
 void runTest() { suite_ScopeTestSuite.TestAppendScope(); }
} testDescription_suite_ScopeTestSuite_TestAppendScope;

static class TestDescription_suite_ScopeTestSuite_TestFindName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestFindName() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 142, "TestFindName" ) {}
 void runTest() { suite_ScopeTestSuite.TestFindName(); }
} testDescription_suite_ScopeTestSuite_TestFindName;

static class TestDescription_suite_ScopeTestSuite_TestSearch : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestSearch() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 159, "TestSearch" ) {}
 void runTest() { suite_ScopeTestSuite.TestSearch(); }
} testDescription_suite_ScopeTestSuite_TestSearch;

static class TestDescription_suite_ScopeTestSuite_TestAssignmentAndCopy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestAssignmentAndCopy() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 177, "TestAssignmentAndCopy" ) {}
 void runTest() { suite_ScopeTestSuite.TestAssignmentAndCopy(); }
} testDescription_suite_ScopeTestSuite_TestAssignmentAndCopy;

static class TestDescription_suite_ScopeTestSuite_TestEquality : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ScopeTestSuite_TestEquality() : CxxTest::RealTestDescription( Tests_ScopeTestSuite, suiteDescription_ScopeTestSuite, 213, "TestEquality" ) {}
 void runTest() { suite_ScopeTestSuite.TestEquality(); }
} testDescription_suite_ScopeTestSuite_TestEquality;

