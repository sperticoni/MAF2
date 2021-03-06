
/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: mafObjectTest.cpp,v $
Language:  C++
Date:      $Date: 2011-05-25 11:58:32 $
Version:   $Revision: 1.2.4.1 $
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

#include "mafObject.h"
#include "mafObjectTest.h"
#include "vtkMAFSmartPointer.h"
#include "mafString.h"


#include <iostream>
#include <utility>

//creation of test object
class mafTestObject: public mafObject
{
public:
  mafTypeMacro(mafTestObject,mafObject);
};

mafCxxTypeMacro(mafTestObject);

//----------------------------------------------------------------------------
void mafObjectTest::TestFixture()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafObjectTest::setUp()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafObjectTest::tearDown()
//----------------------------------------------------------------------------
{
}
//----------------------------------------------------------------------------
void mafObjectTest::TestStaticAllocation()
//----------------------------------------------------------------------------
{
  mafTestObject obj;
}
//----------------------------------------------------------------------------
void mafObjectTest::TestDynamicAllocation()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestGetStaticTypeName()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  //Return the name of this type (static function)
  mafString static_name = obj->GetStaticTypeName();
  bool ok = static_name.Equals("mafTestObject");
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestGetTypeName()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  //Return the class name of this instance
  mafString static_name = obj->GetStaticTypeName();
  bool ok = static_name.Equals("mafTestObject");
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestIsStaticType()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  const char *type = "mafObject";

  bool ok = obj->IsStaticType(type);
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestIsStaticType2()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  //Return TypeId for this object instance (the real type)
  const mafTypeID &type = obj->GetTypeId();

  bool ok = obj->IsStaticType(type);
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestIsA()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  const char *type = "mafObject";

  bool ok = obj->IsA(type);
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestIsA2()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();

  //Return TypeId for this object instance (the real type)
  const mafTypeID &type = obj->GetTypeId();

  bool ok = obj->IsA(type);
  CPPUNIT_ASSERT(ok);

  mafDEL(obj);
}
//----------------------------------------------------------------------------
void mafObjectTest::TestSafeDownCast()
//----------------------------------------------------------------------------
{
  mafTestObject *obj = mafTestObject::New();
  
  //used for casting from (mafObject *)
  mafTestObject* tmp = mafTestObject::SafeDownCast(obj);

  CPPUNIT_ASSERT(tmp != NULL);

  mafDEL(obj);
}
