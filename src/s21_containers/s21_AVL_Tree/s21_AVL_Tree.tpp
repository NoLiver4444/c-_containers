#include "s21_AVL_Tree.h"

// Конструкторы узла
template <typename Key, typename Value>
AVL_Tree<Key, Value>::Node::Node(Key key, value_type value)
    : key(key), value(value) {}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::Node::Node(Key key, value_type value, Node *parent)
    : key(key),
      value(value),
      parent(parent),
      left(nullptr),
      right(nullptr),
      height(0) {}

// Конструкторы дерева
template <typename Key, typename Value>
AVL_Tree<Key, Value>::AVL_Tree() : root(nullptr) {}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::AVL_Tree(const AVL_Tree &other) {
  root = copy_Tree(other.root, nullptr);
}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::AVL_Tree(AVL_Tree &&other) noexcept {
  root = other.root;
  other.root = nullptr;
}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::~AVL_Tree() {
  clear();
}

// Метод для копирования дерева
template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::copy_Tree(
    Node *copy_node, Node *parent) {
  if (copy_node != nullptr) {
    Node *new_node = new Node(copy_node->key, copy_node->value);
    new_node->left = copy_Tree(copy_node->left, new_node);
    new_node->right = copy_Tree(copy_node->right, new_node);
    new_node->parent = parent;
    return new_node;
  }
  return nullptr;
}

template <typename Key, typename Value>
void AVL_Tree<Key, Value>::remove_Tree(Node *node) {
  if (node == nullptr) {
    return;
  }

  remove_Tree(node->left);
  remove_Tree(node->right);

  delete node;
}

// Методы для добавления узла
template <typename Key, typename Value>
std::pair<typename AVL_Tree<Key, Value>::Iterator, bool>
AVL_Tree<Key, Value>::insert(const Key &key) {
  std::pair<Iterator, bool> answ_pair;

  if (root == nullptr) {
    root = new Node(key, key);
    answ_pair.first = Iterator(root);
    answ_pair.second = true;
  } else {
    bool check_insert = insert_place_find(root, key, key);
    answ_pair.first = find(key);
    answ_pair.second = check_insert;
  }

  return answ_pair;
}

// Метод для удаления узла
template <typename Key, typename Value>
void AVL_Tree<Key, Value>::erase(iterator pos) {
  if (root == nullptr || pos.current_node == nullptr) {
    return;
  }
  root = remove_node_find(root, *pos);
}

// Методы итераторов
template <typename Key, typename Value>
AVL_Tree<Key, Value>::Iterator::Iterator()
    : current_node(nullptr), past_node(nullptr) {}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::Iterator::Iterator(Node *current_node, Node *past_node)
    : current_node(current_node), past_node(past_node) {}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *
AVL_Tree<Key, Value>::Iterator::move_forward(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right != nullptr) {
    return get_min(node->right);
  }

  Node *parent = node->parent;
  while (parent != nullptr && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }

  return parent;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::Iterator::move_back(
    Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left != nullptr) {
    return get_max(node->left);
  }

  Node *parent = node->parent;
  while (parent != nullptr && node == parent->left) {
    node = parent;
    parent = parent->parent;
  }

  return parent;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Iterator &
