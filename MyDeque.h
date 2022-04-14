#ifndef EDUCATIONAL3_MYDEQUE_H
#define EDUCATIONAL3_MYDEQUE_H

#include <iostream>
#include <algorithm>

template <typename T>
class MyDeque{
    T *array;
    int front;
    int back;
    int Maxsize{};
public:
//Методы взаимводействия
    MyDeque();
    explicit MyDeque(int Maxsize);
    MyDeque(const MyDeque& cp);
    ~MyDeque() {delete[] array;}
    void PushFront( T key);
    T PopFront();
    void PushBack( T key);
    T PopBack();
//Методы индексирования
    bool Full() { return ((front==(back+1)) or (back == Maxsize-1 and front==0));}
    bool Empty() { return (front == -1);}
    int Size();
    int GetThisPos(int RealPos);
//Операторы взаимодействия
    T &operator[](int i) {
        if(i<=Maxsize)
            return array[GetThisPos(i)];
    }

    friend std::ostream& operator<< (std::ostream &out, MyDeque<T> &dq) {
        for (int i=0; i<dq.Size(); i++)
            out<<dq.array[dq.GetThisPos(i)]<<" ";
        return out;
    }
    friend std::istream& operator>> (std::istream &in, MyDeque<T> &dq){
        std::cout<<"Сначала укажите кол-во чисел, которые хотите ввести, а затем сами числа!"<<std::endl;
        int temp;
        in>>temp;
        while(temp>0){
            T insert;
            in>>insert;
            dq.PushBack(insert);
            temp--;
        }
        return in;
    }
};

template<typename T>
MyDeque<T>::MyDeque(int Maxsize) {
    front = -1;
    back = 0;
    this->Maxsize=Maxsize;
    array = new T[Maxsize];
}

template<typename T>
MyDeque<T>::MyDeque(const MyDeque& cp){
    front=cp.front;
    back=cp.front;
    Maxsize=cp.Maxsize;
    for (int i=0; i<Maxsize; i++)
        array[i]=cp.array[i];
}

template<typename T>
void MyDeque<T>::PushFront(T key) {
    if (Full()) {
        std::cout<<"Overflow!"<<std::endl;
        return;
    }
    if (front==-1){
        front=0;
        back=0;
    }
    else if(front==0) front = Maxsize-1;
    else front-=1;

    array[front]=key;
}

template<typename T>
void MyDeque<T>::PushBack(T key) {
    if (Full()) {
        std::cout<<"Overflow!"<<std::endl;
        return;
    }
    if (front==-1){
        front=0;
        back=0;
    }
    else if (back == Maxsize-1) back=0;
    else back+=1;

    array[back]=key;
}

template<typename T>
T MyDeque<T>::PopFront() {
    if(Empty()){
        std::cout<<"Underflow!!"<<std::endl;
        return NULL;
    }
    int out = front;
    if (front==back){
        front=-1;
        back=0;
    }
    else front+=1;
    return array[out];
}

template<typename T>
T MyDeque<T>::PopBack() {
    if(Empty()){
        std::cout<<"Underflow!!"<<std::endl;
        return NULL;
    }
    int out=back;
    if (front==back){
        front=-1;
        back=0;
    }
    else if (back==0) back=Maxsize-1;
    else back-=1;
    return array[out];
}

template<typename T>
int MyDeque<T>::Size() {
    int count;
    if (this->Empty()) count = 0;
    else if (back==front) count = 1;
    else if (back>front and front!=0) count = Maxsize-front;
    else if (front==0) count = back+1;
    else if (Full()==1) count = Maxsize;
    else count = (Maxsize-front)+(back+1);
    return count;
}

template<typename T>
int MyDeque<T>::GetThisPos(int RealPos) {
    if (back-RealPos>=0) return back-RealPos;
    else if (front+(Size()-RealPos)<=Maxsize+1) return front+(Size()-RealPos)-1;
}


#endif //EDUCATIONAL3_MYDEQUE_H
