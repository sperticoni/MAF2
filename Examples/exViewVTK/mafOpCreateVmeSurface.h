/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpCreateVmeSurface.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 09:57:03 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Silvano Imboden
==========================================================================
  Copyright (c) 2001/2005 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/
#ifndef __mafOpCreateVmeSurface_H__
#define __mafOpCreateVmeSurface_H__
//----------------------------------------------------------------------------
// Include:
//----------------------------------------------------------------------------
#include "mafOp.h"
#include "mafVME.h"
//----------------------------------------------------------------------------
// Forward Refs:
//----------------------------------------------------------------------------
class mafVMESurface;
// ============================================================================
class __declspec( dllexport ) mafOpCreateVmeSurface : public mafOp
// ============================================================================
{
public:
                mafOpCreateVmeSurface(wxString label = "CreateVmeSurface");
               ~mafOpCreateVmeSurface();
	virtual void OnEvent(mafEventBase *event);
  mafOp* Copy();
  mafTypeMacro(mafOpCreateVmeSurface, mafOp);

  bool Accept(mafNode* vme) {return vme && vme->IsMAFType(mafVME);};
  void OpRun();
  void OpDo();
  void OpUndo();

protected:
  mafVMESurface  *m_vme; 
};
#endif // __mafOpCreateVmeSurface_H__
