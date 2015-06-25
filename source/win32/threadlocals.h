#ifndef WEBAPP_THREAD_LOCALS_H__
#define WEBAPP_THREAD_LOCALS_H__
#include <Windows.h>
#include <WinBase.h>

class ThreadLocals 
{
public:
    typedef DWORD Slot;
    static Slot Alloc();
    static void* GetValue(Slot slot);
    static BOOL SetValue(Slot slot, void* value);
};


#endif //WEBAPP_THREAD_LOCALS_H__