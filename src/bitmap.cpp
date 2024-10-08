#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

bool cmp(const pair<int, double>& a, const pair<int, double>& b) {
    if (a.second > b.second)
        return true;
    else if (a.second < b.second)
        return false;
    return a.first < b.first;
}

vector<double> Union(vector<double>& a, vector<double>& b, int n) {
    vector<double> result(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        result[i] = (a[i] == 1 && b[i] == 1) ? 1 : 0;
    }
    a = result;
    return a;
}

vector<double> Or(vector<double>& a, vector<double>& b, int n) {
    vector<double> result(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        result[i] = (a[i] == 0 && b[i] == 0) ? 0 : 1;
    }
    a = result;
    return a;
}

void bitmap_matrix(vector<vector<double>> input, map<int, string> id_name, int n, int dimension) {
    vector<double> temp_vect;
    vector<pair<int, double>> result;
    vector<double> high_values;

    int s, t;
    int d[10000];
    set<double, greater<double>> s1;

    // Generate distinct values in each dimension
    for (int j = 1; j <= dimension; j++) {
        for (int i = 0; i < n; i++) {
            s1.insert(input[i][j]);
        }
        d[j - 1] = s1.size();
        for (auto& value : s1) {
            temp_vect.push_back(value);
        }
        s1.clear();
    }

    // Initialize bitmap matrix
    n = n + 1;
    double bitmap[n][temp_vect.size() + 2] = {0};
    for (int i = 1; i < n; i++) {
        bitmap[i][0] = input[i - 1][0];
    }
    for (int i = 2; i < temp_vect.size() + 2; i++) {
        bitmap[0][i] = temp_vect[i - 2];
    }

    // Populate bitmap matrix
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= dimension; j++) {
            double item = input[i - 1][j];
            if (j == 1) {
                s = 2;
                t = d[j - 1] + 2;
            } else {
                s = t;
                t = s + d[j - 1];
            }
            for (int k = s; k < t; k++) {
                bitmap[i][k] = 1;
                if (item == bitmap[0][k]) {
                    fill(bitmap[i] + k, bitmap[i] + t, 0);
                    break;
                }
            }
        }
    }

    // Calculate scores
    for (int i = 1; i < n; i++) {
        vector<double> A(n - 1, 0.0), B(n - 1, 1.0);
        for (int j = 1; j <= dimension; j++) {
            double item = input[i - 1][j];
            if (j == 1) {
                s = 2;
                t = d[j - 1] + 2;
            } else {
                s = t;
                t = s + d[j - 1];
            }
            for (int k = s; k < t; k++) {
                if (item == bitmap[0][k]) {
                    vector<double> a, b;
                    for (int l = 1; l < n; l++) {
                        a.push_back(bitmap[l][k]);
                        b.push_back((bitmap[0][k] == bitmap[0][s]) ? 1 : bitmap[l][k - 1]);
                    }
                    A = Or(A, a, n);
                    B = Union(B, b, n);
                    break;
                }
            }
        }
        for (int i = 0; i < n - 1; i++) {
            A = Union(A, B, n);
        }
        result.push_back(make_pair(input[i - 1][0], count(A.begin(), A.end(), 1)));
    }

    // Sort and output results
    sort(result.begin(), result.end(), cmp);
    ofstream myFile("final_Output_bitmap.csv");
    myFile << "ID,NAME,SCORE\n";
    for (const auto& res : result) {
        myFile << res.first << "," << id_name[res.first] << "," << res.second << "\n";
    }
    myFile.close();
}

void make_dataset(vector<vector<double>>& dataset, map<int, string>& id_name, int dimension) {
    fstream fin;
    fin.open("database.csv", ios::in);
    ofstream myFile("output.csv");
    myFile << "Name,GP,PPG,RPG,APG\n";

    vector<string> row;
    string line, word, temp, name;
    int id = 0, gp;
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
        stringstream(row[4]) >> gp;
        stringstream(row[17]) >> pts;
        stringstream(row[18]) >> reb;
        stringstream(row[20]) >> ast;

        myFile << name << "," << gp << "," << pts << "," << reb << "," << ast << "\n";
        id_name[id] = name;
        dataset.push_back({double(id), double(gp), pts, reb, ast});
        id++;
    }
    myFile.close();
}

int main() {
    vector<vector<double>> input;
    map<int, string> id_name;
    int dimension = 4;

    auto start = high_resolution_clock::now();

    make_dataset(input, id_name, dimension);
    bitmap_matrix(input, id_name, input.size(), dimension);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: " << duration.count() << " microseconds\n";

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    time_taken *= 1e-9;
    cout << "Time taken by program is : " << fixed << time_taken << setprecision(9) << " sec\n";

    return 0;
}
