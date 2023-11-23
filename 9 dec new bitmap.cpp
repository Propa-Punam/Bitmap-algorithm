#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
bool cmp(const pair<int,double> &a,
         const pair<int,double> &b)
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

vector<double> Union(vector<double>&a,vector<double>&b,int n)
{
    vector<double>result(n-1,0);
    for(int i=0; i<n-1; i++)
    {

        if(a[i]==1 && b[i]==1)
        {
            result[i]=1;
        }
        else
        {
            result[i]=0;
        }

    }
//for(int i=0;i<n-1;i++)
//cout<<result[i]<<endl;
    a=result;
    return a;
}


vector<double> Or(vector<double>&a,vector<double>&b,int n)
{
    vector<double>result(n-1,0);
    for(int i=0; i<n-1; i++)
    {

        if(a[i]==0 && b[i]==0)
        {
            result[i]=0;
        }
        else
        {
            result[i]=1;
        }

    }
//for(int i=0;i<n-1;i++)
//cout<<result[i]<<"\t";
//cout<<"\n";
    a=result;
    return a;
}



void bitmap_matrix(vector<vector<double>>input, int n,const int dimension)
{

    vector<double>temp_vect;
    vector<pair<int,double>>result;
    vector<pair<int,int>>max_bit_score;
    vector<pair<int,int>>max_score;
    vector<double>high_values;
    const int c=dimension;
    vector<double>::iterator ip;

    int s,t;



    vector<vector<double>>first_line(input.size());
    vector<double>v2;
    //int d[4];
    for(int i=0; i<input.size(); i++)
    {


        //first_line[i]=input[i];
        copy(input[i].begin(), input[i].end(), back_inserter(first_line[i]));
        sort(first_line[i].begin(), first_line[i].end(), greater<double>());
        ip = std::unique(first_line[i].begin(), first_line[i].begin() + input[i].size());
        first_line[i].resize(std::distance(first_line[i].begin(), ip));


    }

    map<int,  bitset<1000>> map_bitmap;
//cout<<"size"<<input.size();

    for(int i=0; i<input.size(); i++)
    {
        for(int j=0; j<c; j++)
        {

            if(first_line[i][j]<input[i][j])
        {
            bitset<1000> set8;
            set8.set(j, 1);
                map_bitmap.insert({first_line[i][j],set8});
            }

        }
    }

//        for(int j=0;j<first_line.size();j++){
//
//        }
//
//}
//

//  for (auto i = first_line.begin(); i != first_line.end(); ++i){
//    for (auto j = (*i).begin(); j != (*i).end(); ++j)
//        cout << *j << " ";
//        cout<<"\n";
//
//  }
//


    /*
     int d[10000];
     set<double, greater<double> > s1;
     for (int j=1; j<=dimension; j++)
     {
         for(int i=0; i<n; i++)
         {

             s1.insert(input[i][j]);
             //cout<<input[i][j]<<endl;
         }
         d[j-1]=s1.size();



         set<double, greater<double> >::iterator itr;
         for (itr = s1.begin(); itr != s1.end(); itr++)
         {

             //cout<<*itr<<endl;
             temp_vect.push_back(*itr);

         }
         s1.clear();

     }
     n=n+1;
     double bitmap[n][temp_vect.size()+2]= {0};
     bitmap[0][0]=bitmap[0][1]=0.0;

     for (int i=1; i<n; i++)
     {

         bitmap[i][0]=input[i-1][0];
         bitmap[i][1]=0;

     }
     for (int i=2; i<temp_vect.size()+2; i++)
     {
         bitmap[0][i]=temp_vect[i-2];

     }

     for(int i=1; i<n; i++)
     {
         for (int j=1; j<=dimension; j++)
         {
             // cout<<"here i-1 is "<<i-1<<endl;
             double item=input[i-1][j];



            // cout<<item<<endl;
             if(j==1)
             {
                 s=2;
                 t=d[j-1]+2;
                // cout<<d[j]<<endl;
                //cout<<s<<"\t"<<t<<"\n";


             }

             else
             {
    //                for(int it=0;it<j;it++){
    //                s+=d[it];
    //                }
    //                s+=2;
    //                t=s+d[j];
                   s=t;
                   t=s+d[j-1];
                 //cout<<d[j]<<endl;
               // cout<<s<<"\t"<<t<<"\n";

             }



             for(int k=s; k<t; k++)
             {

                 bitmap[i][k]=1;
                 if(item==bitmap[0][k])
                 {
                     for(int l=k; l<t; l++)
                     {
                         bitmap[i][l]=0.0;



                     }
                     break;
                 }

             }



         }




     }

    //    cout<<"\n Two Dimensional Array is : \n";
    //    for(int i=0; i<n; i++)
    //    {
    //        for(int j=0; j<temp_vect.size()+2; j++)
    //        {
    //            cout<<" "<<bitmap[i][j]<<" ";
    //        }
    //        cout<<"\n";
    //    }
    //


     for(int i=1; i<n; i++)
     {
         vector<double>a;
         vector<double>A(n-1,0.0);
         vector<double>b;
         vector<double>B(n-1,1.0);
      /// int c=INT_MAX;
         vector<double>C;



         for (int j=1; j<=dimension; j++)
         {

             double item=input[i-1][j];
             //cout<<item<<endl;
             if(j==1)
             {
                 s=2;
                 t=d[j-1]+2;
             }
              else
             {
    //                for(int it=0;it<j;++it){
    //                s+=d[it];
    //                }
    //                s+=2;
    //                t=s+d[j];
                    s=t;
                   t=s+d[j-1];

             }
             //cout<<s<<"\t"<<t<<endl;



             for(int k=s; k<t; k++)
             {


                 if(item==bitmap[0][k])
                 {
                     for(int l=1; l<n; l++)
                     {
                         a.push_back(bitmap[l][k]);

                         if(bitmap[0][k]== bitmap[0][s])
                         {
                             b.push_back(1);

                         }
                         else
                         {

                             b.push_back(bitmap[l][k-1]);
                         }




                     }




    //                         vector<int> result;
                    /// C=b;
                     ///C[i-1]=0;

                  ///  c=min(c,count(C.begin(),C.end(),1));


                     A=Or(A,a,n);
                     B=Union(B,b,n);

                     a.clear();
                     b.clear();
                    // C.clear();

                     break;
                 }


             }









         }

       ///  max_score.push_back(make_pair(i,c));

         //cout<<i<<endl;
         for (int i =0; i <n-1 ; ++i)
         {
             A=Union(A,B,n);
         }


         // cout<<i<<endl;
    //        for (auto i = B.begin(); i != B.end(); ++i)
    //
    //        cout<<count(B.begin(),B.end(),1)<<endl;

    //        result.push_back(make_pair(i,count(A.begin(),A.end(),1)));




    //         cout<<i<<endl;
    //        for (auto i = A.begin(); i != A.end(); ++i)
    //        cout << *i << " ";
    //        cout<<endl;




         // cout<<count(A.begin(),A.end(),0)<<endl;
        // B[i-1]=0;
         ///max_bit_score.push_back(make_pair(i,count(B.begin(),B.end(),1)));


         ///string name=id_name[input[i-1][0]];
         result.push_back(make_pair(input[i-1][0],count(A.begin(),A.end(),1)));




    //        for (auto i = B.begin(); i != B.end(); ++i)
    //
    //        {
    //
    //            cout<<*i;
    //        }
    //
    //        cout<<endl;








     }
     sort(result.begin(),result.end(),cmp);
    /// sort(max_bit_score.begin(),max_bit_score.end(),cmp);
     /// sort(max_score.begin(),max_score.end(),cmp);

    ofstream myFile("final_Output_bitmap.csv");
    myFile<<"ID"<<","<<"NAME"<<","<<"SCORE"<<"\n";

     for (auto i = result.begin(); i != result.end(); ++i)
     {
         //cout << (*i).first<<"\t\t\t"<< (*i).second <<endl;
         //outFile << (*i).first-1<<"\t"<< (*i).second <<endl;

         myFile<<(*i).first<<","<<(*i).second<<"\n";

     }
     myFile.close();

     //"\t"<< (*i).second <<endl;
     cout<<endl;
     */

}


