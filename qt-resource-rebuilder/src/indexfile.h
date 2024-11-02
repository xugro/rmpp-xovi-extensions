#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../system.h"
#include "types.h"

REQUIRE_ENVIRONMENT;
#define MAX_LINE_LENGTH 1024

void loadAllModifications(struct ModificationDefinition **definitions);
