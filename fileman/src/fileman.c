#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "utlist.h"
#include "fileman.h"
#include "../../util.h"

static struct FilemanOverride *ENTRIES;
static pthread_mutex_t fopenMutex;
static pthread_mutex_t openMutex;

int endsWith(const char *str, const char *suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix);
}

static inline int min(int a, int b){
    return a > b ? b : a;
}

int startsWith(const char *str, const char *preffix) {
    int length = min(strlen(str), strlen(preffix));
    return strncmp(str, preffix, length);
}

static struct FilemanOverride *findMatch(const char *filePath) {
    struct FilemanOverride *entry;
    LL_FOREACH(ENTRIES, entry) {
        char matched = 0;
        if(entry->name == NULL) {
            continue;
        }
        switch(entry->nameMatchType) {
            case FILEMAN_MATCH_WHOLE:
                matched = strcmp(filePath, entry->name) == 0;
                break;
            case FILEMAN_MATCH_START:
                matched = startsWith(filePath, entry->name) == 0;
                break;
            case FILEMAN_MATCH_END:
                matched = endsWith(filePath, entry->name) == 0;
                break;
        }
        if(matched) {
            LOG("FILEMAN: Matched file %s\n", filePath);
            return entry;
        }
    }
    return NULL;
}

FILE *override$fopen(const char *filePath, const char *mode){
    pthread_mutex_lock(&fopenMutex);
    struct FilemanOverride *entry = findMatch(filePath);
    FILE* result = NULL;
    if(entry == NULL){
        result = (FILE*) $fopen(filePath, mode);
        goto leave;
    }

    switch(entry->handlerType) {
        case FILEMAN_HANDLE_DIRECT:
            result = (FILE*) $fopen(entry->handler.directRemap, mode);
            break;
        case FILEMAN_HANDLE_NAME_MAP:
            result = (FILE*) $fopen(entry->handler.fileNameRemap(filePath, mode, 0, 0), mode);
            break;
        case FILEMAN_HANDLE_FILE_MAP:
            result = entry->handler.fileRemap(filePath, mode, 0, 0);
            break;
        case FILEMAN_HANDLE_FD_MAP:
            result = (FILE*) fdopen(entry->handler.fdRemap(filePath, mode, 0, 0), mode);
            break;
    }

    leave:
    pthread_mutex_unlock(&fopenMutex);
    return result;
}

int override$open(const char *filePath, int flags, int mode) {
    pthread_mutex_lock(&openMutex);
    struct FilemanOverride *entry = findMatch(filePath);
    int result = -1;
    if(entry == NULL){
        result = (int) $open(filePath, flags, mode);
        goto leave;
    }

    switch(entry->handlerType) {
        case FILEMAN_HANDLE_DIRECT:
            result = (int) $open(entry->handler.directRemap, flags, mode);
            break;
        case FILEMAN_HANDLE_NAME_MAP:
            result = (int) $open(entry->handler.fileNameRemap(filePath, NULL, flags, mode), flags, mode);
            break;
        case FILEMAN_HANDLE_FILE_MAP:
            LOG("ERROR: Cannot retrieve FILE*'s fd - pointer would be doomed.\n");
            result = -1;
            break;
        case FILEMAN_HANDLE_FD_MAP:
            result = entry->handler.fdRemap(filePath, NULL, flags, mode);
            break;
    }

    leave:
    pthread_mutex_unlock(&openMutex);
    return result;
}

// EXPORT:
void registerOverride(struct FilemanOverride *entry) {
    LL_APPEND(ENTRIES, entry);
}

void _xovi_construct(){
    pthread_mutex_init(&fopenMutex, NULL);
    pthread_mutex_init(&openMutex, NULL);
}
