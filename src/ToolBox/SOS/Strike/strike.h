//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information. 
//

// ==++==
// 
 
// 
// ==--==
#ifndef __strike_h__
#define __strike_h__

#ifndef _countof
#define _countof(x) (sizeof(x)/sizeof(x[0]))
#endif


#if defined(_MSC_VER)
#pragma warning(disable:4245)   // signed/unsigned mismatch
#pragma warning(disable:4100)   // unreferenced formal parameter
#pragma warning(disable:4201)   // nonstandard extension used : nameless struct/union
#pragma warning(disable:4127)   // conditional expression is constant
#pragma warning(disable:6255)   // Prefast: alloca indicates failure by raising a stack overflow exception
#endif

#include <winternl.h>
#include <winver.h>
#include <windows.h>
    
#include <wchar.h>

//#define NOEXTAPI
#define KDEXT_64BIT
#include <wdbgexts.h>
#undef DECLARE_API
#undef GetContext
#undef SetContext
#undef ReadMemory
#undef WriteMemory
#undef GetFieldValue
#undef StackTrace

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <malloc.h>
#include <stddef.h>

#ifndef FEATURE_PAL
#include <basetsd.h>  
#endif

#define  CORHANDLE_MASK 0x1

#include "static_assert.h"

// exts.h includes dbgeng.h which has a bunch of IIDs we need instantiated.
#define INITGUID
#include "guiddef.h"

#include "exts.h"

//Alignment constant for allocation
#if defined(_TARGET_X86_) || defined(_TARGET_ARM_)
#define ALIGNCONST 3
#else
#define ALIGNCONST 7
#endif

//The large object heap uses a different alignment
#define ALIGNCONSTLARGE 7

#ifdef _WIN64
#define SIZEOF_OBJHEADER    8
#else // !_WIN64
#define SIZEOF_OBJHEADER    4
#endif // !_WIN64

#define plug_skew           SIZEOF_OBJHEADER
#define min_obj_size        (sizeof(BYTE*)+plug_skew+sizeof(size_t))

#ifdef FEATURE_PAL
#define SOS_PTR(x) (size_t)(x)
#else // FEATURE_PAL
#define SOS_PTR(x) (unsigned __int64)(x)
#endif // FEATURE_PAL else

extern BOOL CallStatus;


#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

HRESULT SetNGENCompilerFlags(DWORD flags);


#endif // __strike_h__
