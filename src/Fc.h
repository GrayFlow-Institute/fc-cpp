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
  Fc(const InputIterator &start, const InputIterator &end) {
    auto it = start;
    while (it != end) {
      _list.push_back(*it);
      ++it;
    }
  }

  Fc(const std::vector<T> list) {
    _list = std::move(list);
  }

  Fc map(const std::function<T(T)> &f) {
    for (auto &item :_list) {
      item = (f(item));
    }
    return *this;
  }

  Fc filter(const std::function<bool(T)> &f) {
    auto it=_list.begin();
    while(it!=_list.end()){
      if(!f(*it)){_list.erase(it);}
      else{++it;}
    }
    return *this;
  }

  T reduce(const std::function<T(T, T)> &f) {
    T result = T();
    if (_list.size() > 0) {
      result = *_list.begin();
      if (_list.size() > 1) {
        for (auto it = _list.begin() + 1; it != _list.end(); ++it) {
          result = f(result, *it);
        }
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
