#include "s21_containers_test.hpp"

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> v;
  EXPECT_EQ(v.size(), 0);
  EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SpecifiedLengthConstructor) {
  s21::vector<int> v(10);
  EXPECT_EQ(v.size(), 10);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> v = {11, 22, 33, 44, 55};
  EXPECT_EQ(v.size(), 5);
  EXPECT_EQ(v.capacity(), 5);
}

TEST(VectorTest, PushBack) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1);
  EXPECT_EQ(v.capacity(), 1);
  EXPECT_EQ(v[0], 1);

  v.push_back(2);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.capacity(), 2);
  EXPECT_EQ(v[1], 2);

  v.push_back(3);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_EQ(v[2], 3);
}

// Тест для конструктора копирования
TEST(VectorTest, CopyConstructor) {
  // Создаем исходный вектор
  s21::vector<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  // Создаем копию исходного вектора
  s21::vector<int> copy(original);

  // Проверяем, что размеры и вместимости совпадают
  EXPECT_EQ(copy.size(), original.size());
  EXPECT_EQ(copy.capacity(), original.capacity());

  // Проверяем, что элементы скопированы правильно
  for (size_t i = 0; i < original.size(); ++i) {
    EXPECT_EQ(copy[i], original[i]);
  }

  // Проверяем, что изменение копии не влияет на оригинал
  copy[0] = 10;
  EXPECT_NE(copy[0], original[0]);
}

// Тест для конструктора перемещения
TEST(VectorTest, MoveConstructor) {
  // Создаем исходный вектор
  s21::vector<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  // Сохраняем указатель на массив и размеры исходного вектора
  int* original_arr = original.data();
  size_t original_size = original.size();
  size_t original_capacity = original.capacity();

  // Создаем вектор с перемещением из исходного вектора
  s21::vector<int> moved(std::move(original));
  // s21::vector<int> moved = std::move(original);

  // Проверяем, что размеры и вместимости совпадают
  EXPECT_EQ(moved.size(), original_size);
  EXPECT_EQ(moved.capacity(), original_capacity);

  // Проверяем, что указатель на массив переместился
  EXPECT_EQ(moved.data(), original_arr);

  // Проверяем, что исходный вектор теперь пуст
  EXPECT_EQ(original.data(), nullptr);
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.capacity(), 0);

  // Проверяем, что элементы переместились правильно
  for (size_t i = 0; i < moved.size(); ++i) {
    EXPECT_EQ(moved[i], i + 1);
  }
}

// Тест для деструктора
TEST(VectorTest, DestructorTest) {
  // Создаем указатель на объект vector
  s21::vector<int>* vec = new s21::vector<int>(10);

  // Удаляем объект, чтобы вызвать деструктор
  delete vec;
  SUCCEED();
}

// Тест для метода size()
TEST(VectorTest, SizeTest) {
  // Создаем объект vector с размером 10
  // Проверяем, что метод size() возвращает правильный размер
  s21::vector<int> vec(10);
  EXPECT_EQ(vec.size(), 10);

  s21::vector<int> vec2(5);
  EXPECT_EQ(vec2.size(), 5);

  s21::vector<int> vec3(0);
  EXPECT_EQ(vec3.size(), 0);
}

// Тест для метода capacity()
TEST(VectorTest, CapacityTest) {
  // Создаем объект vector с размером 10
  // Проверяем, что метод capacity() возвращает правильную емкость
  s21::vector<int> vec(10);
  EXPECT_EQ(vec.capacity(), 10);

  s21::vector<int> vec2(5);
  EXPECT_EQ(vec2.capacity(), 5);

  s21::vector<int> vec3(0);
  EXPECT_EQ(vec3.capacity(), 0);
}

// Тест для метода at()
TEST(VectorTest, AtTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем, что метод at() возвращает правильные значения для разных
  // индексов
  EXPECT_EQ(vec.at(0), 0);
  EXPECT_EQ(vec.at(1), 1);
  EXPECT_EQ(vec.at(2), 2);
  EXPECT_EQ(vec.at(3), 3);
  EXPECT_EQ(vec.at(4), 4);
  EXPECT_EQ(vec.at(5), 5);
  EXPECT_EQ(vec.at(6), 6);
  EXPECT_EQ(vec.at(7), 7);
  EXPECT_EQ(vec.at(8), 8);
  EXPECT_EQ(vec.at(9), 9);
}

