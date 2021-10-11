#include <iostream>
#include <math.h>

double f1(double x){
    if (x<-1.5708 or (x>(-1/M_E) and x<0)) {
        std::cout << "Ошибка (значение не может быть вычислено: подкоренное) - ";
        return 0;}
    else {
        double a;
        a = ((x * x + sin(sqrt(M_PI + 2 * x))) / (12 * sqrt(x + x * x * M_E)));
        return a;}
}
double f2(double x, double y){
    double a;
    if (y<0) {
        if (x<0) {
            std::cout << "Ошибка (значение не может быть вычислено: подкоренное) - ";
            return 0;}
        else
            a = f1((x * x * x) - (y * y) + cos(15 * (sqrt(x * (-y)))));
    }
    else if (y>0) {
        if (2*y == 6.12323e-17 or (x*x+tan(2*y))<0){
            std::cout<< "Ошибка (значение не может быть вычислено: тангенс/корень) - ";
            return 0;}
        else
            a = f2(f1(sqrt((x * x) + tan(2 * y))), (sin(y) * (-1)));

    }
    else {
        a = (f1(x * x * x * x * x));
        if (a<0){
            std::cout<< "Ошибка (значение не может быть вычислено: корень) - ";
            return 0;}
        else
            a=sqrt(a);
    }
    return a;
}
double f3(double x, double y, double z){
    double a = 0;
    double xp = 1, yp = 1, zp=1, ep = 1; //переменные для возведения в степень
    double flag;
    for (int k = 0 ; k <= abs(z); k++) {
        flag = (f1(xp / yp)) * f2(zp, (x * y)) / ep;
        if (flag<0){
            std::cout << "Ошибка (значение не может быть вычислено: подкоренное) - ";
            return 0;}
        else{
            a += sqrt(flag);
            xp*=x; yp*=y; zp*=z; ep*=(M_E*M_E*M_E);
        }

    }
    return a;
}
void manipul(){
    std::cout<<"Введите порядковый номер необходимой функции (число от 1 до 3)."<<std::endl;
    int n; std::cin>>n;
    if (n>=1 and n<=3) {
        double x, y, z = 0;
        if (n == 1) {
            std::cout<< "Введите число Х"<<std::endl;
            std::cin >> x;
            std::cout << f1(x)<<std::endl;
        }
        if (n == 2) {
            std::cout<< "Введите числа Х, Y"<<std::endl;
            std::cin >> x >> y;
            std::cout << f2(x, y)<<std::endl;
        }
        if (n == 3) {
            std::cout<< "Введите числа Х, Y, Z"<<std::endl;
            std::cin >> x >> y >> z;
            std::cout << f3(x, y, z)<<std::endl;
        }
    }
    else if (n>3 or n<0)
        std::cout<<"Введен не верный номер функции. Действие невозможно"<<std::endl;
    else
        exit(0);
}

int main(){
    std::cout<<"Добро пожаловать! Для выхода из программы введите 0."<<std::endl;
    while (true)
        manipul();
}
