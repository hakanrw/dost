#include <Person.h>

Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
: id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

// BEGIN Setters and Getters

int Person::getId() {
    return id;
}

void Person::setId(int id) {
    this->id = id;
}

std::string Person::getName() {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

int Person::getAge() {
    return age;
}

void Person::setAge(int age) {
    this->age = age;
}

std::string Person::getGender() {
    return gender;
}

void Person::setGender(std::string gender) {
    this->gender = gender;
}

std::string Person::getOccupation() {
    return occupation;
}

void Person::setOccupation(std::string occupation) {
    this->occupation = occupation;
}

// END Setters and Getters

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Person (id=" << person.id << ", name=" << person.name << ", age=" << person.age
        << ", gender=" << person.gender << ", occupation=" << person.occupation 
        << ", friends=[";

    for(std::vector<int>::const_iterator it = person.friends.begin(); it != person.friends.end(); ++it) {
        if (it == person.friends.begin())
            os << *it;
        else
            os << "," << *it;
    }

    os << "])";

    return os;
}
