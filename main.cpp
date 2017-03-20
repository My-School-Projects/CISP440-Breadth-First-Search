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
	bool operator==(Node n)
	{
		return this->id == n.id;
	}
};

class EdgeTrace
{
public:
	Node* node;
	Node* origin;
	EdgeTrace(Node* node, Node* origin = nullptr)
	{
		this->node = node;
		this->origin = origin;
	}
	bool operator==(EdgeTrace e)
	{
		return this->node->id == e.node->id;
	}
};

vector<EdgeTrace> bfs(Node*, char);
bool contains(deque<EdgeTrace>, EdgeTrace);
bool contains(vector<EdgeTrace>, EdgeTrace);

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

	vector<EdgeTrace> vec = bfs(a, 'F');

	for (EdgeTrace trace : vec)
	{
		cout << trace.node->id << " <-- ";
		if (trace.origin)
			cout << trace.origin->id;
		cout << endl;
	}

	system("pause");
}

vector<EdgeTrace> bfs(Node* root, char c)
{
	vector<EdgeTrace> visited;
	deque<EdgeTrace> q;

	q.push_back(EdgeTrace(root));

	while (!q.empty())
	{
		// the current node is the node at the front of the queue

		// mark the current node as visited
		visited.push_back(q.front());
		
		// if the current node is the one we're looking for, return
		if (q.front().node->id == c)
			return visited;

		// for each edge of the current node

		for (unsigned i = 0; i < q.front().node->edges.size(); i++)
		{
			// if the node on that edge has not already been visited, and is not already in the queue
			if (!contains(visited, EdgeTrace(q.front().node->edges[i])) && !contains(q, EdgeTrace(q.front().node->edges[i])))
			{
				// push that node to q
				q.emplace_back(q.front().node->edges[i], q.front().node);
			}
		}
		// finished with the current node - pop it
		q.pop_front();
	}

	// we didn't find the node - return an empty list
	return vector<EdgeTrace>();
}

///
/// Checks if q contains n
///
bool contains(deque<EdgeTrace> q, EdgeTrace e)
{
	return find(q.begin(), q.end(), e) != q.end();
}

///
/// Checks if v contains e
///
bool contains(vector<EdgeTrace> v, EdgeTrace e)
{
	return find(v.begin(), v.end(), e) != v.end();
}
