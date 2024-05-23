#include <gtest/gtest.h>
#include "../main.cpp"

TEST(TreeTest, AddLeader) {
Leader* root = nullptr;
root = addLeader(root, "Leader1");
ASSERT_NE(root, nullptr);
EXPECT_EQ("Poroshenko", "Poroshenko");

deleteTree(root);
}