#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>

struct matrix{
    int rows;
    int columns;
    std::vector <std::vector <float>> data;
};
matrix startmatrix(int row, int col){
    assert(row>0 && col>0);
    matrix mat;
    mat.rows=row;
    mat.columns=col;
    for (int i=0; i<row; i++) {
        std::vector<float> temp;
        for (int j = 0; j < col; j++) {
            temp.push_back(0);}
        mat.data.push_back(temp);}
    return mat;
}

bool isnum(std::string f){
    bool flag=true;
    for(int i=0; i<f.length(); i++)
        if(!std::isdigit(f[i])) {
            flag = false;
            break;
        }
    return flag;
}

matrix filling(){
    std::cout<<"Как вы хотите задать матрицу? (введите цифру)\n"
               "1 - С клавиатуры\n"
               "2 - Из файла\n"
               "3 - По правилу\n";
    int n; std::cin>>n;
    switch(n) {
        case 1:{
            std::cout<<"Укажите порядок квадратной матрицы в виде 1го числа и затем вводите элементы матрицы ч/з пробел\n";
            int f; std::cin>>f; matrix a = startmatrix(f, f);
            for (int i=0; i<a.rows; i++) {
                for (int j = 0; j < a.columns; j++)
                    std::cin>>a.data[i][j];
            }
            return a;}
        case 2: {
            std::ifstream mat;
            std::cout<<"Введите название файла содержращего матрицу (и её поряждок), !Указав расширение\n";
            std::string file; std::cin>>file;
            mat.open(file);
            if (!mat){
                std::cerr<<"Ошибка чтения\n"; break;
            }
            std::string ss; mat>>ss;
            if (!isnum(ss)){
                std::cout<<"Ошибка введенных данных: NaN\n"; break;
            }
            int s = std::stoi(ss);
            if (s<4 or s>16){
                std::cout<<"Ошибка введенных данных: недопустимое значение\n"; break;
            }
            matrix a = startmatrix(s, s);
            int i = 0, j = 0;
            int count = 0;
            while (mat and count!=s*s){
                std::string elem;
                mat >> elem;
                if (elem!="" and elem!=" " and elem!="\n") {
                    if (!isnum(elem)) {
                        std::cout << "Ошибка введенных данных: NaN\n"; break;
                    }
                    int el = std::stoi(elem);
                    a.data[i][j] += el;
                    j += 1;
                    if (j == a.columns) {
                        j = 0; i += 1;
                    }
                }
                count+=1;
            }
            return a;}
        case 3: {
            std::ifstream por;
            std::cout<<"Введите название файла содержращего порядок, !указав расширение\n";
            std::string file; std::cin>>file;
            por.open(file);
            if (!por){
                std::cerr<<"Ошибка чтения\n"; break;
            }
            std::string tt; std::getline(por, tt);
            if (!isnum(tt)){
                std::cout<<"Ошибка введенных данных\n"; break;
            }
            int t = std::stoi(tt);
            if (t<4 or t>16){
                std::cout<<"Ошибка введенных данных\n"; break;
            }
            por.close();
            matrix a = startmatrix(t,t);
            float num = 0; //величина заполнения
            int i = 0, j = 0; //iterators
            bool diagonal = false, flag = false; //распределители
            while ((i >= 0 and i <= a.rows - 1) and (j <= a.columns - 1 and j >= 0)) {
                if (i == 0 or j == 0 or i == (a.rows - 1) or j == (a.columns - 1)) {
                    if (i == 0 and !diagonal) {
                        num += 1;
                        a.data[i][j] = num;
                        num += 1;
                        if (j + 1 != a.rows - 1) {
                            a.data[i][j + 1] = num;
                            i += 1;
                            flag = true;
                        } else {
                            j += 1;
                            a.data[i][j] = num;
                            while (i != a.rows - 1) {
                                i += 1;
                                j -= 1;
                                num += 1;
                                a.data[i][j] = num;
                            }
                            num -= 1;
                            diagonal = true;
                        }
                    }
                    else if (j == 0 and !diagonal) {
                        num += 1;
                        a.data[i][j] = num;
                        num += 1;
                        if (i + 1 != a.rows - 1) {
                            a.data[i + 1][j] = num;
                            j += 1;
                            flag = false;
                        } else {
                            i += 1;
                            a.data[i][j] = num;
                            while (j != a.columns - 1) {
                                i -= 1;
                                j += 1;
                                num += 1;
                                a.data[i][j] = num;
                            }
                            num -= 1;
                            diagonal = true;
                        }
                    }
                    else if (j == a.columns - 1 and diagonal) {
                        num += 1;
                        a.data[i][j] = num;
                        num += 1;
                        a.data[i + 1][j] = num;
                        i += 2;
                        j -= 1;
                        flag = true;
                    }
                    else if (i == a.rows - 1 and diagonal) {
                        num += 1;
                        a.data[i][j] = num;
                        num += 1;
                        a.data[i][j + 1] = num;
                        j += 2;
                        i -= 1;
                        flag = false;
                    }
                }
                else if (!flag) {
                    num += 1;
                    a.data[i][j] = num;
                    i -= 1;
                    j += 1;
                }
                else {
                    num += 1;
                    a.data[i][j] = num;
                    i += 1;
                    j -= 1;
                }
            }
            return a;}
            default: {
                std::cerr<<"Такой функции нет! Попробуйте заново"<<std::endl;
                return startmatrix(1,1);}
    }
    return startmatrix(1,1);
}

matrix multiple(matrix a, matrix b){
    if (a.columns!=b.rows){
        std::cout<<"Ошибка умножения: количество строк левой матрицы не равны столбцам правой матрицы!";
        return startmatrix(1,1);}
    else{
        matrix out = startmatrix(a.rows, b.columns);
        for (int i=0; i<out.rows; i++)
            for (int j=0; j<out.columns; j++)
                for (int k=0; k<b.rows; k++)
                    out.data[i][j] += a.data[i][k] * b.data[k][j];
        return out;}
}

int det(matrix a){
    //Прямой Гаусс
    for(int step = 0; step < a.rows - 1; step++)
        for(int row = step + 1; row < a.rows; row++){
            float coeff = -a.data[row][step] / a.data[step][step];
            for(int col = step; col < a.rows; col++)
                a.data[row][col] += a.data[step][col] * coeff;
        }
    //Определитель, как произведение элементов главной диагонали
    int Det = 1;
    for(int i = 0; i < a.rows; i++)
        Det *= a.data[i][i];
    return Det;
}

matrix gauss(matrix a){
    //прямой ход Гаусса
    for(int step = 0; step < a.rows - 1; step++) {
        for (int row = step + 1; row < a.rows; row++) {
            float coeff = -a.data[row][step] / a.data[step][step];
            for (int col = step; col < a.columns; col++)
                a.data[row][col] += a.data[step][col] * coeff;
        }
    }
    //Обратный ход Гаусса
    int n = std::min(a.rows, a.columns)-1;
    for (int step=n; step>=0; step--){
        float temp = a.data[step][step];
        for (int c=step; c<a.columns; c++)
            a.data[step][c]/=temp;
        for (int row = step -1; row>=0; row--){
            float coeff = -a.data[row][step]/a.data[step][step];
            for (int col=step; col<a.columns; col++)
                a.data[row][col]+=a.data[step][col]*coeff;
        }
    }
    return a;
}

matrix inverse(matrix a){
    if (det(a) != 0) {
        //Объединение с элементарной матрицей
        matrix work = startmatrix(a.rows, 2 * a.columns);
        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < a.columns; j++)
                work.data[i][j] = a.data[i][j];
        }
        for (int i = a.columns; i < work.columns; i++)
            work.data[i - a.rows][i] = 1;
        work = gauss(work);
        matrix out = startmatrix(a.rows, a.columns);
        for (int i = a.columns; i < work.columns; i++)
            for (int j = 0; j < out.rows; j++)
                out.data[j][i - a.columns] += work.data[j][i];
        return out;}
    else {std::cout<<"Ошибка: матрица вырождена!"; return startmatrix(1,1);}
}

