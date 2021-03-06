/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpCreateSlicer.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:49:23 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Paolo Quadrani
==========================================================================
Copyright (c) 2002/2004
CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __mafOpCreateSlicer_H__
#define __mafOpCreateSlicer_H__

#include "mafOp.h"
#include "mafVMEVolume.h"
//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafVMESlicer;

//----------------------------------------------------------------------------
// mafOpCreateSlicer :
//----------------------------------------------------------------------------
/** */
class MAF_EXPORT mafOpCreateSlicer: public mafOp
{
public:
  mafOpCreateSlicer(const wxString &label = "CreateSlicer");
 ~mafOpCreateSlicer(); 

  mafTypeMacro(mafOpCreateSlicer, mafOp);

  mafOp* Copy();

  bool Accept(mafNode *node);
  void OpRun();
  void OpDo();

  static bool VolumeAccept(mafNode* node) {return(node != NULL  && node->IsMAFType(mafVMEVolume));};

protected: 
  mafVMESlicer *m_Slicer;
  mafNode      *m_SlicedVME;
};
#endif
