#include "json_handler.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// You should move this to level.h/level.c
Level* ProcessMapJSON(const char *mapPath) {
    FILE* mapPtr = fopen(mapPath, "r");
    if (mapPtr == NULL) {
        return 0;
    }

    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), mapPtr);
    fclose(mapPtr);

    cJSON *json = cJSON_Parse(buffer);
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
    cJSON* legend = cJSON_GetObjectItem(json, "legend");
    if (legend == NULL) {
        printf("Could not find legend in map json!\n");
        cJSON_Delete(json);
        return 0;
    }

    char* playerLegend = NULL;
    char* zombieSpawnLegend = NULL;

    cJSON* legendKey;
    cJSON_ArrayForEach(legendKey, legend) {
        printf("%s: %s\n", legendKey->string, legendKey->valuestring);
        if (strncmp(legendKey->valuestring, "player_spawn", 13)) {
            playerLegend = malloc(sizeof(legendKey->string));
            strncpy(playerLegend, legendKey->string, strlen(legendKey->string));
        }
        if (strncmp(legendKey->valuestring, "zombie_spawn", 13)) {
            //zombieSpawnLegend = legendKey->string;
            zombieSpawnLegend = malloc(sizeof(legendKey->string));
            strncpy(zombieSpawnLegend, legendKey->string, strlen(legendKey->string));
        }
    }
    cJSON_Delete(legendKey);
    cJSON_Delete(legend);

    printf("PlayerSpawn: %s\nZombieSpawn: %s\n", playerLegend, zombieSpawnLegend);

    // Copying the map
    cJSON *mapJSON = cJSON_GetObjectItem(json, "map_array");
    if (mapJSON == NULL) {
        printf("Could not find map array in map json!\n");
        cJSON_Delete(json);
        return 0;
    }
    printf("Loaded map array!\n");

    cJSON *mapStr;
    size_t mapLen = cJSON_GetArraySize(mapJSON);
    lvl->mapArr = malloc(sizeof(char*) * mapLen);
    int i = 0;
    cJSON_ArrayForEach(mapStr, mapJSON) {
        lvl->mapArr[i] = mapStr->valuestring;
        printf("%s\n", mapStr->valuestring);
        i++;
    }
    cJSON_Delete(mapStr);
    cJSON_Delete(mapJSON);

    return lvl;
}
