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

bool suite_UniverseTestSuite_init = false;
#include "UniverseTest.h"

static UniverseTestSuite suite_UniverseTestSuite;

static CxxTest::List Tests_UniverseTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_UniverseTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/UniverseTest.h", 8, "UniverseTestSuite", suite_UniverseTestSuite, Tests_UniverseTestSuite );

static class TestDescription_suite_UniverseTestSuite_TestNames : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestNames() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 35, "TestNames" ) {}
 void runTest() { suite_UniverseTestSuite.TestNames(); }
} testDescription_suite_UniverseTestSuite_TestNames;

static class TestDescription_suite_UniverseTestSuite_TestWorldState : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestWorldState() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 47, "TestWorldState" ) {}
 void runTest() { suite_UniverseTestSuite.TestWorldState(); }
} testDescription_suite_UniverseTestSuite_TestWorldState;

static class TestDescription_suite_UniverseTestSuite_TestWorldCurState : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestWorldCurState() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 68, "TestWorldCurState" ) {}
 void runTest() { suite_UniverseTestSuite.TestWorldCurState(); }
} testDescription_suite_UniverseTestSuite_TestWorldCurState;

static class TestDescription_suite_UniverseTestSuite_TestEntityInSector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestEntityInSector() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 90, "TestEntityInSector" ) {}
 void runTest() { suite_UniverseTestSuite.TestEntityInSector(); }
} testDescription_suite_UniverseTestSuite_TestEntityInSector;

static class TestDescription_suite_UniverseTestSuite_TestSectorsInWorld : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestSectorsInWorld() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 102, "TestSectorsInWorld" ) {}
 void runTest() { suite_UniverseTestSuite.TestSectorsInWorld(); }
} testDescription_suite_UniverseTestSuite_TestSectorsInWorld;

static class TestDescription_suite_UniverseTestSuite_TestCreateEntity : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestCreateEntity() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 113, "TestCreateEntity" ) {}
 void runTest() { suite_UniverseTestSuite.TestCreateEntity(); }
} testDescription_suite_UniverseTestSuite_TestCreateEntity;

static class TestDescription_suite_UniverseTestSuite_TestCreateSector : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestCreateSector() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 123, "TestCreateSector" ) {}
 void runTest() { suite_UniverseTestSuite.TestCreateSector(); }
} testDescription_suite_UniverseTestSuite_TestCreateSector;

static class TestDescription_suite_UniverseTestSuite_TestUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_UniverseTestSuite_TestUpdate() : CxxTest::RealTestDescription( Tests_UniverseTestSuite, suiteDescription_UniverseTestSuite, 132, "TestUpdate" ) {}
 void runTest() { suite_UniverseTestSuite.TestUpdate(); }
} testDescription_suite_UniverseTestSuite_TestUpdate;

