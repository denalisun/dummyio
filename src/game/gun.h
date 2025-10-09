#ifndef GUN_H
#define GUN_H

typedef struct Gun {
    const char* name;
    float damage;
    int ammo;
    int maxAmmo;
    int reserveAmmo;
    int maxReserve;
} Gun;

Gun* ConstructGun(const char* name, float damage, int ammo, int maxAmmo, int reserveAmmo, int maxReserve);

#endif