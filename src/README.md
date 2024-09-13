### List

<details> 
  <summary>Общая информация</summary>
<br />

List (список) - это последовательный контейнер, хранящий набор элементов произвольного размера в виде узлов, последовательно связанных указателями. Каждый узел хранит значение, соответствующее элементу списка, и указатель на следующий элемент. Такое устройство контейнера позволяет уйти от жестко фиксированного рамера, как, например, в статическом массиве, и делает более интуитивно понятным процесс добавления нового элемента в контейнер. 

![](../misc/images/list_01.png)

Выше представлен пример списка из четырех элементов. Каждый из элементов списка представлен в виде структуры с двумя полями: значение узла и указатель на следующий элемент списка. Последний элемент списка ни на что не указывает. 

![](../misc/images/list_02.png)

Подобное устройство списка позволяет простым образом (без каскадного сдвига) добавлять как в конец, так и в середину списка. При добавлении элемента в конкретную позицию списка создается новый узел, указывающий на следующий после данной позиции элемент, после чего указатель предыдущего элемента перемещается на новый.

![](../misc/images/list_03.png)

При удалении элемента из списка, соответствующий узел освобождается, а указатели соседних элементов меняют значение: предыдущий элемент перемещает указатель на следующий после удаленного элемент.

Списки бывают односвязные или двусвязные. Односвязный список - это список, каждый узел которого хранит только один указатель: на следующий элемент списка (пример, приведенный выше). В двусвязном списке каждый узел хранит дополнительный указатель и на предыдущий элемент. Стандартная реализация контейнера list в С++ использует двусвязный список. 

В объекте класса контейнера хранятся указатели на "голову" и "хвост" списка, указывающие на первый и последний элементы списка. Контейнер List предоставляет прямой доступ только к "голове" и "хвосту", но позволяет добавлять и удалять элементы в любой части списка.
</details>

<details>
  <summary>Спецификация</summary>
<br />

*List Member type*

В этой таблице перечислены внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), принятые для удобства восприятия кода класса:

| Member type       | definition                                                                                          |
| ----------------- | --------------------------------------------------------------------------------------------------- |
| `value_type`      | `T` defines the type of an element (T is template parameter)                                        |
| `reference`       | `T &` defines the type of the reference to an element                                               |
| `const_reference` | `const T &` defines the type of the constant reference                                              |
| `iterator`        | internal class `ListIterator<T>` defines the type for iterating through the container               |
| `const_iterator`  | internal class `ListConstIterator<T>` defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                           |

*List Functions*

В этой таблице перечислены основные публичные методы для взаимодействия с классом:

| Functions                                              | Definition                                                                              |
| ------------------------------------------------------ | --------------------------------------------------------------------------------------- |
| `list()`                                               | default constructor, creates empty list                                                 |
| `list(size_type n)`                                    | parameterized constructor, creates the list of size n                                   |
| `list(std::initializer_list<value_type> const &items)` | initializer list constructor, creates list initizialized using std::initializer_list<T> |
| `list(const list &l)`                                  | copy constructor                                                                        |
| `list(list &&l)`                                       | move constructor                                                                        |
| `~list()`                                              | destructor                                                                              |
| `operator=(list &&l)`                                  | assignment operator overload for moving object                                          |

*List Element access*

В этой таблице перечислены публичные методы для доступа к элементам класса:

| Element access            | Definition               |
| ------------------------- | ------------------------ |
| `const_reference front()` | access the first element |
| `const_reference back()`  | access the last element  |

*List Iterators*

В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |

*List Capacity*

В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

*List Modifiers*

В этой таблице перечислены публичные методы для изменения контейнера:

| Modifiers                                              | Definition                                                                                |
| ------------------------------------------------------ | ----------------------------------------------------------------------------------------- |
| `void clear()`                                         | clears the contents                                                                       |
| `iterator insert(iterator pos, const_reference value)` | inserts element into concrete pos and returns the iterator that points to the new element |
| `void erase(iterator pos)`                             | erases element at pos                                                                     |
| `void push_back(const_reference value)`                | adds an element to the end                                                                |
| `void pop_back()`                                      | removes the last element                                                                  |
| `void push_front(const_reference value)`               | adds an element to the head                                                               |
| `void pop_front()`                                     | removes the first element                                                                 |
| `void swap(list& other)`                               | swaps the contents                                                                        |
| `void merge(list& other)`                              | merges two sorted lists                                                                   |
| `void splice(const_iterator pos, list& other)`         | transfers elements from list other starting from pos                                      |
| `void reverse()`                                       | reverses the order of the elements                                                        |
| `void unique()`                                        | removes consecutive duplicate elements                                                    |
| `void sort()`                                          | sorts the elements                                                                        |

</details>

### Set

<details>
  <summary>Общая информация</summary>
<br />

Set (множество) - это ассоциативный контейнер уникальных элементов. Это означает, что в множество нельзя добавить один и тот же элемент дважды. Контейнер множество является ассоциативным, так как внутри он также представлен в виде дерева, как и контейнер map (словарь), и, соответственно, также хранит элементы в отсортированном порядке. Разница между словарем и множеством заключается в том, что уникальным в множестве является, не ключ а само значение, ровно как и поиск значения в дереве проверяется не по ключу, а по самому значению. При добавлении уже существующего элемента в множество возникает соответствующее исключение. 

В стандартной реализации, математические операции над множествами (пересечение, объединение, вычитание и т. д.) не реализуются на уровне класса. 

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Set Member type*

В этой таблице перечислены внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), принятые для удобства восприятия кода класса:

| Member type       | Definition                                                                                                                                                                          |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `key_type`        | `Key` the first template parameter (Key)                                                                                                                                            |
| `value_type`      | `Key` value type (the value itself is a key)                                                                                                                                        |
| `reference`       | `value_type &` defines the type of the reference to an element                                                                                                                      |
| `const_reference` | `const value_type &` defines the type of the constant reference                                                                                                                     |
| `iterator`        | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                           |
| `const_iterator`  | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                                                                                           |

*Set Member functions*

В этой таблице перечислены основные публичные методы для взаимодействия с классом:

| Member functions                                      | Definition                                                                                 |
| ----------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `set()`                                               | default constructor, creates empty set                                                     |
| `set(std::initializer_list<value_type> const &items)` | initializer list constructor, creates the set initizialized using std::initializer_list<T> |
| `set(const set &s)`                                   | copy constructor                                                                           |
| `set(set &&s)`                                        | move constructor                                                                           |
| `~set()`                                              | destructor                                                                                 |
| `operator=(set &&s)`                                  | assignment operator overload for moving object                                             |


*Set Iterators*

В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |


*Set Capacity*

В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

*Set Modifiers*

В этой таблице перечислены публичные методы для изменения контейнера:

| Modifiers                                                   | Definition                                                                                                                    |
| ----------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------- |
| `void clear()`                                              | clears the contents                                                                                                           |
| `std::pair<iterator, bool> insert(const value_type& value)` | inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place |
| `void erase(iterator pos)`                                  | erases element at pos                                                                                                         |
| `void swap(set& other)`                                     | swaps the contents                                                                                                            |
| `void merge(set& other);`                                   | splices nodes from another container                                                                                          |

*Set Lookup*

В этой таблице перечислены публичные методы, осуществляющие просмотр контейнера:

| Lookup                          | Definition                                                 |
| ------------------------------- | ---------------------------------------------------------- |
| `iterator find(const Key& key)` | finds element with specific key                            |
| `bool contains(const Key& key)` | checks if the container contains element with specific key |

</details>

### Multiset 

<details>
  <summary>Общая информация</summary>
<br />

