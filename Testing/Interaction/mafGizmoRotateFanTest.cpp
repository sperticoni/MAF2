/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafGizmoRotateFanTest.cpp,v $
Language:  C++
Date:      $Date: 2010-11-30 09:37:52 $
Version:   $Revision: 1.1.2.3 $
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

#include "mafGizmoRotateFanTest.h"

#include <cppunit/config/SourcePrefix.h>
#include <iostream>

#include "mafString.h"
#include "mafGizmoRotateFan.h"
#include "mafVMERoot.h"
#include "mafSmartPointer.h"
#include "mafVMEOutputPolyline.h"
#include "mafVMEGizmo.h"
#include "mafAbsMatrixPipe.h"
#include "mafObserver.h"
#include "mafTransform.h"

#include "mafInteractorGenericMouse.h"
#include "mmaMaterial.h"

#include "vtkMAFSmartPointer.h"
#include "vtkPoints.h"
#include "vtkCellArray.h"
#include "vtkPolyData.h"
#include "vtkAxes.h"
#include "vtkTubeFilter.h"
#include "vtkRenderer.h"
#include "vtkActor.h"
#include "vtkAssembly.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkDataSetMapper.h"
#include "vtkProperty.h"

/** testing facility to receive events */
class mockListener : public mafObserver 
{
public:

  /** Set the event receiver object*/
  void  SetListener(mafObserver *Listener) {m_Listener = Listener;};

  /** Events handling*/        
  virtual void OnEvent(mafEventBase *maf_event) {m_Event =  *maf_event;};

  mafEventBase *GetEvent() {return &m_Event;};

private:
  /**
  Register the event receiver object*/
  mafObserver *m_Listener;

  mafEventBase m_Event;
};

void mafGizmoRotateFanTest::setUp()
{
  CreateRenderStuff();
	CreateTestData();
}

void mafGizmoRotateFanTest::tearDown()
{
  mafSleep(500);

  m_Renderer->Delete();
  m_RenderWindow->Delete();
  m_RenderWindowInteractor->Delete();

  mafDEL(m_GizmoInputSurface);
  mafDEL(m_Root); 
}

void mafGizmoRotateFanTest::CreateTestData()
//----------------------------------------------------------------------------
{
  m_Root = NULL;
  m_GizmoInputSurface = NULL;

  CPPUNIT_ASSERT(m_GizmoInputSurface == NULL);
  mafNEW(m_GizmoInputSurface);

  vtkMAFSmartPointer<vtkAxes> axes;
  axes->SetScaleFactor(2.5);
  
  vtkMAFSmartPointer<vtkTubeFilter> tube;
  tube->SetInput(axes->GetOutput());
  tube->SetRadius(0.5);
  tube->SetNumberOfSides(20);
  
  m_GizmoInputSurface->SetData(tube->GetOutput(),0.0,mafVMEGeneric::MAF_VME_REFERENCE_DATA);
  
  CPPUNIT_ASSERT(m_GizmoInputSurface->GetOutput()->GetVTKData() != NULL);

  mafNEW(m_Root);
  m_GizmoInputSurface->ReparentTo(m_Root);

  CPPUNIT_ASSERT(m_GizmoInputSurface->GetOutput()->GetVTKData() != NULL);
}

void mafGizmoRotateFanTest::TestConstructor()
{
  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);
  
  RenderData(m_GizmoInputSurface->GetOutput()->GetVTKData());
  RenderGizmo(gizmoRotateFan);
  mafSleep(500);

  // m_RenderWindowInteractor->Start();

  cppDEL(gizmoRotateFan);

}


void mafGizmoRotateFanTest::TestSetListener()
{
  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);

  gizmoRotateFan->SetListener(gizmoRotateFan);
  
  // using friend mafGizmoRotateFan
  CPPUNIT_ASSERT(gizmoRotateFan->m_Listener == gizmoRotateFan);

  gizmoRotateFan->SetListener(NULL);
  CPPUNIT_ASSERT(gizmoRotateFan->m_Listener == NULL);

  cppDEL(gizmoRotateFan);
}

void mafGizmoRotateFanTest::TestSetInput()
{
  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);

  gizmoRotateFan->SetInput(m_GizmoInputSurface);

  // using friend mafGizmoRotateFan
  CPPUNIT_ASSERT(gizmoRotateFan->m_InputVme == m_GizmoInputSurface);

  cppDEL(gizmoRotateFan);
}

void mafGizmoRotateFanTest::TestSetGetAbsPose()
{
  mafMatrix absPose;
  absPose.SetElement(0,3,10);

  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);
  gizmoRotateFan->SetAbsPose(&absPose);
  
  mafMatrix gipo = gizmoRotateFan->m_GizmoFan->GetAbsMatrixPipe()->GetMatrix();
  CPPUNIT_ASSERT(gipo.Equals(&absPose));
 
  cppDEL(gizmoRotateFan);
}


void mafGizmoRotateFanTest::TestSetGetAxis()
{
  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);
  gizmoRotateFan->SetAxis(mafGizmoRotateFan::X);
  CPPUNIT_ASSERT(gizmoRotateFan->m_ActiveAxis == mafGizmoRotateFan::X);

  gizmoRotateFan->SetAxis(mafGizmoRotateFan::Y);
  CPPUNIT_ASSERT(gizmoRotateFan->m_ActiveAxis == mafGizmoRotateFan::Y); 
  
  cppDEL(gizmoRotateFan);

}

void mafGizmoRotateFanTest::TestSetGetRadius()
{
  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);
  gizmoRotateFan->SetRadius(10);
  CPPUNIT_ASSERT(gizmoRotateFan->GetRadius() == 10);

  cppDEL(gizmoRotateFan);
}

void mafGizmoRotateFanTest::TestFixture()
{
	
}

void mafGizmoRotateFanTest::TestShow()
{
  mockListener *mockList = new mockListener();

  mafGizmoRotateFan *gizmoRotateFan = new mafGizmoRotateFan(m_GizmoInputSurface);
  gizmoRotateFan->SetListener(mockList);

  gizmoRotateFan->Show(true);

  mafID evId = mockList->GetEvent()->GetId();

  CPPUNIT_ASSERT( evId == VME_SHOW );

  cppDEL(gizmoRotateFan);
  cppDEL(mockList);
}

void mafGizmoRotateFanTest::RenderData( vtkDataSet *data )
{
  vtkDataSetMapper *mapper = vtkDataSetMapper::New();
  mapper->ScalarVisibilityOn();
  mapper->SetInput(data);

  vtkActor *actor = vtkActor::New();
  actor->SetMapper(mapper);

  m_Renderer->AddActor(actor);
  
  m_RenderWindow->Render();
  
  mapper->Delete();
  actor->Delete();

} 
  

void mafGizmoRotateFanTest::CreateRenderStuff()
{
  m_Renderer = vtkRenderer::New();
  m_RenderWindow = vtkRenderWindow::New();
  m_RenderWindowInteractor = vtkRenderWindowInteractor::New() ;
  
  m_Renderer->SetBackground(0.1, 0.1, 0.1);

  m_RenderWindow->AddRenderer(m_Renderer);
  m_RenderWindow->SetSize(640, 480);
  m_RenderWindow->SetPosition(400,0);

  m_RenderWindowInteractor->SetRenderWindow(m_RenderWindow);
}

void mafGizmoRotateFanTest::RenderGizmo( mafGizmoRotateFan *gizmoRotateFan )
{
  RenderData(gizmoRotateFan->m_GizmoFan->GetOutput()->GetVTKData());
}
