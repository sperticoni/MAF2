/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafVMEOutputLandmarkCloud.cpp,v $
  Language:  C++
  Date:      $Date: 2008-07-25 07:05:59 $
  Version:   $Revision: 1.4 $
  Authors:   Paolo Quadrani
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

#include "mafVMEOutputLandmarkCloud.h"
#include "mafGUI.h"
#include "mafDataPipe.h"

#include "mafVME.h"
#include "mafVMELandmarkCloud.h"

#include "vtkDataSet.h"

#include <assert.h>

//-------------------------------------------------------------------------
mafCxxTypeMacro(mafVMEOutputLandmarkCloud)
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
mafVMEOutputLandmarkCloud::mafVMEOutputLandmarkCloud()
//-------------------------------------------------------------------------
{
  m_NumLandmarks = "0";
  m_Gui = NULL;
}

//-------------------------------------------------------------------------
mafVMEOutputLandmarkCloud::~mafVMEOutputLandmarkCloud()
//-------------------------------------------------------------------------
{
}

//-------------------------------------------------------------------------
vtkDataSet *mafVMEOutputLandmarkCloud::GetVTKData()
//-------------------------------------------------------------------------
{
  assert(m_VME);
  assert(mafVMELandmarkCloud::SafeDownCast(m_VME));
  if (mafVMELandmarkCloud::SafeDownCast(m_VME)->IsOpen())
  {
    return NULL;
  }
  else
  {
    return Superclass::GetVTKData();
  }
}

//-------------------------------------------------------------------------
mafGUI* mafVMEOutputLandmarkCloud::CreateGui()
//-------------------------------------------------------------------------
{
  assert(m_Gui == NULL);
  m_Gui = mafVMEOutput::CreateGui();
  m_NumLandmarks = mafVMELandmarkCloud::SafeDownCast(m_VME)->GetNumberOfLandmarks();
  m_Gui->Label(_("points: "), &m_NumLandmarks, true);
  m_Gui->Divider();
	return m_Gui;
}
//-------------------------------------------------------------------------
void mafVMEOutputLandmarkCloud::Update()
//-------------------------------------------------------------------------
{
  assert(m_VME);
  m_VME->Update();
  m_NumLandmarks = mafVMELandmarkCloud::SafeDownCast(m_VME)->GetNumberOfLandmarks();
  if (m_Gui)
  {
    m_Gui->Update();
  }
}
