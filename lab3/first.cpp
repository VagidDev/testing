#include<iostream>
#include<iomanip>
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

bool is_associate() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][matrix[b][c]] != matrix[matrix[a][b]][c])
                    return false;
            
    return true;
}

bool is_medial() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                for (int d = 0; d < side; ++d)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[a][c]][matrix[b][d]])
                        return false;
            
    return true;
}

bool is_paramedial() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                for (int d = 0; d < side; ++d)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[d][b]][matrix[c][a]])
                        return false;
            
    return true;
}

bool is_biocommutative() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                for (int d = 0; d < side; ++d)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[d][c]][matrix[b][a]])
                        return false;
            
    return true;
}

bool is_AG() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[matrix[a][b]][c] != matrix[matrix[c][b]][a])
                    return false;
            
    return true;
}

bool is_GA() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[matrix[a][b]][c] != matrix[c][matrix[b][a]])
                    return false;
            
    return true;
}

bool is_GA_1() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[matrix[a][b]][c] != matrix[matrix[c][a]][b])
                    return false;
            
    return true;
}

bool is_AD() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][matrix[b][c]] != matrix[c][matrix[b][a]])
                    return false;
            
    return true;
}

bool is_DA() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][matrix[b][c]] != matrix[c][matrix[a][b]])
                    return false;
            
    return true;
}


bool is_hexa() 
{
    //TODO: create logic
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][matrix[b][c]] != matrix[c][matrix[a][b]])
                    return false;
            
    return true;
}

bool is_distribute_right() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[matrix[a][b]][c] != matrix[matrix[a][b]][matrix[b][c]])
                    return false;
            
    return true;
}

bool is_distribute_left() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[matrix[a][b]][c] != matrix[matrix[a][b]][matrix[b][c]])
                    return false;
            
    return true;
}

bool is_digit_right() 
{
    //TODO: create algoritm        
    return true;
}

bool is_digit_left() 
{
    //TODO: create algoritm        
    return true;
}

bool is_digit() 
{
    //TODO: create algoritm        
    return true;
}

bool is_urod() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][b] != matrix[matrix[a][b]][matrix[b][c]])
                    return false;
           
    return true;
}

bool is_reverse_urod() 
{
    for (int a = 0; a < side; ++a) 
        for (int b = 0; b < side; ++b)
            for (int c = 0; c < side; ++c)
                if (matrix[a][b] != matrix[matrix[c][a]][matrix[c][b]])
                    return false;
           
    return true;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    string line;
    cout<<"Input the file name: ";
    cin>>line;
    create_and_fill_array(line);

    for (int i = 0; i < side; ++i, cout<<endl) 
        for (int j = 0; j < side; j++)
            cout<<matrix[i][j]<<" ";
        
    //WARNING: functions don't work correct!!!!! 
    //TODO: fix it
    cout<<endl<<"Ассоциативность"<<setw(10)<<is_associate();
    cout<<endl<<"Медиальность"<<setw(10)<<is_medial();
    /*cout<<endl<<"Парамедиальность"<<setw(10)<<is_paramedial();
    cout<<endl<<"Бикоммутативность"<<setw(10)<<is_biocommutative();
    cout<<endl<<"AG-группоид"<<setw(10)<<is_AG();
    cout<<endl<<"GA-группоид"<<setw(10)<<is_GA();
    cout<<endl<<"GA-1 группоид"<<setw(10)<<is_GA_1();
    cout<<endl<<"AD-группоид"<<setw(10)<<is_AD();
    cout<<endl<<"DA-группоид"<<setw(10)<<is_DA();
    cout<<endl<<"Гексагональность"<<setw(10)<<is_hexa();
    cout<<endl<<"Дистрибутивность справа"<<setw(10)<<is_distribute_right();
    cout<<endl<<"Дистрибутивность слева"<<setw(10)<<is_distribute_left();
    cout<<endl<<"Единица справа"<<setw(10)<<is_digit_right();
    cout<<endl<<"Единица слева"<<setw(10)<<is_digit_left();
    cout<<endl<<"Единица"<<setw(10)<<is_digit();
    cout<<endl<<"Уорд"<<setw(10)<<is_urod();
    cout<<endl<<"Обратный Уорд"<<setw(10)<<is_reverse_urod();*/

    cout<<endl;

    return  0;    
} // namespace std;
