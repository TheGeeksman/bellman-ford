#include <cstdio>
#include <climits>
#include <vector>
#include <list>
#include <utility>
#include <iostream>

using namespace ::std;

void PrintNegativeCycle(vector< pair<int, int> > shortestDistances, int vertex, int startVertex)
{
	if (vertex == startVertex) {
		cout << vertex;
	}
	else if (shortestDistances[vertex].second == 0) {
		PrintNegativeCycle(shortestDistances, startVertex, startVertex);
		cout << vertex;
	}
	else {
		PrintNegativeCycle(shortestDistances, shortestDistances[vertex].second, startVertex);
		cout << vertex;
	}
}

int bellmanFord(
	vector< list< pair<int, int> > > adjacencyList,
	int vertices,
	int startVertex,
	vector< pair<int, int> >& shortestDistances
)
{
	list< pair<int, int> >::iterator traverse;
	int i, j, k;

	for (i = 0; i <= vertices; ++i) {
		shortestDistances[i].first = INT_MAX;
		shortestDistances[i].second = -1;
	}

	shortestDistances[startVertex].first = 0;
	shortestDistances[startVertex].second = 0;

	// The Algorithm that computes Shortest Distances
	for (i = 1; i <= vertices - 1; ++i) {    // Runs 'vertices - 1' times = O(|V|)
		for (j = 1; j <= vertices; ++j) {    // Runs as many times as the edges = O(|E|)
			// The code ahead basically explores the whole of Adjcency List,
			// covering one edge once, so the runtime of the code in this 
			// block is O(|E|)

			traverse = adjacencyList[j].begin();

			while (traverse != adjacencyList[j].end()) {
				if (shortestDistances[j].first == INT_MAX) {
					// Important...!
					//traverse = traverse->next;
					++traverse;
					continue;
				}

				// Checking for Relaxation
				if ((*traverse).second + shortestDistances[j].first <
					shortestDistances[(*traverse).first].first) {
					// Relaxation
					shortestDistances[(*traverse).first].first = (*traverse).second
						+ shortestDistances[j].first;
					shortestDistances[(*traverse).first].second = j;
				}

				++traverse;
			}
		}
	}

	// Checking for Negative Cycles
	for (j = 1; j <= vertices; ++j) {
		traverse = adjacencyList[j].begin();

		while (traverse != adjacencyList[j].end()) {
			// Checking for further relaxation
			if ((*traverse).second + shortestDistances[j].first <
				shortestDistances[(*traverse).first].first) {
				// Negative Cycle found as further relaxation is possible
				return j;
			}

			++traverse;
		}
	}

	return -1;
}

int main()
{
	int vertices, edges, v1, v2, weight;

	cout << "Enter the Number of Vertices -\n";
	cin >> vertices;

	cout << "Enter the Number of Edges -\n";
	cin >> edges;

	// Adjacency List is a vector of list.
	// Where each element is a pair<int, int>
	// pair.first -> the edge's destination
	// pair.second -> edge's weight
	vector< list< pair<int, int> > > adjacencyList(vertices + 1);

	cout << "Enter the Edges V1 -> V2, of weight W\n";

	for (int i = 1; i <= edges; ++i) {
		cin >> v1 >> v2 >> weight;

		// Adding Edge to the Directed Graph
		adjacencyList[v1].push_back(make_pair(v2, weight));
	}

	cout << "\nThe Adjacency List-\n";
	// Printing Adjacency List
	for (int i = 1; i < adjacencyList.size(); ++i) {
		cout << "adjacencyList[%d] ", i;

		list< pair<int, int> >::iterator itr = adjacencyList[i].begin();

		while (itr != adjacencyList[i].end()) {
			cout << " -> %d(%d)", (*itr).first, (*itr).second;
			++itr;
		}
		cout << "\n";
	}

	vector< pair<int, int> > shortestDistances(vertices + 1);
	// shortestDistances is a vector of pairs
	// pair.first -> the shortest distance from start vertex
	// pair.second -> parent vertex in the shortest path

	int startVertex;

	cout << "\nEnter a Start Vertex -\n";
	cin >> startVertex;

	int returnValue = bellmanFord(adjacencyList, vertices, startVertex, shortestDistances);

	if (returnValue == -1) {
		cout << "No Negative Cycles exist in the Graph -\n";
	}
	else {
		cout << "Negative Cycles exists in the Graph -\n";
		// The Bellman-Ford Algorithm does not work with negative cycles,
		// all it can do is merely detect them, so when a negative cycle
		// is detected, the shortestDistances vector has wrong values

		PrintNegativeCycle(shortestDistances, shortestDistances[returnValue].second
			, returnValue);

		return 0;
	}

	cout << "\n\nVertex    Shortest Distance to Vertex %d     Parent Vertex-\n", startVertex;
	for (int i = 1; i <= vertices; ++i) {
		cout << i, "\t", shortestDistances[i].first, "\t\t\t\t",
			shortestDistances[i].second, "\n";
	}

	return 0;
}