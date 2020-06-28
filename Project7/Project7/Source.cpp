#include <cstdio>
#include <climits>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include "locale.h"
using namespace ::std;



void PrintNegativeCycle(vector< pair<int, int> > shortestDistances, int vertex, int startVertex)
{
<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
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

	for (i = 1; i <= vertices - 1; ++i) {
		for (j = 1; j <= vertices; ++j) {
			traverse = adjacencyList[j].begin();

			while (traverse != adjacencyList[j].end()) {
				if (shortestDistances[j].first == INT_MAX) {
					++traverse;
					continue;
				}

				if ((*traverse).second + shortestDistances[j].first <
					shortestDistances[(*traverse).first].first) {
					shortestDistances[(*traverse).first].first = (*traverse).second
						+ shortestDistances[j].first;
					shortestDistances[(*traverse).first].second = j;
				}

				++traverse;
			}
		}
	}

	for (j = 1; j <= vertices; ++j) {
		traverse = adjacencyList[j].begin();

		while (traverse != adjacencyList[j].end()) {
			if ((*traverse).second + shortestDistances[j].first <
				shortestDistances[(*traverse).first].first) {
				return j;
			}

			++traverse;
		}
	}

	return -1;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int vertices, edges, v1, v2, weight;

	setlocale(LC_CTYPE, "Russian");

	cout << "Введите количество вершин: -\n";
	cin >> vertices;

	cout << "Введите количество ребер: -\n";
	cin >> edges;

	vector< list< pair<int, int> > > adjacencyList(vertices + 1);

	cout << "Вводите данные в следующем формате: \n"
		<< "Начальная вершина - нажмите Enter\n"
		<< "Конечная вершина - нажмите Enter\n"
		<< "Вес ребра - нажмите Enter\n"
		<< "Повторите это действие для каждого ребра\n";

	for (int i = 1; i <= edges; ++i) {
		cin >> v1 >> v2 >> weight;

		adjacencyList[v1].push_back(make_pair(v2, weight));
	}

	cout << "\nСписок смежностей:-\n";
	for (int i = 1; i < adjacencyList.size(); ++i) {
		cout << "adjacencyList[" << i << "] ";

		list< pair<int, int> >::iterator itr = adjacencyList[i].begin();

		while (itr != adjacencyList[i].end()) {
			cout << " -> " << (*itr).first << "(" << (*itr).second << ")";
			++itr;
		}
		cout << "\n";
	}

	vector< pair<int, int> > shortestDistances(vertices + 1);

	int startVertex;

	cout << "\nВведите начальную (первую) вершину -\n";
	cin >> startVertex;

	int returnValue = bellmanFord(adjacencyList, vertices, startVertex, shortestDistances);

	if (returnValue == -1) {
		cout << "Отрицательных ребер не найдено. -\n";
	}
	else {
		cout << "На данном графе присутствуют отрицательные ребра. -\n";

		PrintNegativeCycle(shortestDistances, shortestDistances[returnValue].second
			, returnValue);

		return 0;
	}

	cout << "\n\nВершина    Кратчайший путь до вершины %d     Предыдущая вершина-\n", startVertex;
	for (int i = 1; i <= vertices; ++i) {
		cout << i << "\t" << shortestDistances[i].first << "\t\t\t\t" <<
			shortestDistances[i].second << "\n";
	}

	return 0;
}