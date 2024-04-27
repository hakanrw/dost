#include <Graph.h>

#include <iostream>

Graph::Graph() : people() {}

void Graph::addPerson(int id, const Person &person) {
    people.push_back(std::pair<int, Person>(id, person));
}

Person* Graph::getPerson(int id) const {
    const Person* person = nullptr;
    
    for (std::vector<std::pair<int, Person>>::const_iterator it = people.begin(); it != people.end(); ++it) {
        if (it->first == id) {
            person = &it->second;
            break;
        }
    }
    
    return (Person*) person;
}

void Graph::degreeCentrality() const {
    for (std::vector<std::pair<int, Person>>::const_iterator it = people.begin(); it != people.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

std::vector<std::pair<int, Person>> Graph::getGraph() const {
    return people;
}

int Graph::getSize() const {
    return people.size();
}