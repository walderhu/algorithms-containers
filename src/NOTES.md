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
 - [ ] iterator insert(iterator pos, const_reference value)  TODO
 - [ ] void erase(iterator pos)
- [x] void push_back(const_reference value) 
- [x] void pop_back() 
- [x] void push_front(const_reference value) 
- [x] void pop_front() 
 - [ ] void swap(list& other)
 - [ ] void merge(list& other)
 - [ ] void splice(const_iterator pos, list& other)
 - [x] void reverse() 
 - [ ] void unique() 
 - [x] void sort() 









 <!-- TODO TASK ~TAIL -->
 <!-- NOTE: TASK ~TAIL -->
 - [ ] iterator insert(iterator pos, const_reference value) ; TODO
 - [ ] void erase(iterator pos) ;стирает элемент в позиции ; TODO
 - [ ] void swap(list& other) ;меняет местами содержимое
 - [ ] void merge(list& other) ;объединяет два отсортированных списка
 - [ ] void splice(const_iterator pos, list& other) ;переносит элементы из списка other, начиная с позиции
 - [ ] void unique() ;удаляет последовательные повторяющиеся элементы


 splice переносит элементы начиная с какого то значения, а мерж полностью переносит
 можно реализовать splice а потом в мерж делегировать на него с условием на весь список

 тз
 для начала хочу попробовать реализовать метод insert который вставляет определенный
 элемент в конкретное место в списке

 добавить мб перегрузку для этого метода, чтобы он работал как и через
 итераторы так и через прямую индексацию

 остановиться и облажить результат
 работы тестами

 а еще у меня вообще не работает reverse 

