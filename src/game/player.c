#include "player.h"
#include "world.h"
#include "projectile.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define USE_MOUSE_CONTROLS

Player* ConstructPlayer(float x, float y, float health, float maxHealth, GameWorld* world)
{
    Player* plr = malloc(sizeof(Player));
    plr->x = x;
    plr->y = y;
    plr->rotation = 0;
    plr->health = health;
    plr->hitBox = (Rectangle){plr->x, plr->y, 50, 50};
    plr->maxHealth = maxHealth;
    plr->timeSinceHit = 0.0f;
    plr->money = 500;
    plr->world = world;
    plr->AllGuns = calloc(GUN_SIZE, sizeof(Gun*));
    plr->EquippedGun = 0;
    plr->bIsADS = false;

    Camera2D *cam = malloc(sizeof(Camera2D));
    cam->offset = (Vector2){ 0.0f, 0.0f };
    cam->rotation = 0.0f;
    cam->zoom = 1.0f;
    cam->target = (Vector2){ 0.0f, 0.0f };
    plr->camera = cam;

    plr->baseZoom = 1.0f;
    plr->fireTime = 0.0f;
    plr->cursorPos = GetMousePosition();
    return plr;
}

void UpdatePlayer(Player *plr)
{
    //Gun* currentGun = plr->AllGuns[plr->EquippedGun];
    
    float x, y;
    float deadzone = 0.2;
    if (plr->world->game->controlType == CONTROLTYPE_CONTROLLER)
    {
        x = 0.0f;
        float leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
        if (leftStickX > deadzone || leftStickX < -deadzone)
        {
            x = leftStickX * ((float)250 * GetFrameTime());
        }
        
        y = 0.0f;
        float leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);
        if (leftStickY > deadzone || leftStickY < -(deadzone))
        {
            y = leftStickY * ((float)250 * GetFrameTime());
        }
    }
    else
    {
        x = ((int)IsKeyDown(KEY_D) - (int)IsKeyDown(KEY_A)) * ((float)250 * GetFrameTime());
        y = ((int)IsKeyDown(KEY_S) - (int)IsKeyDown(KEY_W)) * ((float)250 * GetFrameTime()); 
    }

    const Vector2 mousePos = GetMousePosition();
    if (plr->world->game->controlType == CONTROLTYPE_CONTROLLER)
    {
        const Vector2 rightStickMovement = (Vector2){ GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X) * ((float)600 * GetFrameTime()), GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y) * ((float)600 * GetFrameTime()) };
        plr->cursorPos.x += rightStickMovement.x;
        plr->cursorPos.y += rightStickMovement.y;
    }
    else
    {
        plr->cursorPos.x = GetMousePosition().x;
        plr->cursorPos.y = GetMousePosition().y;
    }
    plr->rotation = atan2(plr->cursorPos.y - (GetScreenHeight() / 2.0f), plr->cursorPos.x - (GetScreenWidth() / 2.0f));

    // printf("%d\n", (int)GetMouseWheelMove());
    if ((IsKeyPressed(KEY_ONE) && plr->world->game->controlType == CONTROLTYPE_MOUSE) || (plr->world->game->controlType == CONTROLTYPE_CONTROLLER && IsGamepadButtonPressed(0, 5)))
    {
        SwapGun(plr);
        printf("%d\n", plr->EquippedGun);
    }

    // Normalizing (making sure it isnt faster diagonally)
    float length = sqrtf(x*x + y*y);
    if (length > 0)
    {
        x = ((x / length) * (250.0f * GetFrameTime())) + plr->x;
        y = ((y / length) * (250.0f * GetFrameTime())) + plr->y;
    }
    else
    {
        x += plr->x;
        y += plr->y;
    }

    plr->hitBox.x = plr->x - 25;
    plr->hitBox.y = plr->y - 25;

    // Check for zombies
    for (int i = 0; i < ZOMBIE_COUNT; i++)
    {
        if (plr->world->AllZombies[i] == 0)
            continue;
        Zombie* them = plr->world->AllZombies[i];
        if (CheckCollisionRecs(plr->hitBox, them->hitBox))
        {
            float dx = x - them->x;
            float dy = y - them->y;
            float dist = sqrt(dx*dx + dy*dy);
            if (dist > 0.001f)
            {
                x += (dx / dist) * 1.0f;
                y += (dy / dist) * 1.0f;

                plr->health -= 300 * GetFrameTime();
                plr->timeSinceHit = 5.0f;
            }
        }
    }

    if (!is_blocked(plr->world, x, plr->y)) plr->x = x;
    if (!is_blocked(plr->world, plr->x, y)) plr->y = y;

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();
    plr->camera->target = (Vector2){plr->x, plr->y};

    if (plr->world->game->controlType == CONTROLTYPE_CONTROLLER)
    {
        plr->bIsADS = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER) > deadzone;
    }
    else
    {
        plr->bIsADS = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
    }

    Gun* currentGun = plr->AllGuns[plr->EquippedGun];
    if (plr->bIsADS && currentGun != NULL)
    {
        float summedMouseX = mousePos.x / screenWidth;
        float summedMouseY = mousePos.y / screenHeight;
        
        summedMouseX = 0.5f + (summedMouseX - 0.5f) * (1.0f - currentGun->adsCenterBias);
        summedMouseY = 0.5f + (summedMouseY - 0.5f) * (1.0f - currentGun->adsCenterBias);

        plr->camera->offset = (Vector2){ screenWidth - (screenWidth * summedMouseX), screenHeight - (screenHeight * summedMouseY) };
        if (plr->baseZoom < 1.2f)
        {
            plr->baseZoom += 1 * GetFrameTime();
        }
    }
    else
    {
        plr->camera->offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
        if (plr->baseZoom > 1.0f) plr->baseZoom -= 1 * GetFrameTime();
        if (plr->baseZoom < 1.0f) plr->baseZoom += 1 * GetFrameTime();
    }
    plr->camera->zoom = plr->baseZoom * ((screenHeight / 450.0f)) * 0.7;

    if (plr->health < 0) plr->health = 0;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && plr->fireTime == 0.0f)
    {
        FireGun(plr);
    }

    if (IsKeyPressed(KEY_R))
    {
        ReloadGun(plr);
    }
    UpdateReload(plr);

    //DEBUG
    if (IsKeyPressed(KEY_U))
    {
        plr->AllGuns[plr->EquippedGun]->upgradeTier++;
    }

    if (plr->fireTime > 0.0f) plr->fireTime -= GetFrameTime();
    if (plr->fireTime < 0.0f) plr->fireTime = 0.0f;

    plr->timeSinceHit -= GetFrameTime();
    if (plr->timeSinceHit <= 0.0f && plr->health < plr->maxHealth) {
        plr->health += 100.0f * GetFrameTime();
        if (plr->health >= plr->maxHealth) plr->health = plr->maxHealth;
    }
}

