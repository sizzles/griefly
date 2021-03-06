#include <gtest/gtest.h>

#include "interfaces_mocks.h"

#include "core/objects/MainObject.h"

using ::testing::ReturnRef;
using ::testing::Return;

TEST(MainObject, Constructor)
{
    IMainObject object(42);
    ASSERT_EQ(object.GetId(), 42);
    ASSERT_EQ(object.GetFreq(), 0);

    IMainObject object2(/*NotLoadItem*/nouse);
    ASSERT_EQ(object2.GetId(), 0);
    ASSERT_EQ(object2.GetFreq(), 0);
}

TEST(MainObject, Types)
{
   ASSERT_EQ(IMainObject::GetTypeStatic(), "main");
   IMainObject object(42);
   ASSERT_EQ(object.GetType(), "main");

   ASSERT_EQ(object.GetTypeIndex(), 0);
   ASSERT_EQ(IMainObject::GetTypeIndexStatic(), 0);
}

TEST(MainObject, Hash)
{
    IMainObject object(24);
    ASSERT_EQ(object.Hash(), 24);
}

TEST(MainObject, EmptyFunctions)
{
    // They just should not crash the game
    IMainObject object(11);
    object.AfterWorldCreation();
    object.Process();
}

TEST(MainObject, Save)
{
    {
        IMainObject object(42);
        FastSerializer save(1);
        object.Save(save);

        const char* const DATA =
            "\x06\x02\x04\x00\x00\x00\x6d\x00\x61\x00"
            "\x69\x00\x6E\x00\x03\x2A\x00\x00\x00"
            "\x02\x00\x00\x00\x00";

        EXPECT_EQ(
            QByteArray(save.GetData(), save.GetIndex()),
            QByteArray(DATA, 24));
    }
    {
        MockIGame game;
        MockIObjectFactory factory;
        EXPECT_CALL(game, GetFactory())
            .WillRepeatedly(ReturnRef(factory));
        EXPECT_CALL(factory, AddProcessingItem(42))
            .WillOnce(Return());

        IMainObject object(42);
        object.SetGame(&game);
        FastDeserializer save("\x02\x08\x00\x00\x00", 5);
        object.Load(save);
        EXPECT_EQ(object.GetFreq(), 8);
    }
}

TEST(MainObjectDeathTest, Deaths)
{
    {
        IMainObject object(42);
        ASSERT_DEATH(
        {
            object.GetGame();
        }, "IMainObject::GetGame\\(\\) is called during construction of object");
    }
    {
        IMainObject object(42);
        const IMainObject* ptr = &object;
        ASSERT_DEATH(
        {
            ptr->GetGame();
        }, "IMainObject::GetGame\\(\\) is called during construction of object");
    }
    {
        IMainObject object(42);
        ASSERT_DEATH(
        {
            object.SetFreq(0);
        }, "SetFreq is called in constructor");
    }
    {
        IMainObject object(0);
        MockIGame game;
        object.SetGame(&game);
        ASSERT_DEATH(
        {
            object.SetFreq(0);
        }, "GetId\\(\\) is zero");
    }
}

TEST(MainObject, SettersAndGettersAndCreateImpl)
{
    {
        MockIGame game;
        MockIObjectFactory factory;

        IMainObject object(43);
        object.SetGame(&game);
        IGame* interface_game = &object.GetGame();
        ASSERT_EQ(interface_game, &game);

        const IMainObject& object_const_ref = object;
        ASSERT_EQ(&object_const_ref.GetGame(), &game);

        EXPECT_CALL(game, GetFactory())
            .WillRepeatedly(ReturnRef(factory));
        ASSERT_EQ(&object.GetFactory(), &factory);

        SyncRandom random;
        random.SetRand(42, 42);
        EXPECT_CALL(game, GetRandom())
            .WillRepeatedly(ReturnRef(random));
        ASSERT_EQ(object.GetRand(), 5885939);
    }
    {
        MockIGame game;
        MockIObjectFactory factory;
        EXPECT_CALL(game, GetFactory())
            .WillRepeatedly(ReturnRef(factory));

        IMainObject object(43);
        object.SetGame(&game);
        ASSERT_EQ(object.GetFreq(), 0);

        EXPECT_CALL(factory, AddProcessingItem(43));
        object.SetFreq(46);
        ASSERT_EQ(object.GetFreq(), 46);

        EXPECT_CALL(factory, AddProcessingItem(84));
        object.SetId(84);
        ASSERT_EQ(object.GetId(), 84);
    }
    {
        MockIGame game;
        MockIObjectFactory factory;
        EXPECT_CALL(game, GetFactory())
            .WillRepeatedly(ReturnRef(factory));
        EXPECT_CALL(factory, CreateImpl(QString("type"), 42))
            .WillOnce(Return(111));

        IMainObject object(43);
        object.SetGame(&game);
        ASSERT_EQ(object.CreateImpl("type", 42), 111);
    }
}

TEST(MainObject, Delete)
{
    MockIGame game;
    MockIObjectFactory factory;
    EXPECT_CALL(game, GetFactory())
        .WillRepeatedly(ReturnRef(factory));

    IMainObject object(43);
    object.SetGame(&game);

    EXPECT_CALL(factory, DeleteLater(43))
        .WillOnce(Return());
    object.Delete();
}
