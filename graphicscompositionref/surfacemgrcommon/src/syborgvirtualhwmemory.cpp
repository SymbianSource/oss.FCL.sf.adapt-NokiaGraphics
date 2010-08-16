// Copyright (c) 2006-2009 Nokia Corporation and/or its subsidiary(-ies).
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

#include "syborgvirtualhwmemory.h"

DVirtualHWMemoryManager::DVirtualHWMemoryManager(TUint32 aBase, TInt aMaxSize):
        iRoot(0, aBase),
        iLast(0, aBase + aMaxSize)
        {
        iRoot.iNext = &iLast;
        }
    
TUint32 DVirtualHWMemoryManager::Allocate(TInt aSize)
        {
        TUint32 address(NULL);
        TAllocatedCell* current(&iRoot);
        TAllocatedCell* next(iRoot.iNext);
        while (next)
            {
            const TInt freeBetweenCells = next->iBase - (current->iBase + current->iSize);
            if (freeBetweenCells >= aSize )
                {
                //Mark area as allocated
                address = current->iBase + current->iSize;
                TAllocatedCell* newCell = new TAllocatedCell(aSize, address);
                if (!newCell)
                    {
                    return NULL;
                    }
                newCell->iNext = next;
                current->iNext = newCell;
                break;
                }
            else
                {
                current = next;
                next = next->iNext;
                }
            }
        return address;
        }
    
    void DVirtualHWMemoryManager::Deallocate(const TUint32 aPhysicalAddress)
        {
        TAllocatedCell* prev(&iRoot);
        TAllocatedCell* next(iRoot.iNext);
        while (next)
            {
            if (next->iBase == aPhysicalAddress)
                {
                prev->iNext = next->iNext;
                delete next;
                next = NULL;
                }
            else
                {
                prev = next;
                next = next->iNext;
                }
            }
        }

    DVirtualHWMemoryManager::~DVirtualHWMemoryManager()
        {
        TAllocatedCell* next(iRoot.iNext);
        while (next)
            {
            TAllocatedCell* deletethis = next;
            next = next->iNext;
            if (deletethis != &iLast)
                {
                delete deletethis;
                }
            }
        }
