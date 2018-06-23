//
// Created by yanyuhl on 18-6-23.
//


#include <gtest/gtest.h>
#include <vector>
#include "../../src/Fc.h"

using namespace std;

TEST(Fc, map) {
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };
  vector<int> vl = {
      2, 3, 4, 5, 6, 7
  };

  auto v = Fc<int>(l)
      .map([](int x) -> int {
        return x + 1;
      })
      .done();

  EXPECT_EQ(vl, v);
}

TEST(Fc, filter) {
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };
  vector<int> vl = {
      4, 5, 6
  };

  auto v = Fc<int>(l)
      .filter([](int x) -> bool {
        return x > 3;
      })
      .done();

  EXPECT_EQ(vl, v);
}

TEST(Fc, reduce) {
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };

  auto v = Fc<int>(l)
      .reduce([](int x, int y) -> int {
        return x + y;
      });

  EXPECT_EQ(v, 21);
}

TEST(Fc, integration) {
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };

  auto v = Fc<int>(l).map([](int x) {
    return x + 1;
  }).filter([](int x) {
    return x > 3;
  }).reduce([](int x, int y) {
    return x + y;
  });

  EXPECT_EQ(v,22);
}