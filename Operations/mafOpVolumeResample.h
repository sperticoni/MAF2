/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafOpVolumeResample.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:49:23 $
  Version:   $Revision: 1.1.2.1 $
  Authors:   Marco Petrone
==========================================================================
Copyright (c) 2002/2004
CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __mafOpVolumeResample_H__
#define __mafOpVolumeResample_H__

//----------------------------------------------------------------------------
// Include :
//----------------------------------------------------------------------------
#include "mafOp.h"

//----------------------------------------------------------------------------
// forward references :
//----------------------------------------------------------------------------
class mafEvent;
class mafVME;
class mafVMEGizmo;
class vtkOutlineSource;
class mafVMEVolumeGray;

//----------------------------------------------------------------------------
class MAF_EXPORT mafOpVolumeResample: public mafOp
{
public:
             
            	 mafOpVolumeResample(const wxString &label = "VolumeResample");
	virtual     ~mafOpVolumeResample();
	virtual void OnEvent(mafEventBase *maf_event);
	
  mafTypeMacro(mafOpVolumeResample, mafOp);

  mafOp* Copy();

	bool Accept(mafNode* vme);
	void OpRun();	
	void OpDo();
	void OpUndo();  

	/**
	Set spacing for test mode*/
	void SetSpacing(double Spacing[3]);

	/**
	Set bounds for test mode*/
	void SetBounds(double Bounds[6],int Type);

	/**
	Resample the input volume*/
	void Resample();

protected:
  mafVMEVolumeGray *m_ResampledVme;

	double m_OldVolumePosition[3];
	double m_NewVolumePosition[3];
	double m_PrecedentPosition[3];
	
  double m_VolumePosition[3];
  double m_VolumeOrientation[3];
  double m_VolumeSpacing[3];
  double m_VolumeBounds[6];

  double m_ZeroPadValue;

	//gizmo's functions
	void CreateGizmoCube();
  virtual void CreateGui();
	void ShiftCenterResampled();
	void UpdateGizmoData();
	void UpdateGui();
	void GizmoDelete();

  // Set resample bounds to some defaults
  void SetBoundsToVMEBounds();
  void SetBoundsToVME4DBounds();
  void SetBoundsToVMELocalBounds();

  void AutoSpacing();

  void InternalUpdateBounds(double bounds[6],bool center);

	vtkOutlineSource *m_ResampleBox;

	mafVMEGizmo *m_ResampleBoxVme;
};
#endif
