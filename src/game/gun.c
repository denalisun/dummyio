#include "gun.h"
#include <stdlib.h>

Gun* ConstructGun(const char* name, float damage, int ammo, int maxAmmo, int reserveAmmo, int maxReserve)
{
    Gun* gun = malloc(sizeof(Gun));
    gun->name = name;
    gun->damage = damage;
    gun->ammo = ammo;
    gun->maxAmmo = maxAmmo;
    gun->reserveAmmo = reserveAmmo;
    gun->maxReserve = maxReserve;
    return gun;
}