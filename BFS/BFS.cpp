#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
#include<vector>
#define INT_MAX 100
using namespace std;
typedef vector<vector<int>> matrix;

// queue node used in BFS
struct Node
{
	// (x, y) are the matrix cell coordinates
	// dist is the minimum distance from the source
	 int x, y, dist;
	 //keep track of the parent node
	 Node* parent;

	 //constructor
	 Node(int x, int y, int dist, Node* parent)
	 {
	     this->x=x;
         this->y=y;
         this->dist=dist;
         this->parent=parent;
	 }

};

// Below arrays details all 4 possible movements from a cell
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

// check if it is possible to go to position (row, col)
// from current position. The function returns false if (row, col)
// is not a valid position or has value 0 or it is already visited
bool isValid(matrix mat, matrix visited, int N, int row, int col)
{
	return (row >= 0) && (row < N) && (col >= 0) && (col < N)
		&& mat[row][col] && !visited[row][col];
}

void getTeleportCoordinates(matrix mat, int N, Node &node)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            //find the other cell with value 2 in the matrix
            if(mat[i][j]==2 & (i!=node.x || j!=node.y))
            {
                node.x=i;
                node.y=j;
                break;
            }
        }
    }
}

void printPath(Node &node, matrix mat, int N) {
        while (node.parent!=nullptr) {
            //mark the path to the solution in the matrix
            //mat[node.x][node.y] = 3;
            cout<<"( "<<node.x<<","<<node.y<<") ";
            //give a new vaue of our node
            node = *(node.parent);
        }
        //coordinates of the src
        cout<<"( "<<node.x<<","<<node.y<<") ";
    }

BFS(matrix mat, int N, int src_x, int src_y, int dest_x, int dest_y)
{
    // construct a matrix to keep track of visited cells
	matrix visited;

	// initially all cells are unvisited
	for(int i=0;i<N;i++)
    {
        visited.push_back(vector<int>());
        for(int j=0;j<N;j++)
            visited[i].push_back(0);
    }

	// create an empty queue
	queue<Node> q;

	// mark source cell as visited and enqueue the source node
	visited[src_x][src_y] = true;

	q.push(Node(src_x, src_y, 0, nullptr));

	// stores length of longest path from source to destination
	int min_dist = INT_MAX;
	Node node(0,0,0,nullptr);
	// run till queue is not empty
	while (!q.empty())
	{
		// pop front node from queue and process it
        node = q.front();
		q.pop();

		// if destination is found, update min_dist and stop
		if (node.x == dest_x && node.y == dest_y)
		{
			min_dist = node.dist;
			break;
		}

		//check if cell can teleport and if true change its coordinates
		if(mat[node.x][node.y]==2)
        {
            //teleport
            getTeleportCoordinates(mat, N, node);

            //make the teleport cell visited too
            visited[node.x][node.y]=true;

        }
		// check for all 4 possible movements from current cell
		// and enqueue each valid movement
		for (int k = 0; k < 4; k++)
		{
			// check if it is possible to go to position
			// (i + row[k], j + col[k]) from current position
			if (isValid(mat, visited, N, node.x + row[k], node.y + col[k]))
			{
				// mark next cell as visited and enqueue it, put the current node as parent
				visited[node.x + row[k]][node.y + col[k]] = true;
				//push in the queue the possible nodes and add the current node address as their parent
				q.push(Node(node.x + row[k], node.y + col[k], node.dist + 1, &node));
			}
		}
	}

	if (min_dist != INT_MAX)
    {
       cout << "The shortest path from source to destination "
				"has length " << min_dist;
       // printPath(node, mat, N);
    }

	else
		cout << "Destination can't be reached from given source";

}

int main()
{

    int N, k;
    cout<<"NxN matrix with k 0's\nInsert N,k\n";
    cin>>N>>k;

  /*  matrix mat =	{
		{ 1, 2, 0 },
		{ 1, 1, 1 },
		{ 2, 0, 1 }
	};
	*/

	matrix mat;
    cout<<"initialize matrix\n";
    int br=0; // indicates the number of 0's inserted in the matrix
    for(int i=0;i<N;i++)
    {
        mat.push_back(vector<int>());
        for(int j=0;j<N;j++)
        {
            int val;
            cin>>val;
            if(val==0)
                br++;
            if(br>k)
            {
               cerr<<"The number of 0's is bigger than k!\n";
               return -1;
            }

            mat[i].push_back(val);
        }
    }
    if(br<k)
    {
        cerr<<"The number of 0's is smaller than k!\n";
               return -1;
    }

    cout<<"matrix: \n";
    for (int i = 0; i < mat.size(); i++)
{
    for (int j = 0; j < mat[i].size(); j++)
    {
        cout << mat[i][j]<<" ";
    }
    cout<<endl;
}


    int src_x, src_y, dest_x, dest_y;
    cout<<"src(src_x, src_y)= ";
    cin>>src_x>>src_y;
    cout<<"dest(dest_x, dest_y)= ";
    cin>>dest_x>>dest_y;
    if(mat[src_x][src_y]==2 or mat[dest_x][dest_y]==2)
    {
        cout<<"src or dest cannot be with value 2!";
        return 0;
    }

    // Find shortest path from source to destination
     BFS(mat, N, src_x, src_y, dest_x, dest_y);

    return 0;
}
