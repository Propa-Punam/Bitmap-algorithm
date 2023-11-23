#include <bits/stdc++.h>
#include <vector>
using namespace std;
using namespace std::chrono;
bool sortbysec(const pair<int,int> &a,
               const pair<int,int> &b)
{
    if(a.second > b.second)
        return true;
    else
    {
        if(a.second<b.second)
            return false;
        else if(a.second==b.second)
        {
            if(a.first<b.first)
                return true;
            else
                return false;
        }
    }


}
class movie
{

public:
    static int total_movies;
   // double a1,a2,a3,a4;
   double a[5];

    int id;
    string name;
    double score;

    movie(int id1,double x,double y,double z,double p,string name1)
    {

        a[0]=x;
        a[1]=y;
        a[2]=z;
        a[3]=p;
        score=0.0;
        id=id1;
        name=name1;

    }

};


//
//bool dominates(movie m1,movie m2)
//{
//    if(m1.a1>m2.a1)
//    {
//        if(m1.a2>=m2.a2)
//        {
//            if(m1.a3>=m2.a3)
//            {
//                if(m1.a4>=m2.a4)
//                {
//                    return true;
//                }
//                else
//                    return false;
//
//            }
//            else
//                return false;
//        }
//        else
//            return false;
//    }
//    else if(m1.a2>m2.a2)
//    {
//        if(m1.a3>=m2.a3)
//        {
//            if(m1.a1>=m2.a1)
//            {
//                if(m1.a4>=m2.a4)
//
//                {
//                    return true;
//                }
//                else
//                    return false;
//            }
//            else
//                return false;
//        }
//        else
//            return false;
//    }
//    else if(m1.a3>m2.a3)
//    {
//        if(m1.a1>=m2.a1)
//        {
//            if(m1.a2>=m2.a2)
//            {
//                if(m1.a4>=m2.a4)
//                {
//                    return true;
//                }
//
//                else
//                    return false;
//            }
//
//            else
//                return false;
//        }
//        else
//            return false;
//    }
//
//    else if(m1.a4>m2.a4)
//    {
//        if(m1.a1>=m2.a1)
//        {
//            if(m1.a2>=m2.a2)
//            {
//                if(m1.a3>=m2.a3)
//                {
//                    return true;
//                }
//
//                else
//                    return false;
//            }
//
//            else
//                return false;
//        }
//        else
//            return false;
//    }
//
//    else if(m1.a1==m2.a1 && m1.a2==m2.a2 && m1.a3==m2.a3 && m1.a4==m2.a4)
//    {
//        return false;
//    }
//    else
//        return false;
//
//
//
//
//
//}
bool dominates(movie x, movie y){




vector<double>pos;
vector<double>observed_pos;

for(int i=0; i<=3; i++)
{
    if(x.a[i]==-1 || y.a[i]==-1)
    {
        continue;
    }

    observed_pos.push_back(i);

    if(x.a[i]<y.a[i])
    {
        return false;

    }

    if(x.a[i]==y.a[i])
    {
        pos.push_back(i);
    }


}

if(pos==observed_pos)
{
    return false;
}

return true;
}
void set_score(vector<movie>&vec)
{

    for(auto i=vec.begin(); i!=vec.end(); ++i)
    {
        int temp= i->score;
        for(auto j=vec.begin(); j!=vec.end(); ++j)
        {

            if(i==j)
                continue;
            if(dominates(*i,*j))
            {

                temp++;

            }

        }
        i->score=temp;
    }
}
void select_top_k(int k,vector<pair<int,int>>& m)
{
    ofstream outFile;
    outFile.open("naive output.txt", ios::out);


    vector<pair<int,int>>::iterator p;
    p=m.begin();
    cout<<"id"<<"\t"<<"score"<<endl;
    for(int i=1 ; i<=k; i++)
    {
        outFile<<(*p).first<<"\t"<<(*p).second<<endl;
        cout<<(*p).first<<"\t"<<(*p).second<<endl;
        p++;

    }
    outFile.close();

}

void select_all(vector<pair<int,double>>& m,map<int,string>&id_name)
{
    vector<pair<int,double>>::iterator p;
    ofstream myFile("final_Output_naive.csv");
     myFile<<"ID"<<","<<"NAME"<<","<<"SCORE"<<"\n";

    //cout<<"id"<<"\t"<<"score"<<endl;
//sort(m.begin(),m.end(),sortBySecondElement());
    for(p=m.begin(); p!=m.end(); p++)
    {
        ///cout<<(*p).first<<"\t"<<id_name[(*p).first]<<"\t"<<(*p).second<<endl;
        myFile<<(*p).first<<","<<id_name[(*p).first]<<","<<(*p).second<<endl;

    }
     myFile.close();

}

vector<pair<int,double>>& calculation(vector<movie>&v,vector<pair<int,double>>&m)
{

    vector<movie>::iterator it;
    for (it = v.begin(); it < v.end(); it++)
        m.push_back(make_pair(it->id,it->score));

    //sort(m.begin(),m.end(),greater<>());
    sort(m.begin(),m.end(),sortbysec);

    return m;


}
vector<pair<int,double>> initialization(vector<movie>&v,vector<pair<int,double>>&m)
{



    set_score(v);
    m=calculation(v,m);
    return m;

}
void take_input(vector<movie>&v,map<int,string>&id_name)
{
    /* int num;

    cout<<"enter number of movies: ";
    cin>>num;
    cout<<"enter 3 rating from audience for each of these movies"<<endl;
    for(int i=1;i<=num;i++){
     int a,b,c;
     cout<<"For movie "<<i<<" enter rating from audience 1: ";
     cin>>a;
     cout<<"For movie "<<i<<" enter rating from audience 2: ";
     cin>>b;
     cout<<"For movie "<<i<<" enter rating from audience 3: ";
     cin>>c;
     v.push_back(movie(a,b,c));*/
    /** int a=1,b=2,c=3;
    for(int i=1;i<=100;i++){
     v.push_back(movie(a,b,c));
     a++;
     b++;
     c++;
    }
    **/





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
        v.push_back(movie(id,gp,pts,reb,ast,name));
        //cout<<name<<endl;


        id++;








    }
    fin.close();






}
int movie::total_movies = 0;

int main()
{
//int k;
//cout<<"Enter k:";
//cin>>k;

    vector<movie>v;
    vector<pair<int,double>>m;
auto start = high_resolution_clock::now();
    map<int,string>id_name;
    take_input(v,id_name);


    m=initialization(v,m);

//select_top_k(k,m);

    select_all(m,id_name);

auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; double time_taken =
      chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(9);
    cout << " sec" << endl;





}

