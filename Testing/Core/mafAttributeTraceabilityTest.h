/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafAttributeTraceabilityTest.h,v $
Language:  C++
Date:      $Date: 2008-11-17 11:30:45 $
Version:   $Revision: 1.1.2.1 $
Authors:   Roberto Mucci
==========================================================================
  Copyright (c) 2002/2008
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafAttributeTraceability_H__
#define __CPP_UNIT_mafAttributeTraceability_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

/** Test for mafAttributeTraceability; Use this suite to trace memory problems */
class mafAttributeTraceabilityTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  // CPPUNIT test suite
  CPPUNIT_TEST_SUITE( mafAttributeTraceabilityTest );
  CPPUNIT_TEST(TestFixture); // just to test that the fixture has no leaks
  CPPUNIT_TEST(TestAddTraceabilityEvent);
  CPPUNIT_TEST(TestRemoveTraceabilityEvent);
  CPPUNIT_TEST(TestGetLastTrialEvent);
  CPPUNIT_TEST(TestStaticAllocation);
  CPPUNIT_TEST(TestDynamicAllocation);
  CPPUNIT_TEST(TestDeepCopy);
  CPPUNIT_TEST(TestEquals);


  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
  void TestStaticAllocation();
  void TestDynamicAllocation();
  void TestAddTraceabilityEvent();
  void TestRemoveTraceabilityEvent();
  void TestGetLastTrialEvent();
  void TestDeepCopy();
  void TestEquals();


  bool result;
};

int main( int argc, char* argv[] )
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
  runner.addTest( mafAttributeTraceabilityTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif
