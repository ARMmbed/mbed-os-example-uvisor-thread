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

static void led3_main(const void *);

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(8192);
UVISOR_BOX_MAIN(led3_main, osPriorityNormal);
UVISOR_BOX_CONFIG(box_led3, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led3_main(const void *)
{
    DigitalOut led3(LED3);
    led3 = LED_OFF;

    while (1) {
        void * memory;

        led3 = !led3;
        memory = malloc(500);
        ++uvisor_ctx->heartbeat;
        Thread::wait(500);
        free(memory);
    }
}
