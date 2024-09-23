#ifndef MAP_H
#define MAP_H

#include "../AVLTree/s21_binary_tree.hpp"
#include "../s21_containers.hpp"

namespace s21 {

template <typename Key, typename T>
class map : public AVLTree<Key, T> {
 public:
  using base_type = AVLTree<Key, T>;
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename base_type::iterator;
  using const_iterator = typename base_type::const_iterator;
  using size_type = std::size_t;

  using AVLTree<Key, T>::root;
  using AVLTree<Key, T>::size_;

  map() : base_type() {}

  map(std::initializer_list<value_type> const& items) : base_type() {
    for (const auto& item : items) {
      insert(item);
    }
  }

  map(const map& m) : base_type() {
    for (auto it = m.cbegin(); it != m.cend(); ++it) {
      insert(*it);
    }
  }

  map(map&& m) noexcept {
    if (this != &m) {
      clear();
      root = m.root;
      size_ = m.size_;
      m.root = nullptr;
      m.size_ = 0;
    }
  }

  map& operator=(map&& m) noexcept {
    if (this != &m) {
      clear();
      root = m.root;
      size_ = m.size_;
      m.root = nullptr;
      m.size_ = 0;
    }
    return *this;
  }

  map& operator=(const map& other) noexcept {
    if (this != &other) {
      map temp(other);
      *this = std::move(temp);
    }
    return *this;
  }

  ~map() {}

  T& at(const Key& key) { return base_type::at(key); }

  T& operator[](const Key& key) { return base_type::operator[](key); }

  iterator begin() { return base_type::begin(); }

  iterator end() { return base_type::end(); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / sizeof(value_type) / 10);
  }

  void clear() { base_type::clear(); }

  std::pair<iterator, bool> insert(const value_type& value) {
    typename base_type::Node* node = root;
    while (node) {
      if (value.first < node->value.first) {
        node = node->left;
      } else if (value.first > node->value.first) {
        node = node->right;
      } else {
        return {iterator(node), false};
      }
    }
    root = base_type::insert(root, value);
    return {base_type::find(value.first), true};
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    typename base_type::Node* node = root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return {iterator(node), false};
      }
    }
    root = base_type::insert(root, std::make_pair(key, obj));
    return {base_type::find(key), true};
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    typename base_type::Node* node = root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        node->value.second = obj;
        return {iterator(node), false};
      }
    }
    root = base_type::insert(root, std::make_pair(key, obj));
    return {base_type::find(key), true};
  }

  void erase(iterator pos) {
    if (pos != end()) remove(pos->first);
  }

  void swap(map& other) {
    std::swap(root, other.root);
    std::swap(size_, other.size_);
  }

  void merge(map& other) {
    map<Key, T> tmp_map;
    for (auto it = other.begin(); it != other.end(); ++it) {
      if (!contains(it->first))
        insert(*it);
      else
        tmp_map.insert(*it);
    }
    other = std::move(tmp_map);
  }

  bool contains(const Key& key) const { return base_type::contains(key); }

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> results;
    for (const auto& arg : {args...}) {
      results.push_back(insert(arg));
    }
    return results;
  }
};

}  // namespace s21

#endif