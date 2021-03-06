/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpStack.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 09:42:20 $
  Version:   $Revision: 1.2.24.1 $
  Authors:   Silvano Imboden
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/
#ifndef __mafOpStack_H__
#define __mafOpStack_H__
//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafOp;
//----------------------------------------------------------------------------
// mafOpStack :
//----------------------------------------------------------------------------
/**
*/
class MAF_EXPORT mafOpStack
{
public:
				mafOpStack();
			 ~mafOpStack(); 
	
	/** Return true is the stack is empty */
	bool 		IsEmpty();

  /** Insert op on top od the stack */
	void 		Push(mafOp* op);
	
  /** Return the op on the top of the stack, and remove it */
	mafOp*	Pop();
	
  /** Empty the stack and call delete on every inserted op */
	void 		Clear();

protected:
	mafOp	 *m_Stack;
};
#endif














