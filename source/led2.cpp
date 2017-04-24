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

/* Box configuration
 * We do not need large stacks in either the main nor the interrupt thread, as
 * we do not do anything special in them. */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(3 * 1024);
UVISOR_BOX_MAIN(led2_main, osPriorityNormal, 512);
UVISOR_BOX_CONFIG(box_led2, acl, 512, box_context);

#define uvisor_ctx ((box_context *) __uvisor_ctx)

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
    alloc = secure_allocator_create_with_pages(4 * kB, 1 * kB);
    /* Allocate another page. */
    SecureAllocator alloc2 = secure_allocator_create_with_pages(4 * kB, 1 * kB);
    /* Deallocate alloc1 page, creating a hole. */
    secure_allocator_destroy(alloc);
    /* Allocate two pages. */
    alloc = secure_allocator_create_with_pages(uvisor_get_page_size() + 3 * kB, 6 * kB);
    /* Deallocate alloc2 page, creating another hole. */
    secure_allocator_destroy(alloc2);

    while (1) {
        static const size_t size = 30;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        led2 = !led2;
        ++uvisor_ctx->heartbeat;
        alloc_fill_wait_verify_free(size, seed, 311);

        /* Allocate in first page */
        specific_alloc_fill_wait_verify_free(alloc, 6 * kB, seed, 0);

        /* Allocate in second page */
        specific_alloc_fill_wait_verify_free(alloc, 6 * kB, seed, 101);
    }
}
