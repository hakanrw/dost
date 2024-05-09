#include <Graph.h>

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <limits>

// #define DEBUG 

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

// Recursive function to find paths from `current` to `start` using the `parent` map
static void findPaths(std::map<int, std::vector<int>> &parent, int start, int current, std::vector<int> &path, std::vector<std::vector<int>> &allPaths) {
    // Add the current node to the path
    path.push_back(current);

    // If the current node is the start node, we have found a path
    if (current == start) {
        // Reverse the path (since we constructed it from end to start)
        std::reverse(path.begin(), path.end());
        // Add the path to the list of all paths
        allPaths.push_back(path);
        // Reverse the path back to its original order
        std::reverse(path.begin(), path.end());
    } else {
        // Recurse through each parent of the current node
        for (int parentNode : parent[current]) {
            findPaths(parent, start, parentNode, path, allPaths);
        }
    }

    // Remove the current node from the path to backtrack
    path.pop_back();
}

// returns all shortest paths between two people
std::vector<std::vector<int>> Graph::bfs(int start, int end) const {
    if (start == end) return std::vector<std::vector<int>>();
    
    std::queue<int> queue;
    std::map<int, int> visited;
    std::map<int, std::vector<int>> parent;
    queue.push(start);
    visited[start] = 1;

    while (queue.size() > 0) {
        const int current = queue.front();
        queue.pop();

        if (current == end) break;
        
        for (const int node : getPerson(current)->getFriends()) {
            if (visited[node] == 0) {
                visited[node] = visited[current] + 1;
                queue.push(node);
                parent[node].push_back(current);
            }
            else if (visited[current] + 1 == visited[node]) {
                parent[node].push_back(current);
            }
        }
    }

    std::vector<std::vector<int>> paths;
    std::vector<int> p;
    findPaths(parent, start, end, p, paths);

    return paths;
}

template <typename T>
void printVectorOfVectors(const std::vector<std::vector<T>> &vec) {
    // Iterate through each inner vector
    for (const std::vector<T> &innerVec : vec) {
        // Iterate through each element in the inner vector
        for (const T &element : innerVec) {
            // Print each element followed by a space
            std::cout << element << " ";
        }
        // Print a newline after printing each inner vector
        std::cout << std::endl;
    }
}

float Graph::edgeBetweenness(int a, int b) const {
    int pathsPassEdge = 0;
    int totalPaths = 0;

    std::vector<int> neighbors = getPerson(a)->getFriends();
    if (std::find(neighbors.begin(), neighbors.end(), b) == neighbors.end()) return 0.0f;

    for (size_t i = 0; i < graph.size(); i++) {
        for (size_t j = i + 1; j < graph.size(); j++) {
            std::vector<std::vector<int>> paths = bfs(graph[i].first, graph[j].first);
            totalPaths += paths.size();

            // std::cout << "-------------------" << std::endl;
            // printVectorOfVectors(paths);

            for (size_t z = 0; z < paths.size(); z++) {
                const std::vector<int> path = paths[z]; 
                auto aLocation = find(path.begin(), path.end(), a);
                auto bLocation = find(path.begin(), path.end(), b);

                if (aLocation == path.end() || bLocation == path.end()) continue;

                if (std::abs(aLocation - bLocation) == 1) pathsPassEdge++;
            }
        }
    }

    // std::cout << "paths pass edge: " << pathsPassEdge << std::endl;
    // std::cout << "total paths: " << totalPaths << std::endl;

    if (totalPaths == 0) return 0.0f;

    return pathsPassEdge /* / (float) totalPaths */;
}

// i am not sure what the teacher wanted by edgeWeight
float Graph::edgeWeight(const Graph& graph, int u, int v) const {
    return graph.edgeBetweenness(u, v);
}

static void dfs(const Graph& graph, int node, std::set<int>& visited, std::vector<int>& component) {
        // Mark the current node as visited
        visited.insert(node);

        // Add the node to the current component
        component.push_back(node);

        // Iterate over the neighbors of the current node
        for (int neighbor : graph.getPerson(node)->getFriends()) {
            // If the neighbor has not been visited, perform DFS on it
            if (visited.find(neighbor) == visited.end()) {
                dfs(graph, neighbor, visited, component);
            }
        }
    }


static std::vector<std::vector<int>> connectedComponentsInGraph(const Graph& graph) {
    std::vector<std::vector<int>> connectedComponents;
    std::set<int> visited;

    for (const std::pair<int, Person>& nodePair : graph.getGraph()) {
        int node = nodePair.first;

        if (visited.find(node) == visited.end()) {
            std::vector<int> component;

            dfs(graph, node, visited, component);

            connectedComponents.push_back(component);
        }
    }

    return connectedComponents;
}

std::vector<std::vector<int>> Graph::girvanNewman(int iteration) const {
    Graph graphCopy = *this;

    for (size_t i = iteration; i > 0; i--) {
        std::map<std::pair<int, int>, float> edgeValues;

        for (size_t x = 0; x < graph.size(); x++) {
            for (size_t y = x + 1; y < graph.size(); y++) {
                edgeValues[{x, y}] = graphCopy.edgeBetweenness(x + 1, y + 1);
            }
        }

#ifdef DEBUG
        // Iterate through the map and print each key-value pair
        for (const auto& entry : edgeValues) {
            const std::pair<int, int>& key = entry.first;
            float value = entry.second;
            if (value == 0) continue;
            std::cout << "Key: (" << key.first << ", " << key.second << "), Value: " << value << std::endl;
        }
#endif // DEBUG

        std::pair<int, int> maxKey;
        float maxValue = std::numeric_limits<float>::lowest(); // Start with the lowest possible value

        // Iterate through the map to find the maximum value and its key
        for (const auto& entry : edgeValues) {
            const std::pair<int, int>& key = entry.first;
            float value = entry.second;

            if (value > maxValue) {
                maxValue = value;
                maxKey = key;
            }
        }

        graphCopy.removeFriendship(maxKey.first, maxKey.second);
    }

    std::vector<std::vector<int>> components = connectedComponentsInGraph(graphCopy);


#ifdef DEBUG
    graphCopy.displayGraph();
    printVectorOfVectors(components);
#endif // DEBUG

    return components;
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
