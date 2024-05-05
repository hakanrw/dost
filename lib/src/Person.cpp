#include <Person.h>
#include <algorithm>

Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
: id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

void Person::removeFriend(int id) {
    friends.erase(find(friends.begin(), friends.end(), id));
}

// BEGIN Setters and Getters

int Person::getId() const {
    return id;
}

void Person::setId(int id) {
    this->id = id;
}

std::string Person::getName() const {
    return name;
}

void Person::setName(std::string name) {
    this->name = name;
}

int Person::getAge() const {
    return age;
}

void Person::setAge(int age) {
    this->age = age;
}

std::string Person::getGender() const{
    return gender;
}

void Person::setGender(std::string gender) {
    this->gender = gender;
}

std::string Person::getOccupation() const {
    return occupation;
}

void Person::setOccupation(std::string occupation) {
    this->occupation = occupation;
}

std::vector<int> Person::getFriends() const {
    return friends;
}

// END Setters and Getters

std::string Person::getSimpleString() const {
    std::string str = "Person (id=" + std::to_string(id) + ", name=" + name + ")";
    return str;
}


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
