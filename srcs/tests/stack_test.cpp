#include "stack.hpp"

#include <gtest/gtest.h>

#include <deque>
#include <vector>

TEST(StackTest, Constructor) {
  ft::stack<int> s;
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
}

TEST(StackTest, ConstructorWithVector) {
  ft::vector<int> v(5, 42);
  ft::stack<int>  s(v);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.top(), 42);
  for (size_t i = 0; i < 5; i++) {
    s.pop();
  }
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
}

TEST(StackTest, Push) {
  ft::stack<int> s;
  s.push(42);
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 42);
}

TEST(StackTest, Assignation) {
  ft::stack<int> s1;
  ft::stack<int> s2;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s2 = s1;
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.top(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, ElementAccess) {
  ft::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, Capacity) {
  ft::stack<int> s;
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.size(), 0);
  s.push(1);
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 1);
  s.pop();
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Modifires) {
  ft::stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_EQ(s.empty(), true);
}

TEST(StackTest, NonMemberFunction) {
  ft::stack<int> s1;
  ft::stack<int> s2;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1 == s2, true);
  EXPECT_EQ(s1 != s2, false);
  EXPECT_EQ(s1 < s2, false);
  EXPECT_EQ(s1 <= s2, true);
  EXPECT_EQ(s1 > s2, false);
  EXPECT_EQ(s1 >= s2, true);
}

// same test with std::vector
TEST(StackTest, ConstructorWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s(v);
  EXPECT_EQ(s.size(), 0);
  EXPECT_EQ(s.empty(), true);
}

TEST(StackTest, AssignationWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s1(v);
  ft::stack<int, std::vector<int>> s2;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s2 = s1;
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.top(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, ElementAccessWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s(v);
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, CapacityWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s(v);
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.size(), 0);
  s.push(1);
  EXPECT_EQ(s.empty(), false);
  EXPECT_EQ(s.size(), 1);
  s.pop();
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, ModifiresWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s(v);
  s.push(1);
  s.push(2);
  s.push(3);
  EXPECT_EQ(s.top(), 3);
  s.pop();
  EXPECT_EQ(s.top(), 2);
  s.pop();
  EXPECT_EQ(s.top(), 1);
  s.pop();
  EXPECT_EQ(s.empty(), true);
}

TEST(StackTest, NonMemberFunctionWithStdVector) {
  std::vector<int>                 v;
  ft::stack<int, std::vector<int>> s1(v);
  ft::stack<int, std::vector<int>> s2;
  s1.push(1);
  s1.push(2);
  s1.push(3);
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.top(), s2.top());
  EXPECT_EQ(s1 == s2, true);
  EXPECT_EQ(s1 != s2, false);
  EXPECT_EQ(s1 < s2, false);
  EXPECT_EQ(s1 <= s2, true);
  EXPECT_EQ(s1 > s2, false);
  EXPECT_EQ(s1 >= s2, true);
}