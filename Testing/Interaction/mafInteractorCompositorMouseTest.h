/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafInteractorCompositorMouseTest.h,v $
Language:  C++
Date:      $Date: 2009-12-17 11:48:24 $
Version:   $Revision: 1.1.2.1 $
Authors:   Stefano Perticoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafInteractorCompositorMouseTest_H__
#define __CPP_UNIT_mafInteractorCompositorMouseTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class mafInteractorCompositorMouseTest : public CPPUNIT_NS::TestFixture
{
  public:
  
  /** CPPUNIT fixture: executed before each test */
  void setUp();

  /** CPPUNIT fixture: executed after each test */
  void tearDown();

  CPPUNIT_TEST_SUITE( mafInteractorCompositorMouseTest );
  
  CPPUNIT_TEST(TestFixture);
  CPPUNIT_TEST(TestConstructorDestructor);
  CPPUNIT_TEST(TestStartInteraction);
  CPPUNIT_TEST(TestOnEvent);
  CPPUNIT_TEST(TestCreateBehavior);
  CPPUNIT_TEST(TestGetBehavior);
  CPPUNIT_TEST_SUITE_END();

  protected:
    
    void TestFixture();
    void TestConstructorDestructor();   
    void TestStartInteraction();
    void TestOnEvent();
    void TestCreateBehavior();
    void TestGetBehavior();    
};


int
main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( mafInteractorCompositorMouseTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