// Тест для метода front()
TEST(VectorTest, FrontTest) {
  // Проверяем, что метод front() возвращает правильное значение
  s21::vector<int> vec = {0};
  EXPECT_EQ(vec.front(), 0);

  s21::vector<int> vec2 = {11, 22};
  EXPECT_EQ(vec2.front(), 11);

  // Проверка на исключение при пустом векторе
  s21::vector<int> vec3(0);
  EXPECT_THROW(vec3.front(), std::out_of_range);
}

// Тест для метода back()
TEST(VectorTest, BackTest) {
  s21::vector<int> vec = {0};
  EXPECT_EQ(vec.back(), 0);

  s21::vector<int> vec2 = {11, 12};
  EXPECT_EQ(vec2.back(), 12);

  // Проверка на исключение при пустом векторе
  s21::vector<int> vec3(0);
  EXPECT_THROW(vec3.back(), std::out_of_range);
}

// Тест для метода data()
TEST(VectorTest, DataTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Получаем указатель на базовый массив
  int* dataPtr = vec.data();

  // Проверяем, что указатель не равен nullptr
  EXPECT_NE(dataPtr, nullptr);

  // Проверяем, что содержимое массива соответствует ожидаемому
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(dataPtr[i], i);
  }
}

// Тест для метода empty()
TEST(VectorTest, EmptyTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec(10);

  // Проверяем, что метод empty() возвращает false для непустого вектора
  EXPECT_FALSE(vec.empty());

  // Создаем объект vector с размером 0
  s21::vector<int> vec2(0);

  // Проверяем, что метод empty() возвращает true для пустого вектора
  EXPECT_TRUE(vec2.empty());
}

// Тест для метода max_size()
TEST(VectorTest, MaxSizeTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec(10);

  // Вычисляем ожидаемое значение max_size для типа int
  s21::vector<int>::size_type expected_max_size =
      (std::numeric_limits<size_t>::max() / sizeof(int)) / 2;

  // Проверяем, что метод max_size() возвращает правильное значение
  EXPECT_EQ(vec.max_size(), expected_max_size);

  // дополнительные проверки для других типов
  s21::vector<double> vec2(10);
  s21::vector<double>::size_type expected_max_size_double =
      (std::numeric_limits<size_t>::max() / sizeof(double)) / 2;
  EXPECT_EQ(vec2.max_size(), expected_max_size_double);
}

// Тест для метода reserve()
TEST(VectorTest, ReserveTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем начальную емкость
  EXPECT_EQ(vec.capacity(), 10);

  // Вызываем метод reserve с новым размером 20
  vec.reserve(20);

  // Проверяем, что емкость увеличилась до 20
  EXPECT_EQ(vec.capacity(), 20);

  // Проверяем, что элементы были скопированы правильно
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), i);
  }

  // Проверяем, что метод reserve не изменяет емкость, если новый размер меньше
  // текущей емкости
  vec.reserve(5);
  EXPECT_EQ(vec.capacity(), 20);
}

// Тест для метода shrink_to_fit()
TEST(VectorTest, ShrinkToFitTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем начальную емкость
  EXPECT_EQ(vec.capacity(), 10);

  // Увеличиваем емкость с помощью reserve
  vec.reserve(20);

  // Проверяем, что емкость увеличилась до 20
  EXPECT_EQ(vec.capacity(), 20);

  // Вызываем метод shrink_to_fit
  vec.shrink_to_fit();

  // Проверяем, что емкость уменьшилась до размера вектора
  EXPECT_EQ(vec.capacity(), vec.size());

  // Проверяем, что элементы были скопированы правильно
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), i);
  }

  // Проверяем, что метод shrink_to_fit не изменяет емкость, если она уже равна
  // размеру вектора
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

// Тест для метода clear()
TEST(VectorTest, ClearTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec(10);

  // Проверяем начальный размер и емкость
  EXPECT_EQ(vec.size(), 10);
  EXPECT_EQ(vec.capacity(), 10);

  // Вызываем метод clear
  vec.clear();

  // Проверяем, что размер стал 0, но емкость не изменилась
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);

  // Проверяем, что вектор теперь пуст
  EXPECT_TRUE(vec.empty());

  // Проверяем, что метод clear не изменяет емкость
  vec.reserve(20);
  EXPECT_EQ(vec.capacity(), 20);
  vec.clear();
  EXPECT_EQ(vec.capacity(), 20);
}

