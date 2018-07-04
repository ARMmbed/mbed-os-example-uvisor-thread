#include "fun_bag.h"
#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    uint32_t heartbeat;
    int toggle;
};

static const UvisorBoxAclItem acl[] = {
};

static void led3_main(const void *);

/* Box configuration
 * We need at least 1kB in the main thread as we use printf in it. The interrupt
 * stack size can be smaller as we do not do anything special in them. */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(2 * 1024);
UVISOR_BOX_MAIN(led3_main, osPriorityNormal, 1024);
UVISOR_BOX_CONFIG(box_led3, acl, 512, box_context);

#define uvisor_ctx ((box_context *) __uvisor_ctx)

static void run_3(void)
{
    while (1) {
        const int toggle = uvisor_ctx->toggle;
        uint16_t size = toggle ? 150 : 99;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        uvisor_ctx->toggle = !uvisor_ctx->toggle;
        alloc_fill_wait_verify_free(size, seed, 0);
    }
}

/* A thin wrapper around run_3 that accepts and ignores a context. This avoid a
 * cast, as mbed's Thread and RTX's osThreadContextNew operate on differently
 * typed thread functions. */
static void run_3_context(void *)
{
    run_3();
}

static void led3_main(const void *)
{
    osStatus status;
    DigitalOut led3(LED3);
    led3 = LED_OFF;

    Thread thread1(osPriorityNormal, 512, NULL);
    status = thread1.start(run_3);
    if (status != osOK) {
        printf("Could not start box_led3 thread1.\r\n");
        uvisor_error(USER_NOT_ALLOWED);
    }

    /* Create page-backed allocator. */
    const uint32_t kB = 1024;
    SecureAllocator alloc = secure_allocator_create_with_pages(4 * kB, 1 * kB);
    /* Prepare the thread definition structure. */
    osThreadAttr_t thread_attr = {0};
    mbed_rtos_storage_thread_t thread_def = {0};
    thread_attr.stack_size = 512;
    /* Allocate the stack inside the page allocator! */
    thread_attr.stack_mem = (uint32_t *) secure_malloc(alloc, 512);
    thread_attr.priority = osPriorityNormal;
    thread_attr.cb_size = sizeof(thread_def);
    thread_attr.cb_mem = &thread_def;
    /* Create a thread with the page allocator as heap. */
    osThreadContextNew(run_3_context, NULL, &thread_attr, alloc);

    while (1) {
        static const size_t size = 20;
        uint16_t seed = (size << 8) | (uvisor_ctx->heartbeat & 0xFF);

        led3 = !led3;
        ++uvisor_ctx->heartbeat;
        alloc_fill_wait_verify_free(size, seed, 211);
    }
}
