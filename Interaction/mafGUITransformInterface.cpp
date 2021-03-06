/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafGUITransformInterface.cpp,v $
  Language:  C++
  Date:      $Date: 2009-12-17 11:47:19 $
  Version:   $Revision: 1.1.2.2 $
  Authors:   Stefano Perticoni
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


#include "mafGUITransformInterface.h"
#include "mafDecl.h"

#include "mafGUI.h"
#include "mafGUIButton.h"

#include "mafInteractorGenericMouse.h"
#include "mafInteractorCompositorMouse.h"

#include "mafMatrix.h"
#include "mafTransform.h"
#include "mafVME.h"

#include "vtkMatrix4x4.h"

//----------------------------------------------------------------------------
mafGUITransformInterface::mafGUITransformInterface()
//----------------------------------------------------------------------------
{
  m_CurrentTime = -1;
  m_Listener = NULL;
  m_InputVME = NULL;
  m_Gui = NULL;
  m_RefSysVME = m_InputVME;
  m_TestMode = false;
}
//----------------------------------------------------------------------------
mafGUITransformInterface::~mafGUITransformInterface() 
//----------------------------------------------------------------------------
{   
 
}

//----------------------------------------------------------------------------
void mafGUITransformInterface::SetRefSys(mafVME* refSysVme)
//----------------------------------------------------------------------------
{ 
  if (refSysVme == NULL)
  return;

  m_RefSysVME = refSysVme;
  RefSysVmeChanged();
}
