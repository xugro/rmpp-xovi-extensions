#include <stdbool.h>

#include "../../system.h"
#include "../../fileman/src/fileman.h"
#include "../../util.h"

REQUIRE_ENVIRONMENT;

volatile bool penInputDisabled = false;
// TODO:
volatile bool running = true;

extern bool startMarkerPipe();
extern bool startHalManager();

void _xovi_construct(){
    Environment->requireExtension("fileman", 0, 1, 0);
    if(!startHalManager()) {
        LOG("[PenRejection]: Bailing!\n");
        return;
    }
    startMarkerPipe();
}
