/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafAction.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 11:35:56 $
  Version:   $Revision: 1.4.4.2 $
  Authors:   Marco Petrone
==========================================================================
  Copyright (c) 2002/2004 
  CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __mafAction_h
#define __mafAction_h

#include "mafAgent.h"
#include "mafStorable.h"
#include "mafSmartPointer.h"
#include <list>

//----------------------------------------------------------------------------
// forward declarations :
//----------------------------------------------------------------------------
template <class T> class vtkTemplatedList;
class mafDevice;
class mafInteractor;
class vtkRenderer;

/** Class used to route events from devices to interactors */
class MAF_EXPORT mafAction : public mafAgent, public mafStorable
{
public:
  /** @ingroup Events */
  /** @{ */
  MAF_ID_DEC(DEVICE_BIND);            ///< force the action to bind to the device
  MAF_ID_DEC(QUERY_CONNECTED_DEVICES);///< Issued by interactors to query for connected devices. @sa ConnectedDeviceEvent
  MAF_ID_DEC(DEVICE_PLUGGED);         ///< Issued by devices when connected to actions or when queried.
  MAF_ID_DEC(DEVICE_UNPLUGGED);       ///< Issued by devices when connected to actions or when queried.

  enum ACTION_TYPE
  {
    SHARED_ACTION = 0, 
    EXCLUSIVE_ACTION 
  };

  typedef std::list<mafAutoPointer<mafDevice> > mmuDeviceList;
  
  mafTypeMacro(mafAction,mafAgent);

  /** Set the type of action*/
  int GetType() {return m_Type;}
  void SetType(int t) {if (t==SHARED_ACTION||t==EXCLUSIVE_ACTION) m_Type=t;}
  void SetTypeToShared() {SetType(SHARED_ACTION);}
  void SetTypeToExclusive() {SetType(EXCLUSIVE_ACTION);}
  
  /** Bind/Unbind a device to this action */
  void BindDevice(mafDevice *device);
  void UnBindDevice(mafDevice *device);

  /** Bind/Unbind an interactor to this action */
  void BindInteractor(mafInteractor *inter);
  void UnBindInteractor(mafInteractor *inter);

  /** Get list of devices assigned to this action */
  const mmuDeviceList *GetDevices() {return &m_Devices;}

  /** Store of action's bindings to an XML file. */
  virtual int InternalStore(mafStorageElement *node);

  /** Restore of action's bindings from an XML file.*/
  virtual int InternalRestore(mafStorageElement *node);

  /** Redefined to answer incoming queries about connected devices. */
  virtual void OnEvent(mafEventBase *event);

protected:
  mafAction();
  virtual ~mafAction();

  int   m_Type;
  std::list<mafAutoPointer<mafDevice> > m_Devices;

private:
  mafAction(const mafAction&);  // Not implemented.
  void operator=(const mafAction&);  // Not implemented.
};

#endif 
