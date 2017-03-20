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

Node* breadth_first_search(Node*, char);
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

	Node* n = breadth_first_search(a, 'F');

	cout << n->id;

	while (!n->edges.empty())
	{
		cout << " --> " << n->edges[0]->id;
		n = n->edges[0];
	}
	cout << endl;

	system("pause");
}

Node* breadth_first_search(Node* root, char c)
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
		{
			// reconstruct path in reverse order
			
			// the final node (the one searched for)
			Node* current_node = new Node(visited.back().node->id);
			// the node before the final node
			Node* prev_node = new Node(visited.back().origin->id);
			prev_node->edges.push_back(current_node);
			// iterate backwards over visited
			for (auto it = visited.rbegin(); it != visited.rend(); it++)
			{
				// locate the most recent reference to the current node
				if (it->node->id == current_node->id)
				{
					// construct a node behind the currend node
					prev_node = new Node(it->origin->id);
					// point it forward to the current node
					prev_node->edges.push_back(current_node);
					
					current_node = prev_node;

					if (current_node->id == root->id)
						return current_node;
				}
			}
		}

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
	return new Node(NULL);
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
