//
// Created by yanyuhl on 18-6-23.
//

#ifndef SRC_FC_H
#define SRC_FC_H

#include <functional>
#include <forward_list>
#include <iterator>


template<class T>
class Fc {
public:

  template<class InputIterator>
  Fc(const InputIterator &start, const InputIterator &end) {
    auto it = start;
    while (it != end) {
      _list.push_front(*it);
      ++it;
    }
  }

  explicit Fc(const std::forward_list<T> list) {
    _list = std::move(list);
  }

  Fc map(const std::function<T(T)> &f) {
    for (auto &item :_list) {
      item = f(item);
    }
    return *this;
  }

  Fc filter(const std::function<bool(T)> &f) {
    _list.remove_if([f](T v) -> bool { return !f(v); });
    return *this;
  }

  T reduce(const std::function<T(T, T)> &f) {
    T result = T();
    for (auto it = _list.begin(); it != _list.end(); ++it) {
      result = f(result, *it);
    }
    return result;
  }

  std::forward_list<T> done() {
    return _list;
  }

  typename std::forward_list<T>::iterator begin() {
    return _list.begin();
  }

  typename std::forward_list<T>::iterator end() {
    return _list.end();
  }

private:
  std::forward_list<T> _list;
};


#endif //SRC_FC_H
