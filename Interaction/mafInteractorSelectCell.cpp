/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafInteractorSelectCell.cpp,v $
  Language:  C++
  Date:      $Date: 2009-12-17 11:46:40 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Stefano Perticoni	
==========================================================================
  Copyright (c) 2002/2004 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#include "mafDefines.h"

#include "mafInteractorSelectCell.h"
#include "mafDeviceButtonsPadMouse.h"
#include "mafAvatar3D.h"
#include "mafInteractor.h"
#include "mafRWIBase.h"
#include "mafEventInteraction.h"
#include "mafEvent.h"

#include "vtkAbstractPicker.h"
#include "vtkCellPicker.h"
#include "vtkPoints.h"
#include "vtkMath.h"
#include "vtkRendererCollection.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkCamera.h"
#include "vtkTransform.h"

#include <assert.h>

//------------------------------------------------------------------------------
mafCxxTypeMacro(mafInteractorSelectCell)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
mafInteractorSelectCell::mafInteractorSelectCell()
//------------------------------------------------------------------------------
{
  m_IsPicking = false;
}

//------------------------------------------------------------------------------
mafInteractorSelectCell::~mafInteractorSelectCell()
//------------------------------------------------------------------------------
{
}

//----------------------------------------------------------------------------
void mafInteractorSelectCell::OnMouseMove() 
//----------------------------------------------------------------------------
{
  // if something has been picked do not move the camera
  if (m_IsPicking == true)
  {
    return;
  }
  else
  {
    Superclass::OnMouseMove();
  }
}
//----------------------------------------------------------------------------
void mafInteractorSelectCell::OnLeftButtonDown(mafEventInteraction *e) 
//----------------------------------------------------------------------------
{
  if (e->GetModifier(MAF_CTRL_KEY)) 
  {
    // picking mode on
    m_IsPicking = true;

    // perform picking
    PickCell((mafDevice *)e->GetSender());
  }
  else
  {
    m_IsPicking = false;
    Superclass::OnLeftButtonDown(e);
  }
}
//----------------------------------------------------------------------------
void mafInteractorSelectCell::OnButtonUp(mafEventInteraction *e)
//----------------------------------------------------------------------------
{
  // reset
  m_IsPicking = false;

  Superclass::OnButtonUp(e);
}
//----------------------------------------------------------------------------
void mafInteractorSelectCell::PickCell( mafDevice *device )
{
  int x = m_LastMousePose[0];
  int y = m_LastMousePose[1];

  mafDeviceButtonsPadMouse *mouse = mafDeviceButtonsPadMouse::SafeDownCast(device);
  if( mouse && m_Renderer)
  {
    double pos_picked[3];

    vtkCellPicker *cellPicker;
    vtkNEW(cellPicker);
    cellPicker->SetTolerance(0.001);
    
    if(cellPicker->Pick(x,y,0,m_Renderer))
    {
      //BES: 29.1.2009 - get the picked coordinates
      cellPicker->GetPickedPositions()->GetPoint(0, pos_picked);

      vtkPoints *pickedPoint = vtkPoints::New();
      pickedPoint->SetNumberOfPoints(1);
      pickedPoint->SetPoint(0,pos_picked);
      mafEventMacro(mafEvent(this,VME_PICKED,(vtkObject *)pickedPoint,cellPicker->GetCellId()));
      pickedPoint->Delete();
      
    }
  
    vtkDEL(cellPicker);
  }
}
void mafInteractorSelectCell::OnEvent(mafEventBase *event)
//------------------------------------------------------------------------------
{
  // if we are in pick modality...
  if (m_IsPicking)
  {
    // is this an interaction event?
    mafEventInteraction* eventInteraction = NULL;
    eventInteraction = mafEventInteraction::SafeDownCast(event);

    // if yes handle the picking
    if (eventInteraction != NULL)
    {
      // is it coming from the mouse?
      if (mafDeviceButtonsPadMouse *mouse=mafDeviceButtonsPadMouse::SafeDownCast((mafDevice *)eventInteraction->GetSender()))
      { 
        PickCell(mouse);
      }
      else
      {
        mafLogMessage("only handling events from the mouse!more code is required in order to handle this device!");
        assert(false);
      } 
    }
  } 

  Superclass::OnEvent(event);
}

