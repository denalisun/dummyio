#ifndef GUN_H
#define GUN_H

typedef enum FireMode
{
    FIREMODE_SEMIAUTO,
    FIREMODE_AUTO
} FireMode;

typedef struct Gun
{
    const char* name;
    float fireRate;
    float damage;
    int ammo;
    int maxAmmo;
    int reserveAmmo;
    int maxReserve;
    FireMode fireMode;
} Gun;

Gun* ConstructGun(const char* name, float fireRate, float damage, int ammo, int maxAmmo, int reserveAmmo, int maxReserve, FireMode fireMode);

#endif