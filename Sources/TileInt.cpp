#include <assert.h>

#include "helpers.h"
#include "MapClass.h"
#include "OnMapInt.h"
#include "TileInt.h"
#include "IMovable.h"

CubeTile::CubeTile()
{
    turf_ = 0;

    posx_ = -1;
    posy_ = -1;
    posz_ = -1;
}

bool CubeTile::CanTouch(id_ptr_on<IOnMapBase> item, int range) const
{
    if (!item.valid())
        return false;

    if (!item->GetOwner())
        return false;

    id_ptr_on<CubeTile> cube_tile;
    cube_tile = item->GetOwner();
    if (!cube_tile)
        return false;

    int x_begin = posx_ - range;
    if (x_begin < 0)
        x_begin = 0;
    int y_begin = posy_ - range;
    if (y_begin < 0)
        y_begin = 0;
    
    int x_end = posx_ + range;
    if (x_end >= GetMapMaster()->GetMapW())
        x_end = GetMapMaster()->GetMapW() - 1;
    int y_end = posy_ + range;
    if (y_end >= GetMapMaster()->GetMapH())
        y_end = GetMapMaster()->GetMapH() - 1;

    // TODO
    // check something like 
    //       xxx     o will be touchable (and its wrond)
    //       xox     maybe whatever?
    //       xxx  

    if (cube_tile->posx() < x_begin)
        return false;
    if (cube_tile->posx() > x_end)
        return false;
    if (cube_tile->posy() < y_begin)
        return false;
    if (cube_tile->posy() > y_end)
        return false;

    return true;
}

bool CubeTile::Contains(id_ptr_on<IOnMapBase> item) const
{
    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        if (it->ret_id() == item.ret_id())
            return true;
    return false;
}

void CubeTile::Bump(id_ptr_on<IMovable> item)
{
    if (GetTurf())
        GetTurf()->Bump(item);

    if (item->GetOwner().ret_id() == GetId())
    {
        for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
            if (!(*it)->IsPassable(item->dMove))
            {
                (*it)->Bump(item);
                return;
            }
        return;
    }

    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        if (!(*it)->IsPassable(helpers::revert_dir(item->dMove)))
        {
            (*it)->Bump(item);
            return;
        }
    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        if (!(*it)->IsPassable(D_ALL))
        {
            (*it)->Bump(item);
            return;
        }
}

bool CubeTile::AddItem(id_ptr_on<IOnMapBase> item_raw)
{
    id_ptr_on<IOnMapItem> item = item_raw;
    if (!item.valid())
        return false;
    auto itr = inside_list_.begin();
    while(itr != inside_list_.end())
    {
        if (itr->ret_id() == item.ret_id())
        {
            SYSTEM_STREAM << "ALERT! " << item.ret_id() << " double added!\n";
            SDL_Delay(5000);
        }
        if (itr->ret_id() > item.ret_id())
            break;
        ++itr;
    }
    InsideType::iterator locit = itr;
    inside_list_.insert(locit, item);
    item->SetOwner(GetId());
    return true;
}
bool CubeTile::RemoveItem(id_ptr_on<IOnMapBase> item_raw)
{
    id_ptr_on<IOnMapItem> item = item_raw;
    if (!item.valid())
        return false;

    if (item == GetTurf())
    {
        SetTurf(0);
        return true;
    }

    auto itr = inside_list_.begin();
    while(itr != inside_list_.end())
    {
        if (itr->ret_id() == item->GetId())
        {
            inside_list_.erase(itr);
            return true;
        }
        ++itr;
    }
    return false;
}



id_ptr_on<IOnMapBase> CubeTile::GetNeighbour(Dir direct)
{
    int new_x = posx_;
    int new_y = posy_;
    int new_z = posz_;
    helpers::move_to_dir(direct, &new_x, &new_y, &new_z);
    return GetMapMaster()->squares[new_x][new_y][new_z];
}

bool CubeTile::IsPassable(Dir direct) const
{
    if (turf_.valid() && !turf_->IsPassable(direct))
        return false;
    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        if (!(*it)->IsPassable(direct))
            return false;
    return true;
}

bool CubeTile::IsTransparent() const
{
    if (turf_.valid() && !turf_->IsTransparent())
        return false;
    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        if (!(*it)->IsTransparent())
            return false;
    return true;
}

size_t CubeTile::GetItemImpl(unsigned int hash)
{
    for (auto it = inside_list_.rbegin(); it != inside_list_.rend(); ++it)
        if (FastIsType(hash, (*it)->RT_ITEM()))
            return it->ret_id();
    return 0;
}

void CubeTile::ForEach(std::function<void(id_ptr_on<IOnMapBase>)> callback)
{
    for (auto it = inside_list_.begin(); it != inside_list_.end(); ++it)
        callback(*it);
}

void CubeTile::LoadInMap()
{
    GetMapMaster()->squares[posx_][posy_][posz_] = GetId();
}
