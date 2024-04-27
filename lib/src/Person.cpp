#include <Person.h>

Person::Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends)
: id(id), name(name), age(age), gender(gender), occupation(occupation), friends(friends) {}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << "Person (id=" << person.id << ", name=" << person.name 
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
