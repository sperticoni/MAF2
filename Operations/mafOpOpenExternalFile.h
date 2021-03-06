/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpOpenExternalFile.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:49:23 $
  Version:   $Revision: 1.1.4.1 $
  Authors:   Stefano Perticoni    Roberto Mucci
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __mafOpOpenExternalFile_H__
#define __mafOpOpenExternalFile_H__


#include "mafOp.h"
//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafOp;
class mafEvent;

//----------------------------------------------------------------------------
// mafOpOpenExternalFile :
//----------------------------------------------------------------------------
/** Open with external programs the data previously imported with the mafOpImporterExternalFile */
class MAF_EXPORT mafOpOpenExternalFile: public mafOp
{
public:
  mafOpOpenExternalFile(const wxString &label = "OpenExternalFile");
 ~mafOpOpenExternalFile();

 mafTypeMacro(mafOpOpenExternalFile, mafOp);

 mafOp* Copy();

 /** Return true for the acceptable vme type. */
 bool Accept(mafNode* node);

 /** Builds operation's interface. */
 void OpRun();

 /** Return the "pid" of the wxExecute() */
 long GetPid();

private:
  long m_Pid;
};
#endif
