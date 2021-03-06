/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafGUIViewFrame.cpp,v $
  Language:  C++
  Date:      $Date: 2008-07-25 06:53:39 $
  Version:   $Revision: 1.1 $
  Authors:   Silvano Imboden
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



#include "mafGUIViewFrame.h"
#include "mafDecl.h"
#include "mafEvent.h"
#include "mafView.h"
//#include "mafSceneGraph.h"
//#include "mafSceneNode.h"
//#include "vtkVersion.h"

//----------------------------------------------------------------------------
// mafGUIViewFrame
//----------------------------------------------------------------------------
BEGIN_EVENT_TABLE(mafGUIViewFrame, wxFrame)
    EVT_CLOSE(mafGUIViewFrame::OnCloseWindow)
    EVT_SIZE(mafGUIViewFrame::OnSize)
    EVT_BUTTON(VIEW_CLICKED, mafGUIViewFrame::OnSelect)
	  EVT_ACTIVATE  (mafGUIViewFrame::OnActivate)
END_EVENT_TABLE()

bool mafGUIViewFrame::m_Quitting = false;
//----------------------------------------------------------------------------
mafGUIViewFrame::mafGUIViewFrame( wxFrame* parent, 
                            wxWindowID id, 
                            const wxString& title,
                            const wxPoint& pos, 
                            const wxSize& size, 
                            long style 
                            )
//----------------------------------------------------------------------------
: wxFrame(parent, id, title, pos, size, style)
{
  m_Listener = NULL;
  m_ClientWin = NULL;
}
//----------------------------------------------------------------------------
mafGUIViewFrame::~mafGUIViewFrame( ) 
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafGUIViewFrame::OnCloseWindow(wxCloseEvent &event)
//----------------------------------------------------------------------------
{ 
	mafEventMacro(mafEvent(this,VIEW_DELETE,m_View));
	Destroy();
}
//----------------------------------------------------------------------------
void mafGUIViewFrame::OnSize(wxSizeEvent &event)
//----------------------------------------------------------------------------
{ 
	Refresh();
  if (m_ClientWin)
  {
    wxLayoutAlgorithm layout;
    layout.LayoutWindow(this,m_ClientWin);
  }

#ifndef WIN32
  int w,h;
  //don't initialize w & h using the event - use GetClientSize instead
  this->GetClientSize(&w,&h); 
  
  if(m_View)
  {
    m_View->SetWindowSize(w,h);
  }
#endif

}
//----------------------------------------------------------------------------
void mafGUIViewFrame::OnSelect(wxCommandEvent &event) 
//----------------------------------------------------------------------------
{
  wxWindow *rwi = (wxWindow*)event.GetEventObject();
  mafEventMacro(mafEvent(this,VIEW_SELECT,m_View,rwi));
}
//----------------------------------------------------------------------------
void mafGUIViewFrame::OnActivate(wxActivateEvent& event)
//----------------------------------------------------------------------------
{ 
	if( event.GetActive() && !m_Quitting )
  {
		mafEventMacro(mafEvent(this,VIEW_SELECT,m_View,(wxWindow*)NULL));
	  Layout();
	}
}
//----------------------------------------------------------------------------
void mafGUIViewFrame::SetView(mafView *view)
//----------------------------------------------------------------------------
{
   m_View = view;
   m_ClientWin = m_View->GetWindow();
   m_ClientWin->Reparent(this);
   m_ClientWin->Show(true);

   SetTitle(wxStripMenuCodes(m_View->GetLabel()));
}
//----------------------------------------------------------------------------
void mafGUIViewFrame::OnEvent(mafEventBase *maf_event)
//----------------------------------------------------------------------------
{
  if (mafEvent *e = mafEvent::SafeDownCast(maf_event))
  {
    switch(e->GetId())
    {
    case VIEW_QUIT:
      mafEventMacro(mafEvent(this,VIEW_DELETE,m_View));
      Destroy();
      break;
    default:
      // forward to ViewManager
      mafEventMacro(*e);
      break;
    }
  }
}
