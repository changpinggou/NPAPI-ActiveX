#include "threadlocals.h"

ThreadLocals::Slot ThreadLocals::Alloc()
{
    return TlsAlloc();
}

void* ThreadLocals::GetValue(Slot slot)
{
    return TlsGetValue(slot);
}

BOOL ThreadLocals::SetValue(Slot slot, void* value)
{
    return TlsSetValue(slot,value);
}