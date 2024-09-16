#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{
}

void parsec_roi_end() 
{
}
struct Result {
    vector< vector<int> > A;
};

Result read(string filename) {
    vector< vector<int> > A;
    Result ab;
    string line;
    ifstream infile;
    infile.open (filename.c_str());

    int i = 0;
    while (getline(infile, line) && !line.empty()) {
        istringstream iss(line);
        A.resize(A.size() + 1);
        int a, j = 0;
        while (iss >> a) {
            A[i].push_back(a);
            j++;
        }
        i++;
    }
    infile.close();
    ab.A = A;
    return ab;
}

vector<vector<int>> convolve(const vector<vector<int>>& matrix) {
    int matrix_size = matrix.size();
    srand(static_cast<unsigned int>(time(0)));  

    
    vector<vector<int>> kernel = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    vector<vector<int>> output(matrix_size, vector<int>(matrix_size, 0));

    
    for (int row = 1; row < matrix_size - 1; ++row) {
        for (int col = 1; col < matrix_size - 1; ++col) {
            double conv_sum = 0.0;

            
            for (int k_row = -1; k_row <= 1; ++k_row) {
                for (int k_col = -1; k_col <= 1; ++k_col) {
                    conv_sum += matrix[row + k_row][col + k_col] * kernel[k_row + 1][k_col + 1];
                }
            }

            output[row][col] = conv_sum;  
        }
    }

    return output;  
}


// Updated to print a 1D vector
void printVector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i + 1 != vec.size()) {
            cout << "\t";
        }
    }
    cout << endl;
}

int main (int argc, char* argv[]) {
    srand(time(0));
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read (filename);
    parsec_roi_begin();
    vector<vector<int>> C = convolve(result.A);  // Corrected to vector<int>
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    //printVector(C);
    
    return 0;
}
