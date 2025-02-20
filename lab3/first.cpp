#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int side;

int get_number_of_strings(string filename)
{
    ifstream file(filename);

    int count = 0;
    string line;

    while (getline(file, line))
        if (!line.empty())
        {
            count++;
        }

    file.close();
    return count;
}

int **create_and_fill_array(string filename)
{
    side = get_number_of_strings(filename);
    int **matrix = new int *[side];

    for (int i = 0; i < side; ++i)
    {
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
    file.close();
    return matrix;
}

bool check_associativity(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[a][matrix[b][c] - 1] != matrix[matrix[a][b] - 1][c])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_mediality(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                for (int d = 0; d < side; d++)
                {
                    if (matrix[matrix[a][b] - 1][matrix[c][d] - 1] != matrix[matrix[a][c] - 1][matrix[b][d] - 1])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool check_paramediality(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                for (int d = 0; d < side; d++)
                {
                    if (matrix[matrix[a][b] - 1][matrix[c][d] - 1] != matrix[matrix[d][b] - 1][matrix[c][a] - 1])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool check_bicommutativity(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                for (int d = 0; d < side; d++)
                {
                    if (matrix[matrix[a][b] - 1][matrix[c][d] - 1] != matrix[matrix[d][c] - 1][matrix[b][a] - 1])
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool check_AG_groupoid(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[matrix[a][b] - 1][c] != matrix[matrix[c][b] - 1][a])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_GA_groupoid(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[matrix[a][b] - 1][c] != matrix[c][matrix[b][a] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_GA1_groupoid(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[matrix[a][b] - 1][c] != matrix[matrix[c][a] - 1][b])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_AD_groupoid(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[a][matrix[b][c] - 1] != matrix[c][matrix[b][a] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_DA_groupoid(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[a][matrix[b][c] - 1] != matrix[c][matrix[a][b] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_hexagonality(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        if ((matrix[a][a] - 1) != a)
        {
            return false;
        }
    }

    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                for (int d = 0; d < side; d++)
                {
                    if (matrix[matrix[a][b] - 1][matrix[c][d] - 1] != matrix[matrix[a][c] - 1][matrix[b][d] - 1])
                    {
                        return false;
                    }
                }
            }
        }
    }

    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            if (matrix[a][matrix[b][a] - 1] != matrix[matrix[a][b] - 1][a] || matrix[a][matrix[b][a] - 1] != b)
            {
                return false;
            }
        }
    }
    return true;
}

bool check_right_distributivity(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[matrix[a][b] - 1][c] != matrix[matrix[a][c] - 1][matrix[b][c] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_left_distributivity(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[c][matrix[a][b] - 1] != matrix[matrix[c][a] - 1][matrix[c][b] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_right_unit(int **matrix)
{
    for (int x = 0; x < side; x++)
    {
        bool has_unit = false;
        for (int e = 0; e < side; e++)
        {
            if ((matrix[x][e] - 1) == x)
            {
                has_unit = true;
                break;
            }
        }
        if (!has_unit)
        {
            return false;
        }
    }
    return true;
}

bool check_left_unit(int **matrix)
{
    for (int x = 0; x < side; x++)
    {
        bool has_unit = false;
        for (int e = 0; e < side; e++)
        {
            if ((matrix[e][x] - 1) == x)
            {
                has_unit = true;
                break;
            }
        }
        if (!has_unit)
        {
            return false;
        }
    }
    return true;
}

bool check_unit(int **matrix)
{
    for (int x = 0; x < side; x++)
    {
        bool has_unit = false;
        for (int e = 0; e < side; e++)
        {
            if ((matrix[x][e] - 1) == x && (matrix[e][x] - 1) == x)
            {
                has_unit = true;
                break;
            }
        }
        if (!has_unit)
        {
            return false;
        }
    }
    return true;
}

bool check_Ward(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[a][b] != matrix[matrix[a][c] - 1][matrix[b][c] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool check_inverse_Ward(int **matrix)
{
    for (int a = 0; a < side; a++)
    {
        for (int b = 0; b < side; b++)
        {
            for (int c = 0; c < side; c++)
            {
                if (matrix[a][b] != matrix[matrix[c][a] - 1][matrix[c][b] - 1])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void delete_matrix(int** matrix)
{
    for (int i = 0; i < side; i++)
        delete[] matrix[i];
    delete[] matrix;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int **matrix;
    string line;
    
    while(true) {

        cout << "Input the file name: ";
        cin >> line;

        if (line == "stop")
            return 0;

        matrix = create_and_fill_array(line);

        for (int i = 0; i < side; ++i, cout << endl)
            for (int j = 0; j < side; j++)
                cout << matrix[i][j] << " ";

        // WARNING: functions don't work correct!!!!!
        // TODO: fix it
        const int textWidth = 30;

        // Вывод с форматированием
        cout << "+---------------------------------+" << endl;
        cout << "| " << setw(textWidth) << left << "Ассоциативность            " << " | " << right << (check_associativity(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Медиальность               " << " | " << right << (check_mediality(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Парамедиальность           " << " | " << right << (check_paramediality(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Бикоммутативность          " << " | " << right << (check_bicommutativity(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "AG-группоид                " << " | " << right << (check_AD_groupoid(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "GA-группоид                " << " | " << right << (check_GA_groupoid(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "GA-1 группоид              " << " | " << right << (check_GA1_groupoid(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "AD-группоид                " << " | " << right << (check_AD_groupoid(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "DA-группоид                " << " | " << right << (check_DA_groupoid(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Гексагональность           " << " | " << right << (check_hexagonality(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Дистрибутивность справа    " << " | " << right << (check_right_distributivity(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Дистрибутивность слева     " << " | " << right << (check_left_distributivity(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Единица справа             " << " | " << right << (check_right_unit(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Единица слева              " << " | " << right << (check_left_unit(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Единица                    " << " | " << right << (check_unit(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Уорд                       " << " | " << right << (check_Ward(matrix) ? "+" : "-") << " |" << endl;
        cout << "| " << setw(textWidth) << left << "Обратный Уорд              " << " | " << right << (check_inverse_Ward(matrix) ? "+" : "-") << " |" << endl;
        cout << "+---------------------------------+" << endl;
        delete_matrix(matrix);
    } 
    return 0;
} // namespace std;
