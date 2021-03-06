/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafAgentThreadedTest.h,v $
Language:  C++
Date:      $Date: 2009-12-16 09:49:38 $
Version:   $Revision: 1.1.2.1 $
Authors:   Stefano Perticoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafAgentThreadedTest_H__
#define __CPP_UNIT_mafAgentThreadedTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

#include "mafObserver.h"

class mafEventBase;

class mafAgentThreadedTest : public CPPUNIT_NS::TestFixture
{
  public:
  
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( mafAgentThreadedTest );
  CPPUNIT_TEST( TestFixture );
  CPPUNIT_TEST( TestConstructorDestructor );
  CPPUNIT_TEST( TestSetGetThreaded );
  CPPUNIT_TEST( TestUpdate );
  CPPUNIT_TEST( TestAsyncSendEvent );
  CPPUNIT_TEST( TestAsyncInvokeEvent );

  CPPUNIT_TEST_SUITE_END();

  protected:
    
  void TestFixture();
  void TestConstructorDestructor();   
  void TestSetGetThreaded();
  void TestUpdate();
  void TestOnEvent();
  void TestAsyncSendEvent();
  void TestAsyncInvokeEvent();

};


class DummyObserver : public mafObserver
{
public:

  DummyObserver() {};
  ~DummyObserver() {};

  virtual void OnEvent(mafEventBase *maf_event);

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
  runner.addTest( mafAgentThreadedTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
