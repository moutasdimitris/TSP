#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

#define BOLDRED     "\033[1m\033[31m"      /* Bold Red    */
#define RESET       "\033[0m"              /* Reset       */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green  */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White  */


std::vector<int> path;
std::vector<int> path1;
std::vector<std::vector<int> > perm;



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

int findMin2(std::vector<std::vector<int> > vector,std::vector<int> p){
    int sum=0;
    for (int i=0;i<p.size()-1;i++){
        int first=p[i];
        int second=p[i+1];
        sum+=vector[first-1][second-1];
    }
    return sum;
}

int findMinPos(std::vector<int> v,int num){
    std::vector<int>::iterator indx=lower_bound(v.begin(),v.end(), num);
    int pos=indx-v.begin();
    if (!(indx == v.end() || *indx!=num))
        return pos+1;
    return -1;
}

int calc(const std::vector<std::vector<int> >& vector){
    std::vector<int> costs;
    for (std::vector<int> vec:perm){
        costs.push_back(findMin2(vector,vec));
    }

    std::sort(costs.begin(),costs.end());
    int pos=findMinPos(costs,costs[0]);
    path1=perm[pos];
    return costs[0];
}

void findPermutations(int n){
    std::vector<int> a;
    for (int i=0;i<n;i++){
        if (i!=0)
          a.push_back(i+1);
    }
    std::vector<std::vector<int> > p;
    do {
        p.push_back(a);
    } while (std::next_permutation(a.begin(), a.end()));

    for (std::vector<int> d:p){
        d.insert(d.begin(),1);
        d.push_back(1);
        perm.push_back(d);
    }
    p.clear();
}

void algNo2(const std::vector<std::vector<int> >& vector){
    std::cout<<BOLDWHITE<<"Starting algorithm No2.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    findPermutations(vector.size());
    int totalCost=calc(vector);
    std::cout<<BOLDWHITE<<"Route is: ";
    for (int a:path1)
        std::cout<<BOLDGREEN<<a<<" ";
    std::cout<<std::endl;
    std::cout <<BOLDWHITE<< "Total cost = "<<BOLDGREEN <<totalCost<< std::endl;
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