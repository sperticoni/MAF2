/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafInteractorTest.h,v $
Language:  C++
Date:      $Date: 2010-03-17 13:11:08 $
Version:   $Revision: 1.1.2.1 $
Authors:   Alberto Losi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafInteractorPERTest_H__
#define __CPP_UNIT_mafInteractorPERTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class mafInteractorTest : public CPPUNIT_NS::TestFixture
{
public:
  
  /** CPPUNIT fixture: executed before each test */
  void setUp();

  /** CPPUNIT fixture: executed after each test */
  void tearDown();

  CPPUNIT_TEST_SUITE( mafInteractorTest );
  CPPUNIT_TEST( TestFixture );
  CPPUNIT_TEST( TestConstructorDestructor );
  CPPUNIT_TEST( TestSetGetRenderer );
  CPPUNIT_TEST( TestSetGetDevice );
  CPPUNIT_TEST( TestSetGetIgnoreTriggerEvents );
  CPPUNIT_TEST( TestSetGetStartInteractionEvent );
  CPPUNIT_TEST( TestSetGetStopInteractionEvent );
  CPPUNIT_TEST( TestSetGetStartButton );
  CPPUNIT_TEST( TestSetGetModifiers );
  CPPUNIT_TEST( TestGetCurrentButton );
  CPPUNIT_TEST( TestGetCurrentModifier );
  CPPUNIT_TEST( TestStartStopInteraction );
  CPPUNIT_TEST( TestIsInteracting );
  CPPUNIT_TEST( TestSetGetButtonMode );
  CPPUNIT_TEST( TestSetGetLockDevice );
  CPPUNIT_TEST_SUITE_END();

protected:
  
  void TestFixture();
  void TestConstructorDestructor();
  void TestSetGetRenderer();
  void TestSetGetDevice();
  void TestSetGetIgnoreTriggerEvents();
  void TestSetGetStartInteractionEvent();
  void TestSetGetStopInteractionEvent();
  void TestSetGetStartButton();
  void TestSetGetModifiers();
  void TestGetCurrentButton();
  void TestGetCurrentModifier();
  void TestStartStopInteraction();
  void TestIsInteracting();
  void TestSetGetButtonMode();
  void TestSetGetLockDevice();

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
  runner.addTest( mafInteractorTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
