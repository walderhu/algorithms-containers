#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "../s21_containers.hpp"

namespace s21 {

template <typename Key, typename T>
class AVLTree {
 protected:
  class iterator;
  class const_iterator;
  struct Node {
    std::pair<const Key, T> value;
    int height;
    Node* left;
    Node* right;
    Node* parent;
    Node(const std::pair<const Key, T>& val)
        : value(val),
          height(1),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
  };
  Node* root;
  std::size_t size_;

  int height(Node* node) { return node ? node->height : 0; }

  int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
  }

  void updateHeight(Node* node) {
    if (node) {
      node->height = 1 + std::max(height(node->left), height(node->right));
    }
  }

  Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    if (T2) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;
    updateHeight(y);
    updateHeight(x);
    return x;
  }

  Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    if (T2) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;
    updateHeight(x);
    updateHeight(y);
    return y;
  }

  Node* balance(Node* node) {
    updateHeight(node);
    int balance = balanceFactor(node);
    if (balance > 1) {
      if (balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
      }
      return rotateRight(node);
    }
    if (balance < -1) {
      if (balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
      }
      return rotateLeft(node);
    }
    return node;
  }

  Node* insert(Node* node, const std::pair<const Key, T>& value) {
    if (!node) {
      size_++;
      return new Node(value);
    }
    if (value.first < node->value.first) {
      node->left = insert(node->left, value);
      node->left->parent = node;
    } else if (value.first > node->value.first) {
      node->right = insert(node->right, value);
      node->right->parent = node;
    } else {
      node->value.second = value.second;
    }
    return balance(node);
  }

  Node* findMin(Node* node) {
    while (node->left) {
      node = node->left;
    }
    return node;
  }

  Node* removeMin(Node* node) {
    if (!node->left) {
      return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
  }

  Node* remove(Node* node, const Key& key) {
    if (!node) {
      return nullptr;
    }
    if (key < node->value.first) {
      node->left = remove(node->left, key);
    } else if (key > node->value.first) {
      node->right = remove(node->right, key);
    } else {
      size_--;
      Node* l = node->left;
      Node* r = node->right;
      delete node;
      if (!r) return l;
      if (!l) return r;
      Node* min = findMin(r);
      min->right = removeMin(r);
      min->left = l;
      min->parent = node->parent;
      return balance(min);
    }
    return balance(node);
  }

  void clear(Node* node) {
    if (node && size_ > 0) {
      clear(node->left);
      clear(node->right);
      delete node;
      size_--;
      node = nullptr;
    }
  }

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;

  AVLTree() : root(nullptr), size_(0) {}

  ~AVLTree() { clear(); }

  void clear() {
    clear(root);
    root = nullptr;
    size_ = 0;
  }

  void insert(const std::pair<const Key, T>& value) {
    root = insert(root, value);
  }

  void remove(const Key& key) { root = remove(root, key); }

  bool contains(const Key& key) const {
    Node* node = root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return true;
      }
    }
    return false;
  }
  /* моя версия
  bool contains(const Key& key) const {
    for (Node* node = root; node;
         node = key < node->value.first ? node->left : node->right)
      if (key == node->value.first) return true;
    return false;
  }
  */

  T& at(const Key& key) {
    Node* node = root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return node->value.second;
      }
    }
    throw std::out_of_range("Key not found");
  }

  T& operator[](const Key& key) {
    Node* node = root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return node->value.second;
      }
    }
    insert(std::make_pair(key, T()));
    return at(key);
  }

  iterator begin() { return iterator(this->root); }

  iterator end() { return iterator(); }

  const_iterator cbegin() const { return const_iterator(this->root); }

  const_iterator cend() const { return const_iterator(); }

  iterator find(const Key& key) {
    Node* node = this->root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return iterator(node);
      }
    }
    return end();
  }

  const_iterator find(const Key& key) const {
    Node* node = this->root;
    while (node) {
      if (key < node->value.first) {
        node = node->left;
      } else if (key > node->value.first) {
        node = node->right;
      } else {
        return const_iterator(node);
      }
    }
    return cend();
  }
};

#include "../Map/s21_map_iterator.hpp"

}  // namespace s21

#endif