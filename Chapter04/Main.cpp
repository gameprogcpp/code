// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE.txt for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include <vector>
#include <queue>
#include <iostream>

struct GraphNode
{
	// Adjacency list
	std::vector<GraphNode*> mAdjacent;
	// Previous node visited on path
	GraphNode* mParent;
};

struct Graph
{
	// A graph contains nodes
	std::vector<GraphNode*> mNodes;
};

struct WeightedEdge
{
	// Which nodes are connected by this edge?
	struct WeightedGraphNode* mFrom;
	struct WeightedGraphNode* mTo;
	// Weight of this edge
	float mWeight;
};
struct WeightedGraphNode
{
	std::vector<WeightedEdge*> mEdges;
	// Edge from parent to me
	WeightedEdge* mParentEdge;
	float f;
	float g;
	float h;
};
struct WeightedGraph
{
	std::vector<WeightedGraphNode*> mNodes;
};

float ComputeHeuristic(WeightedGraphNode* a, WeightedGraphNode* b)
{
	return 0.0f;
}

bool AStar(WeightedGraph& g, WeightedGraphNode* start,
		  WeightedGraphNode* goal)
{
	// Reset mParentEdge for all nodes
	for (WeightedGraphNode* node : g.mNodes)
	{
		node->mParentEdge = nullptr;
	}
	
	// Open/closed sets
	std::vector<WeightedGraphNode*> openSet;
	std::vector<WeightedGraphNode*> closedSet;
	
	// Set current node to start, and add to closed set
	WeightedGraphNode* current = start;
	closedSet.emplace_back(current);
	
	do
	{
		// Add adjacent nodes to open set
		for (WeightedEdge* edge : current->mEdges)
		{
			// Only check nodes that aren't in the closed set
			auto iter = std::find(closedSet.begin(), closedSet.end(),
								  edge->mTo);
			if (iter == closedSet.end())
			{
				iter = std::find(openSet.begin(), openSet.end(), edge->mTo);
				if (iter == openSet.end())
				{
					// Not in the open set, so set parent
					WeightedGraphNode* neighbor = edge->mTo;
					neighbor->mParentEdge = edge;
					neighbor->h = ComputeHeuristic(neighbor, goal);
					// g(x) is the parent's g plus cost of traversing edge
					neighbor->g = current->g + edge->mWeight;
					neighbor->f = neighbor->g + neighbor->h;
					openSet.emplace_back(neighbor);
				}
				else
				{
					WeightedGraphNode* neighbor = edge->mTo;
					// Compute g(x) cost if current becomes the parent
					float newG = current->g + edge->mWeight;
					if (newG < current->g)
					{
						// Adopt this node
						neighbor->mParentEdge = edge;
						neighbor->g = newG;
						// f(x) changes because g(x) changes
						neighbor->f = neighbor->g + neighbor->h;
					}
				}
			}
		}
		
		// If open set is empty, all possible paths are exhausted
		if (openSet.empty())
		{
			break;
		}
		
		// Find lowest cost node in open set
		auto iter = std::min_element(openSet.begin(), openSet.end(),
									 [](WeightedGraphNode* a, WeightedGraphNode* b) {
										 return a->f < b->f;
									 });
		// Set to current and move from open to closed
		current = *iter;
		openSet.erase(iter);
		closedSet.emplace_back(current);
	}
	while (current != goal);
	
	// Did we find a path?
	return (current == goal) ? true : false;
}

