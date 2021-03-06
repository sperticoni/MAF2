/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafVMEInfoTextTest.h,v $
Language:  C++
Date:      $Date: 2009-01-19 11:58:58 $
Version:   $Revision: 1.1.2.1 $
Authors:   Daniele Giunchi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafVMEInfoTextTEST_H__
#define __CPP_UNIT_mafVMEInfoTextTEST_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class vtkPolyData;

class mafVMEInfoTextTest : public CPPUNIT_NS::TestFixture
{
public :
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

	CPPUNIT_TEST_SUITE( mafVMEInfoTextTest );
  CPPUNIT_TEST( TestDynamicAllocation );
	CPPUNIT_TEST( TestGetVTKOutput );
  CPPUNIT_TEST( TestGetOutput );
  CPPUNIT_TEST( TestAddString );
  CPPUNIT_TEST( TestGetSetPosShow );
  CPPUNIT_TEST( TestGetSetPosLabel );
  CPPUNIT_TEST( TestSetTimeStamp );
  CPPUNIT_TEST( TestGetIcon );
  CPPUNIT_TEST( TestDeepCopy );
  CPPUNIT_TEST( TestEquals );
	CPPUNIT_TEST_SUITE_END();

protected:
  void TestDynamicAllocation();
	void TestGetVTKOutput();
  void TestGetOutput();
  void TestAddString();
  void TestGetSetPosShow();
  void TestGetSetPosLabel();
  void TestSetTimeStamp();
  void TestGetIcon();
  void TestDeepCopy();
  void TestEquals();

  bool result;
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
	runner.addTest( mafVMEInfoTextTest::suite());
	runner.run( controller );

	// Print test in a compiler compatible format.
	CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
	outputter.write(); 

	return result.wasSuccessful() ? 0 : 1;
}

#endif
