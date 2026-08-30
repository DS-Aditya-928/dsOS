#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

typedef struct
{
    size_t sizeStatus;
} blockHeader_t;

#define GET_SIZE(header) ((header)->sizeStatus & ~(ALIGNMENT - 1))
#define IS_ALLOC(header) ((header)->sizeStatus & 1)
#define PACK(size, alloc) ((size) | (alloc))
#define NEXT_BLOCK(header) ((blockHeader_t*)((char*)(header) + GET_SIZE(header)))

static blockHeader_t* heapStart = NULL;
static blockHeader_t* heapEnd = NULL;

void heapInit(void* start, size_t totalSize)
{
    size_t aligned_size = totalSize & ~(ALIGNMENT - 1);

    heapStart = (blockHeader_t*)start;
    heapEnd = (blockHeader_t*)((char*)start + aligned_size);

    heapStart->sizeStatus = PACK(aligned_size, 0);
}

void* malloc(size_t size)
{
    if (size == 0 || heapStart == NULL)
        return NULL;

    // size required aligned n rounded up
    size_t required_size = ALIGN(size + sizeof(blockHeader_t));

    blockHeader_t* current = heapStart;
    while (current < heapEnd)
    {
        size_t blockSize = GET_SIZE(current);

        if (!IS_ALLOC(current) && blockSize >= required_size)
        {
            if ((blockSize - required_size) >= (sizeof(blockHeader_t) + ALIGNMENT))
            {
                current->sizeStatus = PACK(required_size, 1);

                blockHeader_t* next = NEXT_BLOCK(current);
                next->sizeStatus = PACK(blockSize - required_size, 0);
            }

            else
            {
                current->sizeStatus = PACK(blockSize, 1);
            }

            return (void*)((char*)current + sizeof(blockHeader_t));
        }

        current = NEXT_BLOCK(current);
    }

    return NULL;
}

void free(void* ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    blockHeader_t* header = (blockHeader_t*)((char*)ptr - sizeof(blockHeader_t));

    size_t blockSize = GET_SIZE(header);
    header->sizeStatus = PACK(blockSize, 0);
    blockHeader_t* next = NEXT_BLOCK(header);

    if (next < heapEnd && !IS_ALLOC(next))
    {
        size_t next_size = GET_SIZE(next);
        header->sizeStatus = PACK(blockSize + next_size, 0);
    }
}

void* calloc(size_t nMemb, size_t size)
{
    if (nMemb == 0 || size == 0)
    {
        return NULL;
    }

    if (size > SIZE_MAX / nMemb)
    {
        return NULL;
    }

    size_t totalSize = nMemb * size;
    void* ptr = malloc(totalSize);

    if (ptr != NULL)
    {
        memset(ptr, 0, totalSize);
    }

    return ptr;
}

void* realloc(void* ptr, size_t size)
{
    if (ptr == NULL)
    {
        return malloc(size);
    }

    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    blockHeader_t* header = (blockHeader_t*)((char*)ptr - sizeof(blockHeader_t));
    size_t oldPayloadSize = GET_SIZE(header) - sizeof(blockHeader_t);

    if (oldPayloadSize >= size)
    {
        return ptr;
    }

    void* newPtr = malloc(size);
    if (newPtr == NULL)
    {
        return NULL;
    }

    memcpy(newPtr, ptr, oldPayloadSize);
    free(ptr);

    return newPtr;
}

void* aligned_alloc(size_t alignment, size_t size)
{
    if (size % alignment != 0)
    {
        return NULL;
    }

    if (alignment <= ALIGNMENT)
    {
        return malloc(size);
    }

    return NULL;
}

static unsigned long int next = 1;
int rand(void)
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}