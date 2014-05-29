#ifndef __DEQUE_H
#define __DEQUE_H
#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
#include "Deque.h"
#include <iostream>
#define debug cout<<"not here\n"
using namespace std;


template <class T>
class Deque
{
private:
    T *elem;
    int first;
    int rear;
    int maxSize;
public:
    class Iterator
    {
    private:
        Deque *location;
        int cur;
        int type;
        bool last;
    public:
        Iterator(Deque *l, int t):location(l),type(t)
        {
            if (type == 0) cur = location -> first;
            if (type == 1) cur = location -> rear;
            last = 0;
        }

        bool hasNext()
        {
            if (type == 0) return (cur != location -> rear);
            if (type == 1) return ((cur  + location -> maxSize) % (location -> maxSize) != location -> first);
        }

        const T &next()
        {
            if (!hasNext()) throw ElementNotExist();
            last = 1;
            if (type == 0)
            {
                cur = (cur + 1) % (location -> maxSize);
                return location -> elem[cur];
            }
            if (type == 1)
            {
                T& tmp = location -> elem[cur];
                cur = (cur - 1 + location -> maxSize) % (location -> maxSize);
                return tmp;
            }
        }

        void remove()
        {
            if (last == 0) throw ElementNotExist();
            last = 0;
            if (type == 0)
            {
                for (int i = cur; i != (location -> first + 1) % location -> maxSize; i = (i - 1 + location -> maxSize) % ( location -> maxSize))
                    {
                        //if (tot == 1)cout<<"i is"<<i<<"rear is"<<location -> rear<<"first is"<<location -> first<<"size is"<<location -> maxSize<<endl;
                        location -> elem[i] = location -> elem[(i - 1 + location -> maxSize) % (location -> maxSize)];
                    }
                location -> first = (location -> first + 1) % (location -> maxSize);
                //cout<<"cur is"<<cur<<"rear is"<<location -> rear<<"first is"<<location -> first<<endl;
              //  cout<<"hasNext is"<<hasNext()<<endl;
            }
            if (type == 1)
            {
                int tmp = (cur + 1) % (location -> maxSize);
                for (int i = tmp; i != (location -> rear); i = (i + 1) % location -> maxSize)
                    location -> elem[i] =  location -> elem[(i + 1) % location -> maxSize];
                location -> rear = (location -> rear - 1 + location -> maxSize) % (location -> maxSize);
            }
        }
    };

    Iterator iterator()
    {
        return Iterator(this,0);
    }

    Iterator descendingIterator()
    {
        return Iterator(this,1);
    }

    Deque()
    {
        first = rear = 0;//first is empty
        maxSize = 10;
        elem = new T[maxSize];
    }

    ~Deque()
    {
        delete [] elem;
    }

    Deque &operator=(const Deque & x)
    {
        delete [] elem;
        first = x.first;
        rear = x.rear;
        maxSize = x.maxSize;
        elem = new T[maxSize];
        for (int i = 0; i < maxSize; i++)
            elem[i] = x.elem[i];
        return (*this);
    }

    Deque (const Deque &x)
    {
        first = x.first;
        rear = x.rear;
        maxSize = x.maxSize;
        elem = new T[maxSize];
        for (int i = 0; i < maxSize; i++)
            elem[i] = x.elem[i];
    }

    void addFirst(const T& e)
    {
        elem[first] = e;
        first = (first - 1 + maxSize) % maxSize;
        if (first == rear) doubleSpace();
    }

    void addLast(const T &e)
    {
        rear = (rear + 1) % maxSize;
        elem[rear] = e;
        if (rear == first) doubleSpace();
    }

    bool contains(const T& e) const
    {
        for (int i = (first + 1) % maxSize; i != (rear + 1) % maxSize; i = (i + 1) % maxSize)
            if (elem[i] == e) return 1;
        return 0;
    }

    void clear()
    {
        rear = first = 0;
    }

    bool isEmpty() const
    {
        return (rear == first);
    }

    const T& getFirst()
    {
        if (first != rear)
            return (elem[(first + 1) % maxSize]);
        else throw ElementNotExist();
    }

    const T& getLast()
    {
        if (first != rear)
            return elem[rear];
        else
            throw ElementNotExist();
    }

    void removeFirst()
    {
        if (size() == 0) throw ElementNotExist();
        first = (first + 1) % maxSize;
    }

    void removeLast()
    {
        if (size() == 0) throw ElementNotExist();
        rear = (rear - 1 + maxSize) % maxSize;
    }

    const T& get(int index) const
    {
        if (index >= size() || index < 0) throw IndexOutOfBound();
        return elem[((first + 1 + index) % maxSize)];
    }

    void set(int index, const T &e)
    {
        if (index >= size() || index < 0) throw IndexOutOfBound();
        elem[(first + 1 + index) % maxSize] = e;
    }

    int size() const
    {
        int length = (rear - first + maxSize) % maxSize;
        return length;
    }

    void doubleSpace()
    {
        T *tmp = elem;
        elem = new T[maxSize *2];
        for (int i = 1; i <= maxSize; i++)
            elem[i] = tmp[(first + i) % maxSize];
        first = 0;
        rear = maxSize;
        maxSize *= 2;
        delete tmp;
    }
};
#endif
