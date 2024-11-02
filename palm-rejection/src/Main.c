#include <stdbool.h>

#include "../../system.h"
#include "../../fileman/src/fileman.h"

REQUIRE_ENVIRONMENT;

volatile bool touchScreenDisabled = false;
// TODO:
volatile bool running = true;

extern bool startTouchPipe();
extern bool startHalManager();

void _xovi_construct(){
    Environment->requireExtension("fileman", 0, 1, 0);
    if(!startHalManager()) {
        printf("[PalmRejection]: Bailing!\n");
        return;
    }
    startTouchPipe();
}
