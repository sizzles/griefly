#pragma once

#include "IMovable.h"

class FlatGlass: public IMovable
{
public:
    DECLARE_SAVED(FlatGlass, IMovable);
    DECLARE_GET_TYPE_ITEM(FlatGlass);
    FlatGlass();

    virtual bool checkMove(Dir direct) override;
    virtual void Bump(id_ptr_on<IMovable> item) override;
};
ADD_TO_TYPELIST(FlatGlass);
