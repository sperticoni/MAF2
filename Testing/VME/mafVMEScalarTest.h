/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafVMEScalarTest.h,v $
Language:  C++
Date:      $Date: 2008-01-24 12:30:22 $
Version:   $Revision: 1.6 $
Authors:   Paolo Quadrani
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_MAFVMESCALARTEST_H__
#define __CPP_UNIT_MAFVMESCALARTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

/** Test for mafVMEScalarMatrix.*/
class mafVMEScalarTest : public CPPUNIT_NS::TestFixture
{
public: 

  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( mafVMEScalarTest );
  CPPUNIT_TEST( TestFixture ); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestVMEScalarFactory );
  CPPUNIT_TEST( TestCopyVMEScalar );
  CPPUNIT_TEST( TestVMEScalarData );
  CPPUNIT_TEST( TestAnimatedVMEScalar );
  CPPUNIT_TEST_SUITE_END();

private:
  void TestFixture();
  void TestVMEScalarFactory();
  void TestCopyVMEScalar();
  void TestVMEScalarData();
  void TestAnimatedVMEScalar();
};

int main(int argc, char* argv[])
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that collects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest(mafVMEScalarTest::suite());
  runner.run(controller);

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}
#endif
