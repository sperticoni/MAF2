/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpDecomposeTimeVarVMETest.h,v $
Language:  C++
Date:      $Date: 2007-11-21 15:38:57 $
Version:   $Revision: 1.1 $
Authors:   Roberto Mucci
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef CPP_UNIT_MAFOPDECOMPOSETIMEVARVMETEST_H
#define CPP_UNIT_MAFOPDECOMPOSETIMEVARVMETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>


class mafOpDecomposeTimeVarVMETest : public CPPUNIT_NS::TestFixture
{
public:

  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( mafOpDecomposeTimeVarVMETest );
  CPPUNIT_TEST( TestFixture ); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestConstructor );
  CPPUNIT_TEST( TestModeTimeStampsVME );
  CPPUNIT_TEST( TestModeIntervalVME );
  CPPUNIT_TEST( TestModePeriodicityVME );
  CPPUNIT_TEST_SUITE_END();

protected:
  void TestFixture();
  void TestConstructor();
  void TestModeTimeStampsVME();
  void TestModeIntervalVME();
  void TestModePeriodicityVME();
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
  runner.addTest( mafOpDecomposeTimeVarVMETest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
