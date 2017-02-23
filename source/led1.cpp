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

static void led1_main(const void *);

/* Box configuration
 * We do not need large stacks in either the main nor the interrupt thread, as
 * we do not do anything special in them. */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(3 * 1024);
UVISOR_BOX_MAIN(led1_main, osPriorityNormal, 512);
UVISOR_BOX_CONFIG(box_led1, acl, 512, box_context);

/* FIXME: The guard is needed for backwards-compatibility reasons. Remove it
 *        when mbed OS is updated. */
#ifdef __uvisor_ctx
#define uvisor_ctx ((box_context *) __uvisor_ctx)
#endif

static void led1_main(const void *)
{
    DigitalOut led1(LED1);
    led1 = LED_OFF;
    const uint32_t kB = 1024;

    SecureAllocator alloc = secure_allocator_create_with_pages(4 * kB, 1 * kB);

    while (1) {
        static const size_t size = 50;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        led1 = !led1;
        ++uvisor_ctx->heartbeat;
        alloc_fill_wait_verify_free(size, seed, 211);
        specific_alloc_fill_wait_verify_free(alloc, 5 * kB, seed, 107);
    }
}
