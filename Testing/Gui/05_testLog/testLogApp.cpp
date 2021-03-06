/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: testLogApp.cpp,v $
  Language:  C++
  Date:      $Date: 2005-06-06 15:11:50 $
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


#include "testLogApp.h"
#include "mafPics.h"

//--------------------------------------------------------------------------------
// Create the Application
//--------------------------------------------------------------------------------
IMPLEMENT_APP(testLogApp)

//--------------------------------------------------------------------------------
bool testLogApp::OnInit()
//--------------------------------------------------------------------------------
{
  mafPics.Initialize();	

	m_logic = new testLogLogic();
  SetTopWindow(m_logic->GetTopWin());  
  m_logic->Show();
  return TRUE;
}
//--------------------------------------------------------------------------------
int testLogApp::OnExit()
//--------------------------------------------------------------------------------
{
  cppDEL(m_logic);
  return 0;
}

