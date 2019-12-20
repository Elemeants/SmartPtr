#include <Arduino.h>
#include <memory.hpp>

void setup()
{
  Serial.begin(38400);
  SmartPointer<float> ptr = make_ptr<float>();
  ptr.set(20);
  Serial.print("Ptr value: ");
  Serial.print(*ptr.get());
  Serial.print(" Address: ");
  Serial.println(ptr.get());
}

void loop()
{
}