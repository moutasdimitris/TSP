#include <iostream>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

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
    std::cout<<"Starting algorithm No1 (Naive Solution).."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    int totalCost = 0,last = 0;
    totalCost+=findMin(vector[0],1);
    do{
       last=getLastV();
       if (last!=1)
         totalCost+=findMin1(vector[last-1]);
    }while(last!=1);
    std::cout<<"Route is: ";
    for (int a:path)
        std::cout<<a<<" ";
    std::cout<<std::endl;
    std::cout<<"Total cost is = "<<totalCost<<std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution time:"<<duration.count()<<"ms"<<std::endl;

}


//Check if element str exists in ver vector.

void algNo2(const std::vector<std::vector<int> >& vector){
    std::cout<<"Starting algorithm No2.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution time:"<<duration.count()<<"ms"<<std::endl;
}

void algNo3(std::vector<std::vector<int> > vector){
    std::cout<<"Starting algorithm No3.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution time:"<<duration.count()<<"ms"<<std::endl;

}

void readFile(std::string path,int choice){
    int n=0;
    std::vector<int> vec,temp;
    std::vector<std::vector<int> > vector;
    std::string line;
    std::ifstream myfile (path);
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
    std::cout<<"Please select an algorithm:"<<std::endl;
    std::cout<<"1)Algorithm No1"<<std::endl;
    std::cout<<"2)Algorithm No2"<<std::endl;
    std::cout<<"3)Algorithm No3"<<std::endl;
    std::cout<<">";
    std::cin>>choice;
    std::cout << std::endl;
    do{
    if (choice==1 | choice==2 | choice==3){
        validChoice=true;
        readFile(file,choice);
    }else{
        std::cout<<"Please enter valid num"<<std::endl;
        std::cout<<"1)Algorithm No1"<<std::endl;
        std::cout<<"2)Algorithm No2"<<std::endl;
        std::cout<<"3)Algorithm No3"<<std::endl;
        std::cout<<">";
        std::cin>>choice;
    }}while(!validChoice);

    return 0;
}