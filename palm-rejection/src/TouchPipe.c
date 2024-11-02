#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>
#include "../../fileman/src/fileman.h"
#include "files.h"

extern volatile bool touchScreenDisabled;
extern volatile bool running;

struct FdContext {
    int realFD;
    int pipeReaderFD;
    int touchScreenSink;
};

static void *_thread(void *data){
    int touchScreen = $open(TOUCHSCREEN, O_RDONLY);
    if(touchScreen == -1) {
        printf("[PalmRejection -> Touch]: Failed to open " TOUCHSCREEN " (touchscreen).\n");
        return NULL;
    }

    struct FdContext *ctx = data;
    printf("[PalmRejection -> Touch]: Sleeping for 10 seconds...\n");
    sleep(10);
    printf("[PalmRejection -> Touch]: Woke up!\n");
    dup2(ctx->pipeReaderFD, ctx->realFD);
    printf("[PalmRejection -> Touch]: Rugpulled the FD\n");
    struct input_event readEvent;
    while(running) {
        read(touchScreen, &readEvent, sizeof(readEvent));
        if(!touchScreenDisabled) {
            write(ctx->touchScreenSink, &readEvent, sizeof(readEvent));
        }
    }
    free(data);
}

static int connectionStart(){
    printf("[PalmRejection -> Touch]: Pipe started.");
    int pipes[2];
    pipe(pipes);
    // 0 - reader. 1 - writer
    struct FdContext *ctx = malloc(sizeof(struct FdContext));
    ctx->touchScreenSink = pipes[1];
    ctx->pipeReaderFD = pipes[0];
    ctx->realFD = $open(TOUCHSCREEN, O_RDONLY);
    pthread_t threadId;

    pthread_create(&threadId, NULL, _thread, ctx);
    pthread_detach(threadId);
    return ctx->realFD;
}

bool startTouchPipe(){
    struct FilemanOverride *fOverride = malloc(sizeof(struct FilemanOverride));
    fOverride->name = TOUCHSCREEN;
    fOverride->nameMatchType = FILEMAN_MATCH_WHOLE;
    fOverride->handler.fdRemap = connectionStart;
    fOverride->handlerType = FILEMAN_HANDLE_FD_MAP;

    fileman$registerOverride(fOverride);
    printf("[PalmRejection -> Touch]: File registered.");
    return true;
}
