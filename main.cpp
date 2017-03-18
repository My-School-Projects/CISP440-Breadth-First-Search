#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Node
{
public:
	char id;
	vector<Node*> edges;
	Node(char id)
	{
		this->id = id;
	}
};

vector<char> bfs(Node*);
bool contains(vector<char>, char);

int main()
{
	Node *a = new Node('A'), *b = new Node('B'), *c = new Node('C'),
		 *d = new Node('D'), *e = new Node('E'), *f = new Node('F');

	a->edges.push_back(c);
	a->edges.push_back(b);
	b->edges.push_back(a);
	b->edges.push_back(d);
	b->edges.push_back(e);
	c->edges.push_back(a);
	c->edges.push_back(f);
	d->edges.push_back(b);
	e->edges.push_back(b);
	e->edges.push_back(f);
	f->edges.push_back(c);
	f->edges.push_back(e);

	vector<char> vec = bfs(a);

	for (char c : vec)
	{
		cout << c << " ";
	}
	cout << endl;

	system("pause");
}

vector<char> bfs(Node* root)
{
	vector<char> visited;
	queue<Node*> q;

	q.push(root);

	while (!q.empty())
	{
		// the current node is the node at the front of the queue

		// mark the current node as visited
		visited.push_back(q.front()->id);

		// for each edge of the current node

		for (int i = 0; i < q.front()->edges.size(); i++)
		{
			// if the node on that edge has not already been visited
			if (!contains(visited, q.front()->edges[i]->id))
			{
				// push that node to q
				q.push(q.front()->edges[i]);
			}
		}
		// finished with the current node - pop it
		q.pop();
	}
	return visited;
}

bool contains(vector<char> vec, char c)
{
	return find(vec.begin(), vec.end(), c) != vec.end();
}
