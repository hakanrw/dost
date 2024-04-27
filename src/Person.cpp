#include <Person.h>

Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
: id(id), name(name), gender(gender), occupation(occupation), friends(friends) {}
