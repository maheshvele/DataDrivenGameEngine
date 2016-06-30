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

bool suite_XMLTestSuite_init = false;
#include "XMLTests.h"

static XMLTestSuite suite_XMLTestSuite;

static CxxTest::List Tests_XMLTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_XMLTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/XMLTests.h", 10, "XMLTestSuite", suite_XMLTestSuite, Tests_XMLTestSuite );

static class TestDescription_suite_XMLTestSuite_TestSharedData : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestSharedData() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 36, "TestSharedData" ) {}
 void runTest() { suite_XMLTestSuite.TestSharedData(); }
} testDescription_suite_XMLTestSuite_TestSharedData;

static class TestDescription_suite_XMLTestSuite_TestParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestParse() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 62, "TestParse" ) {}
 void runTest() { suite_XMLTestSuite.TestParse(); }
} testDescription_suite_XMLTestSuite_TestParse;

static class TestDescription_suite_XMLTestSuite_TestNestedParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestNestedParse() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 78, "TestNestedParse" ) {}
 void runTest() { suite_XMLTestSuite.TestNestedParse(); }
} testDescription_suite_XMLTestSuite_TestNestedParse;

static class TestDescription_suite_XMLTestSuite_TestAttributes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestAttributes() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 100, "TestAttributes" ) {}
 void runTest() { suite_XMLTestSuite.TestAttributes(); }
} testDescription_suite_XMLTestSuite_TestAttributes;

static class TestDescription_suite_XMLTestSuite_TestFile : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestFile() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 119, "TestFile" ) {}
 void runTest() { suite_XMLTestSuite.TestFile(); }
} testDescription_suite_XMLTestSuite_TestFile;

static class TestDescription_suite_XMLTestSuite_TestClone : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestClone() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 141, "TestClone" ) {}
 void runTest() { suite_XMLTestSuite.TestClone(); }
} testDescription_suite_XMLTestSuite_TestClone;

static class TestDescription_suite_XMLTestSuite_TestExceptions : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_XMLTestSuite_TestExceptions() : CxxTest::RealTestDescription( Tests_XMLTestSuite, suiteDescription_XMLTestSuite, 169, "TestExceptions" ) {}
 void runTest() { suite_XMLTestSuite.TestExceptions(); }
} testDescription_suite_XMLTestSuite_TestExceptions;

