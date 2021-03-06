#include "MetalWall.h"

#include "Weldingtool.h"
#include "Girder.h"
#include "Floor.h"
#include "Materials.h"

#include "representation/Sound.h"

#include "../ObjectFactory.h"
#include "../Game.h"

MetalWall::MetalWall(quint32 id) : ITurf(id)
{
    transparent = false;
    SetPassable(Dir::ALL, Passable::EMPTY);

    v_level = 2;

    SetSprite("icons/walls.dmi");
    SetState("metal0");

    name = "Metal wall";
}

void MetalWall::AttackBy(IdPtr<Item> item)
{
    if (IdPtr<Weldingtool> wtool = item)
    {
        if (wtool->Working())
        {
            PlaySoundIfVisible("Welder.wav");
            Create<IOnMapObject>(Girder::GetTypeStatic(), GetOwner());
            Create<IOnMapObject>(Metal::GetTypeStatic(), GetOwner());
            Create<ITurf>(Plating::GetTypeStatic(), GetOwner());
            Delete();
        }
    }
}

ReinforcedWall::ReinforcedWall(quint32 id) : ITurf(id)
{
    transparent = false;
    SetPassable(Dir::ALL, Passable::EMPTY);

    v_level = 2;

    SetSprite("icons/walls.dmi");
    SetState("r_wall");

    name = "Reinforced wall";
}
