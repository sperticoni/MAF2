/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpCutTest.h,v $
Language:  C++
Date:      $Date: 2010-06-04 12:55:32 $
Version:   $Revision: 1.1.2.2 $
Authors:   Matteo Giacomoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafOpCutTest_H__
#define __CPP_UNIT_mafOpCutTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

//forward reference
class mafOpCut;

/** Test for mafMatrix; Use this suite to trace memory problems */
class mafOpCutTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  // CPPUNIT test suite
  CPPUNIT_TEST_SUITE( mafOpCutTest );
  CPPUNIT_TEST( TestFixture ); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestOpDo );
  CPPUNIT_TEST( TestOpUndo );
  CPPUNIT_TEST( TestOpDoVMETimeVarying );
  CPPUNIT_TEST( TestOpUndoVMETimeVarying );
  CPPUNIT_TEST( TestOpUndoVMEWithChildren );
  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
  void TestOpDo();
  void TestOpUndo();
  void TestOpDoVMETimeVarying();
  void TestOpUndoVMETimeVarying();
  void TestOpUndoVMEWithChildren();

  mafOpCut *m_OpCut;
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
  runner.addTest( mafOpCutTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif
