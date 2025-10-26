#include "gun.h"
#include <stdlib.h>

Gun* ConstructGun(const char* name, float fireRate, float damage, int ammo, int maxAmmo, int reserveAmmo, int maxReserve, float reloadTime, FireMode fireMode)
{
    Gun* gun = malloc(sizeof(Gun));
    gun->name = name;
    gun->fireRate = fireRate;
    gun->damage = damage;
    gun->ammo = ammo;
    gun->maxAmmo = maxAmmo;
    gun->reserveAmmo = reserveAmmo;
    gun->maxReserve = maxReserve;
    gun->fireMode = fireMode;
    gun->reloadTime = reloadTime;
    gun->reloadingTimer = 0.0f;
    return gun;
}