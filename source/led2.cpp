#include "fun_bag.h"
#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread * thread;
    uint32_t heartbeat;
};

static const UvisorBoxAclItem acl[] = {
};

static void led2_main(const void *);

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(8192);
UVISOR_BOX_MAIN(led2_main, osPriorityNormal, UVISOR_BOX_STACK_SIZE);
UVISOR_BOX_CONFIG(box_led2, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led2_main(const void *)
{
    DigitalOut led2(LED2);
    led2 = LED_OFF;
    const uint32_t kB = 1024;
    SecureAllocator alloc;

    /* Create one allocator with two non-consecutive pages,
     * by attempting to create a hole in the page allocator.
     * This simulates a fragmented page heap, but note, that
     * this method is not guaranteed to create a fragemented
     * page heap!
     */
    /* Allocate one page. */
    alloc = secure_allocator_create_with_pages(4*kB, 1*kB);
    /* Allocate another page. */
    SecureAllocator alloc2 = secure_allocator_create_with_pages(4*kB, 1*kB);
    /* Deallocate alloc1 page, creating a hole. */
    secure_allocator_destroy(alloc);
    /* Allocate two pages. */
    alloc = secure_allocator_create_with_pages(UVISOR_PAGE_SIZE + 12*kB, 6*kB);
    /* Deallocate alloc2 page, creating another hole. */
    secure_allocator_destroy(alloc2);

    while (1) {
        static const size_t size = 300;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        led2 = !led2;
        ++uvisor_ctx->heartbeat;
        alloc_fill_wait_verify_free(size, seed, 311);

        /* Allocate in first page */
        specific_alloc_fill_wait_verify_free(alloc, 14*kB, seed, 0);

        /* Allocate in second page */
        specific_alloc_fill_wait_verify_free(alloc, 14*kB, seed, 101);
    }
}
