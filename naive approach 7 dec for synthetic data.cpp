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

    int a[100];
    int id;

    int score;

    movie(int iid,int x[],int c)
    {
        id=iid;
        for(int i=0; i<c; ++i)
            a[i] = x[i];

        score=0;


    }

};
bool dominates(movie x,movie y,int c)
{

    vector<double>pos;
    vector<double>observed_pos;


    for(int i=0; i<c; i++)
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
void set_score(vector<movie>&vec,int c)
{

    for(auto i=vec.begin(); i!=vec.end(); ++i)
    {
        int temp= i->score;
        for(auto j=vec.begin(); j!=vec.end(); ++j)
        {

            if(i==j)
                continue;

            if(dominates(*i,*j,c))
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
void select_all(vector<pair<int,int>>& m)
{
    vector<pair<int,int>>::iterator p;
    cout<<"id"<<"\t"<<"score"<<endl;
//sort(m.begin(),m.end(),sortBySecondElement());
    for(p=m.begin(); p!=m.end(); p++)
    {
        cout<<(*p).first<<"\t"<<(*p).second<<endl;
    }

}

vector<pair<int,int>>& calculation(vector<movie>&v,vector<pair<int,int>>&m)
{

    vector<movie>::iterator it;
    for (it = v.begin(); it < v.end(); it++)
        m.push_back(make_pair(it->id,it->score));

    //sort(m.begin(),m.end(),greater<>());
    sort(m.begin(),m.end(),sortbysec);

    return m;


}
vector<pair<int,int>> initialization(vector<movie>&v,vector<pair<int,int>>&m,int c)
{



    set_score(v,c);
    m=calculation(v,m);
    return m;

}
int str2int (const string &str) {
  stringstream ss(str);
  int num;
  if((ss >> num).fail())
  {
      //ERROR
  }
  return num;
}
vector<movie>& take_input(vector<movie>&v,int Count)
{

    fstream fin;

    fin.open("synthetic_500.csv", ios::in);


    int id;
    int a[Count+1];
    string line, word, temp;
    vector<string> row;
    while (fin >> temp)
    {
//cout<<temp<<endl;
        row.clear();

        //getline(fin, line);
        line=temp;

//cout<<line<<endl;
        stringstream s(line);


        // read every column data of a row and
        // store it in a string variable, 'word'


        while (getline(s, word, ','))
        {
            //cout<<"hello"<<endl;

            // add all the column data
            // of a row to a vector
            row.push_back(word);

        }


        //istringstream(row[0])>>id;
        id=str2int(row[0]);
        //cout<<"hello"<<endl;
        //cout<<id<<"\t";
        for(int j=0; j<Count; j++)
            {istringstream(row[j+1])>>a[j];

            }




        v.push_back(movie(id,a,Count));

//cout<<"hi";








    }
    return v;


    }

    int main()
    {


        vector<movie>v;
        int c=30;
        vector<pair<int,int>>m;
        auto start = high_resolution_clock::now();
        v=take_input(v,c);

        int k=1000;

//        for(int i=0; i<v.size(); i++)
//        {
//            cout<<v[i].id<<"\t";
//            for(int j=0; j<c; j++)
//            {
//                cout<<v[i].a[j]<<"\t";
//            }
//            cout<<"\n";
//        }


m=initialization(v,m,c);

//select_top_k(k,m);

select_all(m);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;
        double time_taken =
            chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

        time_taken *= 1e-9;

        cout << "Time taken by program is : " << fixed
             << time_taken << setprecision(9);
        cout << " sec" << endl;





    }
