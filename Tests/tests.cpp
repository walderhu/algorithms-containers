#include "s21_containers_test.hpp"

// >>>>>>>>> STACK <<<<<<<<<<<<<<
TEST(Stack, simple_test) {
  s21::stack<int> my_stack;
  std::stack<int> orig_stack;
  my_stack.push(1);
  my_stack.push(2);
  my_stack.push(2555);
  my_stack.push(365434);
  orig_stack.push(1);
  orig_stack.push(2);
  orig_stack.push(2555);
  orig_stack.push(365434);
  while (!orig_stack.empty() && !my_stack.empty()) {
    ASSERT_EQ(orig_stack.top(), my_stack.top());
    orig_stack.pop();
    my_stack.pop();
  }
  ASSERT_EQ(orig_stack.empty(), my_stack.empty());
}
TEST(Stack, swap_test) {
  std::stack<double> orig_stack1;
  orig_stack1.push(2.55);
  orig_stack1.push(3.55);
  orig_stack1.push(222.55);
  orig_stack1.push(984.55);
  orig_stack1.push(123.55);
  orig_stack1.push(0.55);
  orig_stack1.push(-34.55);
  std::stack<double> orig_stack2;
  orig_stack2.push(342.22);
  orig_stack2.push(355.01);
  orig_stack2.push(123.99);
  orig_stack2.push(888.34);
  orig_stack2.push(-23.11);
  orig_stack2.push(1002.88);
  orig_stack2.push(1.55);
  s21::stack<double> my_stack1;
  my_stack1.push(2.55);
  my_stack1.push(3.55);
  my_stack1.push(222.55);
  my_stack1.push(984.55);
  my_stack1.push(123.55);
  my_stack1.push(0.55);
  my_stack1.push(-34.55);
  s21::stack<double> my_stack2;
  my_stack2.push(342.22);
  my_stack2.push(355.01);
  my_stack2.push(123.99);
  my_stack2.push(888.34);
  my_stack2.push(-23.11);
  my_stack2.push(1002.88);
  my_stack2.push(1.55);
  orig_stack1.swap(orig_stack2);
  my_stack1.swap(my_stack2);
  while (!orig_stack1.empty() && !my_stack1.empty()) {
    ASSERT_DOUBLE_EQ(orig_stack1.top(), my_stack1.top());
    orig_stack1.pop();
    my_stack1.pop();
  }
  while (!orig_stack2.empty() && !my_stack2.empty()) {
    ASSERT_DOUBLE_EQ(orig_stack2.top(), my_stack2.top());
    orig_stack2.pop();
    my_stack2.pop();
  }
  ASSERT_EQ(orig_stack2.empty(), my_stack2.empty());
}

TEST(Stack, copy_constructor_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2(orig_stack1);
  s21::stack<int> my_stack1;
  my_stack1.push(55);
  my_stack1.push(555);
  my_stack1.push(5555);
  my_stack1.push(55555);
  s21::stack<int> my_stack2(my_stack1);
  while (!orig_stack2.empty() && !my_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), my_stack2.top());
    orig_stack2.pop();
    my_stack2.pop();
  }
  s21::stack<int> my_stack3;
  std::stack<int> orig_stack3;
  s21::stack<int> my_stack4(my_stack3);
  std::stack<int> orig_stack4(orig_stack3);
  ASSERT_EQ(orig_stack4.empty(), my_stack4.empty());
}

TEST(Stack, move_constructor_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2(std::move(orig_stack1));
  s21::stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  s21::stack<int> copy_stack2(std::move(copy_stack1));
  while (!orig_stack2.empty() && !copy_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), copy_stack2.top());
    orig_stack2.pop();
    copy_stack2.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

