#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

struct Node
{
    float sl, sw, pl, pw;
    string c;
    float dist;

    Node(float sl, float sw, float pl, float pw, string c, float dist =0)
    {
        this->sl = sl;
        this->sw = sw;
        this->pl = pl;
        this-> pw = pw;
        this->c = c;
        this->dist = dist;
    }

};
// Overloading < operator
bool operator<(const Node &n1, const Node &n2)
{
    return n1.dist < n2.dist;
}

void readData(vector<Node>& data)
{

    ifstream file("hw5_data.txt");

    float sl, sw, pl, pw;
    string c;

    if (!file)
    {
        cerr << "Error in opening the file" << endl;

    }

    string line;

    while(getline(file,line))
    {
        istringstream is(line);

        if(is>>sl>>sw>>pl>>pw>>c)
        {
            //cout<<sl<<' '<<sw<<' '<<c;
            data.push_back(Node(sl,sw,pl,pw,c));
        }
    }
}

void print(vector<Node> const &data)
{
    for(int i=0;i<data.size();i++)
    {
        cout<<data[i].sl<<' '<<data[i].sw<<' '<<data[i].pl<<' '<<data[i].pw<<' '<<data[i].c<<endl;
    }
}


void checkMinMax(float &_min, float &_max, float const &elem)
{
    if(_min > elem)
        _min = elem;
    else if(_max < elem)
        _max = elem;
}

void findMinMax(vector<Node> const &data, float& sl_min, float& sl_max, float& sw_min, float& sw_max, float& pl_min, float& pl_max, float& pw_min, float& pw_max)
{
    sl_min=data.front().sl;
    sl_max=data.front().sl;
    sw_min=data.front().sw;
    sw_max=data.front().sw;
    pl_min=data.front().pl;
    pl_max=data.front().pl;
    pw_min=data.front().pw;
    pw_max=data.front().pw;

    for(int i=0;i<data.size();i++)
    {
        checkMinMax(sl_min,sl_max,data[i].sl);
        checkMinMax(sw_min,sw_max,data[i].sw);
        checkMinMax(pl_min,pl_max,data[i].pl);
        checkMinMax(pw_min,pw_max,data[i].pw);

    }

//    cout<<"minSL="<<pl_min<<endl;
//    cout<<"maxSl="<<pl_max<<endl;
}

void calculate(float & _new, float const &_min, float const&_max, float const& _old)
{
    _new = (_old - _min)/(_max - _min);
}

void normalize(vector<Node>& data, Node& input)
{
    float sl_min,sl_max,sw_min,sw_max,pl_min,pl_max,pw_min,pw_max;
    findMinMax(data,sl_min,sl_max,sw_min,sw_max,pl_min,pl_max,pw_min,pw_max);
    vector<Node> n_data;
    float n_sl,n_sw,n_pl,n_pw;

    //normalize the data set
    for(int i=0;i<data.size();i++)
    {
        calculate(n_sl,sl_min,sl_max,data[i].sl);
        calculate(n_sw,sw_min,sw_max,data[i].sw);
        calculate(n_pl,pl_min,pl_max,data[i].pl);
        calculate(n_pw,pw_min,pw_max,data[i].pw);
        n_data.push_back(Node(n_sl,n_sw,n_pl,n_pw,data[i].c));
    }
    data = n_data;

    //normalize input values
    calculate(n_sl,sl_min,sl_max,input.sl);
    calculate(n_sw,sw_min,sw_max,input.sw);
    calculate(n_pl,pl_min,pl_max,input.pl);
    calculate(n_pw,pw_min,pw_max,input.pw);
    //change input values
    input.sl = n_sl;
    input.sw = n_sw;
    input.pl = n_pl;
    input.pw = n_pw;

    //cout<<"\n Calculated input: "<<n_sl<<' '<<n_sw<<' '<<n_pl<<' '<<n_pw<<endl;

}

float sqSubstract(float const &first, float const &second)
{
    return (first-second)*(first-second);
}

float calculateDistance(Node const &first, Node const &second)
{
    return sqSubstract(first.sl,second.sl) + sqSubstract(first.sw,second.sw)
         + sqSubstract(first.pl,second.pl) + sqSubstract(first.pw,second.pw);
}

void getDistances(vector<Node> &data, Node const& input)
{
    for(int i=0;i<data.size();i++)
    {
        data[i].dist = abs(sqrt(calculateDistance(data[i],input)));
        //cout<<data[i].dist<<endl;
    }
    //cout<<endl<<endl;
}

void classify(int k, vector<Node> const& data, Node &input)
{
    //number of items in each class
    int i_vers = 0;
    int i_virg = 0;
    int i_set = 0;

    for(int i=0;i<k;i++)
    {
        if(data[i].c=="Iris-versicolor")
        {
            i_vers++;
        }
        if(data[i].c=="Iris-virginica")
        {
            i_virg++;
        }
        if(data[i].c=="Iris-setosa")
        {
            i_set++;
        }
    }

    int m = max(i_vers,max(i_virg,i_set));

    //check from which class is the input
    if(i_vers == m)
       input.c = "Iris-versicolor";
       else if(i_virg == m)
        input.c = "Iris-virginica";
        else
            input.c = "Iris-setosa";

}


int main()
{
    int k;
    cout<<"K =";
    cin>>k;

    float sl,sw,pl,pw;
    cout<<"sl>>sw>>pl>>pw\n";
    cin>>sl>>sw>>pl>>pw;

    Node input(sl,sw,pl,pw,"");
    vector<Node> data;

    readData(data);
    normalize(data, input);
    getDistances(data,input);

    sort(data.begin(),data.end());
    classify(k,data,input);

    for(int i=0;i<k;i++)
    {
        cout<<data[i].c<<endl;
    }
    cout<<"Class is "<<input.c<<endl;
    //print(data);
    return 0;
}
