#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"
#include "PriorityQueue.h"
#include <iostream>
#include <stdio.h>
#define debug cout<<"not here\n"
using namespace std;

template <class V, class C = less<V> >
class PriorityQueue
{
private:
	ArrayList<V> elem;
	C cmp;
	void down(int i)
	{
	    int child;
		for (; (2 * i + 1) < elem.size(); i = child)
		{
			child = 2 * i + 1;
			if ((child + 1) < elem.size() && cmp(elem.getForChange(child + 1), elem.getForChange(child))) child++;
			if (cmp(elem.getForChange(child), elem.getForChange(i)))
				swap(elem.getForChange(child), elem.getForChange(i));
            else break;
		}
	}

public:
    class Iterator
    {
    private:
        C cmp;
        ArrayList<V> change;
        PriorityQueue *location;
        int *f1; // iterator array -> heap
        int *f2; // heap -> iterator array
        int cur;
        int preSize;
        bool last;
    public:
        Iterator(PriorityQueue *l):location(l)
        {
            cur = 0;
            last = 0;
            preSize = location -> elem.size();
            f1 = new int [preSize];
            f2 = new int [preSize];
            for (int i = 0; i < preSize; i++)
                f1[i] = f2[i] = i;
            change = location -> elem;
        }

        bool hasNext()
        {
            return (cur < preSize);
        }

        const V &next()
        {
            if (!hasNext()) throw ElementNotExist();
            cur ++;
            last = 1;
            return change.get(cur - 1);
        }

        void remove()
        {
            if (last == 0) throw ElementNotExist();
            last = 0;
            cut(f1[cur - 1]);
        }

        void cut(int i)
        {
            if (i == location -> size() - 1)
            {
                 location -> elem.removeIndex(location -> size() - 1);
                 return;
            }
            swap(location -> elem.getForChange(i),location -> elem.getForChange(location -> size() - 1));
            swap(f1[f2[i]],f1[f2[location -> size() - 1]]);
            swap(f2[i],f2[location -> size() - 1]);
            location -> elem.removeIndex(location -> size() - 1);
          //  printf("%d  %d\n",location -> elem.get(i),location -> elem.get((i - 1) /2));
            while (i > 0 && cmp(location -> elem.get(i),location -> elem.get((i - 1) / 2)))
                {
                    swap(location -> elem.getForChange(i), location -> elem.getForChange((i - 1) / 2));
                    swap(f1[f2[i]],f1[f2[(i - 1) / 2]]);
                    swap(f2[i], f2[(i - 1) / 2]);
                    i = (i - 1) / 2;
                }
            int child;
            for (; (2 * i + 1) < location -> elem.size(); i = child)
            {
                child = 2 * i + 1;
                if ((child + 1) < location -> elem.size() && cmp(location -> elem.getForChange(child + 1),location -> elem.getForChange(child)))
                    child++;
                if (cmp(location -> elem.getForChange(child), location -> elem.getForChange(i)))
                {
                    swap(location -> elem.getForChange(child), location -> elem.getForChange(i));
                    swap(f1[f2[child]],f1[f2[i]]);
                    swap(f2[child],f2[i]);
                }
                else break;
            }

        }

        ~Iterator()
        {
            delete [] f1;
            delete [] f2;
        }
    };

	PriorityQueue() { }
	~PriorityQueue() { }

	PriorityQueue &operator=(const PriorityQueue &x)
	{
		elem = x.elem;
		return (*this);
	}

	PriorityQueue(const PriorityQueue &x)
	{
		elem = x.elem;
	}

	PriorityQueue(const ArrayList<V> &x)
	{
		elem = x;
		for (int i = elem.size() / 2; i >= 0; i--)
			down(i);
	}

	void clear()
	{
		elem.clear();
	}

	const V &front() const
	{
	    if (size() == 0) throw ElementNotExist();
		return elem.get(0);
	}

	bool empty() const
	{
		return elem.isEmpty();
	}

	void push(const V &value)
	{
		elem.add(value);
		int i = elem.size() - 1;
		while (cmp(elem.getForChange(i), elem.getForChange((i - 1) / 2)) && i > 0)
        {
			swap(elem.getForChange(i), elem.getForChange((i - 1) / 2));
			i = (i - 1) / 2;
        }
	}

	void pop()
	{
	    if (size() == 0) throw ElementNotExist();
		swap(elem.getForChange(0),elem.getForChange(elem.size() - 1));
		elem.removeIndex(elem.size() - 1);
		down(0);
	}

	int size() const
	{
		return elem.size();
	}

    Iterator iterator()
    {
        return Iterator(this);
    }
};

#endif