TEST(Stack, move_operator_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  std::stack<int> orig_stack2;
  orig_stack2.push(1);
  orig_stack2.push(2);
  orig_stack2 = std::move(orig_stack1);
  s21::stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  s21::stack<int> copy_stack2{1, 2};
  copy_stack2 = std::move(copy_stack1);
  while (!orig_stack2.empty() && !copy_stack2.empty()) {
    ASSERT_EQ(orig_stack2.top(), copy_stack2.top());
    orig_stack2.pop();
    copy_stack2.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

TEST(Stack, emplace_test) {
  std::stack<int> orig_stack1;
  orig_stack1.push(55);
  orig_stack1.push(555);
  orig_stack1.push(5555);
  orig_stack1.push(55555);
  orig_stack1.emplace(345);
  orig_stack1.emplace(234);
  orig_stack1.emplace(889);
  s21::stack<int> copy_stack1;
  copy_stack1.push(55);
  copy_stack1.push(555);
  copy_stack1.push(5555);
  copy_stack1.push(55555);
  copy_stack1.emplace_front(345);
  copy_stack1.emplace_front(234);
  copy_stack1.emplace_front(889);
  while (!orig_stack1.empty() && !copy_stack1.empty()) {
    ASSERT_EQ(orig_stack1.top(), copy_stack1.top());
    orig_stack1.pop();
    copy_stack1.pop();
  }
  ASSERT_EQ(orig_stack1.size(), copy_stack1.size());
}

TEST(Stack, insert_many_back) {
  s21::stack<int> our_stack_int;
  our_stack_int.insert_many_back(1, 2, 3);
  int arr[3] = {1, 2, 3};
  int i = 2;
  while (!our_stack_int.empty() && i >= 0) {
    ASSERT_EQ(our_stack_int.top(), arr[i]);
    our_stack_int.pop();
    i--;
  }
}

// Queue Test
class TestQueue {
 public:
  s21::queue<int> s21_queue_empty;
  s21::queue<int> s21_queue_three;

  std::queue<int> std_queue_empty;
  std::queue<int> std_queue_three;
};

TEST(Queue, default_constructor) {
  TestQueue tester;
  EXPECT_EQ(tester.s21_queue_empty.size(), tester.std_queue_empty.size());
  EXPECT_EQ(tester.s21_queue_empty.empty(), tester.std_queue_empty.empty());
}

TEST(Queue, initializer_constructor) {
  TestQueue tester;
  while (!tester.s21_queue_three.empty()) {
    EXPECT_EQ(tester.s21_queue_three.front(), tester.std_queue_three.front());
    tester.s21_queue_three.pop();
    tester.std_queue_three.pop();
  }
  EXPECT_EQ(tester.s21_queue_three.size(), tester.std_queue_three.size());
  EXPECT_EQ(tester.s21_queue_three.empty(), tester.std_queue_three.empty());
}

TEST(Queue, move_constructor) {
  TestQueue tester;
  s21::queue<int> s21_queue_move(std::move(tester.s21_queue_three));
  std::queue<int> std_queue_move(std::move(tester.std_queue_three));
  while (!s21_queue_move.empty()) {
    EXPECT_EQ(s21_queue_move.front(), std_queue_move.front());
    s21_queue_move.pop();
    std_queue_move.pop();
  }
  EXPECT_EQ(s21_queue_move.size(), std_queue_move.size());
  EXPECT_EQ(s21_queue_move.empty(), std_queue_move.empty());
  while (!tester.s21_queue_three.empty()) {
    EXPECT_EQ(tester.s21_queue_three.front(), tester.s21_queue_three.front());
    tester.s21_queue_three.pop();
    tester.std_queue_three.pop();
  }
  EXPECT_EQ(tester.s21_queue_three.size(), tester.std_queue_three.size());
  EXPECT_EQ(tester.s21_queue_three.empty(), tester.std_queue_three.empty());
}

TEST(Queue, move_assigment) {
  TestQueue tester;
  s21::queue<int> s21_queue_move{1, 2};
  std::queue<int> std_queue_move;
  std_queue_move.push(1);
  std_queue_move.push(2);
  s21_queue_move = std::move(tester.s21_queue_three);
  std_queue_move = std::move(tester.std_queue_three);
  while (!s21_queue_move.empty()) {
    EXPECT_EQ(s21_queue_move.front(), std_queue_move.front());
    s21_queue_move.pop();
    std_queue_move.pop();
  }
  EXPECT_EQ(s21_queue_move.size(), std_queue_move.size());
  EXPECT_EQ(s21_queue_move.empty(), std_queue_move.empty());
}

TEST(Queue, function_push) {
  TestQueue tester;
  for (int i = 0; i < 10; i++) {
    tester.s21_queue_empty.push(i);
    tester.std_queue_empty.push(i);
  }
  while (!tester.std_queue_empty.empty() && !tester.s21_queue_empty.empty()) {
    EXPECT_EQ(tester.std_queue_empty.front(), tester.s21_queue_empty.front());
    EXPECT_EQ(tester.std_queue_empty.back(), tester.s21_queue_empty.back());
    tester.std_queue_empty.pop();
    tester.s21_queue_empty.pop();
  }
  EXPECT_EQ(tester.std_queue_empty.empty(), tester.s21_queue_empty.empty());
}

TEST(Queue, function_pop) {
  TestQueue tester;
  for (int i = 0; i < 456; i++) {
    tester.s21_queue_empty.push(i);
    tester.std_queue_empty.push(i);
  }
  while (!tester.std_queue_empty.empty() && !tester.s21_queue_empty.empty()) {
    EXPECT_EQ(tester.std_queue_empty.front(), tester.s21_queue_empty.front());
    EXPECT_EQ(tester.std_queue_empty.back(), tester.s21_queue_empty.back());
    tester.std_queue_empty.pop();
    tester.s21_queue_empty.pop();
  }
  EXPECT_EQ(tester.std_queue_empty.empty(), tester.s21_queue_empty.empty());
}

TEST(Queue, simple_test) {
  TestQueue tester;
  tester.s21_queue_empty.push(1);
  tester.s21_queue_empty.push(2);
  tester.s21_queue_empty.push(2555);
  tester.s21_queue_empty.push(365434);
  tester.std_queue_empty.push(1);
  tester.std_queue_empty.push(2);
  tester.std_queue_empty.push(2555);
  tester.std_queue_empty.push(365434);
  while (!tester.std_queue_empty.empty() && !tester.s21_queue_empty.empty()) {
    EXPECT_EQ(tester.std_queue_empty.front(), tester.s21_queue_empty.front());
    EXPECT_EQ(tester.std_queue_empty.back(), tester.s21_queue_empty.back());
    tester.std_queue_empty.pop();
    tester.s21_queue_empty.pop();
  }
  EXPECT_EQ(tester.std_queue_empty.empty(), tester.s21_queue_empty.empty());
}

TEST(Queue, swap_test) {
  std::queue<double> orig_queue1;
  orig_queue1.push(2.55);
  orig_queue1.push(3.55);
  orig_queue1.push(222.55);
  orig_queue1.push(984.55);
  orig_queue1.push(123.55);
  orig_queue1.push(0.55);
  orig_queue1.push(-34.55);
  std::queue<double> orig_queue2;
  orig_queue2.push(342.22);
  orig_queue2.push(355.01);
  orig_queue2.push(123.99);
  orig_queue2.push(888.34);
  orig_queue2.push(-23.11);
  orig_queue2.push(1002.88);
  orig_queue2.push(1.55);
  s21::queue<double> my_queue1;
  my_queue1.push(2.55);
  my_queue1.push(3.55);
  my_queue1.push(222.55);
  my_queue1.push(984.55);
  my_queue1.push(123.55);
  my_queue1.push(0.55);
  my_queue1.push(-34.55);
  s21::queue<double> my_queue2;
  my_queue2.push(342.22);
  my_queue2.push(355.01);
  my_queue2.push(123.99);
  my_queue2.push(888.34);
  my_queue2.push(-23.11);
  my_queue2.push(1002.88);
  my_queue2.push(1.55);
  orig_queue1.swap(orig_queue2);
  my_queue1.swap(my_queue2);
  while (!orig_queue1.empty() && !my_queue1.empty()) {
    ASSERT_DOUBLE_EQ(orig_queue1.front(), my_queue1.front());
    ASSERT_DOUBLE_EQ(orig_queue1.back(), my_queue1.back());
    orig_queue1.pop();
    my_queue1.pop();
  }
  while (!orig_queue2.empty() && !my_queue2.empty()) {
    ASSERT_DOUBLE_EQ(orig_queue2.front(), my_queue2.front());
    ASSERT_DOUBLE_EQ(orig_queue2.back(), my_queue2.back());
    orig_queue2.pop();
    my_queue2.pop();
  }
  ASSERT_EQ(orig_queue2.empty(), my_queue2.empty());
}

TEST(Queue, copy_constructor_test) {
  s21::queue<int> my_queue;
  std::queue<int> orig_queue;
  s21::queue<int> my_queue2(my_queue);
  std::queue<int> orig_queue2(orig_queue);
  ASSERT_EQ(orig_queue2.empty(), my_queue2.empty());

  std::queue<char> orig_q1;
  orig_q1.push('a');
  orig_q1.push('b');
  orig_q1.push('c');
  orig_q1.push('d');
  s21::queue<char> copy_q1;
  copy_q1.push('a');
  copy_q1.push('b');
  copy_q1.push('c');
  copy_q1.push('d');
  std::queue<char> orig_q2(orig_q1);
  s21::queue<char> copy_q2(copy_q1);
  ASSERT_EQ(orig_q2.size(), copy_q2.size());
  while (!orig_q2.empty() && !copy_q2.empty()) {
    ASSERT_EQ(orig_q2.front(), copy_q2.front());
    ASSERT_EQ(orig_q2.back(), copy_q2.back());
    orig_q2.pop();
    copy_q2.pop();
  }
}

TEST(Queue, move_constructor_test) {
  std::queue<char> orig_q1;
  orig_q1.push('a');
  orig_q1.push('b');
  orig_q1.push('c');
  orig_q1.push('d');
  s21::queue<char> copy_q1;
  copy_q1.push('a');
  copy_q1.push('b');
  copy_q1.push('c');
  copy_q1.push('d');
  std::queue<char> orig_q2(std::move(orig_q1));
  s21::queue<char> copy_q2(std::move(copy_q1));
  ASSERT_EQ(orig_q1.size(), copy_q1.size());
  ASSERT_EQ(orig_q2.size(), copy_q2.size());
  while (!orig_q2.empty() && !copy_q2.empty()) {
    ASSERT_EQ(orig_q2.front(), copy_q2.front());
    ASSERT_EQ(orig_q2.back(), copy_q2.back());
    orig_q2.pop();
    copy_q2.pop();
  }
}

TEST(Queue, move_operator_test) {
  std::queue<char> orig_q1;
  orig_q1.push('a');
  orig_q1.push('b');
  orig_q1.push('c');
  orig_q1.push('d');
  s21::queue<char> copy_q1;
  copy_q1.push('a');
  copy_q1.push('b');
  copy_q1.push('c');
  copy_q1.push('d');
  std::queue<char> orig_q2;
  orig_q2.push('h');
  s21::queue<char> copy_q2{'h'};
  EXPECT_EQ(orig_q1.size(), copy_q1.size());
  EXPECT_EQ(orig_q2.size(), copy_q2.size());
  orig_q2 = std::move(orig_q1);
  copy_q2 = std::move(copy_q1);
  EXPECT_EQ(orig_q1.size(), copy_q1.size());
  EXPECT_EQ(orig_q2.size(), copy_q2.size());
  while (!orig_q2.empty() && !copy_q2.empty()) {
    EXPECT_EQ(orig_q2.front(), copy_q2.front());
    EXPECT_EQ(orig_q2.back(), copy_q2.back());
    orig_q2.pop();
    copy_q2.pop();
  }
}

TEST(Queue, insert_many_back) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

// >>>>>>>>>>> ARRAY <<<<<<<<<<<<<<<<
class TestArray {
 public:
  s21::array<int, 0> s21_array_empty;
  s21::array<int, 3> copy_array{234, 21, 11};
  s21::array<char, 0> copy_ar1;
  s21::array<double, 5> copy_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  s21::array<double, 5> copy_array2{-5.3, 1.18, -4.3, 255.34, 1.23};

  std::array<int, 0> std_array_empty;
  std::array<int, 3> orig_array{234, 21, 11};
  std::array<char, 0> orig_ar1;
  std::array<double, 5> orig_array1{2.5, 3.4, 255.3, 1.2, 0.5};
  std::array<double, 5> orig_array2{-5.3, 1.18, -4.3, 255.34, 1.23};
};

TEST(Array, constructor_default) {
  TestArray tester;
  EXPECT_EQ(tester.s21_array_empty.size(), tester.std_array_empty.size());
  EXPECT_EQ(tester.s21_array_empty.empty(), tester.std_array_empty.empty());
}

TEST(Array, constructor_initializer) {
  TestArray tester;
  EXPECT_EQ(tester.copy_array1[1], tester.orig_array1[1]);
  EXPECT_EQ(tester.copy_array1.front(), tester.orig_array1.front());
  EXPECT_EQ(tester.copy_array1.back(), tester.orig_array1.back());
  EXPECT_EQ(tester.copy_array1.size(), tester.orig_array1.size());
  EXPECT_EQ(tester.copy_array1.empty(), tester.orig_array1.empty());
}

TEST(Array, constructor_copy_empty) {
  TestArray tester;
  s21::array<int, 0> s21_array_empty;
  s21::array<int, 0> s21_array_copy(tester.s21_array_empty);
  EXPECT_EQ(s21_array_empty.size(), s21_array_copy.size());
  EXPECT_EQ(s21_array_empty.empty(), s21_array_copy.empty());
}

TEST(Array, simple_test) {
  TestArray logger;
  for (int i{}; i < 3; i++)
    ASSERT_EQ(logger.orig_array.at(i), logger.copy_array.at(i));
  ASSERT_EQ(logger.orig_array.size(), logger.copy_array.size());
  ASSERT_EQ(logger.orig_array.max_size(), logger.copy_array.max_size());
  ASSERT_EQ(logger.orig_ar1.empty(), logger.copy_ar1.empty());
}
TEST(Array, swap_test) {
  TestArray logger;
  logger.orig_array1.swap(logger.orig_array2);
  logger.copy_array1.swap(logger.copy_array2);
  for (int i{}; i < 5; i++) {
    ASSERT_DOUBLE_EQ(logger.orig_array1[i], logger.copy_array1[i]);
    ASSERT_DOUBLE_EQ(logger.orig_array2[i], logger.copy_array2[i]);
  }
  ASSERT_EQ(logger.orig_array1.size(), logger.copy_array1.size());
  ASSERT_EQ(logger.orig_array2.max_size(), logger.copy_array2.max_size());
  ASSERT_EQ(logger.orig_array1.front(), logger.copy_array1.front());
  ASSERT_EQ(logger.orig_array2.front(), logger.copy_array2.front());
  ASSERT_EQ(logger.orig_array1.back(), logger.copy_array1.back());
  ASSERT_EQ(logger.orig_array2.back(), logger.copy_array2.back());
}

TEST(Array, copy_constructor_test) {
  std::array<int, 3> orig_array3{234, 21, 11};
  s21::array<int, 3> copy_array3{234, 21, 11};
  std::array<int, 3> orig_array4(orig_array3);
  s21::array<int, 3> copy_array4(copy_array3);
  for (int i{}; i < 3; i++) {
    ASSERT_EQ(orig_array3.at(i), copy_array3.at(i));
    ASSERT_EQ(orig_array4.at(i), copy_array4.at(i));
  }
  ASSERT_EQ(orig_array3.size(), copy_array3.size());
  ASSERT_EQ(orig_array3.max_size(), copy_array3.max_size());
  ASSERT_EQ(orig_array4.size(), copy_array4.size());
  ASSERT_EQ(orig_array4.max_size(), copy_array4.max_size());
  std::array<char, 0> orig_ar5;
  s21::array<char, 0> copy_ar5;
  std::array<char, 0> orig_ar6(orig_ar5);
  s21::array<char, 0> copy_ar6(copy_ar5);
  ASSERT_EQ(orig_ar5.empty(), copy_ar5.empty());
  ASSERT_EQ(orig_ar6.empty(), copy_ar6.empty());
}

TEST(Array, move_constructor_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2(std::move(orig_array1));
  s21::array<int, 5> copy_array2(std::move(copy_array1));
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, move_operator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  std::array<int, 5> orig_array2{25};
  s21::array<int, 5> copy_array2{25};
  orig_array2 = std::move(orig_array1);
  copy_array2 = std::move(copy_array1);
  for (size_t i{}; i < copy_array2.size(); i++) {
    ASSERT_EQ(orig_array2.at(i), copy_array2.at(i));
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  ASSERT_EQ(orig_array2.size(), copy_array2.size());
  ASSERT_EQ(orig_array2.max_size(), copy_array2.max_size());
  std::array<char, 0> orig_ar1;
  s21::array<char, 0> copy_ar1;
  ASSERT_EQ(orig_ar1.empty(), copy_ar1.empty());
}

TEST(Array, iterator_test) {
  std::array<int, 5> orig_array1{234, 21, 11, 34, 999};
  s21::array<int, 5> copy_array1{234, 21, 11, 34, 999};
  int *orig_beg = orig_array1.begin();
  int *copy_beg = copy_array1.begin();
  int *orig_end = orig_array1.end();
  int *copy_end = copy_array1.end();
  while (orig_beg < orig_end && copy_beg < copy_end) {
    ASSERT_EQ(*orig_beg++, *copy_beg++);
  }
  ASSERT_EQ(orig_array1.size(), copy_array1.size());
  ASSERT_EQ(orig_array1.max_size(), copy_array1.max_size());
  s21::array<char, 0> copy_ar1;
  ASSERT_TRUE(copy_ar1.begin() == copy_ar1.end());
  s21::array<double, 3> my_arr{2.3, 4.5555, 6.1234};
  double *d = my_arr.data();
  ASSERT_DOUBLE_EQ(my_arr[0], *d);
}

TEST(Array, fill_test) {
  std::array<size_t, 10> orig_array;
  s21::array<size_t, 10> my_arr;
  orig_array.fill(555);
  my_arr.fill(555);
  for (size_t i = 0; i < orig_array.size(); i++)
    ASSERT_EQ(orig_array[i], my_arr[i]);
  ASSERT_EQ(orig_array.size(), my_arr.size());
}

// MAP
class TestMap {
 public:
  s21::map<int, int> s21_map_empty;
  s21::map<int, int> s21_map_four{{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  s21::map<int, int> s21_map_swap{{1, 95}, {2, 94}, {3, 93}};

  std::map<int, int> std_map_empty;
  std::map<int, int> std_map_four{{
                                      1,
                                      1,
                                  },
                                  {2, 2},
                                  {3, 3},
                                  {4, 4}};
  std::map<int, int> std_map_swap{{1, 95}, {2, 95}, {3, 95}};
};

TEST(Map, constructor_default) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
}

TEST(Map, constructor_initializer) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
  EXPECT_EQ(tester.s21_map_four[4], tester.std_map_four[4]);
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.std_map_four.empty(), tester.std_map_four.empty());
}

TEST(Map, constructor_copy_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy(tester.s21_map_empty);
  std::map<int, int> std_map_copy(tester.std_map_empty);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(std_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, constructor_copy_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy(tester.s21_map_four);
  std::map<int, int> std_map_copy(tester.std_map_four);
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(std_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, constructor_move_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move = std::move(tester.s21_map_empty);
  std::map<int, int> std_map_move = std::move(tester.std_map_empty);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, constructor_move_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move = std::move(tester.s21_map_four);
  std::map<int, int> std_map_move = std::move(tester.std_map_four);
  EXPECT_EQ(s21_map_move[1], std_map_move[1]);
  EXPECT_EQ(s21_map_move[4], std_map_move[4]);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, operator_copy_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy;
  std::map<int, int> std_map_copy;
  s21_map_copy = tester.s21_map_four;
  std_map_copy = tester.std_map_four;
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, operator_copy_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_copy{{1, 1}, {2, 2}};
  std::map<int, int> std_map_copy{{1, 1}, {2, 2}};
  s21_map_copy = tester.s21_map_four;
  std_map_copy = tester.std_map_four;
  EXPECT_EQ(s21_map_copy[1], std_map_copy[1]);
  EXPECT_EQ(s21_map_copy[4], std_map_copy[4]);
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  EXPECT_EQ(s21_map_copy.empty(), std_map_copy.empty());
}

TEST(Map, operator_move_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move;
  std::map<int, int> std_map_move;
  s21_map_move = std::move(tester.s21_map_four);
  std_map_move = std::move(tester.std_map_four);
  EXPECT_EQ(s21_map_move[1], std_map_move[1]);
  EXPECT_EQ(std_map_move[4], std_map_move[4]);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, operator_move_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_move{{1, 1}, {2, 2}};
  std::map<int, int> std_map_move{{1, 1}, {2, 2}};
  s21_map_move = std::move(tester.s21_map_empty);
  std_map_move = std::move(tester.std_map_empty);
  EXPECT_EQ(s21_map_move[1], std_map_move[1]);
  EXPECT_EQ(s21_map_move[2], std_map_move[2]);
  EXPECT_EQ(s21_map_move.size(), std_map_move.size());
  EXPECT_EQ(s21_map_move.empty(), std_map_move.empty());
}

TEST(Map, function_empty_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(tester.s21_map_empty[1], tester.std_map_empty[1]);
}

TEST(Map, function_empty_not_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
}

TEST(Map, function_size_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(tester.s21_map_empty[1], tester.std_map_empty[1]);
}

TEST(Map, function_size_not_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.std_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_four[1], tester.std_map_four[1]);
  EXPECT_EQ(tester.s21_map_four[4], tester.std_map_four[4]);
}

TEST(Map, function_max_size_empty) {
  TestMap tester;
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(tester.s21_map_empty.max_size(), tester.std_map_empty.max_size());
}

TEST(Map, function_swap_empty) {
  s21::map<int, int> m1({{1, 8}, {4, 2}, {2, 3}});
  s21::map<int, int> m2;
  m1.swap(m2);

  std::map<int, int> m3({{1, 8}, {4, 2}, {2, 3}});
  std::map<int, int> m4;
  m3.swap(m4);

  ASSERT_EQ(m2[1], m4[1]);
  ASSERT_EQ(m2[2], m4[2]);
  ASSERT_EQ(m2[4], m4[4]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}

TEST(Map, function_swap_not_empty) {
  TestMap tester;
  s21::map<int, int> s21_map_swap{{1, 1}, {2, 2}};
  std::map<int, int> std_map_swap{{1, 1}, {2, 2}};
  s21_map_swap.swap(tester.s21_map_four);
  std_map_swap.swap(tester.std_map_four);
  EXPECT_EQ(s21_map_swap[1], std_map_swap[1]);
  EXPECT_EQ(s21_map_swap[4], std_map_swap[4]);
  EXPECT_EQ(s21_map_swap.size(), std_map_swap.size());
  EXPECT_EQ(s21_map_swap.empty(), std_map_swap.empty());
}

TEST(Map, WithDuplicatesCase) {
  s21::map<int, int> m1({{1, 8}, {4, 2}, {2, 3}});
  s21::map<int, int> m2({{1, 3}, {2, 2}});
  m1.merge(m2);

  std::map<int, int> m3({{1, 8}, {4, 2}, {2, 3}});
  std::map<int, int> m4({{1, 3}, {2, 2}});
  m3.merge(m4);

  ASSERT_EQ(m1[1], m3[1]);
  ASSERT_EQ(m1[2], m3[2]);
  ASSERT_EQ(m1[4], m3[4]);

  ASSERT_EQ(m2[1], m4[1]);
  ASSERT_EQ(m2[2], m4[2]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}
TEST(Map, WithoutDuplicatesCase) {
  s21::map<int, int> m1({{1, 2}, {3, 4}, {4, 5}});
  s21::map<int, int> m2({{5, 6}, {7, 7}});
  m1.merge(m2);

  std::map<int, int> m3({{1, 2}, {3, 4}, {4, 5}});
  std::map<int, int> m4({{5, 6}, {7, 7}});
  m3.merge(m4);

  ASSERT_EQ(m1[1], m3[1]);
  ASSERT_EQ(m1[3], m3[3]);
  ASSERT_EQ(m1[4], m3[4]);
  ASSERT_EQ(m1[5], m3[5]);
  ASSERT_EQ(m1[7], m3[7]);

  ASSERT_EQ(m1.size(), m3.size());
  ASSERT_EQ(m2.size(), m4.size());
}

TEST(Map, function_clear_empty) {
  TestMap tester;
  tester.s21_map_empty.clear();
  tester.std_map_empty.clear();
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
}

TEST(Map, function_clear_not_empty) {
  TestMap tester;
  tester.s21_map_four.clear();
  tester.std_map_four.clear();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
}

TEST(Map, function_begin_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_empty.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  EXPECT_EQ(iter_1 == tester.s21_map_empty.end(),
            iter_2 == tester.std_map_empty.end());
}

TEST(Map, function_begin_not_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_four.end());
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}
TEST(Map, const_begin_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_empty.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == tester.s21_map_empty.end(),
            iter_2 == tester.std_map_empty.end());
}
TEST(Map, const_begin_not_empty) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_four.end());
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}
TEST(Map, operator_plus) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}
TEST(Map, operator_minus) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  --iter_1;
  --iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, operator_assignment) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = iter_1;
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  std::map<int, int>::iterator iter_4 = iter_2;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*iter_1).second, (*iter_3).second);
  EXPECT_EQ((*iter_2).second, (*iter_4).second);
}
TEST(Map, operator_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  std::map<int, int>::iterator iter_4 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == iter_3, iter_2 == iter_4);
}
TEST(Map, operatort_not_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_empty.end());
}
TEST(Map, const_operator_plus) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.cbegin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.cbegin();
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}
TEST(Map, const_operator_minus) {
  TestMap tester;
  s21::map<int, int>::const_iterator iter_1 = tester.s21_map_four.cbegin();
  std::map<int, int>::const_iterator iter_2 = tester.std_map_four.cbegin();
  ++iter_1;
  ++iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
  --iter_1;
  --iter_2;
  EXPECT_EQ((*iter_1).second, (*iter_2).second);
}

