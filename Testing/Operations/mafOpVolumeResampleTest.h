/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpVolumeResampleTest.h,v $
Language:  C++
Date:      $Date: 2008-03-06 12:01:16 $
Version:   $Revision: 1.1 $
Authors:   Matteo Giacomoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_MMOVOLUMERESAMPLETEST_H__
#define __CPP_UNIT_MMOVOLUMERESAMPLETEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>



class mafOpVolumeResampleTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( mafOpVolumeResampleTest );
  CPPUNIT_TEST( TestBase );
	CPPUNIT_TEST( TestVMELocalBounds );
	CPPUNIT_TEST( TestVME4DBounds );
	CPPUNIT_TEST( TestVMEBounds );
	CPPUNIT_TEST( TestScalarRange );
  CPPUNIT_TEST_SUITE_END();

  protected:
    void TestBase();
		void TestVMELocalBounds();
		void TestVME4DBounds();
		void TestVMEBounds();
		void TestScalarRange();
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
  runner.addTest( mafOpVolumeResampleTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
