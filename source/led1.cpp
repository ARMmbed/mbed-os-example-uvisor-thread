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

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(8192);
UVISOR_BOX_MAIN(led1_main, osPriorityNormal, UVISOR_BOX_STACK_SIZE);
UVISOR_BOX_CONFIG(box_led1, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led1_main(const void *)
{
    DigitalOut led1(LED1);
    led1 = LED_OFF;
    const uint32_t kB = 1024;

    SecureAllocator alloc = secure_allocator_create_with_pages(4*kB, 1*kB);

    while (1) {
        static const size_t size = 500;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        led1 = !led1;
        ++uvisor_ctx->heartbeat;
        alloc_fill_wait_verify_free(size, seed, 211);
        specific_alloc_fill_wait_verify_free(alloc, 5*kB, seed, 107);
    }
}
