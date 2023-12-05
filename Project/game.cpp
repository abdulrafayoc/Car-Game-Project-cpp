#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

#include "Graph.h"

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

using namespace std;




void dijkstra(Graph& maze, Car& ai)
{
	int gridSize = maze.gridSize;

	// initialize the distance array
	int** distance = new int* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		distance[i] = new int[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			distance[i][j] = INT_MAX;
		}
	}

	// initialize the visited array
	bool** visited = new bool* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		visited[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			visited[i][j] = false;
		}
	}

	// initialize the parent array
	Stack** parent = new Stack * [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		parent[i] = new Stack[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			parent[i][j].push(i, j);
		}
	}

	// initialize the priority queue
	PriorityQueue pq;

	// push the starting vertex in the priority queue
	pq.enqueue(ai.x, ai.y, 0);

	// set the distance of the starting vertex to 0
	distance[ai.x][ai.y] = 0;

	// while the priority queue is not empty
	while (!pq.isEmpty())
	{
		// get the top element from the priority queue
		int x = pq.frontX();
		int y = pq.frontY();
		int d = pq.frontD();

		// pop the top element from the priority queue
		pq.dequeue();

		// if the vertex is already visited, continue
		if (visited[x][y])
		{
			continue;
		}

		// mark the vertex as visited
		visited[x][y] = true;

		// if the vertex is the finish vertex, break
		if (maze.adjacencyList[x][y].finish)
		{
			break;
		}

		// if the vertex is not the finish vertex, continue

		Node* temp = maze.adjacencyList[x][y].head;
		while (temp != nullptr)
		{
			// if the vertex is not visited
			if (!visited[temp->x][temp->y])
			{
				// if the distance of the vertex is greater than the distance of the current vertex + 1
				if (distance[temp->x][temp->y] > d + temp->weight)
				{
					cout << "x: " << temp->x << " y: " << temp->y << endl;
					cout << "d: " << d << " weight: " << temp->weight << endl;
					// update the distance of the vertex

					distance[temp->x][temp->y] = d + temp->weight;

					// push the vertex in the priority queue
					pq.enqueue(temp->x, temp->y, distance[temp->x][temp->y]);

					// update the parent of the vertex
					parent[temp->x][temp->y] = parent[x][y];
					parent[temp->x][temp->y].push(temp->x, temp->y);


				}

			}
			temp = temp->next;
		}





	}



	printGrid(maze);

	// print the path
	cout << endl
		<< "Path: " << endl;
	Stack path = parent[gridSize - 1][gridSize - 1];

	while (!path.isEmpty())
	{
		cout << path.topX() << " " << path.topY() << endl;
		path.pop();
	}

	while (!path.isEmpty())
	{
		int xx = path.topX();
		int yy = path.topY();

		int x = ai.x;
		int y = ai.y;
		maze.adjacencyList[xx][yy].car = true;

		// if move up
		if (x == xx && y == yy - 1)
		{
			ai.cordinates(x, y);
			ai.updateScore(maze);
		}
		// if move down
		else if (x == xx && y == yy + 1)
		{
			ai.cordinates(x, y);
			ai.updateScore(maze);

		}
		// if move left
		else if (x == xx - 1 && y == yy)
		{
			ai.cordinates(x, y);
			ai.updateScore(maze);
		}
		// if move right
		else if (x == xx + 1 && y == yy)
		{
			ai.cordinates(x, y);
			ai.updateScore(maze);
		}


		path.pop();

		//system("cls");

		cout << "\033[42m";
		cout << "\033[30m";
		cout << "\n	Mr Dijkstra is driving the car";
		cout << "\n	Press `esc` to Quit";
		cout << endl;
		cout << "\n	Score: " << ai.score;
		cout << "\033[37m";

		cout << endl
			<< endl
			<< endl;

		printGrid(maze);
		ai.updateScore(maze);
		Sleep(400);
	}


}


void showPath(Stack path, Graph& maze)
{

}

void play(Graph& maze, Car& player)
{
	while (1)
	{
		cout << "\033[42m";
		cout << "\033[30m";
		cout << "\n	Use arrow keys to move the car";
		cout << "\n	Press `esc` to Quit";
		cout << endl;
		cout << "\n	Score: " << player.score;
		cout << "\033[37m";

		cout << endl
			<< endl
			<< endl;

		printGrid(maze);
		int c = 0;

		switch ((c = _getch()))
		{
		case KEY_UP:
			player.moveUp(maze);

			break;
		case KEY_DOWN:
			player.moveDown(maze);

			break;
		case KEY_LEFT:
			player.moveLeft(maze);

			break;
		case KEY_RIGHT:
			player.moveRight(maze);

			break;
		case 27:
			exit(0);

			break;
		default:
			cout << endl
				<< "		Invalid input" << endl;

			break;
		}
		system("cls");
	}
}



int main()
{
	int gridSize = 10;

	Graph maze(gridSize);

	string name;
	cout << "Enter Name: ";
	getline(cin, name);


	// maze.printVertices();

	maze.adjacencyList[0][0].car = true;
	maze.adjacencyList[gridSize - 1][gridSize - 1].finish = true;

	Car player;
	Car AI;

	player.name = name;

	// menu
	cout << "1. Play" << endl;
	cout << "2. AI" << endl;

	cout << "Enter your choice: ";
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		//auto start_time = startTimer();
		play(maze, player);
		break;
	}
	case 2:
	{
		dijkstra(maze, AI);
		cout << "function successfull";
	}
	default:
		break;
	}



	return 0;
}