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

bool suite_AttributedTestSuite_init = false;
#include "AttributedTest.h"

static AttributedTestSuite suite_AttributedTestSuite;

static CxxTest::List Tests_AttributedTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_AttributedTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/AttributedTest.h", 9, "AttributedTestSuite", suite_AttributedTestSuite, Tests_AttributedTestSuite );

static class TestDescription_suite_AttributedTestSuite_TestIsAttribute : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestIsAttribute() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 37, "TestIsAttribute" ) {}
 void runTest() { suite_AttributedTestSuite.TestIsAttribute(); }
} testDescription_suite_AttributedTestSuite_TestIsAttribute;

static class TestDescription_suite_AttributedTestSuite_TestInternalValues : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestInternalValues() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 71, "TestInternalValues" ) {}
 void runTest() { suite_AttributedTestSuite.TestInternalValues(); }
} testDescription_suite_AttributedTestSuite_TestInternalValues;

static class TestDescription_suite_AttributedTestSuite_TestExternalValues : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestExternalValues() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 130, "TestExternalValues" ) {}
 void runTest() { suite_AttributedTestSuite.TestExternalValues(); }
} testDescription_suite_AttributedTestSuite_TestExternalValues;

static class TestDescription_suite_AttributedTestSuite_TestCopies : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestCopies() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 184, "TestCopies" ) {}
 void runTest() { suite_AttributedTestSuite.TestCopies(); }
} testDescription_suite_AttributedTestSuite_TestCopies;

static class TestDescription_suite_AttributedTestSuite_TestAuxiliaryBegin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestAuxiliaryBegin() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 199, "TestAuxiliaryBegin" ) {}
 void runTest() { suite_AttributedTestSuite.TestAuxiliaryBegin(); }
} testDescription_suite_AttributedTestSuite_TestAuxiliaryBegin;

static class TestDescription_suite_AttributedTestSuite_TestPerscribed : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestPerscribed() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 210, "TestPerscribed" ) {}
 void runTest() { suite_AttributedTestSuite.TestPerscribed(); }
} testDescription_suite_AttributedTestSuite_TestPerscribed;

static class TestDescription_suite_AttributedTestSuite_TestAppendAuxiliary : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_AttributedTestSuite_TestAppendAuxiliary() : CxxTest::RealTestDescription( Tests_AttributedTestSuite, suiteDescription_AttributedTestSuite, 269, "TestAppendAuxiliary" ) {}
 void runTest() { suite_AttributedTestSuite.TestAppendAuxiliary(); }
} testDescription_suite_AttributedTestSuite_TestAppendAuxiliary;

