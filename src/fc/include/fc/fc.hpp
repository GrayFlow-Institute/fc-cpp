//
// Created by yanyuhl on 18-6-23.
//

#ifndef SRC_FC_H
#define SRC_FC_H


#include <forward_list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <iostream>

namespace fc {

  template<class T>
  class Fc {
  public:

    template<class InputIterator>
    Fc(const InputIterator &start, const InputIterator &end) {
      auto it = _list.before_begin();
      auto data = start;
      while (data != end) {
        it = _list.insert_after(it, *data);
        ++data;
      }
    }

    explicit Fc(const std::forward_list<T> list) {
      _list = std::move(list);
    }

    Fc &operator=(const Fc &fc) {
      fc._list = this->_list;
    }

    Fc(const Fc &fc) {
      fc = *this;
    }

    Fc(Fc &&fc) noexcept: _list(move(fc._list)) {}

    inline Fc &map(const std::function<T(T)> &f) {
      for (auto &item :_list) {
        item = f(item);
      }
      return *this;
    }

    template<typename E>
    inline Fc<E> map(const std::function<E(T)> &f) {
      auto nl = std::forward_list<E>();
      auto it = nl.before_begin();
      for (const auto &item:_list) {
        it = nl.insert_after(it, f(item));
      }
      return Fc<E>(std::move(nl));
    }

    inline Fc &filter(const std::function<bool(T)> &f) {
      _list.remove_if([f](T v) -> bool { return !f(v); });
      return *this;
    }

    Fc &print() {
      for (const auto &it :_list) {
        std::cout << it << " ";
      }
      return *this;
    }

    Fc &print(const std::function<std::string(T)> &f) {
      for (const auto &it :_list) {
        std::cout << f(it) << " ";
      }
      std::cout << std::endl;
      return *this;
    }

    inline T reduce(const std::function<T(T, T)> &f) {
      T result = T();
      for (const auto &it:_list) {
        result = f(result, it);
      }
      return result;
    }

    template<class E>
    inline E reduce(const std::function<E(E, T)> &f) {
      E result;
      for (const auto &it:_list) {
        result = f(result, it);
      }
      return result;
    }


    inline std::forward_list<T> &done() {
      return _list;
    }

    inline std::vector<T> to_vector() {
      std::vector<T> vector;
      std::for_each(_list.begin(), _list.end(), [&vector](T x) {
        vector.push_back(x);
      });
      return vector;
    };

    typename std::forward_list<T>::iterator begin() {
      return _list.begin();
    }

    typename std::forward_list<T>::iterator end() {
      return _list.end();
    }

  private:
    std::forward_list<T> _list;
  };

}

#endif //SRC_FC_H
