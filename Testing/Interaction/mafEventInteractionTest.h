/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafEventInteractionTest.h,v $
Language:  C++
Date:      $Date: 2009-09-14 12:02:55 $
Version:   $Revision: 1.1.2.1 $
Authors:   Daniele Giunchi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafEventInteractionTest_H__
#define __CPP_UNIT_mafEventInteractionTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

/** 
  class name mafEventInteraction 
  Use this suite to trace memory problems 
*/
class mafEventInteractionTest : public CPPUNIT_NS::TestFixture
{
public: 
  /** CPPUNIT fixture: executed before each test */
  void setUp();

  /** CPPUNIT fixture: executed after each test */ 
  void tearDown();

  /** CPPUNIT test suite */
  CPPUNIT_TEST_SUITE( mafEventInteractionTest );
  /** CPPUNIT test : static allocation */
  CPPUNIT_TEST(TestStaticAllocation);
  /** CPPUNIT test : dynamic allocation */
  CPPUNIT_TEST(TestDynamicAllocation);
  /** CPPUNIT test : set/get position */
  CPPUNIT_TEST(TestSet2DPosition_Get2DPosition);
  /** CPPUNIT test : set/get xyflag */
  CPPUNIT_TEST(TestSetXYFlag_GetXYFlag);
  /** CPPUNIT test : set/get button */
  CPPUNIT_TEST(TestSetButton_GetButton);
  /** CPPUNIT test : set/get key */
  CPPUNIT_TEST(TestSetKey_GetKey);
  /** CPPUNIT test : set/get matrix */
  CPPUNIT_TEST(TestSetMatrix_GetMatrix);
  /** CPPUNIT test : set/get modifier */
  CPPUNIT_TEST(TestSetModifier_GetModifier);
  /** CPPUNIT test : set/get modifiers */
  CPPUNIT_TEST(TestSetModifiers_GetModifiers);
  /** CPPUNIT test : deepcopy of the object */
  CPPUNIT_TEST(TestDeepCopy);
  /** CPPUNIT end test suite */
  CPPUNIT_TEST_SUITE_END();
  

private:
  /** static allocation */
  void TestStaticAllocation();
  /** dynamic allocation */
  void TestDynamicAllocation();
  /** set/get position */
  void TestSet2DPosition_Get2DPosition();
  /** set/get xyflag */
  void TestSetXYFlag_GetXYFlag();
  /** set/get button */
  void TestSetButton_GetButton();
  /** set/get key */
  void TestSetKey_GetKey();
  /** set/get matrix */
  void TestSetMatrix_GetMatrix();
  /** set/get modifier */
  void TestSetModifier_GetModifier();
  /** set/get modifiers */
  void TestSetModifiers_GetModifiers();
  /** deepcopy of the object */
  void TestDeepCopy();

  enum
  {
    ID_MODIFIER_1 = 1,
    ID_MODIFIER_2,
  };
  enum
  {
    ID_KEY_1,
    ID_KEY_2,
  };
  enum
  {
    ID_BUTTON_LEFT,
    ID_BUTTON_RIGHT,
  };
};

int
main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that collects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( mafEventInteractionTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif
