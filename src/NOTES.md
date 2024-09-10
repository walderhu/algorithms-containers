## Задачи на сегодня 
- [ ] посмотреть видосы про односвязные и двухмсвязные списки
- [ ] написать юнит тесты с покрытием
- [ ] приступить к некст тз



## TODO ~HEAD TASK
В этой таблице перечислены основные публичные методы для взаимодействия с классом:
 - [x] list() 
 - [x] list(size_type n)
 - [x] list(std::initializer_list<value_type> const &items)
 - [x] list(const list &l)
 - [x] list(list &&l)
 - [x] ~list() 
 - [x] operator=(list &&l)
 - [x] operator=[size_t index]

*List Element access*
В этой таблице перечислены публичные методы для доступа к элементам класса:

 - [x] const_reference front() 
 - [x] const_reference back() 

*List Iterators*
В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

 - [x] iterator begin() 
 - [x] iterator end() 

*List Capacity*
В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

 - [x] bool empty()  
 - [x] size_type size() 
 - [x] size_type max_size()  

*List Modifiers*
В этой таблице перечислены публичные методы для изменения контейнера:

 - [x] void clear() 
 - [x] iterator insert(iterator pos, const_reference value)  TODO
 - [x] void erase(iterator pos)
- [x] void push_back(const_reference value) 
- [x] void pop_back() 
- [x] void push_front(const_reference value) 
- [x] void pop_front() 
 - [x] void swap(list& other)
 - [x] void merge(list& other)
 - [x] void splice(const_iterator pos, list& other)
 - [x] void reverse() 
 - [x] void unique() 
 - [x] void sort() 









 <!-- TODO TASK ~TAIL -->
 <!-- NOTE: TASK ~TAIL -->
 - [ ] void merge(list& other) ;объединяет два отсортированных списка