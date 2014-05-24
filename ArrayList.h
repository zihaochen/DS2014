#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#include <iostream>
#define debug cout<<"not here\n"
using namespace std;

template <class T>
class ArrayList
{
private:
    T *elem;
    int maxSize,currentLength;

    void doubleSpace()
    {
        T *tmp = elem;
        elem = new T[2 * maxSize];
        for (int i = 0;i < maxSize; i++)
            elem[i] = tmp[i];
        maxSize = 2 * maxSize;
        delete []tmp;
    }
public:
 class Iterator
    {
    private:
        ArrayList<T> *loction;
        int cur;
        int last;
    public:
        Iterator(ArrayList<T> *a):loction(a)
        {
            cur = 0;
            last = -1;
        }

        bool hasNext()
        {
            return cur < loction -> size();
        }

        const T &next()
        {
            if (!hasNext()) throw ElementNotExist();
            last = cur;
            return (loction -> elem[cur++]);
        }

        void remove()
        {
            if (last == -1) throw ElementNotExist();
            loction -> removeIndex(last);
            last = -1;
            cur--;
        }
    };

    ArrayList()
    {
        maxSize = 1000;
        elem = new T[maxSize];
        currentLength = 0;
    }

    ~ArrayList()
    {
       // delete []elem;
       clear();
    }

    ArrayList(const ArrayList &x)
    {
        maxSize = x.maxSize;
        elem = new T [maxSize];
        currentLength = x.currentLength;
        for (int i = 0; i < currentLength; i++)
            elem[i] = x.elem[i];
    }

    ArrayList & operator = (const ArrayList &x)
    {
        delete [] elem;
        maxSize = x.maxSize;
        elem = new T[maxSize];
        currentLength = x.currentLength;
        for (int i = 0; i < currentLength; i++)
            elem[i] = x.elem[i];
        return (*this);
    }

    bool add(const T & e)
    {
        if (currentLength >= maxSize) doubleSpace();
        elem[currentLength++] = e;
        return 1;
    }

    void add(int index, const T& element)
    {
        if (!(index >= 0 && index <= currentLength)) throw IndexOutOfBound();
        if (currentLength >= maxSize) doubleSpace();
        for (int i = currentLength; i > index; i--)
            elem[i] = elem[i - 1];
        elem[index] = element;
        currentLength++;

    }

    void clear()
    {
        if (elem == NULL) return;
        currentLength = 0;
        delete []elem;
        elem = NULL;
    }

    bool contains(const T& e) const
    {
        for (int i = 0; i < currentLength; i++)
            if (elem[i] == e) return 1;
        return 0;
    }

    const T& get(int index) const
    {
        if (!(index >= 0 && index < currentLength)) throw IndexOutOfBound();
        return elem[index];
    }

    T& getForChange(int index)
    {
        if (!(index >= 0 && index < currentLength)) throw IndexOutOfBound();
        return elem[index];
    }

    bool isEmpty() const
    {
        return (currentLength == 0);
    }

    void removeIndex(int index)
    {
        if (!(index >= 0 && index < currentLength))
            throw IndexOutOfBound();
        for (int i = index; i < currentLength - 1; i++)
            elem[i] = elem[i + 1];
        currentLength--;
    }

    bool remove(const T &e)
    {
        int i;
        for (i = 0; i < currentLength; i++)
            if (elem[i] == e)
            {
                removeIndex(i);
                return true;
            }
        return false;
    }

    void set(int index, const T& element)
    {
        if (!(index >= 0 && index < currentLength)) throw IndexOutOfBound();
        elem[index] = element;
    }

    int size() const
    {
        return currentLength;
    }

    Iterator iterator()
    {
        return Iterator(this);
    }
};

#endif



