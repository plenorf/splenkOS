#ifndef __SPLENK__MemoryManager_H
#define __SPLENK__MemoryManager_H


namespace spkenk
{

    struct MemoryBlock
    {
        MemoryBlock *next;
        MemoryBlock *prev;
        bool allocated;
        size_t size;
    };
    

    class MemoryManager
    {

    };
} // namespace spkenk


#endif // __SPLENK__MemoryManager_H