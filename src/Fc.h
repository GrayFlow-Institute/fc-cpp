//
// Created by yanyuhl on 18-6-23.
//

#ifndef SRC_FC_H
#define SRC_FC_H

#include <functional>
#include <vector>
#include <iterator>

template<class T>
class Fc {
public:

  template<class InputIterator>
  Fc(const InputIterator start, const InputIterator end) {
    auto it = start;
    while (it != end) {
      _list.push_back(*it);
      ++it;
    }
  }

  Fc(const std::vector<T> list) {
    _list = list;
  }

  Fc map(std::function<T(T)> f) {
    std::vector<T> newVector;
    for (auto item :_list) {
      newVector.push_back(f(item));
    }
    return Fc(newVector);
  }

  Fc filter(std::function<bool(T)> f) {
    std::vector<T> newVector;
    for (auto item :_list) {
      if (f(item)) {
        newVector.push_back(item);
      }
    }
    return Fc(newVector);
  }

  T reduce(std::function<T(T, T)> f) {
    T result;
    if (_list.size() > 0) {
      result = *_list.begin();
      for (auto it = _list.begin() + 1; it != _list.end(); ++it) {
        result = f(result, *it);
      }
    }
    return result;
  }

  std::vector<T> done() {
    return _list;
  }

private:
  std::vector<T> _list;
};


#endif //SRC_FC_H
