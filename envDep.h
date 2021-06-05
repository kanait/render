////////////////////////////////////////////////////////////////////
//
// $Id: envDep.h 2021/06/05 13:22:49 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _ENVDEP_H
#define _ENVDEP_H

#ifdef HAVE_CONFIG_H
#else
#endif

#ifdef _MSC_VER
# pragma warning(disable:4018)
# pragma warning(disable:4244)
# pragma warning(disable:4267)
# pragma warning(disable:4305)
# pragma warning(disable:4503)
# pragma warning(disable:4786)
# pragma warning(disable:4996)
#undef HAVE_UNISTD_H
#undef HAVE_BZERO
#else
//#include "config.h"
#endif

#if defined(WIN32)
#include <windows.h>
#endif

#if defined(_WINDOWS)
//#include "stdafx.h"
#endif

// M_PI
#ifdef WIN32
#define M_PI		3.14159265358979323846

/*  #if !defined(__MINGW32__) */
/*  #define M_SQRT3		1.732051	// sqrt(3) */
/*  #endif */

#endif // WIN32

#endif // _ENVDEP_H
