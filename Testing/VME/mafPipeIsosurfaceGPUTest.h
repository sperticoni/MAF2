/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafPipeIsosurfaceGPUTest.h,v $
Language:  C++
Date:      $Date: 2009-04-16 13:36:24 $
Version:   $Revision: 1.1.2.1 $
Authors:   Daniele Giunchi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_mafPipeIsosurfaceGPUTest_H__
#define __CPP_UNIT_mafPipeIsosurfaceGPUTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>

class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkRectilinearGrid;

class mafPipeIsosurfaceGPUTest : public CPPUNIT_NS::TestFixture
{
public: 
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( mafPipeIsosurfaceGPUTest );
  CPPUNIT_TEST( TestFixture ); // just to test that the fixture has no leaks
  CPPUNIT_TEST( TestPipeExecutionCountour );
  CPPUNIT_TEST( TestPipeExecutionOpacity );
  CPPUNIT_TEST( TestExtractIsosurface );
  CPPUNIT_TEST_SUITE_END();

protected:
  void TestFixture();
  void TestPipeExecutionCountour();
  void TestPipeExecutionOpacity();
  void TestExtractIsosurface();

  vtkRenderer *m_Renderer;
  vtkRenderWindow *m_RenderWindow;
  vtkRenderWindowInteractor *m_RenderWindowInteractor;

  /**Compare a list of already saved images (control images) with renderized image from render window
  @imageIndex: index X of the image. Original Image is imageX.jpg, created imaged is compX.jpg
  */
  void CompareImages(int imageIndex);
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
  runner.addTest( mafPipeIsosurfaceGPUTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  return result.wasSuccessful() ? 0 : 1;
}

#endif
