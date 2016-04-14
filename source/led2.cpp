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
UVISOR_BOX_MAIN(led2_main, osPriorityNormal);
UVISOR_BOX_CONFIG(box_led2, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led2_main(const void *)
{
    DigitalOut led2(LED2);
    led2 = LED_OFF;

    while (1) {
        void * memory;

        led2 = !led2;
        ++uvisor_ctx->heartbeat;
        memory = malloc(300);
        Thread::wait(300);
        free(memory);
    }
}
