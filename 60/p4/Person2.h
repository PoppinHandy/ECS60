#ifndef PERSON2_H_
#define PERSON2_H_
#include "familyRunner.h"

class Person2{
 public:
  Person2();
  void setPerson(Person &p);
  const Person2 & getPerson();
  //Person2( Person &p);
  Person person;
  int id;
};


#endif /*PERSON2_H*/