Multiset (мультимножество) - это ассоциативный контейнер, повторяющий логику множества, но позволяющий хранить идентичные элементы. Такой контейнер отличается от списка или вектора тем, что элементы при попадании в мультимножество так же, как и в множестве, сортируются на лету. Однако так же, как и множество, мультимножество не позволяет обратиться к элементу по индексу, а требует обращения по значению, которое в мультимножестве может повторяться.

</details>

<details>
  <summary>Спецификация</summary>
<br />

*Multiset Member type*

В этой таблице перечислены внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), принятые для удобства восприятия кода класса:

| Member type       | Definition                                                                                                                                                                           |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `key_type`        | `Key` the first template parameter (Key)                                                                                                                                             |
| `value_type`      | `Key` value type (the value itself is a key)                                                                                                                                         |
| `reference`       | `value_type &` defines the type of the reference to an element                                                                                                                       |
| `const_reference` | `const value_type &` defines the type of the constant reference                                                                                                                      |
| `iterator`        | internal class `MultisetIterator<T>` or `BinaryTree::iterator` as internal iterator of tree subclass; defines the type for iterating through the container                           |
| `const_iterator`  | internal class `MultisetConstIterator<T>` or `BinaryTree::const_iterator` as internal const iterator of tree subclass; defines the constant type for iterating through the container |
| `size_type`       | `size_t` defines the type of the container size (standard type is size_t)                                                                                                            |

*Multiset Member functions*

В этой таблице перечислены основные публичные методы для взаимодействия с классом:

| Member functions                                           | Definition                                                                                 |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| `multiset()`                                               | default constructor, creates empty set                                                     |
| `multiset(std::initializer_list<value_type> const &items)` | initializer list constructor, creates the set initizialized using std::initializer_list<T> |
| `multiset(const multiset &ms)`                             | copy constructor                                                                           |
| `multiset(multiset &&ms)`                                  | move constructor                                                                           |
| `~multiset()`                                              | destructor                                                                                 |
| `operator=(multiset &&ms)`                                 | assignment operator overload for moving object                                             |

*Multiset Iterators*

В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

| Iterators          | Definition                           |
| ------------------ | ------------------------------------ |
| `iterator begin()` | returns an iterator to the beginning |
| `iterator end()`   | returns an iterator to the end       |


*Multiset Capacity*

В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

| Capacity               | Definition                                      |
| ---------------------- | ----------------------------------------------- |
| `bool empty()`         | checks whether the container is empty           |
| `size_type size()`     | returns the number of elements                  |
| `size_type max_size()` | returns the maximum possible number of elements |

*Multiset Modifiers*

В этой таблице перечислены публичные методы для изменения контейнера:

| Modifiers                                  | Definition                                                                 |
| ------------------------------------------ | -------------------------------------------------------------------------- |
| `void clear()`                             | clears the contents                                                        |
| `iterator insert(const value_type& value)` | inserts node and returns iterator to where the element is in the container |
| `void erase(iterator pos)`                 | erases element at pos                                                      |
| `void swap(multiset& other)`               | swaps the contents                                                         |
| `void merge(multiset& other)`              | splices nodes from another container                                       |

*Multiset Lookup*

В этой таблице перечислены публичные методы, осуществляющие просмотр контейнера:

| Lookup                                                     | Definition                                                           |
| ---------------------------------------------------------- | -------------------------------------------------------------------- |
| `size_type count(const Key& key)`                          | returns the number of elements matching specific key                 |
| `iterator find(const Key& key)`                            | finds element with specific key                                      |
| `bool contains(const Key& key)`                            | checks if the container contains element with specific key           |
| `std::pair<iterator,iterator> equal_range(const Key& key)` | returns range of elements matching a specific key                    |
| `iterator lower_bound(const Key& key)`                     | returns an iterator to the first element not less than the given key |
| `iterator upper_bound(const Key& key)`                     | returns an iterator to the first element greater than the given key  |

</details>
