#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

typedef pair<int, int> MyPairType;

// Function to sort by second element, and by first element if second elements are equal
bool sortbysec(const pair<int, int> &a, const pair<int, int> &b) {
    if (a.second > b.second) return true;
    if (a.second < b.second) return false;
    return a.first < b.first;
}

// Functor for comparing pairs by second element (ascending)
struct CompareSecond {
    bool operator()(const MyPairType& left, const MyPairType& right) const {
        return left.second < right.second;
    }
};

// Functor for sorting pairs by second element (descending)
struct sortBySecondElement {
    bool operator()(const MyPairType& left, const MyPairType& right) const {
        return left.second > right.second;
    }
};

// Function to load dataset from a CSV file and initialize the dataset and id_name map
void make_dataset(vector<vector<double>>& dataset, map<int, string>& id_name) {
    fstream fin;
    fin.open("database.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    int id = 0;

    // Skip header
    getline(fin, line);

    // Read data line by line
    while (fin >> temp) {
        row.clear();
        getline(fin, line);
        stringstream s(line);

        // Parse each row
        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        // Extract attributes from the row
        string name = row[0];
        int gp;
        double pts, reb, ast;

        stringstream(row[4]) >> gp;
        istringstream(row[17]) >> pts;
        istringstream(row[18]) >> reb;
        istringstream(row[20]) >> ast;

        id_name[id] = name;
        dataset.push_back({gp, pts, reb, ast});
        id++;
    }
    fin.close();
}

// Function to determine if movie x dominates movie y
bool dominates(vector<double> x, vector<double> y) {
    vector<int> pos, observed_pos;

    // Compare each attribute
    for (int i = 0; i <= 3; i++) {
        if (x[i] == -1 || y[i] == -1) continue;  // Skip missing values

        observed_pos.push_back(i);
        if (x[i] < y[i]) return false;  // x doesn't dominate if any attribute is smaller
        if (x[i] == y[i]) pos.push_back(i);  // Track equal attributes
    }

    return pos != observed_pos;  // x dominates only if it has strictly better attributes
}

// Function to calculate the domination score for each movie
map<int, int>& score_calculation(vector<vector<double>>& dataset, map<int, int>& score_all) {
    int pos = 0;

    for (auto i = dataset.begin(); i < dataset.end(); i++) {
        int score = 0;
        for (auto j = dataset.begin(); j < dataset.end(); j++) {
            if (i == j) continue;
            if (dominates(*i, *j)) score++;
        }
        score_all[pos++] = score;  // Assign score to the current movie
    }

    return score_all;
}

// Function to calculate the maximum possible score for each movie
vector<pair<int, int>>& max_score_calculation(vector<vector<double>>& dataset, vector<pair<int, int>>& max_score_all) {
    int pos = 0;

    for (auto i = dataset.begin(); i < dataset.end(); i++) {
        vector<double> t;
        for (int k = 0; k <= 3; k++) {
            if ((*i)[k] == -1) {
                t.push_back(20);  // Assign a high value for missing data
            } else {
                int temp = (*i)[k];
                int c = 0;
                for (auto j = dataset.begin(); j < dataset.end(); j++) {
                    if (i == j) continue;
                    if ((*j)[k] == -1 || (*j)[k] <= temp) c++;
                }
                t.push_back(c);  // Count how many movies have a lower or equal value
            }
        }
        max_score_all.push_back(make_pair(pos, *min_element(t.begin(), t.end())));  // Minimum value is the max score
        pos++;
    }

    sort(max_score_all.begin(), max_score_all.end(), sortbysec);  // Sort movies by max score
    return max_score_all;
}

// Upper-bound-based scoring function to select top-k movies
vector<int>& ubb(vector<pair<int, int>> max_score_all, int k, vector<vector<double>>& dataset, map<int, string> id_name) {
    vector<int> selected_movies;
    vector<pair<int, int>> sc_score;
    int tau = -1;

    auto score_all = score_calculation(dataset, *(new map<int, int>));

    for (auto& max_score : max_score_all) {
        int o = max_score.first;
        if (max_score.second <= tau) break;

        int score = score_all[o];
        if (score >= tau || tau < 0) {
            sc_score.push_back(make_pair(o, score));
            if (sc_score.size() > k) {
                sc_score.erase(remove_if(sc_score.begin(), sc_score.end(), [tau](auto& p) { return p.second == tau; }), sc_score.end());
            }
            if (sc_score.size() == k) {
                tau = min_element(sc_score.begin(), sc_score.end(), CompareSecond())->second;  // Update tau
            }
        }
    }

    // Output the selected top-k movies
    ofstream myFile("final_Output_ubb.csv");
    myFile << "ID,NAME,SCORE\n";
    for (auto& p : sc_score) {
        myFile << p.first << "," << id_name[p.first] << "," << p.second << endl;
    }
    myFile.close();

    return selected_movies;
}

int main() {
    vector<vector<double>> dataset;
    map<int, string> id_name;
    vector<pair<int, int>> max_score_all;

    auto start = high_resolution_clock::now();

    make_dataset(dataset, id_name);
    max_score_all = max_score_calculation(dataset, max_score_all);
    int k = 10;  // Example: Top-10 movies
    ubb(max_score_all, k, dataset, id_name);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    double time_taken = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
    time_taken *= 1e-9;
    cout << "Time taken by program: " << fixed << time_taken << setprecision(9) << " sec" << endl;

    return 0;
}
