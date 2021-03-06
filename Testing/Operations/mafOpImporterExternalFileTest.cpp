/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafOpImporterExternalFileTest.cpp,v $
Language:  C++
Date:      $Date: 2007-09-17 11:24:35 $
Version:   $Revision: 1.1 $
Authors:   Roberto Mucci
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

#include <cppunit/config/SourcePrefix.h>

#include "mafOpImporterExternalFileTest.h"
#include "mafOpImporterExternalFile.h"
#include "mafVMEFactory.h"
#include "mafString.h"
#include "mafVMERoot.h"
#include "mafVMEStorage.h"
#include <iostream>

//----------------------------------------------------------------------------
void mafOpImporterExternalFileTest::TestFixture()
//----------------------------------------------------------------------------
{
}

//----------------------------------------------------------------------------
void mafOpImporterExternalFileTest::setUp()
//----------------------------------------------------------------------------
{
}

//----------------------------------------------------------------------------
void mafOpImporterExternalFileTest::tearDown()
//----------------------------------------------------------------------------
{
}

//----------------------------------------------------------------------------
void mafOpImporterExternalFileTest::TestConstructor()
//----------------------------------------------------------------------------
{
  //check memory leaks mad by constructor
  mafOpImporterExternalFile *importerExternalFile  = new mafOpImporterExternalFile("importerExtFile");
  mafDEL(importerExternalFile);
}

//----------------------------------------------------------------------------
void mafOpImporterExternalFileTest::TestImporter()
//----------------------------------------------------------------------------
{
  mafVMEStorage *storage = mafVMEStorage::New();
  storage->GetRoot()->SetName("root");

  // in order to create VME from storage I need the factory to be initialized
  mafVMEFactory::Initialize();

	mafOpImporterExternalFile *importer=new mafOpImporterExternalFile("importer");
	importer->SetInput(storage->GetRoot());
	mafString filename=MAF_DATA_ROOT;
  filename<<"/Test_ImporterExternalFile/ExternalFile.doc";
  importer->SetFileName(filename.GetCStr());
  importer->OpRun();

  mafNode *node = importer->GetOutput();
  //Check if the VME is of the right kinnd
  bool type = node->IsA("mafVMEExternalData");
  CPPUNIT_ASSERT(type);

  //check the name of the Group imported by the importerExternalFile
  mafString name = node->GetName();
  CPPUNIT_ASSERT(name.Compare("ExternalFile.doc") == 0);
 
  mafDEL(importer);
  mafDEL(storage);
}
