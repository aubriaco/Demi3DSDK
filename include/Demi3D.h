
#ifndef __DEMI3D_INCLUDED__
#define __DEMI3D_INCLUDED__

#include "DmRoot.h"
#include "DmDevice.h"
#include "DmScene.h"
#include "DmEntity.h"
#include "DmTypes.h"
#include "DmArray.h"
#include "DmString.h"
#include "DmEntity.h"
#include "DmCubeEntity.h"
#include "DmMeshEntity.h"
#include "DmLightEntity.h"
#include "DmResource.h"
#include "DmTexture.h"
#include "DmSystem.h"
#include "DmArray.h"
#include "DmList.h"
#include "DmSMesh.h"
#include "DmColor.h"
#include "DmMaterial.h"
#include "DmEffects.h"
#include "DmMatrix.h"

#ifndef _CRT_SECURE_NO_DEPRECATE
#	define _CRT_SECURE_NO_DEPRECATE
#endif

#define DEMI3D_API

#if defined(_STDCALL_SUPPORTED)
#	define DEMI3DCALL __stdcall
#endif

namespace demi
{
	extern DEMI3D_API DmDevice * createDemiDevice(int width,int height,int bits,bool fullscreen,const char * title);
}



#endif

/**
\mainpage Demi3D Documentation
\section intro Introduction
Welcome to the Demi3D API Documentation. This will give you specific information
on how to use the Demi3D API.
*/