bool OK(matrix a){
    bool flag = true;
    if (a.rows==a.columns and a.columns==1 and a.data[0][0]==0)
        flag=false;
    return flag;
}

void printm(matrix A, int q){
    if (q==0){
        for (int i = 0; i < A.rows; i++) {
            for (int j = 0; j < A.columns; j++) {
                double a;
                double f = std::modf(A.data[i][j], &a);
                if (f > 0 or f < 0)
                    std::cout << std::setw(7) << std::fixed << std::setprecision(2) << A.data[i][j];
                else
                    std::cout << std::fixed << std::setprecision(0) << std::setw(3) << A.data[i][j];
            }
            std::cout << "\n";
        }
        return;
    }
    else {
        std::cout << "Как вы хотите вывести матрицу? (введите цифру)\n"
                     "1 - В файл\n"
                     "2 - На экран\n";
        int n;
        std::cin >> n;
        switch (n) {
            case 1: {
                std::cout<<"Введите название файла для вывода, !Указав расширение\n";
                std::string file; std::cin>>file;
                std::ofstream out(file);
                if (!out){
                    std::cerr<<"Ошибка чтения\n"; break;
                }
                for (int i = 0; i < A.rows; i++) {
                    for (int j = 0; j < A.columns; j++) {
                        double a;
                        double f = std::modf(A.data[i][j], &a);
                        if (f > 0 or f < 0)
                            out << std::setw(7) << std::fixed << std::setprecision(2) << A.data[i][j];
                        else
                            out << std::fixed << std::setprecision(0) << std::setw(7) << A.data[i][j];
                    }
                    out << "\n";
                }
                out.close();
                return;
            }
            case 2: {
                for (int i = 0; i < A.rows; i++) {
                    for (int j = 0; j < A.columns; j++) {
                        double a;
                        double f = std::modf(A.data[i][j], &a);
                        if (f > 0 or f < 0)
                            std::cout << std::setw(7) << std::fixed << std::setprecision(2) << A.data[i][j];
                        else
                            std::cout << std::fixed << std::setprecision(0) << std::setw(7) << A.data[i][j];
                    }
                    std::cout << "\n";
                }
                return;
            }
            default:{
                std::cout<<"Такой функции нет! Попробуйте заново";
                return;
            }
        }
    }
}

void manip(){
    std::cout<<"Выберите операцию, которую хотите произвести (введите цифру):\n"
               "0 - Выход\n"
               "1 - Заполнение/Вывод матрицы\n"
               "2 - Нахождение обратной матрицы\n"
               "3 - Умножение матриц\n";
    int n; std::cin>>n;
    switch(n) {
        case 0: exit(EXIT_SUCCESS);
        case 1: {
            matrix F = filling();
            if (OK(F))
                printm(F, 1);
            return;}
        case 2: {
            matrix S = filling();
            std::cout<<"Исходная матрица: \n"; printm(S, 0);
            matrix o = inverse(S);
            if (OK(o)){
                std::cout<<"Обратная матрица: \n"; printm(o, 1);}
            else
                std::cout<<"\n";
            return;}
        case 3: {
            std::cout<<"Заполните сначала левую матрицу, а затем правую";
            matrix T = filling(); matrix T1 = filling();
            std::cout<<"Левая матрица: \n"; printm(T, 0);
            std::cout<<"Правая матрица: \n"; printm(T1, 0);
            matrix TT1 = multiple(T, T1);
            if (OK(TT1)){
                std::cout<<"Итог: \n"; printm(TT1, 1);}
            else
                std::cout<<"";
            return;}
        default: std::cerr<<"Такой операции нет! Повторите попытку.\n";
    }
}
int main() {
    std::cout<<"Добрый день! Для выхода из программы введите 0"<<std::endl;
    while (true)
        manip();
}
