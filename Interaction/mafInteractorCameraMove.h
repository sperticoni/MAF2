/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafInteractorCameraMove.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:40:18 $
  Version:   $Revision: 1.1.2.2 $
  Authors:   Paolo Quadrani & Marco Petrone
==========================================================================
  Copyright (c) 2002/2004 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __mafInteractorCameraMove_h
#define __mafInteractorCameraMove_h

#define MOUSE_CAMERA_START  0
#define MOUSE_CAMERA_NONE   0

#define MOUSE_CAMERA_ROTATE 1
#define MOUSE_CAMERA_PAN    2
#define MOUSE_CAMERA_SPIN   3
#define MOUSE_CAMERA_DOLLY  4
#define MOUSE_CAMERA_ZOOM   5
#define MOUSE_CAMERA_LINKED_PAN 6
#define MOUSE_CAMERA_LINKED_DOLLY  7
#define MOUSE_CAMERA_LINKED_ROTATE  8

#include "mafInteractor.h"
#include "mafMTime.h"

//----------------------------------------------------------------------------
// forward declarations :
//----------------------------------------------------------------------------
class mafDeviceButtonsPadMouse;
class vtkCamera;

/** implements mouse move of camera in the scene.
  This class implements a mouse move of the renderer camera in the scene. The interaction
  modality is a mouse manipulation, where movements of the mouse are mapped
  into movements of the camera. More details to be written...*/
class MAF_EXPORT mafInteractorCameraMove : public mafInteractor
{
public:
  mafTypeMacro(mafInteractorCameraMove,mafInteractor);

  /** Start the interaction with the selected object */
  virtual int StartInteraction(mafDeviceButtonsPadMouse *mouse);

  /**  Process events coming from tracker */
  virtual void OnEvent(mafEventBase *event);

  virtual void OnMouseMove();
  virtual void OnLeftButtonDown(mafEventInteraction *e);
  virtual void OnLeftButtonUp();
  virtual void OnMiddleButtonDown(mafEventInteraction *e);
  virtual void OnMiddleButtonUp();
  virtual void OnRightButtonDown(mafEventInteraction *e);
  virtual void OnRightButtonUp();

  virtual void Rotate();
  virtual void Spin();
  virtual void Pan();
  virtual void Dolly();

  virtual void LinkedDolly();
  virtual void LinkedPan();
  virtual void LinkedRotate();

  virtual void StartRotate();
  virtual void EndRotate();
  virtual void StartZoom();
  virtual void EndZoom();
  virtual void StartPan();
  virtual void EndPan();
  virtual void StartSpin();
  virtual void EndSpin();
  virtual void StartDolly();
  virtual void EndDolly();

  virtual void StartState(int newstate);
  virtual void StopState();

  void ResetClippingRange(); // to work with layers

  /** Add vtkCamera to the link vector camera.*/
  void AddLinkedCamera(vtkCamera *cam);

  /** Remove a linked camera at a given index of the linking vector. */
  void RemoveLinkedCamera(vtkCamera *cam);

  /** Remove all linked camera from the link camera vector.*/
  void RemoveAllLinkedCamera();

  virtual void AutoResetClippingRangeOn();
  virtual void AutoResetClippingRangeOff();

protected:
  mafInteractorCameraMove();
  virtual ~mafInteractorCameraMove();

  virtual void OnButtonDown(mafEventInteraction *e);
  
  virtual void OnButtonUp(mafEventInteraction *e);

  /** Test if m_CurrentCamera is present into the linked vector cameras.*/
  bool CameraIsPresent();

  float         m_MotionFactor;
  int           m_State;  

  int           m_MousePose[2];
  int           m_LastMousePose[2];
  int           m_ButtonPressed;
  bool          m_ActiveCameraToCurrentCameraFlag;
  vtkCamera*    m_CurrentCamera;  ///< Stores camera to which the interaction is currently assigned
  mafMTime      m_UpdateTime;     ///< Time stamp of the last update of the tracker to world transformation 
  std::vector<vtkCamera *> m_LinkedCamera; ///< List of vtkCamera which will be forwarded the motion according to the main camera that is the camera in which the user is interacting with.
  bool			m_AutoResetClippingRange; // Turn on (default)-off the auto reset of clipping range

private:
  mafInteractorCameraMove(const mafInteractorCameraMove&);  // Not implemented.
  void operator=(const mafInteractorCameraMove&);  // Not implemented.
};
#endif 
