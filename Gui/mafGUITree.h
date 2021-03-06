/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafGUITree.h,v $
  Language:  C++
  Date:      $Date: 2008-07-25 06:53:39 $
  Version:   $Revision: 1.1 $
  Authors:   Silvano Imboden
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/
#ifndef __mafGUITree_H__
#define __mafGUITree_H__
//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include <wx/laywin.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/treectrl.h>
#include <wx/hash.h>
#include "mafEvent.h"
#include "mafObserver.h"
#include "mafGUINamedPanel.h"

//----------------------------------------------------------------------------
// const :
//----------------------------------------------------------------------------
const int ID_TREE = 200;
//----------------------------------------------------------------------------
// mafGUITree :
//----------------------------------------------------------------------------
/**
mafGUITree allows a simplified and lot easier use of a wxWindows tree widget. 
- Nodes have id, parent, label and icon.
- Nodes can be added and deleted
- Parent,label and icon can be changed.
- Delete or reparent a node affect its whole subtree.
- mafGUITree doesn't assume anything about what the nodes represented, thus nodes objects may be everything. 
  Nodes are referenced by a node_id of type long, so a node_id may be a numeric value or a pointer.
- mafGUITree doesn't use the wxWindows event-system: to receive event notification provide 
  a mafObserver object by calling SetListener.

  events generated by mafGUITree:
- VME_SELECTED   node_id

\par implementation details:
the term "Node" refer to the object represented in the Tree,
the term "Item" refer to the graphics object shown in the Tree.

Calling wxTreeCtrl::AddNode return an object of type wxTreeCtrlItem,
these objects are to be kept somewhere to be able to edit or delete the items later.
The easy solution is to store a pointer to wxTreeCtrlItem in the node,
but this will mean that mafGUITree has some knowledge on the node objects 
thus making mafGUITree non-general-purposes and also that
every node can be connected to one mafGUITree only.

The solution adopted here is to store all the wxTreeCtrlItem in a HashTable (m_NodeTable)
indexed by the node_id's. Thus explicit conversion between node_ids and items has to be addressed.

ItemFromNode is implemented using m_NodeTable. Note that wxHashTable store only object 
of type mafGUITreeTableElement so a new class mafGUITreeTableItem was derived from wxHashTableItem
to store a pointer to wxTreeCtrlItem

NodeFromItem may be implemented searching all the elements in m_NodeTable but this
will be time-consuming, another solution is to store the node_id in the item.
Items may store user-data in a class derived from wxTreeItemData, so a class mafGUITreeItemData
was created for this purposes. A new mafGUITreeItemData object is created every time 
an item is inserted in the tree.

Further aspect:
One Item may have a cross-icon that mean that it has children and thus can be opened,
to show the cross-icon the developer must call SetItemHasChildren.
wxTreeCtrl doesn't set-up the HasChildren flag itself, so when a node is added or deleted the 
HasChildren flag of the parent has to be kept consistent.Another flag control if 
a subtree is expanded or collapsed, this flag has to be kept consistent when moving a node.
  
Moving a node:
wxTreeCtrl doesn't provide a way to change item's parent, so that operation has to be implemented
explicitly. Delete and recreate the item doesn't work because delete the item destroy
all the items in the subtree.The correct approach is to copy the item under the new parent,
recursively move all the item in the subtree, and then delete the old item.During this operation 
the HasChildren flag, the IsExpanded flag and the HashTable contents has to be kept consistent.

Deleting a node:
Deleting an item destroy all the sub-items,leaving the m_NodeTable inconsistent.
To correctly implement the operation, DeleteNode must call itself recursively on the 
item subtree, then Delete the item and remove the corresponding m_NodeTable entry. 
*/
class mafGUITree: public mafGUINamedPanel
{
public:
                 mafGUITree (wxWindow* parent, wxWindowID id=-1, bool CloseButton = false, bool HideTitle = false); 
  virtual       ~mafGUITree();

  /** Clears all items in the tree. */
	void Reset();
  
	/** Create a new tree item with the specified parent,label and icon. 
      Set parent = 0 to create the root. 0 is not a valid node_id.
  */
	bool AddNode(long node_id, long parent_id , wxString label, int icon = 0);
  
	/** Delete the specified node, and its subtree. */
	bool DeleteNode(long node_id);
  
