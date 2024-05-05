#include <Graph.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <set>

Graph::Graph() : graph() {}

void Graph::addPerson(int id, const Person &person) {
    graph.push_back(std::pair<int, Person>(id, person));
}

Person* Graph::getPerson(int id) const {
    const Person* person = nullptr;
    
    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        if (it->first == id) {
            person = &it->second;
            break;
        }
    }
    
    return (Person*) person;
}

void Graph::removeFriendship(int id1, int id2) {
    getPerson(id1)->removeFriend(id2);
    getPerson(id2)->removeFriend(id1);
}

float Graph::degreeCentralityOfPerson(int id) const {
    return getPerson(id)->getFriends().size() / (float) (graph.size() - 1);
}

void Graph::degreeCentrality() const {
    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        const Person& person = it->second; 
        
        std::cout << "Degree centrality for " << person.getSimpleString() << ": " 
            << degreeCentralityOfPerson(person.getId()) << std::endl;
    }
}

float Graph::clusteringCoefficient(int id) const {
    const Person* person = getPerson(id);
    const std::vector<int> friends = person->getFriends();

    if (friends.size() < 2) {
        return 0.0f; // Not enough friends to form any triangles
    }

    std::set<std::pair<int, int>> pairSet;

    for (size_t i = 0; i < friends.size(); i++) {
        int friendId = friends[i];
        const Person* currentFriend = getPerson(friendId);
        const std::vector<int> friendFriends = currentFriend->getFriends();

        for (int friendFriendId : friendFriends) {
            if (std::find(friends.begin(), friends.end(), friendFriendId) != friends.end()) {
                pairSet.insert({std::min(friendId, friendFriendId), std::max(friendId, friendFriendId)});
            }
        }
    }

    int Kv = friends.size();
    int Nv = pairSet.size();
    return (2 * Nv) / (float) (Kv * (Kv - 1));
}

void Graph::displayGraph() const {
    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

std::vector<std::pair<int, Person>> Graph::getGraph() const {
    return graph;
}

int Graph::getSize() const {
    return graph.size();
}

std::vector<Person*> Graph::suggestFriends(int person_id, int mode) const {
    const Person* person = getPerson(person_id);

    if (person == nullptr) {
        throw std::runtime_error("person with id " + std::to_string(person_id) + " not found.");
    }
    
    if (mode == 1) { // 1.Common Friends,
        return suggestFriendsByCommonFriends(person);
    }
    else if (mode == 2) { // 2.Similar Occupation,
        return suggestFriendsByOccupation(person);
    }
    else if (mode == 3) { // 3.Similar Age.
        return suggestFriendsByAge(person);
    }
    else {
        throw std::runtime_error("mode " + std::to_string(mode) + " is not supported.");
    }
}

std::vector<Person*> Graph::suggestFriendsByCommonFriends(const Person* person) const {
    std::vector<Person*> suggestedPeople;
    const std::vector<int> friends = person->getFriends();

    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        std::vector<int> theirFriends = it->second.getFriends();

        if (std::find(friends.begin(), friends.end(), it->first) == friends.end() // dont suggest existing friends
            && std::any_of(theirFriends.begin(), theirFriends.end(), [&friends](int i){ return std::find(friends.begin(), friends.end(), i) != friends.end(); })
            && it->first != person->getId()) 
            suggestedPeople.push_back((Person*) &it->second);
    }

    return suggestedPeople;}

std::vector<Person*> Graph::suggestFriendsByOccupation(const Person* person) const {
    std::vector<Person*> suggestedPeople;
    const std::vector<int> friends = person->getFriends();

    std::vector<std::string> occupationWords;

    std::stringstream ss(person->getOccupation());
    std::string s;

    while (getline(ss, s, ' ')) {
        occupationWords.push_back(s);
    }

    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        std::vector<std::string> theirOccupationWords;

        std::stringstream ss(it->second.getOccupation());
        std::string s;

        while (getline(ss, s, ' ')) {
            theirOccupationWords.push_back(s);
        }

        if (std::find(friends.begin(), friends.end(), it->first) == friends.end() // dont suggest existing friends
            && std::any_of(theirOccupationWords.begin(), theirOccupationWords.end(), [&occupationWords](std::string i){ return std::find(occupationWords.begin(), occupationWords.end(), i) != occupationWords.end(); })
            && it->first != person->getId()) 
            suggestedPeople.push_back((Person*) &it->second);
    }

    return suggestedPeople;
}

std::vector<Person*> Graph::suggestFriendsByAge(const Person* person) const {
    std::vector<Person*> suggestedPeople;
    std::vector<int> friends = person->getFriends();

    for (std::vector<std::pair<int, Person>>::const_iterator it = graph.begin(); it != graph.end(); ++it) {
        if (abs(it->second.getAge() - person->getAge()) < 4 
            && std::find(friends.begin(), friends.end(), it->first) == friends.end() // dont suggest existing friends
            && it->first != person->getId()) 
            suggestedPeople.push_back((Person*) &it->second);
    }

    return suggestedPeople;
}
