#include <iostream>
#include <chrono>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

/**
 * Χρώματα για την εμφάνιση της εξόδου.
 */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red    */
#define RESET       "\033[0m"              /* Reset       */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green  */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White  */

/**
 * Όλα τα vector και οι μεταβλητές όπου θα
 * αποθηκευτούν οι απαραίτητες πληροφορίες.
 */
std::vector<int> path;
std::vector<int> path1;
std::vector<std::vector<int> > path2;
std::vector<std::vector<int> > perm;
int totalMin=0;


/**
 * Ελέγχει εάν υπάρχει στο σύνολο path που
 * περιέχει την διαδρομή του πρώτου αλγορίθμου
 * τον αριθμό str και επιστρέφει true εάν έχει
 * βρεθεί και false σε αντίθετη περίπτωση.
 * @param str
 * @return
 */
bool checkIfExists(int str){
    for (int i:path){
        if (str==i)
            return true;
    }
        return false;
}

/**
 * Η μέθοδος αυτή βρίσκει και επιστρέφει το
 * μικρότερο μη μηδενικό στοιχείο που είναι
 * μικρότερο από το min και εισάγει το στοιχείο
 * στο vector path που είναι και το μονοπάτι
 * που αντιστοιχεί στο ελάχιστο.
 * @param vec
 * @param p
 * @return
 */
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

/**
 *  Όπως και στην μέθοδο findMin υπολογίζει
 *  και επιστρέφει το min με τη διαφορά ότι
 *  τσεκάρει εάν υπάρχει το αντίστροφο ζεύγος
 *  πχ. εάν έχουμε ήδη επισκεφτεί το ζεύγος
 *  1-2 με την checkIfexists δεν μπορούμε να
 *  χρησιμοποιήσουμε το ζεύγος 2-1. Και πάλι
 *  βάζουμε τα κατάλληλα στοιχεία στο vector
 *  path που είναι και το μονοπάτι με τη
 *  συντομότερη διαδρομή.
 * @param vec
 * @return
 */
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

/**
 * Επιστρέφει το τελευταίο στοιχείο του path
 * το οποίο θα το χρησιμοποιήσει για να συνεχίσει
 * στο επόμενο ζεύγος του μονοπατιού.
 * @return
 */
int getLastV() {
    return path[path.size()-1];
}

/**
 * Σε αυτή τη μέθοδο οργανώνεται όλη η λογική του
 * πρώτου αλγορίθμου η οποία καλεί την findMin
 * για τον πρώτο κόμβο (αφού πάντα οι αλγόριθμοι
 * ξεκινάνε από τον κόμβο 1) και στη συνέχεια υπολογίζει
 * το συνολικό κόστος μέχρι να φτάσει πάλι στον αρχικό
 * κόμβο από τον οποίο ξεκίνησε (δηλαδή τον κόμβο 1).
 * @param vector
 */
