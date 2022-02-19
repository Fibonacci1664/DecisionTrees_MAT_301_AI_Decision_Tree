#pragma once

#include <vector>
#include <functional>

class Node
{
public:

	// Constructor - saves the custom function passed into the class when created
	Node(std::function<int()> new_custom_func) : custom_func(new_custom_func) {}

	// Basic node just calls its custom function when run() is called
	virtual void run()
	{
		custom_func();
	}

	// Adds a child node to a vector
	void addChildNode(Node* new_child) { child_nodes.push_back(new_child); }

protected:
	std::vector<Node*> child_nodes;		// Vector of child nodes (branches or leaves)
	std::function<int()> custom_func;	// Custom function that tells the node what to do
};

class DecisionNode : public Node
{
public:

	// Constructor - saves the custom function passed into the class when created
	DecisionNode(std::function<int()> new_custom_func) : Node(new_custom_func) {}

	// Override the run() function
	// custom_func() needs to be designed to return an index to which child branch to run
	// Runs that child branch if it can access it
	void run() override
	{
		int index = custom_func();

		if (index >= 0 && index < child_nodes.size())
		{
			Node* child = child_nodes[index];
			child->run();
		}
	}
};