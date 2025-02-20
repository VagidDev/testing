#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

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

int** create_and_fill_array(string filename) {
    side = get_number_of_strings(filename);
    int** matrix = new int*[side + 1];

    for (int i = 0; i < side + 1; ++i) {
        matrix[i] = new int[side + 1];
    }

    ifstream file(filename);

    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            file >> matrix[i][j];
        }
    }
    file.close();
    return matrix;
}

bool is_associate(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[a][matrix[b][c]] != matrix[matrix[a][b]][c])
                    return false;
    return true;
}

bool is_medial(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                for (int d = 0; d < side; d++)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[a][c]][matrix[b][d]])
                        return false;
    return true;
}

bool is_paramedial(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                for (int d = 0; d < side; d++)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[d][b]][matrix[c][a]])
                        return false;
    return true;
}

bool is_biocommutative(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                for (int d = 0; d < side; d++)
                    if (matrix[matrix[a][b]][matrix[c][d]] != matrix[matrix[d][c]][matrix[b][a]])
                        return false;
    return true;
}

bool is_AG(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[matrix[a][b]][c] != matrix[matrix[c][b]][a])
                    return false;
    return true;
}

bool is_GA(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[matrix[a][b]][c] != matrix[c][matrix[b][a]])
                    return false;
    return true;
}

bool is_GA_1(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[matrix[a][b]][c] != matrix[matrix[c][a]][b])
                    return false;
    return true;
}

bool is_AD(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[a][matrix[b][c]] != matrix[c][matrix[b][a]])
                    return false;
    return true;
}

bool is_DA(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[a][matrix[b][c]] != matrix[c][matrix[a][b]])
                    return false;
    return true;
}

bool is_hexa(int** matrix) {
    for (int a = 0; a < side; a++)
        if (matrix[a][a] != a)
            return false;

    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            if (matrix[a][matrix[b][a]] != matrix[matrix[a][b]][a] || matrix[a][matrix[b][a]] != b)
                return false;
    return true;
}

bool is_distribute_right(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[matrix[a][b]][c] != matrix[matrix[a][c]][matrix[b][c]])
                    return false;
    return true;
}

bool is_distribute_left(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[c][matrix[a][b]] != matrix[matrix[c][a]][matrix[c][b]])
                    return false;
    return true;
}

bool is_digit_right(int** matrix) {
    for (int x = 0; x < side; x++) {
        bool has_unit = false;
        for (int e = 0; e < side; e++)
            if (matrix[x][e] == x) {
                has_unit = true;
                break;
            }
        if (!has_unit)
            return false;
    }
    return true;
}

bool is_digit_left(int** matrix) {
    for (int x = 0; x < side; x++) {
        bool has_unit = false;
        for (int e = 0; e < side; e++)
            if (matrix[e][x] == x) {
                has_unit = true;
                break;
            }
        if (!has_unit)
            return false;
    }
    return true;
}

bool is_digit(int** matrix) {
    return is_digit_left(matrix) && is_digit_right(matrix);
}

bool is_urod(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[a][b] != matrix[matrix[a][c]][matrix[b][c]])
                    return false;
    return true;
}

bool is_reverse_urod(int** matrix) {
    for (int a = 0; a < side; a++)
        for (int b = 0; b < side; b++)
            for (int c = 0; c < side; c++)
                if (matrix[a][b] != matrix[matrix[c][a]][matrix[c][b]])
                    return false;
    return true;
}

int main() 
{
    setlocale(LC_ALL, "Russian");

    int **matrix;


    string line;
    cout<<"Input the file name: ";
    cin>>line;
    
    matrix = create_and_fill_array(line); 

    for (int i = 0; i < side; ++i, cout<<endl) 
        for (int j = 0; j < side; j++)
            cout<<matrix[i][j]<<" ";
        
    //WARNING: functions don't work correct!!!!! 
    //TODO: fix it
    const int textWidth = 30;

    // Вывод с форматированием
    cout << "+---------------------------------+" << endl;
    cout << "| " << setw(textWidth) << left << "Ассоциативность            " << " | " << right << (is_associate(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Медиальность               " << " | " << right << (is_medial(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Парамедиальность           " << " | " << right << (is_paramedial(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Бикоммутативность          " << " | " << right << (is_biocommutative(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "AG-группоид                " << " | " << right << (is_AG(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "GA-группоид                " << " | " << right << (is_GA(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "GA-1 группоид              " << " | " << right << (is_GA_1(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "AD-группоид                " << " | " << right << (is_AD(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "DA-группоид                " << " | " << right << (is_DA(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Гексагональность           " << " | " << right << (is_hexa(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Дистрибутивность справа    " << " | " << right << (is_distribute_right(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Дистрибутивность слева     " << " | " << right << (is_distribute_left(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Единица справа             " << " | " << right << (is_digit_right(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Единица слева              " << " | " << right << (is_digit_left(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Единица                    " << " | " << right << (is_digit(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Уорд                       " << " | " << right << (is_urod(matrix) ? "+" : "-") << " |" << endl;
    cout << "| " << setw(textWidth) << left << "Обратный Уорд              " << " | " << right << (is_reverse_urod(matrix) ? "+" : "-") << " |" << endl;
    cout << "+---------------------------------+" << endl;

    return  0;    
} // namespace std;
