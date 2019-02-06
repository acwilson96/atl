#include "gtest/gtest.h"

#include "../include/shared_ptr.h"
#include <memory>

TEST(SharedPtrTest, DefaultConstruction) {
  atl::shared_ptr<int> atlSP;
  std::shared_ptr<int> stdSP;
  ASSERT_EQ(atlSP.get(), stdSP.get());
}

TEST(SharedPtrTest, PtrConstruction) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  std::shared_ptr<int> stdSP(myInt);
  ASSERT_EQ(atlSP.get(), stdSP.get());
  ASSERT_EQ(*atlSP, *stdSP);
}

TEST(SharedPtrTest, RefCount) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  atl::shared_ptr<int> atlSP2(atlSP);

  ASSERT_EQ(atlSP.get(), atlSP2.get());
  ASSERT_EQ(*atlSP, *atlSP2);

  std::shared_ptr<int> stdSP(myInt);
  std::shared_ptr<int> stdSP2(stdSP);

  ASSERT_EQ(stdSP.use_count(), atlSP.use_count());
  ASSERT_EQ(*atlSP, *stdSP2);
}

TEST(SharedPtrTest, Equality) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  atl::shared_ptr<int> atlSP2(atlSP);

  std::shared_ptr<int> stdSP(myInt);
  std::shared_ptr<int> stdSP2(stdSP);

  ASSERT_TRUE(atlSP == atlSP2);
  ASSERT_TRUE(stdSP == stdSP2);
  ASSERT_FALSE(atlSP != atlSP2);
  ASSERT_FALSE(stdSP != stdSP2);
}

TEST(SharedPtrTest, MakeShared) {
  atl::shared_ptr<int> atlMSP = atl::make_shared<int>(5);
  atl::shared_ptr<int> atlMSP2 = atl::make_shared<int>(5);
  ASSERT_FALSE(atlMSP == atlMSP2);
  atl::shared_ptr<int> atlSP(atlMSP);
  ASSERT_TRUE(atlSP == atlMSP);
}

TEST(SharedPtrTest, SharedFromThis) {
  class TestInt : public atl::enable_shared_from_this<TestInt> {
  public:
    int val;
    TestInt(const int val) : val(val) {}
    atl::shared_ptr<TestInt> get_ptr() { return shared_from_this(); }
  };

  TestInt myTestInt(5);

  atl::shared_ptr<TestInt> myTestIntPtr1(&myTestInt);
  atl::shared_ptr<TestInt> myTestIntPtr2 = myTestInt.get_ptr();

  ASSERT_TRUE(myTestIntPtr1 == myTestIntPtr2);

  atl::shared_ptr<TestInt> myTestIntPtr3(myTestIntPtr1);
  atl::shared_ptr<TestInt> myTestIntPtr4(myTestIntPtr2);
  atl::shared_ptr<TestInt> myTestIntPtr5 = myTestInt.get_ptr();

  ASSERT_TRUE(myTestIntPtr3 == myTestIntPtr4);
  ASSERT_TRUE(myTestIntPtr4 == myTestIntPtr5);
}

// The fixture for testing class Project1. From google test primer.
class Test_SharedPtr : public ::testing::Test {
protected:
  Test_SharedPtr() {
    // You can do set-up work for each test here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
};