#include <iostream>

#include <Graph.h>
#include <utils.h>

Graph graph;

void suggestFriendsInterface() {
    std::cout << "Enter Mode" << std::endl;
    std::cout << "1. By common friends" << std::endl;
    std::cout << "2. By occupation" << std::endl;
    std::cout << "3. By age" << std::endl;

    int mode;
    std::cin >> mode;

    std::cout << "Enter User ID" << std::endl;

    int id;
    std::cin >> id;

    const Person* person = graph.getPerson(id);

    if (person == nullptr) {
        std::cerr << "Person with ID " << id << " not found" << std::endl;
        return;
    }

    std::cout << "For person:\n" << *person << "\n\nWe suggest:" << std::endl;

    const std::vector<Person*> suggestedPeople = graph.suggestFriends(id, mode);

    for (const Person* person : suggestedPeople) {
        std::cout << person->getId() << ": " << *person << std::endl;
    }
}

void clusteringCoefficient() {
    for (const std::pair<int, Person>& pair : graph.getGraph()) {
        const Person& person = pair.second;

        std::cout << "Clustering coefficient for " << person.getSimpleString() 
            << ": " << graph.clusteringCoefficient(person.getId()) << std::endl;
    }
}

int main() {
	graph = readData("social_network.csv");

    // std::cout << graph.edgeBetweenness(14, 15) << std::endl;
    graph.girvanNewman(4);

    while (true) {
        std::cout << "1. Display the social network" << std::endl;
        std::cout << "2. Suggest friends" << std::endl;
        std::cout << "3. Calculate degree centrality for each user" << std::endl;
        std::cout << "4. Calculate clustering coefficient for each user" << std::endl;
        std::cout << "5. Detect communities" << std::endl;
        std::cout << "6. Exit" << std::endl;

        int option;
        std::cin >> option;

        if (option == 1) graph.displayGraph();
        else if (option == 2) suggestFriendsInterface();
        else if (option == 3) graph.degreeCentrality();
        else if (option == 4) clusteringCoefficient();
        else if (option == 6) break;
        else std::cout << "Operation not supported." << std::endl;

        std::cout << std::endl;
    }

	return 0;
}
