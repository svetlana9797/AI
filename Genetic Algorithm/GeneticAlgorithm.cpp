#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<ctime>
using namespace std;

#define MAX_ITER 500
#define POPULATION_SIZE 16
//N is the number of items with value, price
//W is the max sum which should not be exceeded
//K is the number of crossovers to be made in each iteration
//M is mutation speed
int N,W,K,M;
vector<int> price, value;
vector<string> item;

struct Individual
{
    //chromozome size is N
    vector<bool> chromosome;
    int fitness;

Individual(const vector<bool>& chromosome)
{
    this->chromosome = chromosome;
    fitness = calculate_fitness();
}

int calculate_fitness()
{
    int f = 0;
    int total_price =0;

    for(int i = 0;i<N;i++)
    {
        f = f + chromosome[i]*value[i];
        total_price+=chromosome[i]*price[i];
    }
    //if we exceed the price
    if(total_price>W)
        return 0;

    return f;
}

//switch 2 random values in the chromosome
void mutate()
{
    int idx = rand()%N;
    chromosome[idx]=!chromosome[idx];
}

};

bool random_num()
{
    int r = rand()%POPULATION_SIZE;
    return r%2;
}

//bool operator<(const Individual &ind1, const Individual &ind2)
//{
//    return ind1.fitness < ind2.fitness;
//}
bool operator>(const Individual &ind1, const Individual &ind2)
{
    return !(ind1.fitness < ind2.fitness);
}

Individual crossover(const vector<bool>& chr1, const vector<bool>& chr2, vector<bool> &child_chr1, vector<bool> &child_chr2)
{
    int r=rand()%N;

    for(int i = 0;i < N; i++)
    {
        if(i<r)
        {
            child_chr1.push_back(chr1[i]);
            child_chr2.push_back(chr2[i]);
        }
        else
        {
            child_chr1.push_back(chr2[i]);
            child_chr2.push_back(chr1[i]);
        }
    }

}

vector<bool> create_chromosome()
{
    vector<bool> c;
    for(int i=0;i< N; i++)
    {
        c.push_back(random_num());
    }
    return c;
}

void printSolution(const Individual &ind)
{
    string sol;
    int pr;
    for(int i=0;i<N;i++)
    {
        cout<<ind.chromosome[i]<<" ";
        if(ind.chromosome[i])
        {
            sol= sol + item[i] + " ";
            pr+=price[i];
        }
    }

    cout<<"\n\nItems taken: "<<sol<<endl;
    cout<<"\nFitness: "<<ind.fitness<<endl;
}

int main()
{
    srand(time(0));
    freopen("in.txt", "r", stdin);
    cin>>N>>W>>K>>M;
    string obj;
    int p,v;

    //initialize the items and their value&price
    for(int i=0;i<N;i++)
    {
        getline(std::cin,obj,' ');
        item.push_back(obj);
        cin>>p>>v;
        price.push_back(p);
        value.push_back(v);
    }

    vector<Individual> population;

    // generate initial population
    for(int i = 0;i<POPULATION_SIZE;i++)
    {
        vector<bool> c = create_chromosome();
        population.push_back(Individual(c));

    }


    for(int gen=0; gen < MAX_ITER; gen++)
    {

       sort(population.begin(), population.end(),greater<Individual>());
       
       //crossover 10 times => 20% new population
       for(int i=0;i<10;i++)
       {
           //pick from the best 10 parents
           int r1 = rand()%10;//random number 0%K-1
           int r2 = rand()%10;
           crossover(population[r1].chromosome, population[r2].chromosome,)
       }

       for(int i=0;i<POPULATION_SIZE;i++)
       {
           //crossover from the first K individuals
           if(i>POPULATION_SIZE-K)
           {
               int r1 = rand()%K;//random number 0%K-1
               int r2 = rand()%K;

               //the last K Individuals are switched with the children
               crossover(population[r1].chromosome, population[r2].chromosome, population[i].chromosome);
               population[i].fitness = population[i].calculate_fitness();
           }
       }


      //mutate M times
      for(int i=0;i<M;i++)
      {
          //take a random individual from the population
          int idx=rand()%(POPULATION_SIZE);
          population[idx].mutate();
      }

}

cout<<"Solution\n";
printSolution(population.front());
return 0;
}
