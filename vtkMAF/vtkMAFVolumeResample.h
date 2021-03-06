/*=========================================================================

  Program:   Multimod Fundation Library
  Module:    $RCSfile: vtkMAFVolumeResample.h,v $
  Language:  C++
  Date:      $Date: 2009-02-10 16:03:54 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Alexander Savenko
  Project:   MultiMod Project (www.ior.it/multimod)

==========================================================================
  Copyright (c) 2002 
  CINECA - Interuniversity Consortium (www.cineca.it)
  v. Magnanelli 6/3
  40033 Casalecchio di Reno (BO)
  Italy
  ph. +39-051-6171411 (90 lines) - Fax +39-051-6132198

Use, modification and redistribution of the software, in source or
binary forms, are permitted provided that the following terms and
conditions are met:

1) Redistribution of the source code, in verbatim or modified
   form, must retain the above copyright notice, this license,
   the following disclaimer, and any notices that refer to this
   license and/or the following disclaimer.  

2) Redistribution in binary form must include the above copyright
   notice, a copy of this license and the following disclaimer
   in the documentation or with other materials provided with the
   distribution.

3) Modified copies of the source code must be clearly marked as such,
   and must not be misrepresented as verbatim copies of the source code.

THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE SOFTWARE "AS IS"
WITHOUT EXPRESSED OR IMPLIED WARRANTY INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  IN NO EVENT SHALL ANY COPYRIGHT HOLDER OR OTHER PARTY WHO MAY
MODIFY AND/OR REDISTRIBUTE THE SOFTWARE UNDER THE TERMS OF THIS LICENSE
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, LOSS OF DATA OR DATA BECOMING INACCURATE
OR LOSS OF PROFIT OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF
THE USE OR INABILITY TO USE THE SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

=========================================================================*/
// .NAME vtkMAFVolumeResample- a filter for creating slices from structured volume data (rectilinear grid or structured points)
//
// .SECTION Description
// Inputs of the filter are:
//   volume (vtkRectilinearGrid or vtkImageData)
//   plane definition: origin and two vectors that define the axes of the image rectangle
//   color mapping: window and level of color mapping
//   
// Outputs of the filter are:
//   image (vtkImageData): The resolution and spacing of the output volume image should be specified by consumer. 
//                         The origin will be automatically set to zero.
//   polyline slice (vtkPolyData): This output includes both the polyline that define the cut of a plane and corresponded triangles. The texture coordinates are provided as well.
// .SECTION See Also
// vtkProbeFilter, vtkPlaneSource

#ifndef __vtkMAFVolumeResample_h
#define __vtkMAFVolumeResample_h

#include "vtkMAFConfigure.h"
#include "vtkDataSetToDataSetFilter.h"
#include "vtkImageData.h"

//class vtkImageData;
class vtkRectilinearGrid;


class VTK_vtkMAF_EXPORT vtkMAFVolumeResample: public vtkDataSetToDataSetFilter {
public:
  static vtkMAFVolumeResample*New();
  vtkTypeRevisionMacro(vtkMAFVolumeResample, vtkDataSetToDataSetFilter);
  
  void PrintSelf(ostream& os, vtkIndent indent);

  /**
  Specify a point defining the origin of the plane.*/
  vtkSetVector3Macro(VolumeOrigin, double);
  vtkGetVectorMacro(VolumeOrigin, double, 3);

  /**
  Specify x-axis of the plane*/
  void SetVolumeAxisX(double axis[3]);
  vtkGetVectorMacro(VolumeAxisX, double, 3);

  /**
  Specify x-axis of the plane*/
  void SetVolumeAxisY(double axis[3]);
  vtkGetVectorMacro(VolumeAxisY, double, 3);

  /**
  Set / Get the Window for color modulation. The formula for modulation is 
  (S - (L - W/2))/ W where S is the scalar value, L is the level and W is the window.*/
  vtkSetMacro( Window, double );
  vtkGetMacro( Window, double );
  
  /**
  Set / Get the Level to use -> modulation will be performed on the 
  color based on (S - (L - W/2))/W where S is the scalar value, L is
  the level and W is the window.*/
  vtkSetMacro( Level, double );
  vtkGetMacro( Level, double );

  /**
  Set/Get the value used for padding empty areas*/
  vtkSetMacro( ZeroValue, double );
  vtkGetMacro( ZeroValue, double );
  

  /**
  Set/get auto-spacing feature. In this mode the image spacing is selected automatically to fit the whole slice*/
  vtkSetMacro( AutoSpacing, int );
  vtkGetMacro( AutoSpacing, int );
  vtkBooleanMacro(AutoSpacing, int );

  void SetOutput(vtkImageData *data) { vtkDataSetSource::SetOutput(data); }

protected:
  vtkMAFVolumeResample();
  ~vtkMAFVolumeResample();

  void ExecuteInformation();
  void ExecuteData(vtkDataObject *output);
  
  void ExecuteData(vtkImageData *output);

  void ComputeInputUpdateExtents(vtkDataObject *output);

  void PrepareVolume();
  void CalculateTextureCoordinates(const double point[3], const int size[2], const double spacing[2], double ts[2]);

  template<typename InputDataType, typename OutputDataType> void CreateImage(const InputDataType *input, OutputDataType *output, vtkImageData *outputObject);

  // plane coordinates
  double VolumeOrigin[3];
  double VolumeAxisX[3];
  double VolumeAxisY[3];
  double VolumeAxisZ[3];

  double ZeroValue;

  // color mapping
  double Window;
  double Level;

  int   AutoSpacing;

  // look-up tables and caches
  vtkTimeStamp PreprocessingTime;

  double*       VoxelCoordinates[3];
  double        DataOrigin[3];
  double        DataBounds[3][2];
  int           DataDimensions[3];
  double        SamplingTableMultiplier[3];

private:
  vtkMAFVolumeResample(const vtkMAFVolumeResample&);  // Not implemented.
  void operator=(const vtkMAFVolumeResample&);  // Not implemented.
};

#endif

