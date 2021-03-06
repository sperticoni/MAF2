/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mmaApplicationLayoutTest.cpp,v $
Language:  C++
Date:      $Date: 2008-07-25 07:04:07 $
Version:   $Revision: 1.2 $
Authors:   Paolo Quadrani
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
#include "mmaApplicationLayoutTest.h"

#include "mafSmartPointer.h"
#include "mmaApplicationLayout.h"

#include "mafView.h"
#include "mafGUIMDIChild.h"

#include <iostream>

#define TEST_RESULT CPPUNIT_ASSERT(result);

//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestFixture()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::setUp()
//----------------------------------------------------------------------------
{
  m_Toplevel = new wxFrame(NULL,-1,"Title");
  result = false;
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::tearDown()
//----------------------------------------------------------------------------
{
  cppDEL(m_Toplevel);
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestDynamicAllocation()
//----------------------------------------------------------------------------
{
  mmaApplicationLayout *appLayout = mmaApplicationLayout::New();
  result = appLayout->GetReferenceCount() == 0;
  TEST_RESULT;
  appLayout->Delete();

  mafNEW(appLayout);
  result = appLayout->GetReferenceCount() == 1;
  TEST_RESULT;
  appLayout->Delete();
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestAddView()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mmaApplicationLayout> appLayout;

  mafView *v1 = new mafView("v1");
  mafView *v2 = new mafView("v2");

  v1->SetFrame(m_Toplevel);
  v2->SetFrame(m_Toplevel);

  appLayout->AddView(v1);
  result = appLayout->GetNumberOfViewsInLayout() == 1;
  TEST_RESULT;

  appLayout->AddView(v2);
  result = appLayout->GetNumberOfViewsInLayout() == 2;
  TEST_RESULT;

  cppDEL(v1);
  cppDEL(v2);
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestRemoveView()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mmaApplicationLayout> appLayout;

  mafView *v1 = new mafView("v1");
  mafView *v2 = new mafView("v2");
  v1->SetFrame(m_Toplevel);
  v2->SetFrame(m_Toplevel);

  appLayout->AddView(v1);
  appLayout->AddView(v2);

  appLayout->RemoveView(0);
  result = appLayout->GetNumberOfViewsInLayout() == 1;
  TEST_RESULT;

  appLayout->AddView(v1);

  appLayout->RemoveView(v1);
  result = appLayout->GetNumberOfViewsInLayout() == 1;
  TEST_RESULT;

  cppDEL(v1);
  cppDEL(v2);
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestEquals()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mmaApplicationLayout> appLayout1;
  mafSmartPointer<mmaApplicationLayout> appLayout2;

  mafView *v1 = new mafView("v1");
  mafView *v2 = new mafView("v2");
  v1->SetFrame(m_Toplevel);
  v2->SetFrame(m_Toplevel);

  appLayout1->AddView(v1);
  appLayout1->AddView(v2);

  appLayout2->AddView(v1);
  appLayout2->AddView(v2);

  result = appLayout1->Equals(appLayout2);
  TEST_RESULT;

  cppDEL(v1);
  cppDEL(v2);
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestDeepCopy()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mmaApplicationLayout> appLayout1;
  mafSmartPointer<mmaApplicationLayout> appLayout2;

  mafView *v1 = new mafView("v1");
  mafView *v2 = new mafView("v2");
  v1->SetFrame(m_Toplevel);
  v2->SetFrame(m_Toplevel);

  appLayout1->AddView(v1);
  appLayout1->AddView(v2);

  mafView *v3 = new mafView("v3");
  v3->SetFrame(m_Toplevel);

  appLayout2->AddView(v3);
  appLayout2->DeepCopy(appLayout1);

  result = appLayout1->Equals(appLayout2);
  TEST_RESULT;

  cppDEL(v1);
  cppDEL(v2);
  cppDEL(v3);
}
//----------------------------------------------------------------------------
void mmaApplicationLayoutTest::TestClearLayout()
//----------------------------------------------------------------------------
{
  mafSmartPointer<mmaApplicationLayout> appLayout;

  mafView *v1 = new mafView("v1");
  mafView *v2 = new mafView("v2");
  v1->SetFrame(m_Toplevel);
  v2->SetFrame(m_Toplevel);

  appLayout->AddView(v1);
  appLayout->AddView(v2);

  appLayout->ClearLayout();
  
  result = appLayout->GetNumberOfViewsInLayout() == 0;
  TEST_RESULT;

  mafString default_name = "Null Layout";
  result = default_name.Equals(appLayout->GetLayoutName());
  TEST_RESULT;

  cppDEL(v1);
  cppDEL(v2);
}