TEST(Map, const_operator_assignment) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = iter_1;
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  std::map<int, int>::iterator iter_4 = iter_2;
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*iter_1).second, (*iter_3).second);
  EXPECT_EQ((*iter_2).second, (*iter_4).second);
}
TEST(Map, const_operator_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  s21::map<int, int>::iterator iter_3 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_empty.begin();
  std::map<int, int>::iterator iter_4 = tester.std_map_empty.begin();
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ(tester.s21_map_empty.size(), tester.std_map_empty.size());
  EXPECT_EQ(tester.s21_map_empty.empty(), tester.std_map_empty.empty());
  EXPECT_EQ(iter_1 == iter_3, iter_2 == iter_4);
}
TEST(Map, const_operatort_not_equal) {
  TestMap tester;
  s21::map<int, int>::iterator iter_1 = tester.s21_map_four.begin();
  std::map<int, int>::iterator iter_2 = tester.std_map_four.begin();
  EXPECT_EQ(iter_1 != tester.s21_map_four.end(),
            iter_2 != tester.std_map_empty.end());
}

TEST(Map, function_insert_without_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert({5, 2});
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({5, 2});
  EXPECT_EQ((*(iter_1.first)).second, (*(iter_2.first)).second);
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_with_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert({1, 2});
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({1, 2});
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_key_value_without_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert(7, 7);
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({7, 7});
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_EQ((*(iter_1.first)).second, (*(iter_2.first)).second);
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_key_value_with_duplicate) {
  TestMap tester;
  std::pair<s21::map<int, int>::iterator, bool> iter_1 =
      tester.s21_map_four.insert(1, 7);
  std::pair<std::map<int, int>::iterator, bool> iter_2 =
      tester.std_map_four.insert({1, 7});
  EXPECT_EQ(tester.s21_map_four.size(), tester.std_map_four.size());
  EXPECT_EQ(tester.s21_map_four.empty(), tester.std_map_four.empty());
  EXPECT_TRUE(iter_1.second == iter_2.second);
}