int str2int (const string &str)
{
    stringstream ss(str);
    int num;
    if((ss >> num).fail())
    {
        //ERROR
    }
    return num;
}

void make_dataset(vector<vector<double>>&dataset,int c)
{


    // ifstream inFile;
    fstream fin;
    fin.open("transpose.csv", ios::in);

    double a[c+1];
    vector<string> row;
    string line, word, temp;


    // int id=0;



    getline(fin, line);

    while (fin >> temp)
    {


        row.clear();
//cout<<temp;
//
//        // read an entire row and
//        // store it in a string variable 'line'
        line=temp;


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

        //cout<<"hello"<<endl;
        //cout<<id<<"\t";
        for(int j=0; j<c; j++)
        {
            istringstream(row[j])>>a[j];

        }





        vector<double>m;


        m.insert(m.begin(),a, a+c ) ;

        dataset.push_back(m);
        //cout<<name<<endl;












    }
    fin.close();


}



int main()
{
//    int n=5;
//    int input[n][3] =
//    {
//
//
//
//    };
//int input[100][3];
    time_t begin = time(NULL);
    vector<vector<double>>input;



    //int c;
    const int c = []() -> int
    {
        int t;
        t=1000;
        return t;
    }();
    // c=1000;

    make_dataset(input,c);
//    print dataset
//cout<<"input size"<<input.size()<<endl;
//    for(auto i=0;i<input.size();i++){
//        for(auto j=0;j<c;j++){
//            cout<<input[i][j]<<"\t";
//        }
//        cout<<"\n\n\n";
//    }
///printing map
//map<int,string>::iterator itr;
//
//    for (itr = id_name.begin(); itr != id_name.end(); ++itr) {
//        cout << '\t' << itr->first
//             << '\t' << itr->second << '\n';
//    }
//    cout << endl;
//auto start = high_resolution_clock::now();
//
    bitmap_matrix(input,input.size(),c);
//    time_t end = time(NULL);
//    printf("The elapsed time is %d seconds", (end - begin));
//    auto stop = high_resolution_clock::now();
//auto duration = duration_cast<microseconds>(stop - start);
//
//  cout << "Time taken by function: "
//         << duration.count() << " microseconds" << endl; double time_taken =
//      chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
//
//    time_taken *= 1e-9;
//
//    cout << "Time taken by program is : " << fixed
//         << time_taken << setprecision(9);
//    cout << " sec" << endl;
    return 0;


}


