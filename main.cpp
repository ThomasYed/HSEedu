#include <iostream>
#include <algorithm>

template<typename T>
class LinkedList {
public:
    class Iterator;
    class rIterator;

private:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef Iterator iterator;
    typedef const Iterator const_iterator;
    typedef rIterator riterator;
    typedef const rIterator const_riterator;

    struct ListNode;

    ListNode* head;
    ListNode* tail;
    size_type count;
    ListNode* rhead;
    ListNode* rtail;

    void copy(const LinkedList& other);

public:
    LinkedList();
    LinkedList(const LinkedList& list);
    explicit LinkedList(size_type);
    ~LinkedList();

    iterator begin();
    iterator end();
    riterator rbegin();
    riterator rend();

    LinkedList& operator=(const LinkedList& list) {
        resize(1);
        pop_back();
        copy(list);
        return *this;
    }
    friend std::ostream& operator<<(std::ostream& out, LinkedList& list) {
        size_type i = list.size();
        ListNode* temp = list.head;
        while(i){
            out << temp->value << " ";
            temp = temp->next;
            --i;
        }
        return out;
    }
    bool empty() {
        return count == 0;
    }
    size_type size() {
        return count;
    }
    value_type front() {
        return head->value;
    }
    value_type back() {
        return tail->value;
    }

    void push_front(value_type val);
    void pop_front();
    void push_back(value_type val);
    void pop_back();
    void assign(size_type amount, const_reference val);
    void assign(const_iterator pos, size_type amount, const_reference val);
    void insert(const_iterator pos, const_reference val);
    void insert(size_type amount, const_reference val);
    void erase(iterator pos);
    void erase(iterator first, iterator last);
    void clear();
    void resize(size_type amount, const_reference val = 0);
    void reverse();
    void swap(LinkedList& other);
};

template<typename T>
struct LinkedList<T>::ListNode {
    value_type value;
    LinkedList<T>::ListNode* prev;
    LinkedList<T>::ListNode* next;
};

template<typename T>
class LinkedList<T>::Iterator {

    typedef LinkedList<T>::ListNode* node;
    node p;



public:
    friend class LinkedList;

    template<class Iter>
    friend struct std::iterator_traits;

    typedef std::ptrdiff_t difference_type;

    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::reference reference;
    typedef std::random_access_iterator_tag iterator_category;

    Iterator() : p(nullptr) {}
    Iterator(node p) : p(p) {}
    Iterator(const Iterator& it) : p(it.p) {}
    int ind() const {
        int i = 0;
        node temp = p;
        while (temp->prev != nullptr) {
            i++;
            temp = temp->prev;
        }
        return i - 1;
    }
    reference operator*() {
        return p->value;
    }
    bool operator==(const Iterator& sec) {
        return (p->prev == (sec.p)->prev and p->next == (sec.p)->next and p->value == (sec.p)->value);
    }
    bool operator!=(const iterator& sec) {
        return (p->prev != (sec.p)->prev or p->next != (sec.p)->next or p->value != (sec.p)->value);
    }
    Iterator& operator++() {
        if (p->next != nullptr)
            p = p->next;
        return *this;
    }
    Iterator& operator++(int) {
        if (p->next != nullptr)
            p = p->next;
        return *this;
    }
    Iterator& operator--() {
        if (p->prev != nullptr)
            p = p->prev;
        return *this;
    }
    Iterator& operator--(int) {
        if (p->prev != nullptr)
            p = p->prev;
        return *this;
    }
    Iterator operator+(int n) {
        iterator temp = p;
        while (n and temp.p->next != nullptr) {
            temp++;
            --n;
        }
        return temp;
    }
    Iterator operator-(int n) {
        iterator temp = p;
        while (n and temp.p->prev != nullptr) {
            temp--;
            --n;
        }
        return temp;
    }
    difference_type operator-(const Iterator& it) {
        difference_type i = (ind() - it.ind());
        return i;
    }
    Iterator& operator+=(int n) {
        while (n and p->next != nullptr) {
            p = p->next;
            --n;
        }
        return *this;
    }
    Iterator& operator-=(int n) {
        while (n and p->prev != nullptr) {
            p = p->prev;
            --n;
        }
        return *this;
    }
    bool operator<(const Iterator it) {
        return ind() < it.ind();
    }
    bool operator>(const Iterator it) {
        return ind() > it.ind();
    }
    bool operator<=(const Iterator it) {
        return (ind() < it.ind() or p == it.p);
    }
    bool operator>=(const Iterator it) {
        return (ind() > it.ind() or p == it.p);
    }
    reference operator[](int n) {
        iterator temp = p;
        return (temp + n).p->value;
    }
};

template<typename T>
class LinkedList<T>::rIterator {

    typedef LinkedList<T>::ListNode* node;
    node p;

    int ind() const {
        int i = 0;
        node temp = p;
        while (temp->prev != nullptr) {
            i++;
            temp = temp->prev;
        }
        return i - 1;
    }

public:
    friend class LinkedList;

    template<class Iter>
    friend struct std::iterator_traits;

