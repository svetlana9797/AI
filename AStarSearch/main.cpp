#include "Node.h"

int dirX[4] = {0, 0, 1, -1}; // RIGHT-LEFT-DOWN-UP
int dirY[4] = {1, -1, 0, 0}; // RIGHT-LEFT-DOWN-UP

//for each node keep its cost
map<Node, NodeInfo> visited;
//checks if the coordinates are correct
bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < 3 && y < 3;
    }

bool getZeroPos(const Node &node, int &zX, int &zY) {
		zX = zY = -1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				if (!node.A[i][j]) {
					zX = i, zY = j;
					return true;
				}
		}
		return false;
		}

 int Manhattan_Heuristic(const Node &a, const Node &b) {
		int sum = 0;
		int cX[10]; // coordinates of X
		int cY[10]; // coordinates of Y

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
                    //we keep the x,y indexes in 2 arrays
				cX[a.A[i][j]] = i;
				cY[a.A[i][j]] = j;
			}
		}

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (b.A[i][j]) // we check for all the values except 0
					sum += abs(cX[b.A[i][j]] - i) + abs(cY[b.A[i][j]] - j); //|xi-xj| + |yi - yj|
		return sum;
	}


int AStarSearch(const Node &Start, const Node &Goal) {
		int nExpanded = 0; //nodesExpanded

		priority_queue<pair<int, Node> > pQ;
		pQ.push({0, Start}); //in the beginning we push only the start
        visited[Start] = {false, 0}; //at the beginning the node is open
		while (!pQ.empty()) {
                //get the top element
			Node node = pQ.top().second;
			pQ.pop();
			++nExpanded;

			//NodeInfo &nodeInfo = visited[node];
			int nodeCost = visited[node].cost;
			visited[node].isClosed = true; //once we pop a node, it becomes closed

			//we reached the goal
			if (node == Goal) {
				break;
			}

			int zeroX = -1, zeroY = -1;
			getZeroPos(node, zeroX, zeroY);

			//check all possible directions for the next step
			for (int dir = 0; dir < 4; dir ++) {
				int zXnew = zeroX + dirX[dir];
				int zYnew = zeroY + dirY[dir];

				if (isValid(zXnew, zYnew)) {

					Node curr = node;
					//move the 'blank' field
					swap(curr.A[zeroX][zeroY], curr.A[zXnew][zYnew]);

					//bool isVisited = (visited.find(curr) != visited.end());//must check this
					bool isVisited = visited.find(curr) != visited.end();
					if (isVisited && visited[curr].isClosed)continue;//we skip the node if it is visited/closed

					int newCost = nodeCost + 1;
					if (!isVisited) {

						visited[curr] = {false, newCost};
						int f = newCost + Manhattan_Heuristic(curr, Goal);
						pQ.push({-f, curr});
					}
				}
			}

		}

		return nExpanded;
	}

void printNode(const Node &node)
{
    for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
				cout << (node.A[i][j]) << " ";
		cout << endl;
	}
	cout << " ----------- " << endl;
}

int main() {
	freopen("in.txt", "r", stdin);

	Node Start;
	Node Goal;

	int x;
	int count =0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
        {
            cin >> x;
            Start.A[i][j] = x;
            Goal.A[i][j] = count + 1;
            count++;
        }
        Goal.A[2][2] = 0;


	printNode(Start);
	printNode(Goal);

	AStarSearch(Start, Goal);

	cout << "Number of Steps: " <<visited[Goal].cost << endl;
	cout << endl;

}
