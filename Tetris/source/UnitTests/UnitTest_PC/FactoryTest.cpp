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

bool suite_FactoryTestSuite_init = false;
#include "FactoryTest.h"

static FactoryTestSuite suite_FactoryTestSuite;

static CxxTest::List Tests_FactoryTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_FactoryTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/FactoryTest.h", 12, "FactoryTestSuite", suite_FactoryTestSuite, Tests_FactoryTestSuite );

static class TestDescription_suite_FactoryTestSuite_TestName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestName() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 46, "TestName" ) {}
 void runTest() { suite_FactoryTestSuite.TestName(); }
} testDescription_suite_FactoryTestSuite_TestName;

static class TestDescription_suite_FactoryTestSuite_TestFind : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestFind() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 52, "TestFind" ) {}
 void runTest() { suite_FactoryTestSuite.TestFind(); }
} testDescription_suite_FactoryTestSuite_TestFind;

static class TestDescription_suite_FactoryTestSuite_TestCreate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestCreate() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 63, "TestCreate" ) {}
 void runTest() { suite_FactoryTestSuite.TestCreate(); }
} testDescription_suite_FactoryTestSuite_TestCreate;

static class TestDescription_suite_FactoryTestSuite_TestCreateFromName : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestCreateFromName() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 97, "TestCreateFromName" ) {}
 void runTest() { suite_FactoryTestSuite.TestCreateFromName(); }
} testDescription_suite_FactoryTestSuite_TestCreateFromName;

static class TestDescription_suite_FactoryTestSuite_TestBegin : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestBegin() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 131, "TestBegin" ) {}
 void runTest() { suite_FactoryTestSuite.TestBegin(); }
} testDescription_suite_FactoryTestSuite_TestBegin;

static class TestDescription_suite_FactoryTestSuite_TestEnd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestEnd() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 138, "TestEnd" ) {}
 void runTest() { suite_FactoryTestSuite.TestEnd(); }
} testDescription_suite_FactoryTestSuite_TestEnd;

static class TestDescription_suite_FactoryTestSuite_TestIteration : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_FactoryTestSuite_TestIteration() : CxxTest::RealTestDescription( Tests_FactoryTestSuite, suiteDescription_FactoryTestSuite, 145, "TestIteration" ) {}
 void runTest() { suite_FactoryTestSuite.TestIteration(); }
} testDescription_suite_FactoryTestSuite_TestIteration;

