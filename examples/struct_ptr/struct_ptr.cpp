#include <Arduino.h>
#include <memory.hpp>
using namespace memory;

struct TypeTest
{
  uint32_t ui_type;
  float f_type;

  operator String() const {
    String buff = "";
    buff += "uint32_t: " ;
    buff += String(ui_type);
    buff += " float: " ;
    buff += String(f_type);
    return buff;
  }
};
typedef struct TypeTest TypeTest;

void setup()
{
  Serial.begin(38400);
  SmartPointer<TypeTest> struct_ptr = make_ptr<TypeTest>();
  struct_ptr.set(TypeTest{ 400, 23.23f });
  Serial.println(*struct_ptr.get());
}

void loop()
{
}