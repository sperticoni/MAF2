/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafGUIListBox.h,v $
  Language:  C++
  Date:      $Date: 2008-11-07 13:12:24 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Silvano Imboden
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/
#ifndef __mafGUIListBox_H__
#define __mafGUIListBox_H__
//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include <wx/laywin.h>
#include <wx/listctrl.h>
#include "mafEvent.h"
#include "mafObserver.h"
#include "mafGUIPanel.h"

//----------------------------------------------------------------------------
// mafGUIListBox :
/**
a ListBox that send mafEventNotification in the form
mafEvent(this, widget_id, item_id, checked)
*/
//----------------------------------------------------------------------------

class mafGUIListBox: public mafGUIPanel
{
public:
    mafGUIListBox(wxWindow* parent, 
                    wxWindowID id, 
                    const wxPoint& pos = wxDefaultPosition, 
                    const wxSize& size = wxDefaultSize, 
                    long style = wxTAB_TRAVERSAL | wxCLIP_CHILDREN);

    virtual  ~mafGUIListBox();

  void Clear();
  void AddItem(wxString label, bool checked = false);
  void RemoveItem(long id);
  bool IsChecked();
	void CheckItem(long id);
  void CheckSelectedItem();
  void SetItemLabel(long id, wxString label);
  void SetItemLabel(wxString label);
	wxString GetStringSelection() {return m_ListBox->GetStringSelection();};
	int GetNumberOfItems()	{return m_ListBox->GetCount();};
  void SetListener(mafObserver *listener) {m_Listener = listener;};
  void Select(int id);

  wxListBox *m_ListBox;

protected:
  void OnSelect(wxCommandEvent &event);
  void OnSize(wxSizeEvent& event);

  wxString     m_ItemSelected;
	mafObserver *m_Listener;
  bool         m_PreventNotify;

  DECLARE_EVENT_TABLE()
};
#endif
