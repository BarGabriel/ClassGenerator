
# Class Generator

An application for generate C++ & python classes.

# Features

 - Time-saver (especially with big classes).
 - Easy to use.
 - Cross-platform (linux and windows).
 - Generates getters & setters for private members.

  
# Building

#### Linux

```bash
  mkdir build && cd build
  cmake ..
  make
```

#### Windows 
Using Visual Studio command prompt

```bash
  mkdir build && cd build
  cmake ..
  msbuild ClassGenerator.sln
```

  
# Usage & Examples






#### Program options
`--lang`: The class language - c++ \ python.  
`--name`: The class name.  
`--private`: Private members.



### C++ classes
```bash
./ClassGenerator --lang=c++ --name=Student --private=i,firstName,s,age
```
####  output:
- Header file - Student.hpp
```bash
#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>

class Student
{
public:
	Student(std::string firstName, int age);

	void set_firstName(std::string value);
	std::string get_firstName() const;

	void set_age(int value);
	int get_age() const;


private:
	std::string _firstName;
	int _age;
};

#endif
```

- Source file - Student.cpp
```bash
#include "Student.hpp"

Student::Student(std::string firstName, int age)
{
	_firstName = firstName;
	_age = age;
}

void Student::set_firstName(std::string value)
{
	_firstName = value;
}

std::string Student::get_firstName() const
{
	return _firstName;
}

void Student::set_age(int value)
{
	_age = value;
}

int Student::get_age() const
{
	return _age;
}
```

### Python classes
```bash
./ClassGenerator --lang=python --name=Student --private=firstName,age
```
####  output:
Student.py

```
class Student:
   def __init__(self, first_name, age):
      self._first_name = first_name
      self._age = age

   def set_first_name(self, value):
      self._first_name = value

   def get_first_name(self):
      return self._first_name

   def set_age(self, value):
      self._age = value

   def get_age(self):
      return self._age
```
      


