#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <linux/input.h>
#include "files.h"
#include "../../util.h"
#include "../xovi.h"

static FILE *halSensors = NULL;
extern volatile bool touchScreenDisabled;
extern volatile bool running;
static pthread_t thread_id;

static void *_thread(void *_){
    LOG("[PalmRejection -> HAL]: Started HAL monitoring thread\n");
    struct input_event readEvent;
    while(running) {
        fread(&readEvent, sizeof(readEvent), 1, halSensors);
        if(readEvent.code && readEvent.type) {
            // Valid packet.
            touchScreenDisabled = !readEvent.value;
            // printf instead of LOG on purpose.
            printf("[PalmRejection -> HAL]: Detected marker status change. Set touch screen disabled to: %s\n", touchScreenDisabled ? "true" : "false");
        }
    }
}

bool startHalManager() {
    halSensors = $fopen(HAL_SENSOR, "r");
    if(!halSensors) {
        LOG("[PalmRejection -> HAL]: Failed to open " HAL_SENSOR " (Hal sensors)\n");
        return false;
    }
    pthread_create(&thread_id, NULL, _thread, NULL);
    return true;
}
