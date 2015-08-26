#include "LoginMob.h"

#include "Text.h"
#include "sound.h"

LoginMob::LoginMob(size_t id) : IMob(id)
{
    //SetFreq(0);
    interface_.Init();
}

void LoginMob::DeinitGUI()
{
    GetTexts().Delete("LoginScreen");
    GetSoundPlayer().StopMusic();
}


void LoginMob::InitGUI()
{
    GetTexts()["LoginScreen"].SetUpdater
    ([this](std::string* str)
    {
        *str = "CLICK ME";
    }).SetFreq(1000)
      .SetSize(26)
      .SetPlace(sizeW / 2 - 144 + 16, sizeH / 2 - 13);

    GetSoundPlayer().PlayMusic("lobby.ogg", 10.0f);
}


void LoginMob::processGUI()
{
    interface_.Draw();
}


void LoginMob::processGUImsg(const Message& msg)
{

}

void LoginMob::process()
{

}

void LoginMob::CalculateVisible(std::list<point>* visible_list)
{
    visible_list->clear();
}

std::ostream& operator<<(std::stringstream& file, LoginInterface& interf)
{
    WrapWriteMessage(file, interf.view_);
    return file;
}
std::istream& operator>>(std::stringstream& file, LoginInterface& interf)
{
    WrapReadMessage(file, interf.view_);
    return file;
}

void LoginInterface::Init()
{
    view_.SetSprite("icons/288x288.dmi");
    view_.SetState("singularity_s9");
}

bool LoginInterface::Click(int x, int y)
{
    return !view_.IsTransp(x - (sizeW / 2 - 144), y - (sizeH / 2 - 144), 0);
}

void LoginInterface::Draw()
{
    view_.Draw(0, sizeW / 2 - 144, sizeH / 2 - 144);
}

unsigned int LoginInterface::hash() const
{
    return ::hash(view_);
}