void DrawPlayer(Player *plr)
{
    DrawRectanglePro(
        (Rectangle){plr->x, plr->y, 40, 40},
        (Vector2){20, 20},
        plr->rotation * RAD2DEG,
        (Color){0xff, 0xb3, 0x19, 0xff});
    //DrawRectangleLines(plr->hitBox.x, plr->hitBox.y, plr->hitBox.width, plr->hitBox.height, RED);

    EndMode2D();
    if (plr->world->game->controlType == CONTROLTYPE_CONTROLLER)
    {
        DrawRectangle(plr->cursorPos.x - 25, plr->cursorPos.y - 25, 50, 50, WHITE);
    }
    BeginMode2D(*plr->camera);
}

void SwapGun(Player *plr)
{
    plr->EquippedGun++;
    if (plr->EquippedGun > (GUN_SIZE+1))
    {
        plr->EquippedGun = 0;
    }

    if (plr->AllGuns[plr->EquippedGun] == 0)
    {
        plr->EquippedGun = 0;
    }
}

void GiveGun(Player *plr, Gun *gun)
{
    bool bIsSlotFree = false;
    for (int i = 0; i < GUN_SIZE; i++)
    {
        if (plr->AllGuns[i] != 0) continue;
        plr->AllGuns[i] = gun;
        bIsSlotFree = true;
        break;
    }
    if (!bIsSlotFree) plr->AllGuns[plr->EquippedGun] = gun;
}

void FireGun(Player *plr)
{
    Gun* currentGun = plr->AllGuns[plr->EquippedGun];
    if (currentGun == 0) return;
    if (currentGun->ammo > 0)
    {
        switch (currentGun->fireMode)
        {
        case FIREMODE_AUTO:
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && plr->fireTime == 0.0f && currentGun->reloadingTimer == 0.0f)
            {
                WorldSpawnProjectile(plr->world, currentGun, plr, plr->rotation);
                plr->fireTime = currentGun->fireRate;
                currentGun->ammo--;
            }
            break;
        case FIREMODE_SEMIAUTO:
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && plr->fireTime == 0.0f && currentGun->reloadingTimer == 0.0f)
            {
                WorldSpawnProjectile(plr->world, currentGun, plr, plr->rotation);
                plr->fireTime = currentGun->fireRate;
                currentGun->ammo--;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        ReloadGun(plr);
    }
}

void ReloadGun(Player *plr)
{
    Gun *currentGun = plr->AllGuns[plr->EquippedGun];
    if (currentGun == 0) return;
    if (currentGun->ammo < currentGun->maxAmmo && currentGun->reloadingTimer == 0.0f)
    {
        currentGun->reloadingTimer = currentGun->reloadTime;
    }
}

void UpdateReload(Player *plr)
{
    Gun *currentGun = plr->AllGuns[plr->EquippedGun];
    if (currentGun == 0) return;
    if (currentGun->reloadingTimer > 0.0f)
    {
        currentGun->reloadingTimer -= GetFrameTime();
        if (currentGun->reloadingTimer <= 0.0f)
        {
            currentGun->reloadingTimer = 0.0f;
            if (currentGun->reserveAmmo >= currentGun->maxAmmo)
            {
                int ammoLeft = currentGun->maxAmmo - currentGun->ammo;
                currentGun->ammo = currentGun->maxAmmo;
                currentGun->reserveAmmo -= ammoLeft;
            }
            else
            {
                currentGun->ammo = currentGun->reserveAmmo;
                currentGun->reserveAmmo = 0;
            }
        }
    }
}
