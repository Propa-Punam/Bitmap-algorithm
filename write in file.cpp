#include<bits/stdc++.h>
using namespace std;

int main()
{

//    ifstream inFile;
//    inFile.open("Numbers.txt", ios::out);
//    inFile >> myint >> myfloat;
//    inFile.close();
//    cout << "myint = " << myint << "; myfloat = " << myfloat << endl;
//    return 0;

    int randomNumber;
    //vector<vector<int>>database;
    ofstream myFile("synthetic_500.csv");
    ofstream outFile;
    outFile.open("Numbers.txt", ios::out);
    //outFile<<"ID\tAudience1\tAudience2\tAudience3\t\tType"<< endl;
    vector<int>m;
    for (int i = 0; i <10; i++)
    {
        outFile<<i<<"\t\t";
        myFile<<i<<",";

        for(int j=0; j<5; j++)
        {
            randomNumber = (rand() % 5) + 1;
           // m.push_back(randomNumber);
            outFile<<randomNumber<<"\t\t";
            myFile<<randomNumber<<",";

        }
        myFile<<"\n";
        outFile<<"\n";
        //randomNumber = (rand() % 3) + 1;
        //m.push_back(randomNumber);
        //outFile<<randomNumber<<"\n";
        //myFile<<randomNumber<<",";
        //database.push_back(m);
    }

    outFile.close();
    myFile.close();


}
