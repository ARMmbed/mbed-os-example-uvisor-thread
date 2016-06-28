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

    while (1) {
        static const size_t size = 300;

        led2 = !led2;
        ++uvisor_ctx->heartbeat;
        alloc_wait_free(size, 300);
    }
}
