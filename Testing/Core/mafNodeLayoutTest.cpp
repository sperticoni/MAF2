/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafNodeLayoutTest.cpp,v $
Language:  C++
Date:      $Date: 2008-04-23 09:04:49 $
Version:   $Revision: 1.1 $
Authors:   Roberto Mucci
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/


#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------

#include <cppunit/config/SourcePrefix.h>
#include "mafNodeLayoutTest.h"

#include "mafNodeLayout.h"
#include "mmaApplicationLayout.h"
#include "mafVMERoot.h"

#include <iostream>

#define TEST_RESULT CPPUNIT_ASSERT(result);


//----------------------------------------------------------------------------
void mafNodeLayoutTest::TestFixture()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafNodeLayoutTest::setUp()
//----------------------------------------------------------------------------
{
  result = false;
}
//----------------------------------------------------------------------------
void mafNodeLayoutTest::tearDown()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafNodeLayoutTest::TestDynamicAllocation()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mafNodeLayout> layout;
  mafNodeLayout *layout2 = mafNodeLayout::New();
  layout2->Delete();
}

//----------------------------------------------------------------------------
void mafNodeLayoutTest::GetLayoutTest()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mafVMERoot> root;
  mafSmartPointer<mafNodeLayout> child;
  root->AddChild(child);

  mmaApplicationLayout *appLayout;
  mafNEW(appLayout);
  int pos[] = {5,6};
  int size[] = {1,9};
  appLayout->SetApplicationInfo(10, pos, size);
  child->SetAttribute("ApplicationLayout", appLayout); 
  
  mmaApplicationLayout *appLayout2 = child->GetLayout();

  //test if mmaApplicationLayout returned (appLayout2) equals the one set
  result = (appLayout2->Equals(appLayout));
  TEST_RESULT;
  mafDEL(appLayout);
}
