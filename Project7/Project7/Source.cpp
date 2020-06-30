#include <cstdio>
#include <climits>
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include "locale.h"

using namespace ::std;

struct sard {
	int vertex;
	struct sard* next;
	struct sard* prev;
};

void PrintNegativeCycle(vector< pair<int, int> > shortestDistances, int vertex, int startVertex)//Поиск Негативного цикла
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
int bellmanFord(vector< list< pair<int, int> > > adjacencyList,
	int vertices, int startVertex, vector< pair<int, int> >& shortestDistances)
	//Алгоритм Форда-Беллмана
{
	list< pair<int, int> >::iterator traverse;//переборка элементов
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

				if ((*traverse).second + shortestDistances[j].first < shortestDistances[(*traverse).first].first) {
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
	int vertices, edges, v1, v2, weight;//задаются кол-во вершин, ребер, вершины ребра, вес ребра


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

	cout << "\nСписок смежностей:-\n";// показываем соединненые вершины и с кем они соединены 
	for (int i = 1; i < adjacencyList.size(); ++i) {
		cout << "adjacencyList[" << i << "] ";

		list< pair<int, int> >::iterator itr = adjacencyList[i].begin();

		while (itr != adjacencyList[i].end()) {
			cout << " -> " /*<< (*itr).first << "(" */ << (*itr).second << ")";
			++itr;
		}
		cout << "\n";
	}

	vector< pair<int, int> > shortestDistances(vertices + 1);

	int startVertex;

	cout << "\nВведите начальную (первую) вершину -\n";
	cin >> startVertex;// вводим вершину от которой необходимо найти кратчайший путь до других вершин

	int returnValue = bellmanFord(adjacencyList, vertices, startVertex, shortestDistances);// передача данный функции ФБ

	if (returnValue == -1) {
		cout << "Отрицательных ребер не найдено. -\n";
	}
	else {
		cout << "На данном графе присутствуют отрицательные ребра. -\n";

		PrintNegativeCycle(shortestDistances, shortestDistances[returnValue].second
			, returnValue);

		return 0;
	}

	/*for (int i = 1; i <= vertices; i++)
	{
		if(shortestDistances[i].second != shortestDistances[i-1].second&& shortestDistances[i].first != shortestDistances[i - 1].first)cout <<shortestDistances[i].second << "-";

	}*/
	cout << vertices;

	cout << "\n\nВершина    Кратчайший путь до вершины       Предыдущая вершина-\n", startVertex;
	for (int i = 1; i <= vertices; ++i) {
		cout << i << "\t" << shortestDistances[i].first << "\t\t\t\t" <<
			shortestDistances[i].second << "\n";
	}
	int i = vertices;
	sard* way;
	way = (sard*)std::malloc(sizeof(sard));

	while (i != 1)
	{
		way->vertex = i;

		cout << i << "-";
		i = shortestDistances[i].second;
		if (i == 1)cout << i;

	}
	return 0;
}