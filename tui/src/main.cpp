#include <Graph.h>
#include <utils.h>

int main() {
	Graph graph = readData("social_network.csv");

    graph.getPerson(1)->setAge(19);
    graph.degreeCentrality();

	return 0;
}
