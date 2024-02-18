#include <iostream>
#include <unordered_map>
#include <vector>

int Median(std::vector<int> a, int n){
    nth_element(a.begin(),a.begin() + (n-1)/2, a.end());
    return a[(n-1)/2];
}

int main(){

    int N; std::cout<<"Введите количество элементов массива: "<<std::endl; std::cin>>N;
    std::unordered_map <int, int> mass;
    std::unordered_map <int, int> :: iterator it;
    std::vector<int> allel;
    std::cout<<"Вводите числа (элементы массива): "<<std::endl; int a; //Заполнение словаря по входным значениям
    for (int i = 0; i<N; ++i){
        std::cin>>a;
        mass[a]++;
        allel.push_back(a);
    }

    /*for (it = mass.begin(); it != mass.end(); ++it)
        std::cout<< it->first << " : " << it->second <<std::endl; //Вывод словаря

    for (int i = 0; i<N; i++) //Вывод вектора
        std::cout<<allel[i]<<" ";
    std::cout<<"\n";*/

    int maxim = 2, key =INT_MAX; int def = INT_MAX;
    for (it = mass.begin(); it!=mass.end(); ++it){
        if (it->first < def)
            def = it->first;
        if ((it->second) >= maxim and (it->first)<key){  //Находим максимум
            maxim = (it->second);
            key = (it->first);
        }
    }
    if (key!=INT_MAX)
        std::cout<<"Элемент(Минимальный) с максимальным вхождением: "<<key<<std::endl;
    else
        std::cout<<"Все елементы повторяются один раз. Минимальный из них: "<<def<<std::endl;

    std::cout<<"Медианное значение: " << Median(allel, N);

    return 0;
}