TEST(Map, function_insert_or_assign_value) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  s21::map<int, int> m2({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert_or_assign(5, 2);
  std::pair<s21::map<int, int>::iterator, bool> it2 = m2.insert_or_assign(5, 2);
  ASSERT_TRUE(it1.second == it2.second);
}

TEST(Map, function_insert_or_assign) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  s21::map<int, int> m2({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert_or_assign(1, 2);
  std::pair<s21::map<int, int>::iterator, bool> it2 = m2.insert_or_assign(1, 2);
  ASSERT_EQ((*(it1.first)).second, (*(it2.first)).second);
  ASSERT_TRUE(it1.second == it2.second);
}

TEST(Map, function_insert_s) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::pair<s21::map<int, int>::iterator, bool> it1 = m1.insert(5, 2);
  ASSERT_EQ((*(it1.first)).second, 2);
  ASSERT_TRUE(it1.second);
}

TEST(Map, function_at) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  ASSERT_EQ(m1.at(1), m2.at(1));
}
TEST(Map, function_erase) {
  s21::map<int, int> m1({{1, 3}, {4, 2}});
  std::map<int, int> m2({{1, 3}, {4, 2}});
  m1.erase(m1.begin());
  m2.erase(m2.begin());
  ASSERT_EQ(m1[1], m2[1]);
}

TEST(Map, function_ontains) {
  s21::map<int, int> s1({{1, 3}, {4, 2}});
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(4));
  ASSERT_FALSE(s1.contains(3));
}

TEST(Map, insert_many_test) {
  s21::map<int, std::string> my_map;
  std::map<int, std::string> orig_map;
  my_map.insert_many(std::make_pair(1, "Moscow"), std::make_pair(2, "Kazan"),
                     std::make_pair(3, "Ufa"));

  orig_map.insert(std::make_pair(1, "Moscow"));
  orig_map.insert(std::make_pair(2, "Kazan"));
  orig_map.insert(std::make_pair(3, "Ufa"));

  ASSERT_EQ(my_map.size(), orig_map.size());

  auto my_it = my_map.begin();
  auto std_it = orig_map.begin();
  for (; my_it != my_map.end() && std_it != orig_map.end(); ++my_it, ++std_it) {
    EXPECT_EQ(my_it->first, std_it->first);
    EXPECT_EQ(my_it->second, std_it->second);
  }
}
