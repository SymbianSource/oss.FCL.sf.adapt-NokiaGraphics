// Copyright (c) 2006-2010 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Syborg Virtual Hardware Memory implementation

/**
 @file
 @internalTechnology
 @prototype
*/

#ifndef __SYBORGVIRTUALHWMEMORY_H__
#define __SYBORGVIRTUALHWMEMORY_H__

#include <klib.h>
#include <graphics/virtualvideohwinterface.h>
#include <graphics/guestvideodriverinterfaceconstants.h>

/**

Very simple memory manager for platsim virtual HW memory

*/
class DVirtualHWMemoryManager: public DBase
    {
    struct TAllocatedCell
        {
        TAllocatedCell( TInt aSize, TUint32 aBase ):
            iSize( aSize ),
            iBase( aBase ),
            iNext( NULL )
            {
            }
        
        TInt iSize;
        TUint32 iBase;
        TAllocatedCell* iNext;
        };
    
public:
    DVirtualHWMemoryManager(TUint32 aBase, TInt aMaxSize);
    
    TUint32 Allocate(TInt aSize);
    
    void Deallocate(const TUint32 aPhysicalAddress);

    ~DVirtualHWMemoryManager();

private:
    TAllocatedCell iRoot;
    TAllocatedCell iLast;
    };

#endif
