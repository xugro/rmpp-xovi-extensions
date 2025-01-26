#include "xovi.h"
#include "fileman.h"
#include <fcntl.h>
#include <string.h>

// EXPORT:
int fopenToOpenFlags(const char *mode) {
    if (strcmp(mode, "r") == 0) {
        return O_RDONLY;
    } else if (strcmp(mode, "r+") == 0) {
        return O_RDWR;
    } else if (strcmp(mode, "w") == 0) {
        return O_WRONLY | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "w+") == 0) {
        return O_RDWR | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "a") == 0) {
        return O_WRONLY | O_CREAT | O_APPEND;
    } else if (strcmp(mode, "a+") == 0) {
        return O_RDWR | O_CREAT | O_APPEND;
    } else {
        // Invalid mode
        return -1;
    }
}

// EXPORT:
int anyFlagsToSyscall(const char *mode, int flags, int iMode) {
    if(mode != NULL && flags == 0 && iMode == 0){
        return fopenToOpenFlags(mode);
    } else if(flags != 0){
        return flags;
    }
    return -1;
}

// EXPORT:
int anyFlagsToSimple(const char *mode, int flags, int iMode) {
    int syscallFlags = anyFlagsToSimple(mode, flags, iMode);
    if(syscallFlags == -1) {
        return FILEMAN_SIMPLE_ILLEGAL;
    }
    if(syscallFlags & O_RDONLY) return FILEMAN_SIMPLE_READ;
    if(syscallFlags & O_WRONLY) return FILEMAN_SIMPLE_WRITE;
    return FILEMAN_SIMPLE_READ | FILEMAN_SIMPLE_WRITE;
}