bool GBFS(WeightedGraph& g, WeightedGraphNode* start,
		  WeightedGraphNode* goal)
{
	// Reset mParentEdge for all nodes
	for (WeightedGraphNode* node : g.mNodes)
	{
		node->mParentEdge = nullptr;
	}
	
	// Open/closed sets
	std::vector<WeightedGraphNode*> openSet;
	std::vector<WeightedGraphNode*> closedSet;
	
	// Set current node to start, and add to closed set
	WeightedGraphNode* current = start;
	closedSet.emplace_back(current);
	
	do
	{
		// Add adjacent nodes to open set
		for (WeightedEdge* edge : current->mEdges)
		{
			// Only check nodes that aren't in the closed set
			auto iter = std::find(closedSet.begin(), closedSet.end(),
								  edge->mTo);
			if (iter == closedSet.end())
			{
				// Set the adjacent node's parent edge
				edge->mTo->mParentEdge = edge;
				iter = std::find(openSet.begin(), openSet.end(), edge->mTo);
				if (iter == openSet.end())
				{
					// Compute the heuristic for this node, and add to open set
					edge->mTo->h = ComputeHeuristic(edge->mTo, goal);
					openSet.emplace_back(edge->mTo);
				}
			}
		}
		
		// If open set is empty, all possible paths are exhausted
		if (openSet.empty())
		{
			break;
		}
		
		// Find lowest cost node in open set
		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[](WeightedGraphNode* a, WeightedGraphNode* b) {
				return a->h < b->h;
		});
		// Set to current and move from open to closed
		current = *iter;
		openSet.erase(iter);
		closedSet.emplace_back(current);
	}
	while (current != goal);
	
	// Did we find a path?
	return (current == goal) ? true : false;
}

bool BFS(Graph& graph, GraphNode* start, GraphNode* goal)
{
	// Reset mParent for all nodes
	for (GraphNode* node : graph.mNodes)
	{
		node->mParent = nullptr;
	}
	
	// Whether or not we found a path
	bool pathFound = false;
	// Nodes to consider
	std::queue<GraphNode*> q;
	// Enqueue the first node
	q.emplace(start);
	
	while (!q.empty())
	{
		// Dequeue a node
		GraphNode* current = q.front();
		q.pop();
		if (current == goal)
		{
			pathFound = true;
			break;
		}
		
		// Enqueue adjacent nodes that aren't already queued
		for (GraphNode* node : current->mAdjacent)
		{
			// If the parent is null, it hasn't been enqueued
			// (except for the start node)
			if (node->mParent == nullptr && node != start)
			{
				// Enqueue this node, setting its parent
				node->mParent = current;
				q.emplace(node);
			}
		}
	}
	
	return pathFound;
}

void test()
{
	WeightedGraph g;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			WeightedGraphNode* node = new WeightedGraphNode;
			g.mNodes.emplace_back(node);
		}
	}
	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			WeightedGraphNode* node = g.mNodes[i*5 + j];
			if (i > 0)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[(i - 1) * 5 + j];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (i < 4)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[(i + 1) * 5 + j];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (j > 0)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[i*5 + j - 1];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
			if (j < 4)
			{
				WeightedEdge* e = new WeightedEdge;
				e->mFrom = node;
				e->mTo = g.mNodes[i*5 + j + 1];
				e->mWeight = 1.0f;
				node->mEdges.emplace_back(e);
			}
		}
	}
	bool found = AStar(g, g.mNodes[0], g.mNodes[9]);
	std::cout << found << '\n';
}

struct GameState
{
	// (For tic-tac-toe, array of board)
	enum SquareState { Empty, X, O };
	SquareState mBoard[3][3];
};

struct GTNode
{
	// Children nodes
	std::vector<GTNode*> mChildren;
	// State of game
	GameState mState;
};

void GenStates(GTNode* root, bool xPlayer)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (root->mState.mBoard[i][j] == GameState::Empty)
			{
				GTNode* node = new GTNode;
				root->mChildren.emplace_back(node);
				node->mState = root->mState;
				node->mState.mBoard[i][j] = xPlayer ? GameState::X : GameState::O;
				GenStates(node, !xPlayer);
			}
		}
	}
}

