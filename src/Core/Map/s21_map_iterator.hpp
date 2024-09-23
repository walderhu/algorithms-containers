#ifndef MAP_ITERATOR_H
#define MAP_ITERATOR_H

// #include "s21_binary_tree.hpp"
#include "../s21_containers.hpp"

template <typename Key, typename T>
class AVLTree<Key, T>::iterator {
 public:
  iterator() : node(nullptr) {}
  iterator(typename AVLTree<Key, T>::Node* root) : node(root) {
    if (node) {
      while (node->left) {
        node = node->left;
      }
    }
  }

  reference operator*() const { return node->value; }

  pointer operator->() const { return &node->value; }

  iterator& operator++() {
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    } else {
      typename AVLTree<Key, T>::Node* tmp = node;
      while (tmp->parent && tmp == tmp->parent->right) {
        tmp = tmp->parent;
      }
      node = tmp->parent;
    }
    return *this;
  }

  iterator operator++(int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  iterator& operator--() {
    if (node) {
      if (node->left) {
        node = node->left;
        while (node->right) {
          node = node->right;
        }
      } else {
        while (node->parent && node == node->parent->left) {
          node = node->parent;
        }
        node = node->parent;
      }
      return *this;
    }
    return *this;
  }

  iterator operator--(int) {
    iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const iterator& other) const { return node == other.node; }

  bool operator!=(const iterator& other) const { return node != other.node; }

 private:
  Node* node;
};

template <typename Key, typename T>
class AVLTree<Key, T>::const_iterator : public AVLTree<Key, T>::iterator {
 public:
  const_iterator() : node(nullptr) {}
  const_iterator(typename AVLTree<Key, T>::Node* root) : node(root) {
    if (node) {
      while (node->left) {
        node = node->left;
      }
    }
  }

  const_reference operator*() const { return node->value; }

  pointer operator->() const { return &node->value; }

  const_iterator& operator++() {
    if (node->right) {
      node = node->right;
      while (node->left) {
        node = node->left;
      }
    } else {
      while (node->parent && node == node->parent->right) {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  const_iterator operator++(int) {
    const_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  const_iterator& operator--() {
    if (node->left) {
      node = node->left;
      while (node->right) {
        node = node->right;
      }
    } else {
      while (node->parent && node == node->parent->left) {
        node = node->parent;
      }
      node = node->parent;
    }
    return *this;
  }

  const_iterator operator--(int) {
    const_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const const_iterator& other) const {
    return node == other.node;
  }

  bool operator!=(const const_iterator& other) const {
    return node != other.node;
  }

 private:
  Node* node;
};

#endif
