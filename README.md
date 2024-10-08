# Bitmap Matrix Algorithm for NBA Player Query Processing

This repository contains a C++ implementation of a Bitmap Matrix algorithm designed to process NBA player statistics and compute scores based on predefined performance criteria. The program converts player statistics into a bitmap matrix and applies various operations to determine the score of each player.

## 📊 Dataset

This implementation uses the [2021-22 NBA Player Stats dataset from NBAstuffer](https://www.nbastuffer.com/2021-2022-nba-player-stats/) (accessed January 23, 2022). The dataset contains comprehensive statistics for NBA players from the 2021-2022 season.

## ✨ Features

- Processes NBA player statistics from CSV input (`database.csv`)
- Converts player data into an efficient bitmap matrix representation
- Performs OR and UNION operations on the bitmap matrix for score computation
- Generates detailed output in CSV format (`final_Output_bitmap.csv`)
- Includes player ID, name, and computed performance scores
- Optimized computation using custom sorting and bitmap-based techniques

## 📁 File Structure

```
.
├── main.cpp                    # Main implementation of the bitmap matrix algorithm
├── database.csv               # Input dataset with NBA player stats
├── final_Output_bitmap.csv    # Intermediate processed data
└── output.csv                # Generated output with calculated scores 
```

## 🔧 Dependencies

The implementation uses standard C++ libraries only:
- `<bits/stdc++.h>` for comprehensive standard library access
- `<chrono>` for performance measurement

## 🚀 Getting Started

### Prerequisites

- C++ compiler (GCC recommended)
- Input data in CSV format

### Installation & Running

1. Clone the repository:
```bash
git clone https://github.com/yourusername/bitmap-matrix-algorithm.git
cd bitmap-matrix-algorithm
```

2. Compile the code:
```bash
g++ -o bitmap_matrix main.cpp
```

3. Run the program:
```bash
./bitmap_matrix
```

### Input Format

The `database.csv` should contain the following columns:
- Name
- GP (Games Played)
- PPG (Points Per Game)
- RPG (Rebounds Per Game)
- APG (Assists Per Game)

### Output Format

The program generates `final_Output_bitmap.csv` with the following structure:

```csv
ID,NAME,SCORE
1,Joel Embiid,85
2,Giannis Antetokounmpo,82
...
```

## ⚡ Performance

The program provides execution time metrics in both microseconds and seconds. Example output:

```
Time taken by function: 10000 microseconds
Time taken by program is: 0.001000000 sec
```

## 🛠️ Customization

You can modify the code to analyze different aspects of player performance:

1. Adjust the number of dimensions (currently set to 4)
2. Modify the scoring criteria in the bitmap operations
3. Add additional statistical categories for analysis

## 📝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is open-source and available for modification and use in any application. See the LICENSE file for details.

