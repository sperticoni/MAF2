/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpReparentTo.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:49:23 $
  Version:   $Revision: 1.2.2.1 $
  Authors:   Paolo Quadrani
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __mafOpReparentTo_H__
#define __mafOpReparentTo_H__

//----------------------------------------------------------------------------
// Include :
//----------------------------------------------------------------------------
#include "mafOp.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafNode;
class mafVME;
class mafEvent;
class mafGUI;

//----------------------------------------------------------------------------
// mafOpReparentTo :
//----------------------------------------------------------------------------
/** */
class MAF_EXPORT mafOpReparentTo: public mafOp
{
public:
  mafOpReparentTo(const wxString &label = "ReparentTo");
 ~mafOpReparentTo(); 
  
  mafTypeMacro(mafOpReparentTo, mafOp);

  mafOp* Copy();

	/** Return true for the acceptable vme type. */
  bool Accept(mafNode *node);

	/** Builds operation's interface. */
  void OpRun();

	/** Execute the operation. */
  void OpDo();

	/** Makes the undo for the operation. */
  void OpUndo();

  /** Set the target vme (used to be called without using interface)*/
  void SetTargetVme(mafVME *target);

protected:
	mafVME *m_TargetVme;
  mafVME *m_OldParent;
};
#endif
