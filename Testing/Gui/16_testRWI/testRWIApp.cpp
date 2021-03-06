/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: testRWIApp.cpp,v $
  Language:  C++
  Date:      $Date: 2005-06-06 15:11:52 $
  Version:   $Revision: 1.1.1.1 $
  Authors:   Silvano Imboden
==========================================================================
  Copyright (c) 2001/2005 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/


#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------


#include "testRWIApp.h"
#include "mafPics.h"

//--------------------------------------------------------------------------------
// Create the Application
//--------------------------------------------------------------------------------
IMPLEMENT_APP(testRWIApp)

//--------------------------------------------------------------------------------
bool testRWIApp::OnInit()
//--------------------------------------------------------------------------------
{
  mafPics.Initialize();	

  m_logic = new testRWILogic();
  SetTopWindow(m_logic->m_win);
  m_logic->Show();
  return TRUE;
}
//--------------------------------------------------------------------------------
int testRWIApp::OnExit()
//--------------------------------------------------------------------------------
{
  cppDEL(m_logic);
  return 0;
}











