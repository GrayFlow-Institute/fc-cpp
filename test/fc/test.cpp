//
// Created by yanyuhl on 18-6-23.
//


#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <forward_list>
#include "fc/fc.hpp"

using namespace std;

namespace {


TEST(Fc, map) {
  forward_list<int> l = {
      1, 2, 3, 4, 5, 6
  };
  forward_list<int> vl = {
      2, 3, 4, 5, 6, 7
  };

  auto v = Fc<int>(l)
      .map([](int x) -> int {
        return x + 1;
      })
      .done();
  // 验证 map 正常操作
  EXPECT_EQ(vl, v);

  forward_list<int> l0;
  v = Fc<int>(l0)
      .map([](int x) -> int {
        return x + 1;
      })
      .done();

  // 验证空 list 的 map 操作是否也为空
  EXPECT_EQ(l0, v);
}

TEST(Fc, filter) {
  forward_list<int> l = {
      1, 2, 3, 4, 5, 6
  };
  forward_list<int> vl = {
      4, 5
  };
  auto v = Fc<int>(l)
      .filter([](int x) -> bool {
        return x > 3 and x < 6;
      })
      .done();

//  验证 filter 的正常过滤操作
  EXPECT_EQ(vl, v);

  forward_list<int> l0;
  v = Fc<int>(l0)
      .filter([](int x) -> int {
        return 1;
      })
      .done();

// 验证 filter 过滤空列表操作
  EXPECT_EQ(l0, v);
}

TEST(Fc, reduce) {
  forward_list<int> l = {
      1, 2, 3, 4, 5, 6
  };

  auto v = Fc<int>(l)
      .reduce([](int x, int y) -> int {
        return x + y;
      });

//  验证 reduce 正常操作
  EXPECT_EQ(v, 21);

  forward_list<int> l0;
  auto v0 = Fc<int>(l0)
      .reduce([](int x, int y) -> int {
        return x + y;
      });

//  验证 reduce 空列表操作
  EXPECT_EQ(v0, 0);

  forward_list<int> l1 = {1};
  auto v1 = Fc<int>(l1)
      .reduce([](int x, int y) -> int {
        return x + y;
      });

//  验证 reduce 单一元素操作
  EXPECT_EQ(v1, 1);

}

TEST(Fc, Container) {

  // vector iterator
  vector<int> l = {1, 2, 3, 4, 5, 6};
  auto v = Fc<int>(l.begin(), l.end()).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });
  EXPECT_EQ(v, 22);

  // forward_list iterator
  forward_list<int> l1 = {1, 2, 3, 4, 5, 6};
  v = Fc<int>(l1.begin(), l1.end()).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });
  EXPECT_EQ(v, 22);

  // list iterator
  list<int> l2 = {1, 2, 3, 4, 5, 6};
  v = Fc<int>(l2.begin(), l2.end()).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });
  EXPECT_EQ(v, 22);

}

TEST(Fc, Iterator) {
  forward_list<int> list1 = {1};
  auto fc = Fc<int>(list1);

  // i is a const type
  for (const auto i:fc) {
    EXPECT_EQ(i,1);
  }
  // i is a const reference
  for (const auto& i:fc) {
    EXPECT_EQ(i,1);
  }

  // i is a local variable
  for (auto i :fc) {
    EXPECT_EQ(i, 1);
    i = 2;
    EXPECT_EQ(i, 2);
  }

  for (auto i :fc) {
    EXPECT_NE(i, 2);
  }

  // i is a reference,it will change variable
  for (auto &i:fc) {
    EXPECT_EQ(i, 1);
    i = 2;
  }
  for (auto i:fc) {
    EXPECT_EQ(i, 2);
  }

}
}