	/** Set the label for the node. */
	bool SetNodeLabel(long node_id, wxString label);

  /** Get the label for the node. Add by Mucci 19/09/2007*/
  wxString GetNodeLabel(long node_id);

  /** Check if the node has children. Add by Mucci 19/09/2007*/
  bool NodeHasChildren(long node_id);

  /** Return the parent id of the node. Add by Mucci 19/09/2007*/
  long GetNodeParent(long node_id);
  
	/** Move a node, and its subtree. */
	bool SetNodeParent(long node_id, long parent_id );
  
	/** Set the icon for the node. */
  bool SetNodeIcon(long node_id, int icon);
  
  /** Return the icon index for the node 'node_id'. */
  int  GetNodeIcon(long node_id);

  /** Select the node. */
  bool SelectNode(long node_id);

  /** Set the images to be used for the nodes. 
      Must be set before adding any node. 
      The default ImageList provide 4 icons :
      -1 gray dot 
      -2 red dot 
      -3 blue dot 
      -4 yellow dot 
  */
  void SetImageList(wxImageList *img);

  /** Sort the children of node_id. (not the subtree) 
      give node_id = 0 to specify the root. */
  void SortChildren(long node_id =0);

  /** if autosort is on - the tree is always kept sorted */
  void SetAutoSort(bool enable) {m_Autosort=enable;};

  /** Get the autosort flag. */
  bool GetAutoSort() {return m_Autosort;};

  /** collapse the children of node_id */
  void CollapseNode(long node_id);

  /** expand the children of node_id */
  void ExpandNode(long node_id);

  /** Set the Listener that will receive event-notification, the Listener can be changed any time  */
  void SetListener(mafObserver *listener)   {m_Listener=listener;}; 

  /** Return the node item from node id. */
  wxTreeItemId ItemFromNode(long node_id);

  /** Return node id from node item. */
  long NodeFromItem(wxTreeItemId& item);
  
  
  void SetTreeStyle(long style) {m_NodeTree->SetWindowStyle(style);};
  long GetTreeStyle()           {return m_NodeTree->GetWindowStyle();};

protected:
  /** Private function that notify the Listener of node selection and deselection. */
  virtual void OnSelectionChanged(wxTreeEvent& event);
  
	/** When tree is used on a wxNotebook m_NodeTree must be called on Sizing . */
  void OnSize(wxSizeEvent& event);

	/** Return true if node exist. */
  bool NodeExist(long node_id);
  
	/** Delete recursively a node and its subtree. */
	void DeleteNode2(long node_id);
  
	/** Move a node, and its subtree. */
  void SetNodeParent2(long node_id, long parent_id );
    
  /** Check that id is a valid index in the imagelist - return the (eventually clamped) value */
  int CheckIconId(int icon);

  bool IsRootHidden() {return (GetTreeStyle() & wxTR_HIDE_ROOT) != 0; };

  bool               m_PreventNotify;
  bool               m_Autosort;
  long               m_NodeRoot;
  wxTreeCtrl        *m_NodeTree;         
  wxImageList       *m_NodeImages;       
  wxHashTable       *m_NodeTable;        
  mafObserver       *m_Listener;     

	//----------------------------------------------------------------------------
	// mafGUITreeItemData :
	/// Data to be attached to an item of mafGUITree, holds the reference to a node_id 
	//----------------------------------------------------------------------------
	class mafGUITreeItemData: public wxTreeItemData{
	public:
			mafGUITreeItemData(long node_id) {m_NodeId = node_id; };
			long GetNode()                {return m_NodeId;};
	protected:
			long m_NodeId;
	};
	//----------------------------------------------------------------------------
	// mafGUITreeTableElement:
	/// specialized HashTable element used in mafGUITree to store a reference to a wxTreeItemId 
	//----------------------------------------------------------------------------
	class mafGUITreeTableElement: public wxObject
	{
	public:
	  mafGUITreeTableElement(wxTreeItemId item) {m_TreeItemId=item;  };
		wxTreeItemId GetItem()                 {return m_TreeItemId;};
		void SetItem(wxTreeItemId item){m_TreeItemId=item;  };
	protected:
		wxTreeItemId m_TreeItemId;          
	};

DECLARE_EVENT_TABLE()
}; // end of mafGUITree
#endif
