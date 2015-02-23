#include "Person2.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>


Person2::Person2()
{
  person.year = -1;
  id = 0;
}

void Person2::setPerson(Person &p)
{
  memcpy(&person, &p, sizeof(Person));
  id = person.year;
  id += atoi(person.firstName);
  id += atoi(person.lastName);
}

const Person2 & Person2::getPerson()
{
  return *this;
}
