#include <iostream>
using namespace std;
const int V = 8;

//Алгоритм Дейкстра
void Dijkstra(int GR[V][V], int st)
{
	int distance[V], index, u, m = st + 1;
	bool visited[V];

	for (int i = 0; i < V; i++)
	{
		distance[i] = INT_MAX; visited[i] = false;
	}

	distance[st] = 0; 

	for (int count = 0; count < V - 1; count++) 
	{
		int min = INT_MAX;

		for (int i = 0; i < V; i++) 
		{

			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; index = i;
			}
		}

		u = index; 
		visited[u] = true;

		for (int i = 0; i < V; i++) 
		{
			if (!visited[i] && GR[u][i] && distance[u] != INT_MAX && distance[u] + GR[u][i] < distance[i])
			{
				distance[i] = distance[u] + GR[u][i];
			}
		}	
	}

	cout << "Кратчайшие расстояния: \t\n";

	for (int i = 0; i < 8; i++)
	{
		if (distance[i] != INT_MAX)
		{
			cout << m << " --> " << i + 1 << " = " << distance[i] << endl;
		}

		else
		{
			cout << m << " --> " << i + 1 << " = " << "вершина недоступна" << endl;
		}
	}

}


void main()
{
	setlocale(LC_ALL, "Rus");
	int start;
	int GR[V][V] = {
			{0, 5, 2,  0, 0, 0, 0, 0},
			{5, 0, 2,  3, 2, 0, 0, 0},
			{2, 2, 0, 10, 7, 0, 0, 0},
			{0, 3, 10, 0, 0, 5, 5, 0},
			{0, 2,  7, 0, 0, 6, 4, 0},
			{0, 0,  0, 5, 6, 0, 0, 3},
			{0, 0,  0, 5, 4, 0, 0, 2},
			{0, 0,  0, 0, 0, 3, 2, 0}};

	char startSym;
	cout << "Стартовая вершина: "; 
	cin >> startSym;
	char word[8] = { '1','2','3','4','5','6','7','8'};

	for (int i = 0; i < 8; i++)
	{
		if (word[i] == startSym)
		{
			start = i;
		}
	}

	Dijkstra(GR, start);
}