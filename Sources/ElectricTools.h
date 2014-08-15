#pragma once

#include "Item.h"

class AtmosTool: public Item
{
public:
    DECLARE_SAVED(AtmosTool, Item);
    DECLARE_GET_TYPE_ITEM(AtmosTool);
    AtmosTool();
    virtual void AttackBy(id_ptr_on<Item> item) override;
};
ADD_TO_TYPELIST(AtmosTool)