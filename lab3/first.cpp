#include<iostream>
#include<fstream>

using namespace std;

int **matrix;
int side;

int get_number_of_strings(string filename) {
    ifstream file(filename);
    
    int count = 0;
    string line;

    while (getline(file, line))
        if (!line.empty()) {
            count++;
        }
    
    file.close();
    return count;
}

void create_and_fill_array(string filename) {
    side = get_number_of_strings(filename);
    matrix = new int*[side];

    for (int i = 0; i < side; ++i) {
        matrix[i] = new int[side];
    }

    ifstream file(filename);

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            file >> matrix[i][j];
        }
    }
    
}

int main() 
{
    string line;
    cout<<"Input the file name: ";
    cin>>line;
    create_and_fill_array(line);

    for (int i = 0; i < side; ++i, cout<<endl) 
        for (int j = 0; j < side; j++)
            cout<<matrix[i][j]<<" ";
        

    return  0;    
} // namespace std;
