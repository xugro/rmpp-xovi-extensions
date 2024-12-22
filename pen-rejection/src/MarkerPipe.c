#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <linux/input.h>
#include "../../fileman/src/fileman.h"
#include "files.h"
#include "../../util.h"

extern volatile bool penInputDisabled;
extern volatile bool running;

struct FdContext {
    int realFD;
    int pipeReaderFD;
    int penInputSink;
};

static void *_thread(void *data){
    int penInput = $open(MARKER, O_RDONLY);
    if( penInput == -1) {
        LOG("[PenRejection -> Marker]: Failed to open " MARKER " (Pen input).\n");
        return NULL;
    }

    struct FdContext *ctx = data;
    LOG("[PenRejection -> Marker]: Sleeping for 10 seconds...\n");
    sleep(10);
    LOG("[PenRejection -> Marker]: Woke up!\n");
    dup2(ctx->pipeReaderFD, ctx->realFD);
    LOG("[PenRejection -> Marker]: Rugpulled the FD\n");
    struct input_event readEvent;
    while(running) {
        read(penInput, &readEvent, sizeof(readEvent));
        if(!penInputDisabled) {
            write(ctx->penInputSink, &readEvent, sizeof(readEvent));
        }
    }
    free(data);
}

static int connectionStart(){
    LOG("[PenRejection -> Marker]: Pipe started.");
    int pipes[2];
    pipe(pipes);
    // 0 - reader. 1 - writer
    struct FdContext *ctx = malloc(sizeof(struct FdContext));
    ctx->penInputSink = pipes[1];
    ctx->pipeReaderFD = pipes[0];
    ctx->realFD = $open(MARKER, O_RDONLY);
    pthread_t threadId;

    pthread_create(&threadId, NULL, _thread, ctx);
    pthread_detach(threadId);
    return ctx->realFD;
}

bool startMarkerPipe(){
    struct FilemanOverride *fOverride = malloc(sizeof(struct FilemanOverride));
    fOverride->name = MARKER;
    fOverride->nameMatchType = FILEMAN_MATCH_WHOLE;
    fOverride->handler.fdRemap = connectionStart;
    fOverride->handlerType = FILEMAN_HANDLE_FD_MAP;

    fileman$registerOverride(fOverride);
    LOG("[PenRejection -> Marker]: File registered.");
    return true;
}