void algNo1(const std::vector<std::vector<int> >& vector){
    std::cout<<BOLDWHITE<<"Starting algorithm No1.."<<std::endl;
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

/**
 * Η μέθοδος αυτή υπολογίζει το άθροισμα του μονοπατιού
 * που βρίσκει στο vector p και το επιστρέφει.
 * @param vector
 * @param p
 * @return
 */
int findMin2(std::vector<std::vector<int> > vector,std::vector<int> p){
    int sum=0;
    for (int i=0;i<p.size()-1;i++){
        int first=p[i];
        int second=p[i+1];
        sum+=vector[first-1][second-1];
    }
    return sum;
}

/**
 * Η μέθοδος αυτή βρίσκει τη θέση στην οποία βρίσκεται
 * το στοιχείο num και την επιστρέφει ενώ επιστρέφει
 * -1 σε άλλη περίπτωση (το στοιχείο δεν βρέθηκε).
 * @param v
 * @param num
 * @return
 */
int findMinPos(std::vector<int> v,int num){
    std::vector<int>::iterator indx=lower_bound(v.begin(),v.end(), num);
    int pos=indx-v.begin();
    if (!(indx == v.end() || *indx!=num))
        return pos+1;
    return -1;
}

/**
 * Η μέθοδος αυτή εισάγει στο vector costs όλα τα
 * κόστη που υπολογίζει από την κλήση της μεθόδου
 * findMin2 και στη συνεχεια κάνει sort ποροκειμένου
 * να πάρουμε το μικρότερο κόστος που θα είναι το
 * πρώτο στοιχείο αυτού και το οποίο το επιστρέφει
 * στο σημείο όπου καλείται αυτή η μέθοδος.
 * @param vector
 * @return
 */
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

/**
 * Υπολογίζει όλες τις αντιμεταθέσεις των στοιχείων
 * και τα εισάγει στο vector perm το οποίο θα
 * χρησιμοποιηθεί για να υπολογιστεί το κόστος όλων
 * των πιθανών διαδρομών και να βρούμε εκείνη με το
 * μικρότερο κόστος.
 * @param n
 */
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

/**
 * Η μέθοδος αυτή αρχικά καλεί την findPermutations
 * για να υπολογίσει όλα τα πιθανά μονοπάτια και
 * στη συνέχεια να καλέσει την calc για να υπολογίσει
 * το τελικό κόστος το οποίο και θα εκτυπωθεί μαζί με
 * το μονοπάτι που αντιστοιχεί σε αυτό (vector path1).
 * @param vector
 */
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

/**
 *  Σε αυτή τη μέθοδο υπολίζεται για την πρώτη πιθανή
 *  διαδρομή (από αυτές που υπολογίστηκαν με την μέθοδο
 *  findPermutations) το κόστος και αντίστοιχα εισάγει
 *  στο vector path2 αυτή τη διαδρομή.
 * @param vector
 */
void calc2first(std::vector<std::vector<int> > vector){
    totalMin=findMin2(vector,perm[0]);
    path2.push_back(perm[0]);
}

/**
 * Υπολογίζει το κόστος για την διαδρομή που βρίσκεται στο vector p
 * με την προϋπόθεση ότι κατά τον υπολογισμό  εάν το σκορ σε κάθε βήμα είναι
 * μεγαλύτερο από το totalMin (που είναι το ελάχιστο κόστος από όλα τα μονοπάτια
 * που μελετήθηκαν μέχρι εκείνη τη στιγμή) τότε δεν συνεχίζει να υπολογίζει για το
 * τρέχον μονοπάτι το κόστος αφού αυτό θα είναι μεγαλύτερο από κάποιο άλλο μονοπάτι
 * οπότε και επιστρέφει στο σημείο όπου κλήθηκε  και ταυτόχρονα στο vector path2
 * εισάγει το μονοπάτι αυτό εφόσον ισχύει η παραπάνω συνθήκη.
 * @param vector
 * @param p
 */
void findMin3(std::vector<std::vector<int> > vector,std::vector<int> p){
    int sum=0;
    for (int i=0;i<p.size()-1;i++){
        int first=p[i];
        int second=p[i+1];
        sum+=vector[first-1][second-1];
        if (sum>=totalMin){
            return;
        }
    }

    path2.clear();
    path2.push_back(p);
    totalMin=sum;
}

/**
 * Καλεί αρχικά την μέθοδο υπολογισμού του κόστους για το
 * πρώτο μονοπάτι για να πάρει εκείνο το κόστος σαν
 * μικρότερο και στη συνέχεια καλεί αναδρομικά για κάθε
 * πιθανό μονοπάτι τη findMin3 για να υπολογίσει το
 * μικρότερο κόστος.
 * @param vector
 */
void calc2(std::vector<std::vector<int> > vector){
    calc2first(vector);
    for (int i=1;i<perm.size();i++) {
        findMin3(vector,perm[i]);
    }
}

/**
 * Η μέθοδος αυτή αρχικά καλεί την findPermutations
 * για να υπολογίσει όλα τα πιθανά μονοπάτια και
 * στη συνέχεια να καλέσει την calc2 για να υπολογίσει
 * το τελικό κόστος το οποίο και θα εκτυπωθεί μαζί με
 * το μονοπάτι που αντιστοιχεί σε αυτό (vector path2).
 * @param vector
 */
void algNo3(const std::vector<std::vector<int> >& vector){
    std::cout<<BOLDWHITE<<"Starting algorithm No3.."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    findPermutations(vector.size());
    calc2(vector);
    std::cout<<BOLDWHITE<<"Route is: ";
    for (std::vector<int> a:path2){
        for (int i:a)
            std::cout<<BOLDGREEN<<i<<" ";
    }
    std::cout<<std::endl;
    std::cout <<BOLDWHITE<< "Total cost = "<<BOLDGREEN <<totalMin<< std::endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Execution time:"<<duration.count()<<"ms"<<std::endl;

}

/**
 * Ανοίγει το αρχείο filePath και παίρνει τα κόστη
 * για κάθε κόμβο και φτιάχνει τον πίνακα γειτνίασης
 * ενώ στο τέλος κλείνει το αρχείο ή εάν υπάρχει
 * πρόβλημα με το αρχείο (δεν βρέθηκε..) τότε εκτυπώνει
 * κατάλληλο μήνυμα. Επίσης διαβάζει απο το χρήστη
 * ποιόν αλγόριθμο θέλει να τρέξει.
 * @param filePath
 * @param choice
 */
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

/**
 * Κύρια συνάρτηση main στην οποία συντονίζεται όλη η λειτουργία
 * του προγράμματος. Εκτυπώνει κατάλληλο μενού με διαθέσιμες
 * επιλογές και παίρνει την επιλογή του χρήστη ενώ ελέγχει
 * παράλληλα εάν είναι αποδεκτή και ξεκινάει η εκτέλεση της
 * κατάλληλης μεθόδου. Τέλος στην readFile δίνεται σαν όρισμα
 * το πρώτο όρισμα που δεχτεί κατά το τρέξιμο απο τη γραμή εντολών
 * και αντιστοιχεί στη θέση 1 (argv[1]) καθώς στη θέση 0 είναι το
 * εκτελέσιμο αρχείο του προγράμματος.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[] ) {
    int choice;
    bool validChoice=false;
    std::cout<<BOLDGREEN<<"Please select an algorithm:"<<std::endl;
    std::cout<<BOLDYELLOW<<"1)Algorithm No1(Naive Solution)"<<std::endl;
    std::cout<<"2)Algorithm No2(Dynamic Programming)"<<std::endl;
    std::cout<<"3)Algorithm No3(Backtracking)"<<RESET<<std::endl;
    std::cout<<">";
    std::cin>>choice;
    std::cout << std::endl;
    do{
    if (choice==1 | choice==2 | choice==3){
        validChoice=true;
        readFile(argv[1],choice);
    }else{
        std::cout<<BOLDRED<<"Please enter valid num"<<RESET<<std::endl;
        std::cout<<BOLDYELLOW<<"1)Algorithm No1(Naive Solution)"<<std::endl;
        std::cout<<"2)Algorithm No2(Dynamic Programming)"<<std::endl;
        std::cout<<"3)Algorithm No3(Backtracking)"<<std::endl;
        std::cout<<">"<<RESET;
        std::cin>>choice;
    }}while(!validChoice);
    return 0;
}