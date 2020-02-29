#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include <algorithm>
#include <time.h>
using namespace std;

struct Point
{
    int pid, cid;
    vector<double> values; // each point has 4 values
    string c;

    Point(int pid, vector<double>& values, string c)
    {
        this->c = c;
        this->pid = pid;

        for(int i = 0; i < values.size(); i++)
            this->values.push_back(values[i]);

        cid = -1;
    }

    void setCluster(int cid)
    {
        this->cid = cid;
    }
};

struct Cluster
{
    int cid;
    vector<double> central_values; // values of the mean of the cluster
    //string c;
    vector<Point> points;

    Cluster(int cid, Point pt)
    {
        this->cid = cid;
        this->c = pt.c;

        for(int i = 0; i < 4; i++)
            central_values.push_back(pt.values[i]);

        points.push_back(pt);
    }

    bool removePoint(int pid)
    {

        for(int i = 0; i < points.size(); i++)
        {
            if(points[i].pid == pid)
            {
                points.erase(points.begin() + i);
                return true;
            }
        }
        return false;
    }

    void setCentralValue(int i, double value)
    {
        central_values[i] = value;
    }
};

void readData(vector<Point>& data)
{

    ifstream file("hw6_data.txt");

    double sl, sw, pl, pw;
    string c;

    if (!file)
    {
        cerr << "Error in opening the file" << endl;
    }

    string line;
    int i=0;

    while(getline(file,line))
    {
        istringstream is(line);

        if(is>>sl>>sw>>pl>>pw>>c)
        {
            vector<double> temp;
            temp.push_back(sl);
            temp.push_back(sw);
            temp.push_back(pl);
            temp.push_back(pw);
            data.push_back(Point(i,temp,c));
            i++;
        }
    }

}

void selectRandomCenters(int K, vector<Point> &points, vector<Cluster>& clusters)
{
    vector<int> used;

    // choose K distinct values for the centers of the clusters
    for(int i = 0; i < K; i++) //pick K random points
    {
        while(true)
        {
            int idx = rand() % points.size();

            // check if indexes have already been picked
            if(find(used.begin(), used.end(),idx) == used.end())
            {
                used.push_back(idx);
                points[idx].setCluster(i);

                Cluster cluster(i, points[idx]);//constructor for cluster
                clusters.push_back(cluster);
                break;
            }
        }
    }

}

int getIDNearestCenter(int K, Point & point, vector<Cluster> &clusters)
{
		double sum = 0.0;
        double min_dist = 10000;
		int cid_center = 0;

		for(int i = 0; i < K; i++) //for each cluster
		{
			double dist;
			sum = 0.0;

			for(int j = 0; j < 4; j++) //go through all the values of the point
			{
				sum += pow(clusters[i].central_values[j] -
						   point.values[j], 2.0);
			}

			dist = sqrt(sum);

			if(dist < min_dist)
			{
				min_dist = dist;
				cid_center = i;
			}
		}

		return cid_center;
	}

void associatePointsToClusters(int K, vector<Point>& points, vector<Cluster> &clusters)
{
    for(int i = 0; i < points.size(); i++)
			{
				int old_cid = points[i].cid;
				int nearest = getIDNearestCenter(K, points[i], clusters);

				if(old_cid != nearest)
				{
					if(old_cid != -1) //if it is not the first initialization
						clusters[old_cid].removePoint(points[i].pid);

					points[i].setCluster(nearest); //set the cluster id in the point
					clusters[nearest].points.push_back(points[i]);//add the point to the new cluster
				}
            }
}

void recalculateCenter(int K, vector<Cluster> & clusters)
{
    // recalculating the center of each cluster
			for(int i = 0; i < K; i++)
			{
				for(int j = 0; j < 4; j++) //for each value of a point
				{
					int points_in_cluster = clusters[i].points.size();
					double sum = 0.0;

					if(points_in_cluster > 0) //if the cluster has points
					{
						for(int p = 0; p < points_in_cluster; p++)
							sum += clusters[i].points[p].values[j];

						clusters[i].setCentralValue(j, sum / points_in_cluster);
					}
				}
			}
}

void print(int K, vector<Cluster> const &clusters)
{
    for(int i = 0; i < K; i++)
    {
        int total_pts =  clusters[i].points.size();//how many points each cluster has

        cout << "Cluster " << clusters[i].cid + 1 << endl;//number of cluster
        for(int j = 0; j < total_pts; j++)
        {
            cout << "Point " << clusters[i].points[j].pid + 1 << ": ";//id of point
            for(int p = 0; p < 4; p++)
                cout << clusters[i].points[j].values[p] << " ";
                cout<<clusters[i].points[j].c;

            cout << endl;
        }

        cout << "\nCluster central values: ";

        for(int j = 0; j < 4; j++)
            cout << clusters[i].central_values[j] << " ";
            //cout<<clusters[i].c<<endl;

        cout << "\n\n";
    }
}

int main()
{
    srand (time(NULL));
    int K;
    cout<<"K =";
    cin>>K;


    int max_iterations = 100;

    vector<Point> points;
    readData(points);

    vector<Cluster> clusters;

    selectRandomCenters(K, points, clusters);

    for(int i=0; i<max_iterations; i++)
    {
        associatePointsToClusters(K, points, clusters);
        recalculateCenter(K, clusters);
    }


    print(K, clusters);

    return 0;
}
