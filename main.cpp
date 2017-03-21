#include <iostream>
#include <fstream>
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
Node* create_tree(ifstream&);
void print_path(Node*, ostream&);
bool contains(deque<EdgeTrace>, EdgeTrace);
bool contains(vector<EdgeTrace>, EdgeTrace);

int main()
{
	ifstream in;
	in.open("triangle_test.txt");
	
	Node* test_tree = create_tree(in);

	in.close();
	in.open("triangle.txt");

	Node* tree = create_tree(in);

	in.close();

	Node* n = breadth_first_search(test_tree, 9);

	print_path(n, cout);

	n = breadth_first_search(tree, 93);

	print_path(n, cout);

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
		
		int test = q.front().node->id;

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

Node* create_tree(ifstream& in)
{
	int level = 2;
	int input;
	in >> input;
	Node* root = new Node(input);
	vector<Node*>* level_above = new vector<Node*>(1);
	vector<Node*>* current_level = nullptr;
	(*level_above)[0] = root;

	while (!in.eof())
	{

		current_level = new vector<Node*>(level);
		for (int i = 0; i < level; i++)
		{
			in >> input;
			Node* node = new Node(input);
			(*current_level)[i] = node;
			
			// if this is not the first node in the layer
			if (i > 0)
			{
				// add an edge from the node to its upper left
				(*level_above)[i - 1]->edges.push_back(node);
			}
			// if this is not the last node in the layer
			if (i < level - 1)
			{
				// add an edge from the node to its upper right
				(*level_above)[i]->edges.push_back(node);
			}
		}
		level++;
		delete level_above;
		level_above = current_level;
	}
	delete current_level;
	return root;
}

void print_path(Node* n, ostream& out)
{
	out << int(n->id);

	while (!n->edges.empty())
	{
		out << " --> " << int(n->edges[0]->id);
		n = n->edges[0];
	}
	out << endl;
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
