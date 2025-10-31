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
    float reloadTime;
    float reloadingTimer;
    FireMode fireMode;
    float adsCenterBias;
    int upgradeTier;
} Gun;

Gun* ConstructGun(const char* name, float fireRate, float damage, int ammo, int maxAmmo, int reserveAmmo, int maxReserve, float reloadTime, FireMode fireMode);

float calculate_damage_from_upgrade(Gun *gun);

#endif
