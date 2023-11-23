
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
typedef pair<int, int> MyPairType;
bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    if(a.second > b.second)
        return true;
    else
    {
        if(a.second<b.second)
            return false;
        else if(a.second==b.second){
            if(a.first<b.first)
                return true;
            else
                return false;
        }
    }


}
struct CompareSecond
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second < right.second;
    }
};

struct sortBySecondElement
{
    bool operator()(const MyPairType& left, const MyPairType& right) const
    {
        return left.second > right.second;
    }
};

void make_dataset(vector<vector<double>>&dataset,map<int,string>&id_name){

    double a1,a2,a3,a4;
    fstream fin;
    fin.open("database.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    string name;
    int gp;
    double pts,reb,ast;
    int id=0;
    getline(fin, line);
    while (fin >> temp)
    {


        row.clear();
//cout<<temp;
//
//        // read an entire row and
//        // store it in a string variable 'line'
        getline(fin, line);


//
//        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'

        while (getline(s, word, ','))
        {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        // convert string to integer for comparision
        //roll2 = stoi(row[0]);

        // Compare the roll number


        // Print the found data



//            cout << "Details of Roll " << row[0] << " : \n";
//            cout << "Name: " << row[4] << "\n";
//            cout << "Maths: " << row[17] << "\n";
//            cout << "Physics: " << row[18] << "\n";
//            cout << "Chemistry: " << row[20] << "\n";

        name=row[0];
        stringstream geek(row[4]);
        geek>>gp;

        istringstream(row[17])>>pts;
        istringstream(row[18])>>reb;
        istringstream(row[20])>>ast;

//myFile<<name<<","<<gp<<","<<pts<<","<<reb<<","<<ast<<"\n";

        id_name.insert(pair<int,string>(id, name));
        vector<double>m{gp,pts,reb,ast};
        dataset.push_back(m);
        //cout<<name<<endl;


        id++;








    }
    fin.close();








}
bool dominates(vector<double>x,vector<double>y){
vector<int>pos;
vector<int>observed_pos;

for(int i=0;i<=3;i++){
    if(x[i]==-1 || y[i]==-1)
    {
        continue;
    }

    observed_pos.push_back(i);

    if(x[i]<y[i])
    {
        return false;

    }
    if(x[i]==y[i])
    {
        pos.push_back(i);
    }


}

if(pos==observed_pos){
    return false;
}

return true;
}
map<int,int>& score_calculation(vector<vector<double>>&dataset,map<int,int>&score_all){

int pos=0;
int score=0;
vector<vector<double>>::iterator i;
vector<vector<double>>::iterator j;

    for (i= dataset.begin(); i< dataset.end(); i++)
        {

             for (j= dataset.begin(); j< dataset.end(); j++) {
                if(i==j)
                    {continue;}
                if(dominates(*i,*j))
                   {

                       score++;
                   }


             }
            // cout<<pos<<"\t"<<score<<endl;

             score_all.insert(pair<int, int>(pos, score));

            pos++;
            score=0;

        }
return score_all;

 }
vector<pair<int,int>>&  max_score_calculation(vector<vector<double>>&dataset,vector<pair<int,int>>& max_score_all){
int pos=0;
int max_score=0;
vector<double>t;
int c=0;
vector<vector<double>>::iterator i;
vector<vector<double>>::iterator j;

    for (i= dataset.begin(); i< dataset.end(); i++)
        {

            for(int k=0;k<=3;k++){
                if((*i)[k]==-1){
                t.push_back(20);

                }
                else{
                        int temp=(*i)[k];
                    for (j= dataset.begin(); j< dataset.end(); j++){
                        if(i==j)
                            continue;

                            if((*j)[k]==-1)
                                c++;
                            else if((*j)[k]<=temp)
                                c++;


                    }
                    t.push_back(c);
                    c=0;

                }


            }

           //  cout<<pos<<"\t"<<*min_element(t.begin(), t.end())<<endl;
            max_score_all.push_back(make_pair(pos,*min_element(t.begin(), t.end())));
            pos++;
             t.clear();

        }
       sort(max_score_all.begin(), max_score_all.end(), sortbysec);
//        for (int i=0; i<20; i++)
//    {
//        // "first" and "second" are used to access
//        // 1st and 2nd element of pair respectively
//        cout << max_score_all[i].first << " "
//             << max_score_all[i].second << endl;
//    }

return max_score_all;
}



vector<int>& ubb(/*vector<int>& sg,*/vector<pair<int,int>> max_score_all,int k,vector<vector<double>>&dataset,map<int,string>id_name){
//vector<int>sc;
vector<int>min_calc;

vector<pair<int,int>>sc_score;
int tau=-1;
int o;
int score;
map<int,int>score_all;
score_all=score_calculation(dataset,score_all);
vector<pair<int,int>>::iterator i;
for(i=max_score_all.begin();i<max_score_all.end();i++){
        o=(*i).first;

        if((*i).second <= tau){



            break;

            }
        else{
            // cout<<o<<endl;
             map<int, int>::iterator it ;

            it = score_all.find(o);
            score=it->second;

            if(score >= tau || tau<0){
               // sc.push_back(o);

                sc_score.push_back(make_pair(o,score));

                 if(sc_score.size()>k){

                for (auto it = sc_score.rbegin(); it != sc_score.rend();it++)
                 {
                       if (it->second == tau && sc_score.size()>k)
                       // sc_score.erase(it);
                        sc_score.erase( next(it).base() );

                 }

//                   vector<int>::iterator it2;
//                   it2=find(sc.begin(), sc.end(),tau);
//                   if(it2!=sc.end()){
//                        cout<<"here when k is larger"<<endl;
//                        sc.erase(it2);
//
//                   }

                }
//                 map<int, int>::iterator it1;
//                for(it1=sc.begin();it1<sc.end();it1++){
//                    //cout<<*i<<endl;
//                  it1 = score_all.find(*i);
//                    min_calc.push_back(it1->second);
//
//                }

                 if(sc_score.size()==k){
                pair<int,int>min= *min_element(sc_score.begin(), sc_score.end(), CompareSecond());
                tau=min.second;
               // cout<<"tau:"<<tau<<endl;
                }


            }


        }




}
sort(sc_score.begin(),sc_score.end(),sortbysec);
 ofstream myFile("final_Output_ubb.csv");
     myFile<<"ID"<<","<<"NAME"<<","<<"SCORE"<<"\n";
for(auto i=sc_score.begin();i!=sc_score.end();i++){
myFile<<i->first <<","<<id_name[i->first]<<","<<i->second<<endl;
}
myFile.close();
}
int main(){
 vector<vector<double>>dataset;
  map<int,string>id_name;

int k;
int dimension=4;
 vector<pair<int,int>>max_score_all;
 auto start = high_resolution_clock::now();
 make_dataset(dataset,id_name);


///cout<<"Enter k:";
///cin>>k;

max_score_all=max_score_calculation(dataset,max_score_all);

ubb(max_score_all,k,dataset,id_name);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

  cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9);
    cout << " sec" << endl;

return 0;

}

