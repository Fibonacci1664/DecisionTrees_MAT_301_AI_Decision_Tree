#include "Node.h"
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

/*

											 ROOT
									   <Enemy Visible>
									 0	 /		   \   1
									 NO /			\ YES
									   /			 \
							  <Enemy Audible>	<Enemy < 10m Away>
						   0	/		\	1	0	/		\   1
						   NO  /		 \ YES  NO /		 \ YES
							  /			  \		  /			  \
					[DO NOTHING] [CREEP ACTION]  /			   \
												/				\
											   /				 \
										<Enemy on Flank>	[ATTACK ACTION]
										0	/		\   1
										NO /		 \ YES
										  /			  \
								  [ATTACK ACTION]	[MOVE ACTION]

	*/

int main()
{
	srand(time(NULL));

	// Create functions / lambdas for each unique node in the tree
	auto rootNodeEnemyVisible = []() -> int
	{
		int enemyIsVisible = rand() % 2;

		if (enemyIsVisible)
		{
			// Yes branch
			std::cout << "The enemy is visible\n";
			return 1;
		}
		else
		{
			// No branch
			std::cout << "The enemy is not visible\n";
			return 0;
		}
	};

	auto enemyAudibleNode = []() -> int
	{
		int enemyIsAudible = rand() % 2;

		if (enemyIsAudible)
		{
			// Yes branch
			std::cout << "The enemy is audible\n";
			return 1;
		}
		else
		{
			// No branch
			std::cout << "The enemy is not audible\n";
			return 0;
		}
	};

	auto enemyDistanceNode = []() -> int
	{
		int enemyLessThan10m = rand() % 2;

		if (enemyLessThan10m)
		{
			// Yes branch
			std::cout << "The enemy is < 10m away\n";
			return 1;
		}
		else
		{
			// No branch
			std::cout << "The enemy is > 10m away\n";
			return 0;
		}
	};

	auto enemyPositionNode = []() -> int
	{
		int enemyIsFlanked = rand() % 2;

		if (enemyIsFlanked)
		{
			// Yes branch
			std::cout << "The enemy is on my flank\n";
			return 1;
		}
		else
		{
			// No branch
			std::cout << "The enemy is not on my flank\n";
			return 0;
		}
	};

	auto creepLeaf = []() -> int
	{
		std::cout << "You begin to quietly creep past the enemy\n";

		return 0;
	};

	auto moveLeaf = []() -> int
	{
		std::cout << "You move past the enemy\n";

		return 0;
	};

	auto attackLeaf = []() -> int
	{
		std::cout << "You attack the enemy\n";

		return 0;
	};

	auto doNothingLeaf = []() -> int
	{
		std::cout << "You do nothing\n";

		return 0;
	};

	// Create instances of decision nodes and leaf nodes as appropriate
	DecisionNode rootNode(rootNodeEnemyVisible);
	DecisionNode audibleNode(enemyAudibleNode);
	DecisionNode distanceNode(enemyDistanceNode);
	DecisionNode positionNode(enemyPositionNode);

	Node creepAction(creepLeaf);
	Node moveAction(moveLeaf);
	Node attackAction(attackLeaf);
	Node doNothingAction(doNothingLeaf);

	// Add the leaf nodes as children to the connected decision nodes
	rootNode.addChildNode(&audibleNode);			// Index	: 0
	rootNode.addChildNode(&distanceNode);			//			: 1

	audibleNode.addChildNode(&doNothingAction);		//			: 0
	audibleNode.addChildNode(&creepAction);			//			: 1
	
	distanceNode.addChildNode(&positionNode);		//			: 0
	distanceNode.addChildNode(&attackAction);		//			: 1	

	positionNode.addChildNode(&attackAction);		//			: 0
	positionNode.addChildNode(&moveAction);			//			: 1

	// Run the root node of the tree

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		std::cout << '\n';
		rootNode.run();
		std::cout << '\n';
	}
}