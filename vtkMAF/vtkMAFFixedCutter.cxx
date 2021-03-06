/*=========================================================================

  Program:   Multimod Fundation Library
  Module:    $RCSfile: vtkMAFFixedCutter.cxx,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:53:13 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Silvano Imboden 
  Project:   MultiMod Project (www.ior.it/multimod)

==========================================================================*/

#include "vtkMAFFixedCutter.h"
#include "vtkViewport.h"
#include "vtkObjectFactory.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkPointData.h"
#include "vtkDataSet.h"

vtkCxxRevisionMacro(vtkMAFFixedCutter, "$Revision: 1.1.2.1 $");
vtkStandardNewMacro(vtkMAFFixedCutter);

//----------------------------------------------------------------------------
vtkMAFFixedCutter::vtkMAFFixedCutter()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
vtkMAFFixedCutter::~vtkMAFFixedCutter()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void vtkMAFFixedCutter::Execute()
//----------------------------------------------------------------------------
{
  vtkCutter::Execute();
  
  if(this->GetOutput()->GetNumberOfPoints() == 0)
  {
	  vtkPoints *pts = vtkPoints::New();
	  pts->InsertNextPoint(this->GetInput()->GetCenter());
    this->GetOutput()->SetPoints(pts);
    pts->Delete();
  }
  this->GetOutput()->GetPointData()->SetNormals(NULL);
}