    typedef std::ptrdiff_t difference_type;

    typedef typename LinkedList<T>::value_type value_type;
    typedef typename LinkedList<T>::value_type* pointer;
    typedef typename LinkedList<T>::reference reference;
    typedef std::random_access_iterator_tag iterator_category;

    rIterator() : p(0) {}
    rIterator(node p) : p(p) {}
    rIterator(const rIterator& it) : p(it.p) {}

    reference operator*() {
        return p->value;
    }
    bool operator==(const rIterator& sec) {
        return (p->prev == (sec.p)->prev and p->next == (sec.p)->next and p->value == (sec.p)->value);
    }
    bool operator!=(const riterator& sec) {
        return (p->prev != (sec.p)->prev or p->next != (sec.p)->next or p->value != (sec.p)->value);
    }
    rIterator& operator++() {
        if (p->prev != nullptr)
            p = p->prev;
        return *this;
    }
    rIterator& operator++(int) {
        if (p->prev != nullptr)
            p = p->prev;
        return *this;
    }
    rIterator& operator--() {
        if (p->next != nullptr)
            p = p->next;
        return *this;
    }
    rIterator& operator--(int) {
        if (p->next != nullptr)
            p = p->next;
        return *this;
    }
    rIterator operator+(int n) {
        riterator temp = p;
        while (n and temp.p->prev != nullptr) {
            temp++;
            --n;
        }
        return temp;
    }
    rIterator operator-(int n) {
        riterator temp = p;
        while (n and temp.p->next != nullptr) {
            temp--;
            --n;
        }
        return temp;
    }
    difference_type operator-(const rIterator& it) {
        difference_type i = (ind() - it.ind());
        return i;
    }
    rIterator& operator+=(int n) {
        while (n and p->prev != nullptr) {
            p = p->prev;
            --n;
        }
        return *this;
    }
    rIterator& operator-=(int n) {
        while (n and p->next != nullptr) {
            p = p->next;
            --n;
        }
        return *this;
    }
    bool operator<(const rIterator it) {
        return ind() < it.ind();
    }
    bool operator>(const rIterator it) {
        return ind() > it.ind();
    }
    bool operator<=(const rIterator it) {
        return (ind() < it.ind() or p == it.p);
    }
    bool operator>=(const rIterator it) {
        return (ind() > it.ind() or p == it.p);
    }
    reference operator[](int n) {
        iterator temp = p;
        return (temp + n).p->value;
    }
};

template<typename T>
void LinkedList<T>::copy(const LinkedList& other) {
    count = other.count;
    ListNode *curr = other.head;
    ListNode *temp = new ListNode;
    temp->value = curr->value;
    head = tail = temp;
    curr = curr->next;
    for (int i = 0; i < count - 1; i++) {
        temp = new ListNode;
        temp->value = curr->value;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        curr = curr->next;
    }
    rhead = new ListNode;
    rtail = new ListNode;
    tail->next = rtail;
    head->prev = rhead;
    rtail->prev = tail;
    rhead->next = head;
}

template<typename T>
LinkedList<T>::LinkedList() {
    count = 0;
    head = tail = new ListNode;
    rhead = new ListNode;
    rtail = new ListNode;
    head->next = tail;
    tail->prev = head;
    head->prev = rhead;
    tail->next = rtail;
    rtail->prev = tail;
    rhead->next = head;
} //Конструктор без параметров

template<typename T>
LinkedList<T>::LinkedList(LinkedList::size_type size) {
    count = size;
    ListNode *temp = new ListNode;
    temp->value = 0;
    head = tail = temp;
    for (int i = 0; i < count - 1; i++) {
        temp = new ListNode;
        temp->value = 0;
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    rhead = new ListNode;
    rtail = new ListNode;
    tail->next = rtail;
    head->prev = rhead;
    rtail->prev = tail;
    rhead->next = head;
} //Конструктор с одним параметром

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& list) {
    copy(list);
} //Конструктор копирования

template<typename T>
LinkedList<T>::~LinkedList() {
    delete rhead;
    while (count + 1) {
        tail = head->next;
        delete head;
        head = tail;
        count--;
    }
} //Деструктор

template<typename T>
void LinkedList<T>::push_front(value_type val) {
    if(count){
        ++count;
        ListNode* temp = new ListNode;
        temp->value = val;
        temp->prev = rhead;
        temp->next = head;
        head->prev = temp;
        head = temp;
        rhead->next = head;
    }
    else{
        ++count;
        head->value = val;
    }
} //ready

template<typename T>
void LinkedList<T>::pop_front() {
    if(count == 1){
        --count;
        delete head;
        head = tail = new ListNode;
        head->next = tail;
        tail->prev = head;
        head->prev = rhead;
        tail->next = rtail;
        rtail->prev = tail;
        rhead->next = head;
    }
    else{
        --count;
        ListNode* temp = head;
        head = head->next;
        head->prev = rhead;
        rhead->next = head;
        delete temp;
    }
} //ready

