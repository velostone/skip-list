#include <gtest.h>
#include "skiplist.h"

TEST(SkiplistTest, can_create_skiplist)
{
    ASSERT_NO_THROW(SkipList<int> S);
}
TEST(SkipListTest, can_insert_and_find_elem) 
{
    SkipList<int> S;
    S.insert(1, 8);
    S.insert(2, 24);
    S.insert(4, 32);
    EXPECT_EQ(*S.find(1), 8);
    EXPECT_EQ(*S.find(2), 24);
    EXPECT_EQ(*S.find(4), 32);
}
TEST(SkipListTest, cant_insert_elem_with_non_uniqu_key) 
{
    SkipList<int> S;
    S.insert(1, 8);
    EXPECT_FALSE(S.insert(1, 16));
}
TEST(SkipListTest, cant_find_non_existing_elem) 
{
    SkipList<int> S;
    S.insert(1, 8);
    EXPECT_TRUE(S.find(3) == nullptr);
}
TEST(SkipListTest, can_erase_elem) 
{
    SkipList<int> S;
    S.insert(1, 8);
    S.erase(1);
    EXPECT_TRUE(S.find(1) == nullptr);
}
TEST(SkipListTest, cant_erase_non_existing_elem) 
{
    SkipList<int> S;
    S.insert(1, 8);
    EXPECT_FALSE(S.erase(2));
}