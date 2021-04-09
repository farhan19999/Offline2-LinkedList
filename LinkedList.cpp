#include<bits/stdc++.h>
using namespace std;

class Node
{
private:
    Node* prev;
    Node* next;
    int personNo;
    int reflex_time;
public:
    Node()
    {
        personNo = 0;
        reflex_time = 0;
        next = NULL;
        prev = NULL;
    }
    Node(int personNo,int ref_t)
    {
        this->personNo = personNo;
        reflex_time = ref_t;
    }

    Node* next_Node()
    {
        return next;
    }
    Node* prev_Node()
    {
        return prev;
    }

    void setNext(Node* next)
    {
        this->next = next;
    }
    void setPrev(Node* prev)
    {
        this->prev = prev;
    }
    int getRefT()
    {
        return reflex_time;
    }
    int getPersonNo()
    {
        return personNo;
    }

};

class LinkedList
{
private:
    Node* cur; // Cursor refers head and cur->prev refers tail

public:
    LinkedList()
    {
        cur = NULL;
    }

    bool isEmpty()
    {
        return cur == NULL;
    }

    Node* find(int personNo)
    {
        if(isEmpty())
        {
            cout<<"The list is empty...."<<endl;
            return cur;
        }
        Node* t = cur->next_Node();
        while(t != cur && t->getPersonNo() != personNo) t = t->next_Node();
        if(t->getPersonNo() != personNo)
        {
            cout<<"The element is not in the list"<<endl;
            return cur;
        }
        else return t;

    }
    //Insert in head position
    void addFirst(Node* e)
    {
        if(isEmpty())
        {
            e->setNext(e);
            e->setPrev(e);
            cur = e;
            return;
        }

        e->setNext(cur);
        e->setPrev(cur->prev_Node());
        cur->prev_Node()->setNext(e);
        cur->setPrev(e);
        cur = e;

    }
    //Insert into tail position
    void addLast(Node* e)
    {
        if(isEmpty())
        {
            addFirst(e);
            return;
        }

        e->setNext(cur);
        e->setPrev(cur->prev_Node());
        cur->prev_Node()->setNext(e);
        cur->setPrev(e);
    }

    void insertBefore(int personNo, Node* elem)
    {
        if(isEmpty())return;
        Node* right = find(personNo);
        elem->setNext(right);
        elem->setPrev(right->prev_Node());
        right->prev_Node()->setNext(elem);
        right->setPrev(elem);
    }

    void insertAfter(int personNo, Node* elem )
    {
        if(isEmpty())return;
        Node* left = find(personNo);
        elem->setPrev(left);
        elem->setNext(left->next_Node());
        left->next_Node()->setPrev(elem);
        left->setNext(elem);
    }

    Node* head()
    {
        if(isEmpty())
        {
            cout<<"The list is empty"<<endl;
            return cur;
        }
        return cur;
    }

    Node* tail()
    {
        if(isEmpty())
        {
            cout<<"The list is empty"<<endl;
            return cur;
        }
        return cur->prev_Node();
    }


    void remove(Node* n)
    {
        if(cur == n)
        {
            if(cur != cur->next_Node())cur = cur->next_Node();
            else{
                cur = NULL;
                return;
            }
        }

        Node* old = n;
        old->next_Node()->setPrev(old->prev_Node());
        old->prev_Node()->setNext(old->next_Node());
        delete old;
    }

    void remove(int personNo)
    {
        Node* t  = find(personNo);
        remove(t);
    }

    void printForwardFrom(Node* n)
    {
        Node* temp = n;
        while(1)
        {
            cout<<temp->getPersonNo();
            temp = temp->next_Node();
            if(temp == n)break;
            cout<<", ";
        }
    }

    void printBackwardFrom(Node* n)
    {
        Node* temp = n;
        while(1)
        {
            cout<<temp->getPersonNo();
            temp = temp->prev_Node();
            if(temp == n)break;
            cout<<", ";
        }
    }

    ~LinkedList()
    {
        Node* temp  = cur->next_Node();
        while(!isEmpty())
        {
            temp  = temp->next_Node();
            remove(temp->prev_Node());
        }
    }
};
