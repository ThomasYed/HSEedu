#ifndef EDUCATIONAL3_HASH_H
#define EDUCATIONAL3_HASH_H

#include <iostream>
#include <string>

using namespace std;

class Hash{
    string hash;
    //Making ANSI-code
    int ExistCode(int x);
    //Getting Control(Original) sum of string;
    unsigned int ControlSum(string &str);

public:
    //Making Hash
    string GetHash(string &UserStr, unsigned int HashLen);
};

int Hash::ExistCode(int x) {
    while(!(((x>=48) && (x<=57))||((x>=65) && (x<=90))||((x>=97) && (x<=122)))){
        if(x<48) x+=16;
        else x-=25;
    }
    return x;
}

unsigned int Hash::ControlSum(string &str) {
    unsigned int sault=0, strlen=1;
    for(;strlen<str.size();strlen++)
        sault+=int(str[strlen]+str[strlen-1]);
    return sault;
}

string Hash::GetHash(string &UserStr, unsigned int HashLen = 64) {
    //Минимально возможная длинна хеша кратная двум
    unsigned int minLen = 2;
    //длина строки, ближайшая к нужной длине хэша
    unsigned int realMinLen = 0;

    //Добавление уникальной соли
    unsigned int originalSault =ControlSum(UserStr);
    UserStr += to_string(originalSault);
    unsigned int originalLen = UserStr.size();

    //Нахождение минимальной необходимой длины хеша и минимальной возможной на 1 этапе
    while(minLen<=HashLen)
        realMinLen = (minLen *= 2);
    //Для ситуаций, когда строка много больше нужной длины хэша
    while(minLen<originalLen)
        minLen *= 2;

    //Первый этап - доводим строку [длину] до минимального числа кратного 2 уникальными символами
    //Получаем первичный максимальный хэш из максимальной строки
    unsigned int addCount = minLen - originalLen;
    for(int i=0;i<addCount;i++)
        UserStr += ExistCode(UserStr[i] + UserStr[i + 1]);

    //Сжатие строки хэша до цели (кратной двум, по умолчанию до 64)
    while(UserStr.size()!=realMinLen/2){
        for (int i = 0, c = UserStr.size()/2; i<c; i++)
            hash += ExistCode(UserStr[c - i] + UserStr[c + i]);
        UserStr=hash;
        hash.clear();
    }
    hash=UserStr;
    return hash;
}

#endif //EDUCATIONAL3_HASH_H
