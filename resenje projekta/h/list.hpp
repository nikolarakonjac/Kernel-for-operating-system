//
// Created by os on 8/27/22.
//

#ifndef PROJECT_BASE_V1_0_LIST_HPP
#define PROJECT_BASE_V1_0_LIST_HPP



template<typename T>
class List {
private:
    struct Elem{
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}
    };

    Elem *head, *tail;

public:
    List() : head(0), tail(0) {}

    List(const List<T> &) = delete;

    Elem* getElem(){
        return head;
    }

    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T *data){
        Elem *elem = new Elem(data, head);
        head = elem;
        //ako je to jedini element, i pokazivac tail treba da pokazuje na taj element
        if (!tail) { tail = head; }
    }

    void addLast(T *data){
        Elem *elem = new Elem(data, 0);
        if (tail){
            //ako postoji tail
            tail->next = elem;
            tail = elem;
        }
        else{
            //nema nijedan element u listi
            head = tail = elem;
        }
    }

    T *removeFirst(){
        if (!head) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekFirst(){
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast(){
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next){
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekLast(){
        if (!tail) { return 0; }
        return tail->data;
    }

    int listSize(){
        Elem* temp = head;
        int counter = 0;
        while(temp){
            counter++;
            temp = temp->next;
        }
        return counter;
    }

    T* getData(int index){
        //index od 0 do n-1
        if(!head || index >= listSize())  return nullptr;

        Elem* temp = head;
        for(int i=0;i<index;i++){
            temp = temp->next;
        }
        return temp->data;
    }

};


#endif //PROJECT_BASE_V1_0_LIST_HPP
