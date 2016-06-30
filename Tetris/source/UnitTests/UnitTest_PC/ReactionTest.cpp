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

bool suite_ReactionTestSuite_init = false;
#include "ReactionTest.h"

static ReactionTestSuite suite_ReactionTestSuite;

static CxxTest::List Tests_ReactionTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ReactionTestSuite( "C:/dev/Cohort11-Public/Classes/Programming II/Tetris/Tetris Engine/source/UnitTests/UnitTest_PC/ReactionTest.h", 13, "ReactionTestSuite", suite_ReactionTestSuite, Tests_ReactionTestSuite );

static class TestDescription_suite_ReactionTestSuite_TestMessageGetSet : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestMessageGetSet() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 40, "TestMessageGetSet" ) {}
 void runTest() { suite_ReactionTestSuite.TestMessageGetSet(); }
} testDescription_suite_ReactionTestSuite_TestMessageGetSet;

static class TestDescription_suite_ReactionTestSuite_TestMessageAttributes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestMessageAttributes() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 53, "TestMessageAttributes" ) {}
 void runTest() { suite_ReactionTestSuite.TestMessageAttributes(); }
} testDescription_suite_ReactionTestSuite_TestMessageAttributes;

static class TestDescription_suite_ReactionTestSuite_TestReactionAttributed : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestReactionAttributed() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 69, "TestReactionAttributed" ) {}
 void runTest() { suite_ReactionTestSuite.TestReactionAttributed(); }
} testDescription_suite_ReactionTestSuite_TestReactionAttributed;

static class TestDescription_suite_ReactionTestSuite_TestActionEventInstantiation : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestActionEventInstantiation() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 144, "TestActionEventInstantiation" ) {}
 void runTest() { suite_ReactionTestSuite.TestActionEventInstantiation(); }
} testDescription_suite_ReactionTestSuite_TestActionEventInstantiation;

static class TestDescription_suite_ReactionTestSuite_TestActionEventSubtypeArgs : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestActionEventSubtypeArgs() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 192, "TestActionEventSubtypeArgs" ) {}
 void runTest() { suite_ReactionTestSuite.TestActionEventSubtypeArgs(); }
} testDescription_suite_ReactionTestSuite_TestActionEventSubtypeArgs;

static class TestDescription_suite_ReactionTestSuite_TestActionEventUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestActionEventUpdate() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 206, "TestActionEventUpdate" ) {}
 void runTest() { suite_ReactionTestSuite.TestActionEventUpdate(); }
} testDescription_suite_ReactionTestSuite_TestActionEventUpdate;

static class TestDescription_suite_ReactionTestSuite_TestEmptyActionEventUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestEmptyActionEventUpdate() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 266, "TestEmptyActionEventUpdate" ) {}
 void runTest() { suite_ReactionTestSuite.TestEmptyActionEventUpdate(); }
} testDescription_suite_ReactionTestSuite_TestEmptyActionEventUpdate;

static class TestDescription_suite_ReactionTestSuite_TestFactories : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestFactories() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 304, "TestFactories" ) {}
 void runTest() { suite_ReactionTestSuite.TestFactories(); }
} testDescription_suite_ReactionTestSuite_TestFactories;

static class TestDescription_suite_ReactionTestSuite_TestParseEmpty : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestParseEmpty() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 341, "TestParseEmpty" ) {}
 void runTest() { suite_ReactionTestSuite.TestParseEmpty(); }
} testDescription_suite_ReactionTestSuite_TestParseEmpty;

static class TestDescription_suite_ReactionTestSuite_TestMultipleSubtypes : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestMultipleSubtypes() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 395, "TestMultipleSubtypes" ) {}
 void runTest() { suite_ReactionTestSuite.TestMultipleSubtypes(); }
} testDescription_suite_ReactionTestSuite_TestMultipleSubtypes;

static class TestDescription_suite_ReactionTestSuite_TestParseWithArgs : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestParseWithArgs() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 437, "TestParseWithArgs" ) {}
 void runTest() { suite_ReactionTestSuite.TestParseWithArgs(); }
} testDescription_suite_ReactionTestSuite_TestParseWithArgs;

static class TestDescription_suite_ReactionTestSuite_TestParseReactionActionList : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestParseReactionActionList() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 504, "TestParseReactionActionList" ) {}
 void runTest() { suite_ReactionTestSuite.TestParseReactionActionList(); }
} testDescription_suite_ReactionTestSuite_TestParseReactionActionList;

static class TestDescription_suite_ReactionTestSuite_TestFullSystemParse : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestFullSystemParse() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 574, "TestFullSystemParse" ) {}
 void runTest() { suite_ReactionTestSuite.TestFullSystemParse(); }
} testDescription_suite_ReactionTestSuite_TestFullSystemParse;

static class TestDescription_suite_ReactionTestSuite_TestMultipleReactionsAndEvents : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_ReactionTestSuite_TestMultipleReactionsAndEvents() : CxxTest::RealTestDescription( Tests_ReactionTestSuite, suiteDescription_ReactionTestSuite, 658, "TestMultipleReactionsAndEvents" ) {}
 void runTest() { suite_ReactionTestSuite.TestMultipleReactionsAndEvents(); }
} testDescription_suite_ReactionTestSuite_TestMultipleReactionsAndEvents;

