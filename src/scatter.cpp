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

vector< vector<int> > scatterData(vector< vector<int> > matrix) {
	
    vector<int> random_indices(total_elements), random_values(total_elements);
    int matrix_size = matrix.size();
    int total_elements = 1000;
    
   
    for(int idx = 0; idx < total_elements; idx++) {
        random_indices[idx] = rand() % (matrix_size * matrix_size);
        random_values[idx] = rand();
    }

    for(int idx = 0; idx < total_elements; idx++) {
        int row_position = random_indices[idx] / matrix_size;
        int col_position = random_indices[idx] % matrix_size;
        matrix[row_position][col_position] = random_values[idx];
    }
    
    return matrix;
}


void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
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
	vector< vector<int> > C = scatterData(result.A);
    parsec_roi_end();
	//printMatrix(C);
	return 0;
}
