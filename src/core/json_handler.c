#include "json_handler.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>

Level* ProcessMapJSON(const char *mapPath) {
    FILE* mapPtr = fopen(mapPath, "r");
    if (mapPtr == NULL) {
        return 0;
    }

    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), mapPtr);
    fclose(mapPtr);

    cJSON* json = cJSON_Parse(buffer);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return 0;
    }

    Level* lvl = malloc(sizeof(Level));

    // Getting the legend


    return lvl;
}