// Тест для метода erase()
TEST(VectorTest, EraseTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем начальный размер
  EXPECT_EQ(vec.size(), 10);

  // Удаляем элемент в позиции 5
  vec.erase(vec.begin() + 5);

  // Проверяем, что размер уменьшился на 1
  EXPECT_EQ(vec.size(), 9);

  // Проверяем, что элементы были сдвинуты правильно
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i < 5) {
      EXPECT_EQ(vec.at(i), i);
    } else {
      EXPECT_EQ(vec.at(i), i + 1);
    }
  }

  // Проверка на исключение при некорректном итераторе
  EXPECT_THROW(vec.erase(vec.end()), std::out_of_range);
  EXPECT_THROW(vec.erase(vec.begin() - 1), std::out_of_range);
}

// Тест для метода pop_back()
TEST(VectorTest, PopBackTest) {
  // Создаем объект vector с размером 10
  s21::vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем начальный размер
  EXPECT_EQ(vec.size(), 10);

  // Удаляем последний элемент
  vec.pop_back();

  // Проверяем, что размер уменьшился на 1
  EXPECT_EQ(vec.size(), 9);

  // Проверяем, что последний элемент был удален
  EXPECT_EQ(vec.back(), 8);

  // Удаляем все элементы
  while (!vec.empty()) {
    vec.pop_back();
  }

  // Проверяем, что вектор теперь пуст
  EXPECT_TRUE(vec.empty());

  // Проверяем, что pop_back() не изменяет пустой вектор
  vec.pop_back();
  EXPECT_TRUE(vec.empty());
}

// Тест для метода swap()
TEST(VectorTest, SwapTest) {
  // Создаем два объекта vector с разными размерами
  s21::vector<int> vec1 = {0, 1, 2, 3, 4};
  s21::vector<int> vec2 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Проверяем начальные размеры и емкости
  EXPECT_EQ(vec1.size(), 5);
  EXPECT_EQ(vec1.capacity(), 5);
  EXPECT_EQ(vec2.size(), 10);
  EXPECT_EQ(vec2.capacity(), 10);

  // Проверяем начальные содержимое векторов
  for (size_t i = 0; i < vec1.size(); ++i) {
    EXPECT_EQ(vec1.at(i), i);
  }
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2.at(i), i);
  }

  // Вызываем метод swap
  vec1.swap(vec2);

  // Проверяем, что размеры и емкости поменялись местами
  EXPECT_EQ(vec1.size(), 10);
  EXPECT_EQ(vec1.capacity(), 10);
  EXPECT_EQ(vec2.size(), 5);
  EXPECT_EQ(vec2.capacity(), 5);

  // Проверяем, что содержимое векторов поменялось местами
  for (size_t i = 0; i < vec1.size(); ++i) {
    EXPECT_EQ(vec1.at(i), i);
  }
  for (size_t i = 0; i < vec2.size(); ++i) {
    EXPECT_EQ(vec2.at(i), i);
  }
}

// Тест для метода insert_many()
TEST(VectorTest, InsertManyTest) {
  // Создаем объект vector с размером 5
  s21::vector<int> vec = {0, 1, 2, 3, 4};

  // Проверяем начальный размер
  EXPECT_EQ(vec.size(), 5);

  // Вставляем элементы 777, 888, 999 перед позицией 2
  vec.insert_many(vec.begin() + 2, 777, 888, 999);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 8);

  // Проверяем, что элементы были вставлены правильно
  std::vector<int> expected = {0, 1, 777, 888, 999, 2, 3, 4};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Вставляем элементы 100, 200, 300 перед позицией 0
  vec.insert_many(vec.begin(), 100, 200, 300);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 11);

  // Проверяем, что элементы были вставлены правильно
  expected = {100, 200, 300, 0, 1, 777, 888, 999, 2, 3, 4};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Вставляем элементы 400, 500, 600 перед позицией end()
  vec.insert_many(vec.end(), 400, 500, 600);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 14);

  // Проверяем, что элементы были вставлены правильно
  expected = {100, 200, 300, 0, 1, 777, 888, 999, 2, 3, 4, 400, 500, 600};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }
}

