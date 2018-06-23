//
// Created by yanyuhl on 18-6-23.
//

#include "fc.h"
#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> l = {
      1, 2, 3, 4, 5, 6
  };

  cout<< Fc<int>(l).map([](int x){
    return x+1;
  }).filter([](int x){
    return x>3;
  }).reduce([](int x,int y){
    return x+y;
  });

  auto v = Fc<int>(l)
      .map([](int x) -> int {
        return x + 1;
      })
      .done();

  auto k = Fc<int>(l.begin(), l.end())
      .map([](int x) -> int {
        return x + 1;
      })
      .done();

  auto m = Fc<int>(l)
      .filter([](int x) -> bool {
        return x > 3;
      })
      .done();

  auto a = Fc<int>(l)
      .reduce([](int x, int y) -> int {
        return x + y;
      });
}