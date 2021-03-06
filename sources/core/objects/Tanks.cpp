#include "Tanks.h"

#include "Weldingtool.h"
#include "representation/Sound.h"

FuelTank::FuelTank(quint32 id)
    : Tank(id)
{
    name = "Fueltank";

    v_level = 6;

    transparent = true;

    SetSprite("icons/objects.dmi");
    SetState("weldtank");

    SetPassable(Dir::ALL, Passable::AIR);
}

void FuelTank::AttackBy(IdPtr<Item> item)
{
    if (IdPtr<Weldingtool> w = item)
    {
        w->AddFuel(50);
        PlaySoundIfVisible("refill.wav");
    }
}

WaterTank::WaterTank(quint32 id)
    : Tank(id)
{
    name = "Watertank";

    v_level = 6;

    transparent = true;

    SetSprite("icons/objects.dmi");
    SetState("watertank");

    SetPassable(Dir::ALL, Passable::AIR);
}

void WaterTank::AttackBy(IdPtr<Item> item)
{

}