float GetScore(GameState& state)
{
	// Are any of the rows the same?
	for (int i = 0; i < 3; i++)
	{
		bool same = true;
		GameState::SquareState v = state.mBoard[i][0];
		for (int j = 1; j < 3; j++)
		{
			if (state.mBoard[i][j] != v)
			{
				same = false;
			}
		}
		
		if (same)
		{
			if (v == GameState::X)
			{
				return 1.0f;
			}
			else
			{
				return -1.0f;
			}
		}
	}
	
	// Are any of the columns the same?
	for (int j = 0; j < 3; j++)
	{
		bool same = true;
		GameState::SquareState v = state.mBoard[0][j];
		for (int i = 1; i < 3; i++)
		{
			if (state.mBoard[i][j] != v)
			{
				same = false;
			}
		}
		
		if (same)
		{
			if (v == GameState::X)
			{
				return 1.0f;
			}
			else
			{
				return -1.0f;
			}
		}
	}
	
	// What about diagonals?
	if (((state.mBoard[0][0] == state.mBoard[1][1]) &&
		(state.mBoard[1][1] == state.mBoard[2][2])) ||
		((state.mBoard[2][0] == state.mBoard[1][1]) &&
		 (state.mBoard[1][1] == state.mBoard[0][2])))
	{
		if (state.mBoard[1][1] == GameState::X)
		{
			return 1.0f;
		}
		else
		{
			return -1.0f;
		}
	}
	// We tied
	return 0.0f;
}

float MinPlayer(GTNode* node);

float MaxPlayer(GTNode* node)
{
	// If this is a leaf, return score
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	
	float maxValue = -std::numeric_limits<float>::infinity();
	// Find the subtree with the maximum value
	for (GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, MinPlayer(child));
	}
	return maxValue;
}

float MinPlayer(GTNode* node)
{
	// If this is a leaf, return score
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	
	float minValue = std::numeric_limits<float>::infinity();
	// Find the subtree with the minimum value
	for (GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, MaxPlayer(child));
	}
	return minValue;
}

GTNode* MinimaxDecide(GTNode* root)
{
	// Find the subtree with the maximum value, and save the choice
	GTNode* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	for (GTNode* child : root->mChildren)
	{
		float v = MinPlayer(child);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}

float AlphaBetaMin(GTNode* node, float alpha, float beta);

float AlphaBetaMax(GTNode* node, float alpha, float beta)
{
	// If this is a leaf, return score
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	
	float maxValue = -std::numeric_limits<float>::infinity();
	// Find the subtree with the maximum value
	for (GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, AlphaBetaMin(child, alpha, beta));
		if (maxValue >= beta)
		{
			return maxValue; // Beta prune
		}
		alpha = std::max(maxValue, alpha);
	}
	return maxValue;
}

float AlphaBetaMin(GTNode* node, float alpha, float beta)
{
	// If this is a leaf, return score
	if (node->mChildren.empty())
	{
		return GetScore(node->mState);
	}
	
	float minValue = std::numeric_limits<float>::infinity();
	// Find the subtree with the minimum value
	for (GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, AlphaBetaMax(child, alpha, beta));
		if (minValue <= alpha)
		{
			return minValue; // Alpha prune
		}
		beta = std::min(minValue, beta);
	}
	return minValue;
}

GTNode* AlphaBetaDecide(GTNode* root)
{
	// Find the subtree with the maximum value, and save the choice
	GTNode* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	float beta = std::numeric_limits<float>::infinity();
	for (GTNode* child : root->mChildren)
	{
		float v = AlphaBetaMin(child, maxValue, beta);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}

void test2()
{
	GTNode* root = new GTNode;
	root->mState.mBoard[0][0] = GameState::O;
	root->mState.mBoard[0][1] = GameState::Empty;
	root->mState.mBoard[0][2] = GameState::X;
	root->mState.mBoard[1][0] = GameState::X;
	root->mState.mBoard[1][1] = GameState::O;
	root->mState.mBoard[1][2] = GameState::O;
	root->mState.mBoard[2][0] = GameState::X;
	root->mState.mBoard[2][1] = GameState::Empty;
	root->mState.mBoard[2][2] = GameState::Empty;
	
	GenStates(root, true);
	GTNode* choice = AlphaBetaDecide(root);
	std::cout << choice->mChildren.size();
}

int main(int argc, char** argv)
{
	Game game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}
