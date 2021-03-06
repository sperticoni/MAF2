/*==============================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpDummy.h,v $
Language:  C++
Date:      $Date: 2011-05-25 11:58:32 $
Version:   $Revision: 1.1.2.2 $
Authors:   Matteo Giacomoni
================================================================================
Copyright (c) 2009 Cineca, UK (www.cineca.it)
All rights reserved.
===============================================================================*/

#include "mafDefines.h" 
//------------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//------------------------------------------------------------------------------

#include "mafOp.h"
#include "mafNode.h"

//-------------------------------------------------------------------------
/** class for testing */
class mafOpDummy: public mafOp
//-------------------------------------------------------------------------
{
public:
  mafOpDummy(wxString label = "DummyOp",  bool canundo = false, int opType = OPTYPE_OP, bool inputPreserving = false);

  mafTypeMacro(mafOpDummy,mafOp);

  /** Return true for the acceptable vme type. */
  /*virtual*/ bool Accept(mafNode* vme);
  /*virtual*/ mafOp* Copy();
  /** Builds operation's interface. */
  /*virtual*/ void OpRun();
  /** Execute the operation. */
  /*virtual*/ void OpDo();
  /** Makes the undo for the operation. */
  /*virtual*/ void OpUndo();

  void End();


  static bool m_Executed;
  static bool m_Do;
  static bool m_Undo;
  static bool m_Stop;

protected:

  /** This method is called at the end of the operation and result contain the wxOK or wxCANCEL. */
  /*virtual*/ void OpStop(int result);
};
//----------------------------------------------------------------------------
mafOpDummy::mafOpDummy(wxString label,  bool canundo, int opType, bool inputPreserving)
//----------------------------------------------------------------------------
{

  m_Canundo = true;
  m_OpType = opType;
  m_InputPreserving = inputPreserving;
}
//----------------------------------------------------------------------------
bool mafOpDummy::Accept(mafNode* vme)
//----------------------------------------------------------------------------
{
  return vme->IsA("mafVMEDummy");
}
//----------------------------------------------------------------------------
mafOp* mafOpDummy::Copy()
//----------------------------------------------------------------------------
{
  return new mafOpDummy();
}
//----------------------------------------------------------------------------
void mafOpDummy::OpDo()
//----------------------------------------------------------------------------
{
  mafOpDummy::m_Do = true;
}
//----------------------------------------------------------------------------
void mafOpDummy::OpUndo()
//----------------------------------------------------------------------------
{
  m_Undo = true;
}
//----------------------------------------------------------------------------
void mafOpDummy::OpRun()
//----------------------------------------------------------------------------
{
  m_Executed = true; 
}
//----------------------------------------------------------------------------
void mafOpDummy::End()
//----------------------------------------------------------------------------
{
  mafEventMacro(mafEvent(this,OP_RUN_OK));
}
//----------------------------------------------------------------------------
void mafOpDummy::OpStop(int result)
//----------------------------------------------------------------------------
{
  m_Stop = true;
  mafEventMacro(mafEvent(this,result));        
}

mafCxxTypeMacro(mafOpDummy);