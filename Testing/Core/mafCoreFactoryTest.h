/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafCoreFactoryTest.h,v $
Language:  C++
Date:      $Date: 2009-04-06 12:56:01 $
Version:   $Revision: 1.1.2.1 $
Authors:   Stefano Perticoni
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafCoreFactoryTest_H__
#define __CPP_UNIT_mafCoreFactoryTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>



class mafCoreFactoryTest : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( mafCoreFactoryTest );
	CPPUNIT_TEST( TestStaticAllocation );
	CPPUNIT_TEST( TestDynamicAllocation );
  CPPUNIT_TEST( TestGetSourceVersion );
  CPPUNIT_TEST( TestGetDescription );

  // These tests play with the factory to check that everything is working as expected: 
  CPPUNIT_TEST( TestCreateInstance );
	CPPUNIT_TEST( TestGetRegisteredFactories );
	CPPUNIT_TEST( TestRegisterFactory );
	CPPUNIT_TEST( TestUnRegisterAllFactories );
  CPPUNIT_TEST( TestRegisterOverride );
  CPPUNIT_TEST( TestRegisterNewObject );
  CPPUNIT_TEST( TestDisable );
  CPPUNIT_TEST( TestSetEnableFlag );
  CPPUNIT_TEST( TestUnRegisterFactory );
  CPPUNIT_TEST( TestGetArgs );
  CPPUNIT_TEST( TestReHash );
  CPPUNIT_TEST( TestCreateAllInstance );
  CPPUNIT_TEST_SUITE_END();

  protected:
  void TestGetSourceVersion();
  void TestGetDescription();
  void TestCreateInstance();
	void TestStaticAllocation();
	void TestDynamicAllocation();
	void TestGetRegisteredFactories();
	void TestRegisterFactory();
	void TestUnRegisterAllFactories();
  void TestRegisterOverride();
  void TestRegisterNewObject();
  void TestDisable();
  void TestSetEnableFlag();
  void TestUnRegisterFactory();
  void TestGetArgs();
  void TestReHash();
  void TestCreateAllInstance();
  
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
  runner.addTest( mafCoreFactoryTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