// Тест для метода insert_many_back()
TEST(VectorTest, InsertManyBackTest) {
  // Создаем объект vector с размером 5
  s21::vector<int> vec = {0, 1, 2, 3, 4};

  // Проверяем начальный размер
  EXPECT_EQ(vec.size(), 5);

  // Добавляем элементы 777, 888, 999 в конец вектора
  vec.insert_many_back(777, 888, 999);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 8);

  // Проверяем, что элементы были добавлены правильно
  std::vector<int> expected = {0, 1, 2, 3, 4, 777, 888, 999};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Добавляем элементы 100, 200, 300 в конец вектора
  vec.insert_many_back(100, 200, 300);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 11);

  // Проверяем, что элементы были добавлены правильно
  expected = {0, 1, 2, 3, 4, 777, 888, 999, 100, 200, 300};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Добавляем элементы 400, 500, 600 в конец вектора
  vec.insert_many_back(400, 500, 600);

  // Проверяем, что размер увеличился на 3
  EXPECT_EQ(vec.size(), 14);

  // Проверяем, что элементы были добавлены правильно
  expected = {0, 1, 2, 3, 4, 777, 888, 999, 100, 200, 300, 400, 500, 600};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }
}

// Тест для метода insert()
TEST(VectorTest, InsertTest) {
  // Создаем объект vector с размером 5
  s21::vector<int> vec = {0, 1, 2, 3, 4};

  // Проверяем начальный размер
  EXPECT_EQ(vec.size(), 5);

  // Вставляем элемент 777 в позицию 2
  s21::vector<int>::iterator it = vec.insert(vec.begin() + 2, 777);

  // Проверяем, что размер увеличился на 1
  EXPECT_EQ(vec.size(), 6);

  // Проверяем, что итератор указывает на новый элемент
  EXPECT_EQ(*it, 777);

  // Проверяем, что элементы были вставлены правильно
  std::vector<int> expected = {0, 1, 777, 2, 3, 4};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Вставляем элемент 100 в позицию 0
  it = vec.insert(vec.begin(), 100);

  // Проверяем, что размер увеличился на 1
  EXPECT_EQ(vec.size(), 7);

  // Проверяем, что итератор указывает на новый элемент
  EXPECT_EQ(*it, 100);

  // Проверяем, что элементы были вставлены правильно
  expected = {100, 0, 1, 777, 2, 3, 4};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Вставляем элемент 200 в позицию end()
  it = vec.insert(vec.end(), 200);

  // Проверяем, что размер увеличился на 1
  EXPECT_EQ(vec.size(), 8);

  // Проверяем, что итератор указывает на новый элемент
  EXPECT_EQ(*it, 200);

  // Проверяем, что элементы были вставлены правильно
  expected = {100, 0, 1, 777, 2, 3, 4, 200};
  for (size_t i = 0; i < vec.size(); ++i) {
    EXPECT_EQ(vec.at(i), expected[i]);
  }

  // Проверка на исключение при некорректном итераторе
  EXPECT_THROW(vec.insert(vec.end() + 1, 300), std::out_of_range);
  EXPECT_THROW(vec.insert(vec.begin() - 1, 300), std::out_of_range);
}

// Тест для метода begin()
TEST(VectorTest, BeginTest) {
  // Создаем объект vector с размером 5
  s21::vector<int> vec = {0, 1, 2, 3, 4};

  // Проверяем, что метод begin() возвращает правильный итератор
  s21::vector<int>::iterator it = vec.begin();
  EXPECT_EQ(*it, 0);

  // Проверяем, что итератор указывает на первый элемент
  EXPECT_EQ(*it, vec.at(0));

  // Проверяем, что итератор можно инкрементировать и указывать на следующие
  // элементы
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);

  // Проверяем, что итератор указывает на конец после последнего элемента
  ++it;
  EXPECT_EQ(it, vec.end());
}

// Тест для метода end()
TEST(VectorTest, EndTest) {
  // Создаем объект vector с размером 5
  s21::vector<int> vec = {0, 1, 2, 3, 4};

  // Проверяем, что метод end() возвращает правильный итератор
  s21::vector<int>::iterator it = vec.end();

  // Проверяем, что итератор указывает на конец вектора
  EXPECT_EQ(it, vec.begin() + vec.size());

  // // Проверяем, что итератор не указывает на какой-либо элемент
  // EXPECT_THROW(*it, std::out_of_range);

  // // Проверяем, что итератор можно декрементировать и указывать на последний
  // элемент
  // --it;
  // EXPECT_EQ(*it, 4);
  // EXPECT_EQ(it, vec.begin() + vec.size() - 1);

  // // Проверяем, что итератор можно декрементировать и указывать на предыдущие
  // элементы
  // --it;
  // EXPECT_EQ(*it, 3);
  // --it;
  // EXPECT_EQ(*it, 2);
  // --it;
  // EXPECT_EQ(*it, 1);
  // --it;
  // EXPECT_EQ(*it, 0);

  // // Проверяем, что итератор указывает на начало перед первым элементом
  // --it;
  // EXPECT_EQ(it, vec.begin() - 1);
}