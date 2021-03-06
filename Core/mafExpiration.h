/*=========================================================================
  Program:   Multimod Application Framework
  Module:    $RCSfile: mafExpiration.h,v $
  Language:  C++
  Date:      $Date: 2011-05-25 09:35:14 $
  Version:   $Revision: 1.1.2.2 $
  Authors:   Daniele Giunchi
==========================================================================
  Copyright (c) 2002/2004
  CINECA - Interuniversity Consortium (www.cineca.it) 
=========================================================================*/

#ifndef __mafExpiration_H__
#define __mafExpiration_H__

#include "mafConfigure.h"

/**
  Class Name: mafExpiration.
  Abstract class that supplies API for generic expiration.
  Need to specify classes like mafExpiration*Modality* in which a modality of expiration
  is defined.
*/
class MAF_EXPORT mafExpiration  
{
public:
  /** Retrieve result of the expiration criteria */
	virtual bool HasExpired() = 0;
  /** Retrieve a textual information */
  virtual const char* GetInformation() = 0;

  /** constructor. */
	mafExpiration(){};
  /** destructor. */
	virtual ~mafExpiration(){};

private:

};
#endif // mafExpiration