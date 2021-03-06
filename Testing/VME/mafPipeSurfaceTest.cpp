/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafPipeSurfaceTest.cpp,v $
Language:  C++
Date:      $Date: 2008-10-08 14:14:32 $
Version:   $Revision: 1.1.2.2 $
Authors:   Matteo Giacomoni
==========================================================================
Copyright (c) 2002/2008
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
#include "mafPipeSurfaceTest.h"
#include "mafPipeSurface.h"

#include "mafSceneNode.h"
#include "mafVMESurface.h"
#include "mmaMaterial.h"

#include "mafVMERoot.h"
#include "vtkMAFAssembly.h"

#include "vtkMapper.h"
#include "vtkJPEGWriter.h"
#include "vtkJPEGReader.h"
#include "vtkWindowToImageFilter.h"
#include "vtkImageMathematics.h"
#include "vtkImageData.h"
#include "vtkPointData.h"
#include "vtkDataSetReader.h"
#include "vtkPolyData.h"

// render window stuff
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"

#include <iostream>

enum PIPE_SURFACE_ACTORS
  {
    PIPE_SURFACE_ACTOR,
    PIPE_SURFACE_ACTOR_WIRED,
    PIPE_SURFACE_ACTOR_OUTLINE_CORNER,
    PIPE_SURFACE_NUMBER_OF_ACTORS,
  };

enum TESTS_PIPE_SURFACE
{
  BASE_TEST,
  EDGE_TEST,
  NORMAL_TEST,
  SCALAR_TEST,
  VTK_PROPERTY_TEST,
  NUMBER_OF_TEST,
};


