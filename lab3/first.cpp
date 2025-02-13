#include<iostream>
#include<fstream>

using namespace std;

int **matrix;

void createAndFillArray() {
    int cols = 0, rows = 0;
    matrix = new int*[rows];

    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
}

int main() 
{
    

    return  0;    
} // namespace std;