template<typename T>
void LinkedList<T>::push_back(value_type val) {
    if (count){
        ++count;
        ListNode* temp = new ListNode;
        temp->value = val;
        temp->prev = tail;
        temp->next = rtail;
        tail->next = temp;
        tail = temp;
        rtail->prev = tail;
    } else {
        ++count;
        tail->value = val;
    }
} //ready

template<typename T>
void LinkedList<T>::pop_back() {
    if(count == 1){
        --count;
        delete tail;
        head = tail = new ListNode;
        head->next = tail;
        tail->prev = head;
        head->prev = rhead;
        tail->next = rtail;
        rtail->prev = tail;
        rhead->next = head;
    }
    else{
        --count;
        ListNode* temp = tail;
        tail = tail->prev;
        tail->next = rtail;
        rtail->prev = tail;
        delete temp;
    }
} //ready

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
    return iterator(head);
}

template<typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
    return iterator(rtail);
}

template<typename T>
typename LinkedList<T>::rIterator LinkedList<T>::rbegin() {
    return riterator(tail);
}

template<typename T>
typename LinkedList<T>::rIterator LinkedList<T>::rend() {
    return riterator(rhead);
}

template<typename T>
void LinkedList<T>::assign(size_type amount, const_reference val) {
    ListNode* temp = head;
    if(amount <= count)
        while(amount){
            temp->value = val;
            temp = temp->next;
            --amount;
        }
    else{
        size_type i = count;
        while (i) {
            temp->value = val;
            temp = temp->next;
            --i;
        }
        while (count != amount)
            push_back(val);
    }
}

template<typename T>
void LinkedList<T>::insert(const_iterator pos, const_reference val) {
    ++count;
    ListNode* temp = new ListNode;
    ListNode* tempN = (pos.p)->next;
    temp->value = val;
    temp->prev = pos.p;
    pos.p->next = temp;
    temp->next = tempN;
    tempN->prev = temp;
}

template<typename T>
void LinkedList<T>::insert(size_type amount, const_reference val) {
    while(amount){
        push_back(val);
        --amount;
    }
}

template<typename T>
void LinkedList<T>::erase(iterator pos) {
    if(pos == begin())
        pop_front();
    else if (pos == end() - 1)
        pop_back();
    else{
        --count;
        ListNode* temp = pos.p;
        ListNode* Nprev = pos.p->prev;
        ListNode* Nnext = pos.p->next;
        Nprev->next = Nnext;
        Nnext->prev = Nprev;
        delete temp;
    }
}

template<typename T>
void LinkedList<T>::erase(iterator first, iterator last) {
    if (last == end() - 1)
        while (last != first){
            last = last.p->prev;
            pop_back();
        }
    else
        while (first != last){
            erase(first);
            first = first.p->next;
        }
}

template<typename T>
void LinkedList<T>::clear() {
    ListNode* temp = head;
    size_type i = count;
    while (i){
        temp->value = 0;
        temp = temp->next;
        --i;
    }
}

template<typename T>
void LinkedList<T>::resize(size_type amount, const_reference val) {
    if (amount == count) return;
    else if (amount > count)
        while (count != amount)
            push_back(val);
    else{
        while (count != amount)
            pop_back();
    }

}

template<typename T>
void LinkedList<T>::reverse() {
    ListNode* beg = head;
    ListNode* end = tail;
    for (size_type i = 0; i < count/2; i++){
        value_type temp = beg->value;
        beg->value = end->value;
        end->value = temp;
        beg = beg->next;
        end = end->prev;
    }
}

template<typename T>
void LinkedList<T>::swap(LinkedList& other) {
    LinkedList<T> temp(other);
    other = *this;
    *this = temp;

}

template<typename T>
void LinkedList<T>::assign(const_iterator pos, size_type amount, const_reference val) {
    ListNode* temp = pos.p;
    if(amount <= (count-pos.ind()-1))
        while(amount){
            temp->value = val;
            temp = temp->next;
            --amount;
        }
    else{
        size_type i = count-pos.ind();
        while (i) {
            temp->value = val;
            temp = temp->next;
            --i;
        }
        while (count != amount+pos.ind())
            push_back(val);
    }
}


int main() {
    LinkedList<int> q(2), k;
    q.push_front(4);
    q.push_front(5);
    q.push_front(6);
    q.pop_back();

    LinkedList<int>::Iterator e, r;

    r = q.end();

    LinkedList<int> w(q);
    e = w.begin();
    w.assign(e+2, 4, 77);
    std::cout << w << std::endl;
    /*k = w;
    k.resize(7, 99);

    //std::cout << q << std::endl;

    //std::cout << k << std::endl;

    q.insert(2, 10);
    q.resize(9, 11);
    q.reverse();
    q.insert(e + 2, 32);
    q.erase(e, e + 1);

    //std::cout << q << std::endl;

    std::sort(q.rbegin(), q.rend());
    //std::cout << q << std::endl;

    std::cout << *(std::find(q.begin(), q.end(), 6)) << std::endl;

    std::reverse(q.begin(), q.end());
    //std::cout << q << std::endl;

    std::fill(q.begin(), q.begin() + 5, 121);
    //std::cout << q << std::endl;
*/
    return 0;
}