//----------------------------------------------------------------------------
void mafPipeSurfaceTest::TestFixture()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafPipeSurfaceTest::setUp()
//----------------------------------------------------------------------------
{
  vtkNEW(m_Renderer);
  vtkNEW(m_RenderWindow);
  vtkNEW(m_RenderWindowInteractor);
}
//----------------------------------------------------------------------------
void mafPipeSurfaceTest::tearDown()
//----------------------------------------------------------------------------
{
  vtkDEL(m_Renderer);
  vtkDEL(m_RenderWindow);
  vtkDEL(m_RenderWindowInteractor);
}
//----------------------------------------------------------------------------
void mafPipeSurfaceTest::TestPipeExecution()
//----------------------------------------------------------------------------
{
  ///////////////// render stuff /////////////////////////

  m_Renderer->SetBackground(0.1, 0.1, 0.1);

  m_RenderWindow->AddRenderer(m_Renderer);
  m_RenderWindow->SetSize(320, 240);
  m_RenderWindow->SetPosition(400,0);

  m_RenderWindowInteractor->SetRenderWindow(m_RenderWindow);

  ///////////// end render stuff /////////////////////////


  ////// Create VME (import vtkData) ////////////////////
  vtkDataSetReader *Importer;
  vtkNEW(Importer);
  mafString filename=MAF_DATA_ROOT;
  filename<<"/Test_PipeSurface/surface0.vtk";
  Importer->SetFileName(filename);
  Importer->Update();
  mafVMESurface *surface;
  mafNEW(surface);
  surface->SetData((vtkPolyData*)Importer->GetOutput(),0.0);
  surface->GetOutput()->Update();
  surface->GetMaterial();
  surface->GetMaterial()->m_MaterialType = mmaMaterial::USE_LOOKUPTABLE;
  surface->Update();
  
  //Assembly will be create when instancing mafSceneNode
  mafSceneNode *sceneNode;
  sceneNode = new mafSceneNode(NULL,NULL,surface, NULL);

  /////////// Pipe Instance and Creation ///////////
  mafPipeSurface *pipeSurface = new mafPipeSurface;
  pipeSurface->Create(sceneNode);
  
  ////////// ACTORS List ///////////////
  vtkPropCollection *actorList = vtkPropCollection::New();
  pipeSurface->GetAssemblyFront()->GetActors(actorList);
  
  actorList->InitTraversal();
  vtkProp *actor = actorList->GetNextProp();
  while(actor)
  {   
    m_Renderer->AddActor(actor);
    m_RenderWindow->Render();

    actor = actorList->GetNextProp();
  }
	
	const char *strings[NUMBER_OF_TEST];
	strings[0] = "BASE_TEST";
	strings[1] = "EDGE_TEST";
	strings[2] = "NORMAL_TEST";
	strings[3] = "SCALAR_TEST";
	strings[4] = "VTK_PRPOERTY_TEST";

  for(int i=0;i<NUMBER_OF_TEST;i++)
  {
    if(i == EDGE_TEST)
    {
      pipeSurface->SetEdgeVisibilityOn();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_EDGE_VISIBILITY));

      pipeSurface->GetAssemblyFront()->GetActors(actorList);
  
      actorList->InitTraversal();
      vtkProp *actor = actorList->GetNextProp();
      while(actor)
      {   
        m_Renderer->AddActor(actor);
        m_RenderWindow->Render();

        actor = actorList->GetNextProp();
      }

    }
    else if(i == NORMAL_TEST)
    {
      pipeSurface->SetNormalVisibilityOn();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_NORMAL_VISIBILITY));
      
      pipeSurface->GetAssemblyFront()->GetActors(actorList);
  
      actorList->InitTraversal();
      vtkProp *actor = actorList->GetNextProp();
      while(actor)
      {   
        m_Renderer->AddActor(actor);
        m_RenderWindow->Render();

        actor = actorList->GetNextProp();
      }
    }
    else if(i == SCALAR_TEST)
    {
      pipeSurface->SetScalarVisibilityOn();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_SCALAR_VISIBILITY));
    }
    else if(i == VTK_PROPERTY_TEST)
    {
      pipeSurface->SetUseVtkPropertyOn();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_USE_VTK_PROPERTY));
    }

    vtkActor *surfaceActor;
    surfaceActor = (vtkActor *) SelectActorToControl(actorList, PIPE_SURFACE_ACTOR);
    CPPUNIT_ASSERT(surfaceActor != NULL);

    m_RenderWindow->Render();
	  printf("\n Visualizzazione: %s \n", strings[i]);
    mafSleep(800);
    CompareImages(i);

    if(i == EDGE_TEST)
    {
      pipeSurface->SetEdgeVisibilityOff();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_EDGE_VISIBILITY));
    }
    else if(i == NORMAL_TEST)
    {
      pipeSurface->SetNormalVisibilityOff();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_NORMAL_VISIBILITY));
    }
    else if(i == SCALAR_TEST)
    {
      pipeSurface->SetScalarVisibilityOff();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_SCALAR_VISIBILITY));
    }
    else if(i == VTK_PROPERTY_TEST)
    {
      pipeSurface->SetUseVtkPropertyOff();
      pipeSurface->OnEvent(&mafEvent(this, mafPipeSurface::ID_USE_VTK_PROPERTY));
    }
  }

  vtkDEL(actorList);

  delete pipeSurface;
  delete sceneNode;

  mafDEL(surface);
  vtkDEL(Importer);

  delete wxLog::SetActiveTarget(NULL);
}
//----------------------------------------------------------------------------
void mafPipeSurfaceTest::CompareImages(int scalarIndex)
//----------------------------------------------------------------------------
{
  char *file = __FILE__;
  std::string name(file);
  int slashIndex =  name.find_last_of('\\');

  name = name.substr(slashIndex+1);

  int pointIndex =  name.find_last_of('.');
  name = name.substr(0, pointIndex);

  mafString controlOriginFile=MAF_DATA_ROOT;
  controlOriginFile<<"/Test_PipeSurface/";
  controlOriginFile<<name.c_str();
  controlOriginFile<<"_";
  controlOriginFile<<"image";
  controlOriginFile<<scalarIndex;
  controlOriginFile<<".jpg";

  fstream controlStream;
  controlStream.open(controlOriginFile.GetCStr()); 

  // visualization control
	m_RenderWindow->OffScreenRenderingOn();
  vtkWindowToImageFilter *w2i;
  vtkNEW(w2i);
  w2i->SetInput(m_RenderWindow);
  //w2i->SetMagnification(magnification);
  w2i->Update();
	m_RenderWindow->OffScreenRenderingOff();

  //write comparing image
  vtkJPEGWriter *w;
  vtkNEW(w);
  w->SetInput(w2i->GetOutput());
  mafString imageFile=MAF_DATA_ROOT;

  if(!controlStream)
  {
    imageFile<<"/Test_PipeSurface/";
    imageFile<<name.c_str();
    imageFile<<"_";
    imageFile<<"image";
  }
  else
  {
    imageFile<<"/Test_PipeSurface/";
    imageFile<<name.c_str();
    imageFile<<"_";
    imageFile<<"comp";
  }
  
  imageFile<<scalarIndex;
  imageFile<<".jpg";
  w->SetFileName(imageFile.GetCStr());
  w->Write();

  if(!controlStream)
  {
    controlStream.close();
    vtkDEL(w);
    vtkDEL(w2i);
    return;
  }
  controlStream.close();

  //read original Image
  vtkJPEGReader *rO;
  vtkNEW(rO);
  mafString imageFileOrig=MAF_DATA_ROOT;
  imageFileOrig<<"/Test_PipeSurface/";
  imageFileOrig<<name.c_str();
  imageFileOrig<<"_";
  imageFileOrig<<"image";
  imageFileOrig<<scalarIndex;
  imageFileOrig<<".jpg";
  rO->SetFileName(imageFileOrig.GetCStr());
  rO->Update();

  vtkImageData *imDataOrig = rO->GetOutput();

  //read compared image
  vtkJPEGReader *rC;
  vtkNEW(rC);
  rC->SetFileName(imageFile.GetCStr());
  rC->Update();

  vtkImageData *imDataComp = rC->GetOutput();


  vtkImageMathematics *imageMath = vtkImageMathematics::New();
  imageMath->SetInput1(imDataOrig);
  imageMath->SetInput2(imDataComp);
  imageMath->SetOperationToSubtract();
  imageMath->Update();

  double srR[2] = {-1,1};
  imageMath->GetOutput()->GetPointData()->GetScalars()->GetRange(srR);

  CPPUNIT_ASSERT(srR[0] == 0.0 && srR[1] == 0.0);

  // end visualization control
  vtkDEL(imageMath);
  vtkDEL(rC);
  vtkDEL(rO);

  vtkDEL(w);
  vtkDEL(w2i);
}
//----------------------------------------------------------------------------
vtkProp *mafPipeSurfaceTest::SelectActorToControl(vtkPropCollection *propList, int index)
//----------------------------------------------------------------------------
{
  propList->InitTraversal();
  vtkProp *actor = propList->GetNextProp();
  int count = 0;
  while(actor)
  {   
    if(count == index) return actor;
    actor = propList->GetNextProp();
    count ++;
  }
  return NULL;
}