AVL_Tree<Key, Value>::Iterator::operator++() {
  Node *tmp_node = nullptr;
  if (current_node != nullptr) {
    tmp_node = get_max(current_node);
  }
  current_node = move_forward(current_node);
  if (current_node == nullptr) {
    past_node = tmp_node;
  }

  return *this;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Iterator &
AVL_Tree<Key, Value>::Iterator::operator--() {
  if (current_node == nullptr) {
    if (past_node) {
      current_node = past_node;
      past_node = nullptr;
    } else {
      throw std::out_of_range("Decrementing end() iterator");
    }
  } else {
    current_node = move_back(current_node);
  }
  return *this;
}

template <typename Key, typename Value>
Key &AVL_Tree<Key, Value>::Iterator::operator*() {
  if (current_node == nullptr) {
    throw std::out_of_range("Dereferencing nullptr iterator");
  }
  return current_node->key;
}

template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::Iterator::operator!=(const Iterator &other) const {
  return current_node != other.current_node;
}

template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::Iterator::operator==(const Iterator &other) const {
  return current_node == other.current_node;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *
AVL_Tree<Key, Value>::Iterator::operator->() const {
  return current_node;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Iterator AVL_Tree<Key, Value>::begin() {
  return AVL_Tree::Iterator(get_min(root));
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Iterator AVL_Tree<Key, Value>::end() {
  if (root == nullptr) return begin();

  Node *last_node = get_max(root);
  Iterator test(nullptr, last_node);
  return test;
}

// Методы для поиска
template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Iterator AVL_Tree<Key, Value>::find(
    const Key &key) {
  Node *exact_node = find_node(key, root);
  return Iterator(exact_node);
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::find_node(
    const Key &key, Node *node) {
  if (node == nullptr) {
    return node;
  }

  if (key < node->key) {
    node = find_node(key, node->left);
  } else if (key > node->key) {
    node = find_node(key, node->right);
  }

  return node;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::get_min(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left != nullptr) {
    return get_min(node->left);
  }
  return node;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::get_max(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right != nullptr) {
    return get_max(node->right);
  }

  return node;
}

template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::insert_place_find(AVL_Tree::Node *node,
                                             const Key &key, Value value) {
  bool check_insert = false;
  if (key < node->key) {
    if (node->left == nullptr) {
      node->left = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = insert_place_find(node->left, key, value);
    }
  } else if (key > node->key) {
    if (node->right == nullptr) {
      node->right = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = insert_place_find(node->right, key, value);
    }
  } else if (key == node->key) {
    return check_insert;
  }
  update_height(node);
  balance_Tree(node);
  return check_insert;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::remove_node_find(
    Node *node, Key key) {
  if (node == nullptr) {
    return nullptr;
  }

  // Поиск узла для удаления
  if (key < node->key) {
    node->left = remove_node_find(node->left, key);
  } else if (key > node->key) {
    node->right = remove_node_find(node->right, key);
  } else {
    // Узел найден - начинаем удаление
    if (node->left == nullptr || node->right == nullptr) {
      // Случай 1: У узла 0 или 1 потомок
      Node *temp = (node->left != nullptr) ? node->left : node->right;

      if (temp == nullptr) {
        // Нет потомков - просто удаляем узел
        temp = node;
        node = nullptr;
      } else {
        // Один потомок - заменяем удаляемый узел на потомка
        Node *parent = node->parent;
        *node = *temp;  // Проблема: старые данные node теряются
        node->parent = parent;
      }
      delete temp;
    } else {
      // Случай 2: У узла два потомка
      // Находим минимальный узел в правом поддереве
      Node *min_in_right = get_min(node->right);

      // Копируем данные из min_in_right в текущий узел
      node->key = min_in_right->key;
      node->value = min_in_right->value;

      // Рекурсивно удаляем дубликат из правого поддерева
      node->right = remove_node_find(node->right, min_in_right->key);
      if (node->right != nullptr) {
        node->right->parent = node;
      }
    }
  }

  // Обновляем высоту и балансируем дерево
  if (node != nullptr) {
    update_height(node);
    node = balance_Tree(node);
  }

  return node;
}

// Метод для обновления высоты
template <typename Key, typename Value>
void AVL_Tree<Key, Value>::update_height(Node *node) {
  if (node == nullptr) {
    return;
  }

  int left_height = (node->left) ? node->left->height : -1;
  int right_height = (node->right) ? node->right->height : -1;

  node->height = std::max(left_height, right_height) + 1;
}

// Методы для баланса
template <typename Key, typename Value>
int AVL_Tree<Key, Value>::balance_factor(Node *node) {
  if (!node) return 0;
  int left_h = (node->left) ? node->left->height : -1;
  int right_h = (node->right) ? node->right->height : -1;
  return left_h - right_h;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::balance_Tree(
    Node *node) {
  if (node == nullptr) {
    return nullptr;
  }

  update_height(node);
  int balance = balance_factor(node);

  // Левый тяжелый случай
  if (balance > 1) {
    if (balance_factor(node->left) >= 0) {
      node = Left_Left(node);
    } else {
      node = Left_Right(node);
    }
  }
  // Правый тяжелый случай
  else if (balance < -1) {
    if (balance_factor(node->right) <= 0) {
      node = Right_Right(node);
    } else {
      node = Right_Left(node);
    }
  }

  // Обновляем корень, если балансировали его
  if (node->parent == nullptr) {
    root = node;
  }

  return node;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::Left_Left(
    Node *node) {
  Node *new_root = node->left;

  // Обновляем родителя нового корня
  new_root->parent = node->parent;

  // Перенаправляем родительские указатели
  if (node->parent) {
    if (node->parent->left == node) {
      node->parent->left = new_root;
    } else {
      node->parent->right = new_root;
    }
  }

  node->left = new_root->right;
  if (new_root->right) {
    new_root->right->parent = node;
  }

  new_root->right = node;
  node->parent = new_root;

  update_height(node);
  update_height(new_root);

  return new_root;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::Right_Right(
    Node *node) {
  Node *new_root = node->right;

  // Обновляем родителя нового корня
  new_root->parent = node->parent;

  // Перенаправляем родительские указатели
  if (node->parent) {
    if (node->parent->left == node) {
      node->parent->left = new_root;
    } else {
      node->parent->right = new_root;
    }
  }

  node->right = new_root->left;
  if (new_root->left) {
    new_root->left->parent = node;
  }

  new_root->left = node;
  node->parent = new_root;

  update_height(node);
  update_height(new_root);

  return new_root;
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::Left_Right(
    Node *node) {
  node->left = Right_Right(node->left);
  return Left_Left(node);
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::Node *AVL_Tree<Key, Value>::Right_Left(
    Node *node) {
  node->right = Left_Left(node->right);
  return Right_Right(node);
}

template <typename Key, typename Value>
void AVL_Tree<Key, Value>::print_tree(Node *node, int indent, bool last) {
  if (node != nullptr) {
    // Вывод отступов для визуализации уровней
    for (int i = 0; i < indent; i++) {
      if (i == indent - 1 && last)
        std::cout << "└── ";
      else if (i == indent - 1 && !last)
        std::cout << "├── ";
      else
        std::cout << (last ? "    " : "│   ");
    }

    // Вывод ключа и значения узла
    std::cout << node->key << ":" << node->value << " (h:" << node->height
              << ", b:" << balance_factor(node) << ")" << std::endl;

    // Рекурсивный вывод дочерних узлов
    if (node->left || node->right) {
      if (node->left) {
        print_tree(node->left, indent + 1, !node->right);
      }
      if (node->right) {
        print_tree(node->right, indent + 1, true);
      }
    }
  }
}

// Обертка для вывода всего дерева
template <typename Key, typename Value>
void AVL_Tree<Key, Value>::print() {
  std::cout << "AVL Tree Structure:" << std::endl;
  print_tree(root, 0, true);
}

// Метод сравнения деревьев
template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::eq_Tree(AVL_Tree *other) {
  Iterator this_it = begin();
  Iterator other_it = other->begin();
  Iterator this_end = end();
  Iterator other_end = other->end();

  while (this_it != this_end && other_it != other_end) {
    if (!(this_it.current_node->eq_Node(other_it.current_node))) {
      return false;
    }
    ++this_it;
    ++other_it;
  }

  return this_it == this_end && other_it == other_end;
}

// Метод сравнения узлов
template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::Node::eq_Node(Node *other) {
  return this->value == other->value && this->key == other->key;
}

template <typename Key, typename Value>
AVL_Tree<Key, Value>::ConstIterator::ConstIterator() : Iterator(){};

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::const_reference
AVL_Tree<Key, Value>::ConstIterator::operator*() const {
  return Iterator::operator*();
}

template <typename Key, typename Value>
typename AVL_Tree<Key, Value>::size_type AVL_Tree<Key, Value>::size() {
  size_type len = 0;

  Iterator iter = begin();
  while (iter != end()) {
    ++len;
    ++iter;
  }

  return len;
}

template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::empty() {
  bool answ = false;

  if (size() == 0) {
    answ = true;
  }

  return answ;
}

template <typename Key, typename Value>
size_t AVL_Tree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename AVL_Tree<Key, Value>::Node);
}

template <typename Key, typename Value>
void AVL_Tree<Key, Value>::swap(AVL_Tree &other) {
  std::swap(root, other.root);
}

template <typename Key, typename Value>
void AVL_Tree<Key, Value>::merge(AVL_Tree &other) {
  AVL_Tree const_tree(other);
  Iterator const_it = const_tree.begin();

  for (; const_it != const_tree.end(); ++const_it) {
    std::pair<Iterator, bool> pr = insert(*const_it);
    if (pr.second) other.erase(pr.first);
  }
}

template <typename Key, typename Value>
bool AVL_Tree<Key, Value>::contains(const Key &key) {
  Iterator iter = find(key);
  bool answ = false;

  if (iter.current_node != nullptr) {
    answ = true;
  }

  return answ;
}

template <typename Key, typename Value>
void AVL_Tree<Key, Value>::clear() {
  if (root == nullptr) {
    return;
  }
  remove_Tree(root);
}