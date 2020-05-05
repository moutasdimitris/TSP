#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

std::vector<int> path;

bool checkIfExists(int str){
    for (int i:path){
        if (str==i)
            return true;}
        return false;
}


int findMin(std::vector<int> vec,int p){
    int min=INT_MAX;
    int pos=0;
    for (int i=0;i<vec.size();i++){
        if (vec[i]!=0 && vec[i]<min){
            min=vec[i];
            pos=i+1;
        }
    }
    path.push_back(p);
    path.push_back(pos);
    return min;
}

int findMin1(std::vector<int> vec){
    int min=INT_MAX;
    int pos=0;
    for (int i=0;i<vec.size();i++){
        bool exists=checkIfExists(i+1);
            if (!exists && vec[i]!=0 && vec[i]<min)  {
                min = vec[i];
                pos=i+1;
        }
    }
    if (min==INT_MAX){
        min=vec[0];
        pos=1;
    }
    path.push_back(pos);
    return min;
}

int getLastV() {
    return path[path.size()-1];
}

void algNo1(const std::vector<std::vector<int> >& vector){
    std::cout<<BOLDWHITE<<"Starting algorithm No1 (Naive Solution).."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int totalCost = 0,last = 0;
    totalCost+=findMin(vector[0],1);
    do{
       last=getLastV();
       if (last!=1)
         totalCost+=findMin1(vector[last-1]);
    }while(last!=1);
    std::cout<<BOLDWHITE<<"Route is: ";
    for (int a:path)
        std::cout<<BOLDGREEN<<a<<" ";
    std::cout<<std::endl;
    std::cout<<BOLDWHITE<<"Total cost = "<<BOLDGREEN<<totalCost<<std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<BOLDWHITE<<"Execution time:"<<BOLDGREEN<<duration.count()<<"ms"<<std::endl;

}
int calc(const std::vector<std::vector<int>> cities, int pos, int visited, std::vector<std::vector<int>> state) {
    if(visited == ((1 << cities.size()) - 1))
        return cities[pos][0]; // return to starting city

    if(state[pos][visited] != INT_MAX)
        return state[pos][visited];

    for(int i = 0; i < cities.size(); ++i)
    {
        // can't visit ourselves unless we're ending & skip if already visited
        if(i == pos || (visited & (1 << i)))
            continue;

        int distance = cities[pos][i] + calc(cities, i, visited | (1 << i), state);
        if(distance < state[pos][visited])
            state[pos][visited] = distance;
    }

    return state[pos][visited];
}

void algNo2(const std::vector<std::vector<int> >& vector){
    std::cout<<BOLDWHITE<<"Starting algorithm No2.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> vec(vector.size());
    for(auto& neighbors : vec)
        neighbors = std::vector<int>((1 << vector.size()) - 1, INT_MAX);
    std::cout <<BOLDWHITE<< "Total cost = "<<BOLDGREEN << calc(vector, 0, 1, vec)<< std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<BOLDWHITE<<"Execution time = "<<BOLDGREEN<<duration.count()<<"ms"<<std::endl;
}

void algNo3(const std::vector<std::vector<int> >& vector){
    std::cout<<"Starting algorithm No3.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution time:"<<duration.count()<<"ms"<<std::endl;

}

void readFile(std::string filePath, int choice){
    int n=0;
    std::vector<int> vec,temp;
    std::vector<std::vector<int> > vector;
    std::string line;
    std::ifstream myfile (filePath);
    if (myfile.is_open())
    {
        while (getline(myfile,line))
        {
            n++;
            int w= stoi(line.substr(line.find("=") + 1));
            vec.push_back(w);
        }
        int h=sqrt(n);//plithos n
        int d=0;
        for (int i=0;i<h;i++) {
            for (int j = 0; j < h; j++) {
                temp.push_back(vec[d]);
                d++;
            }
            vector.push_back(temp);
            temp.clear();
        }
        myfile.close();
    }
    else {
        std::cout <<"Unable to open file."<<std::endl;
        std::cout<<"Give me the right path.."<<std::endl;
        std::cout<<">";
        std::string cpath;
        std::cin>>cpath;
        readFile(cpath,choice);
    }
    if (choice==1){
        algNo1(vector);
    }else if (choice==2){
        algNo2(vector);
    }else{
        algNo3(vector);
    }
}


int main(int argc, char *argv[] ) {
    int choice;
    std::string file="/Users/root1/CLionProjects/TSP/graph.txt";
    bool validChoice=false;
    std::cout<<BOLDGREEN<<"Please select an algorithm:"<<std::endl;
    std::cout<<BOLDYELLOW<<"1)Algorithm No1(Naive Solution)"<<std::endl;
    std::cout<<"2)Algorithm No2(Dynamic Programming)"<<std::endl;
    std::cout<<"3)Algorithm No3"<<RESET<<std::endl;
    std::cout<<">";
    std::cin>>choice;
    std::cout << std::endl;
    do{
    if (choice==1 | choice==2 | choice==3){
        validChoice=true;
        readFile(file,choice);
    }else{
        std::cout<<BOLDRED<<"Please enter valid num"<<RESET<<std::endl;
        std::cout<<BOLDYELLOW<<"1)Algorithm No1(Naive Solution)"<<std::endl;
        std::cout<<"2)Algorithm No2(Dynamic Programming)"<<std::endl;
        std::cout<<"3)Algorithm No3"<<RESET<<std::endl;
        std::cout<<">";
        std::cin>>choice;
    }}while(!validChoice);

    return 0;
}