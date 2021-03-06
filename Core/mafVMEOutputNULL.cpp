/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafVMEOutputNULL.cpp,v $
  Language:  C++
  Date:      $Date: 2005-04-11 11:23:20 $
  Version:   $Revision: 1.2 $
  Authors:   Marco Petrone
==========================================================================
  Copyright (c) 2001/2005 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/


#include "mafDefines.h" 
//----------------------------------------------------------------------------
// NOTE: Every CPP file in the MAF must include "mafDefines.h" as first.
// This force to include Window,wxWidgets and VTK exactly in this order.
// Failing in doing this will result in a run-time error saying:
// "Failure#0: The value of ESP was not properly saved across a function call"
//----------------------------------------------------------------------------



#include "mafVMEOutputNULL.h"
#include "mafAbsMatrixPipe.h"
#include "mafDataPipe.h"
#include "mafSmartPointer.h"
#include "mafTransform.h"
#include "mafIndent.h"

#include <assert.h>

//-------------------------------------------------------------------------
mafCxxTypeMacro(mafVMEOutputNULL)
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
mafVMEOutputNULL::mafVMEOutputNULL()
//-------------------------------------------------------------------------
{
}

//-------------------------------------------------------------------------
mafVMEOutputNULL::~mafVMEOutputNULL()
//-------------------------------------------------------------------------
{
}

