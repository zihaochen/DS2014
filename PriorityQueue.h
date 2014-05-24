#ifndef __PRIORITYQUEUE_H
#define __PRIORITYQUEUE_H

#include "ArrayList.h"
#include "ElementNotExist.h"
#include "PriorityQueue.h"
#include <iostream>
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
        PriorityQueue *location;
        PriorityQueue *tmp;
        int cur;
        int cnt; // for remove
        int preSize;
        bool last;
    public:
        Iterator(PriorityQueue *l):location(l)
        {
            cur = 0;
            last = 0;
            cnt = 0;
            preSize = location -> elem.size();
        }

        bool hasNext()
        {
            return (cur < preSize);
        }

        const V &next()
        {
            cur ++;
            last = 1;
            return location -> elem.get(cur - 1 - cnt);
        }

        void remove()
        {
            if (last == 0) throw ElementNotExist();
            location -> elem.removeIndex(cur - 1 - cnt);
            cnt++;
            last = 0;
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
		while (cmp(elem.getForChange(i), elem.getForChange((i - 1) / 2)))
			swap(elem.getForChange(i), elem.getForChange((i - 1) / 2));
	}

	void pop()
	{
		swap(elem.getForChange(0),elem.getForChange(elem.size() - 1));
		elem.removeIndex(elem.size() - 1);
		down(0);
	} // question: how to reduce to O(log n)??

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
