// This is extremely hacky, but I just don't want to use 

#include "qstring.h"
#include "qresource.h"

extern "C" {
    void registerRCCFile(const char *rcc){
        QResource::registerResource(QString(rcc), QString());
    }
}
