#include <bits/stdc++.h>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

bool sortbysec(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second > b.second) {
        return true;
    } else if (a.second < b.second) {
        return false;
    } else {
        return a.first < b.first;
    }
}

class movie {
public:
    static int total_movies;
    double a[5];
    int id;
    string name;
    double score;

    movie(int id1, double x, double y, double z, double p, string name1) {
        a[0] = x;
        a[1] = y;
        a[2] = z;
        a[3] = p;
        score = 0.0;
        id = id1;
        name = name1;
    }
};

bool dominates(movie x, movie y) {
    vector<double> pos, observed_pos;
    for (int i = 0; i <= 3; i++) {
        if (x.a[i] == -1 || y.a[i] == -1) {
            continue;
        }

        observed_pos.push_back(i);
        if (x.a[i] < y.a[i]) {
            return false;
        }
        if (x.a[i] == y.a[i]) {
            pos.push_back(i);
        }
    }

    if (pos == observed_pos) {
        return false;
    }

    return true;
}

void set_score(vector<movie> &vec) {
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        int temp = i->score;
        for (auto j = vec.begin(); j != vec.end(); ++j) {
            if (i == j) continue;
            if (dominates(*i, *j)) {
                temp++;
            }
        }
        i->score = temp;
    }
}

void select_all(vector<pair<int, double>> &m, map<int, string> &id_name) {
    ofstream myFile("final_Output_naive.csv");
    myFile << "ID,NAME,SCORE\n";

    for (auto p = m.begin(); p != m.end(); p++) {
        myFile << (*p).first << "," << id_name[(*p).first] << "," << (*p).second << endl;
    }
    myFile.close();
}

vector<pair<int, double>> &calculation(vector<movie> &v, vector<pair<int, double>> &m) {
    for (auto it = v.begin(); it < v.end(); it++) {
        m.push_back(make_pair(it->id, it->score));
    }
    sort(m.begin(), m.end(), sortbysec);
    return m;
}

vector<pair<int, double>> initialization(vector<movie> &v, vector<pair<int, double>> &m) {
    set_score(v);
    m = calculation(v, m);
    return m;
}

void take_input(vector<movie> &v, map<int, string> &id_name) {
    fstream fin;
    fin.open("database.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    string name;
    int gp, id = 0;
    double pts, reb, ast;

    getline(fin, line);
    while (fin >> temp) {
        row.clear();
        getline(fin, line);
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        name = row[0];
        stringstream geek(row[4]);
        geek >> gp;
        istringstream(row[17]) >> pts;
        istringstream(row[18]) >> reb;
        istringstream(row[20]) >> ast;

        id_name.insert({id, name});
        v.push_back(movie(id, gp, pts, reb, ast, name));
        id++;
    }
    fin.close();
}

int movie::total_movies = 0;

int main() {
    vector<movie> v;
    vector<pair<int, double>> m;
    map<int, string> id_name;

    auto start = high_resolution_clock::now();

    take_input(v, id_name);
    m = initialization(v, m);
    select_all(m, id_name);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    time_taken *= 1e-9;
    cout << "Time taken by program is: " << fixed << time_taken << setprecision(9) << " sec" << endl;

    return 0;
}
