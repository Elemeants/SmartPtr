#ifdef UNIT_TEST
#include <unity.h>
#include <SmartPtr.hpp>
using namespace memory;

#ifndef TEST_CASE
#define TEST_CASE(func, name) UnityDefaultTestRun(func, #name, __LINE__)
#endif // !TEST_CASE

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <stdio.h>
#include <stdlib.h>
#endif // ARDUINO

namespace TestMemory
{
void Execute()
{
  TEST_CASE([]() -> void {
    SmartPointer<int> ptr = make_ptr<int>();

    TEST_ASSERT_NOT_NULL(ptr.get());
  },
            Test_make_ptr);

  TEST_CASE([]() -> void {
    int *original_ptr = new int();
    {
      SmartPointer<int> srt_ptr(original_ptr);
    }
    TEST_ASSERT(!(*original_ptr));
  },
            Test_memory_auto_destroy_ptr);

  TEST_CASE([]() -> void {
    SmartPointer<int> ptr = make_ptr<int>();
    int *_ptr = ptr.get();
    ptr = make_ptr<int>();
    TEST_ASSERT(!(*_ptr));
  },
            Test_memory_destroy_on_assignation);

  TEST_CASE([]() -> void {
    SmartPointer<int> ptr = make_ptr<int>();
    int *_ptr = ptr.get();
    ptr.reset();
    TEST_ASSERT(!(*_ptr));
  },
            Test_memory_destroy_on_reset);

  TEST_CASE([]() -> void {
    SmartPointer<int> ptr = make_ptr<int>();
    ptr.set(20);
    TEST_ASSERT(*ptr.get() == 20);
  },
            Test_memory_change_pointer_val_int);

  TEST_CASE([]() -> void {
    SmartPointer<double> ptr = make_ptr<double>();
    ptr.set(20.2f);
    TEST_ASSERT(*ptr.get() == 20.2f);
  },
            Test_memory_change_pointer_val_double);

  TEST_CASE([]() -> void {
    typedef struct
    {
      int x;
      int y;
    } Test;
    SmartPointer<Test> ptr = make_ptr<Test>();
    ptr.set(Test{10, 20});
    Test *val = ptr.get();
    TEST_ASSERT(val->x == 10 && val->y == 20);
  },
            Test_memory_change_pointer_val_struct);
}
}; // namespace TestMemory

#ifndef ARDUINO
int main()
{
  TestMemory::Execute();
}
#endif // ARDUINO

#endif // UNIT_TEST