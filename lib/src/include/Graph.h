#pragma once

#include <vector>

#include "Person.h"

class Graph {
    public:
        Graph();
        void addPerson(int id, const Person &person);
        Person* getPerson(int id) const;

        void removeFriendship(int id1, int id2);

        std::vector<Person*> suggestFriends(int person_id, int mode) const;
        std::vector<Person*> suggestFriendsByCommonFriends(const Person* person) const;
        std::vector<Person*> suggestFriendsByOccupation(const Person* person) const;
        std::vector<Person*> suggestFriendsByAge(const Person* person) const;

        std::vector<std::pair<int, Person>> getGraph() const;
        int getSize() const;

        void displayGraph() const;
        float degreeCentralityOfPerson(int id) const;
        void degreeCentrality() const;
        float clusteringCoefficient(int id) const;
        int girvanNewman(int iterations) const;
        double edgeWeight(const Graph &graph, int u, int v) const;

    private:
        std::vector<std::pair<int, Person>> graph;
};