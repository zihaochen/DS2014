#ifndef __TREEMAP_H
#define __TREEMAP_H
#define debug cout<<"not here\n"
#include "ElementNotExist.h"
#include "cstdlib"
#include "ctime"
#include <iostream>
using namespace std;

template<class K, class V>
class TreeMap
{

public:
     class Entry
    {
        K key;
        V value;

    public:
        int fix, Size;
        Entry *left, *right;
        Entry(K k, V v)
        {
            key = k;
            value = v;
            fix = rand();
            Size = 1;
        }

        Entry()
        {
            left = right = NULL;
            fix = rand();
            Size = 0;
            key = -1;
        }

        void resize()
        {
            if (Size != 0)
                Size = left -> Size + right -> Size + 1;
        }

        const K& getKey() const
        {
            return key;
        }

        const V& getValue() const
        {
            return value;
        }

        V & changeValue()
        {
            return value;
        }
    };


private:
    Entry *nullnode, *root;
	void insert(K k, V v, Entry *&i)
	{
		if (i == nullnode)
        {
			i = new Entry(k, v);
			i -> left = i -> right = nullnode;
        }
		else if (k < i -> getKey())
		{
			insert(k, v, i -> left);
			if (i -> left -> fix > i -> fix) rrot(i);
			else i -> resize();
		}
		else if (k == i -> getKey())
        {
            i -> changeValue() = v;
        }
		else
		{
			insert(k, v, i -> right);
			if (i -> right -> fix > i -> fix) lrot(i);
			else i -> resize();
		}
	}

	void remove(K x, Entry *&i)
	{
	    if (i == nullnode) throw ElementNotExist();
		if (x < i -> getKey() ) remove(x, i -> left);
		if (x > i -> getKey() ) remove(x, i -> right);
		if (x == i -> getKey())
		{
			if (i -> left == nullnode && i -> right == nullnode)
			{
				delete i;
				i = nullnode;
			}
			else if (i -> left == nullnode)
			{
				Entry *tmp = i;
				i = i -> right;
				delete tmp;
			}
			else if (i -> right == nullnode)
			{
				Entry *tmp = i;
				i = i -> left;
				delete tmp;
			}
			else if (i -> left -> fix > i -> right -> fix)
			{
				rrot(i);
				remove(x, i -> right);
			}
			else
			{
				lrot(i);
				remove(x, i -> left);
			}
		}
		i -> resize();
	}

	void rrot(Entry *&i)
	{
		Entry *tmp = i -> left;
		i -> left = tmp -> right;
		tmp -> right = i;
		i -> resize();
		tmp -> resize();
		i = tmp;
	}

	void lrot(Entry *&i)
	{
		Entry *tmp = i -> right;
		i -> right = tmp -> left;
		tmp -> left = i;
		i -> resize();
		tmp -> resize();
		i = tmp;
	}

	void clear(Entry *&i)
	{
	    if (i == nullnode) return;
		if (i -> left != nullnode) clear(i -> left);
		if (i -> right != nullnode) clear(i -> right);
		delete i;
		i = nullnode;
	}

	bool findKey(K x, Entry *i) const
	{
		if (i == nullnode) return 0;
		if (i -> getKey() == x) return 1;
		else if (i -> getKey() > x) return findKey(x, i -> left);
		else return findKey(x, i -> right);
	}

	const V& get(const K &x, const Entry *i) const
	{
		if (x == i -> getKey()) return i -> getValue();
		if (x < i -> getKey() && i -> left != nullnode) return get(x, i -> left);
		if (x < i -> getKey() && i -> left == nullnode) throw ElementNotExist();
		if (x > i -> getKey() && i -> right != nullnode) return get(x, i -> right);
		if (x > i -> getKey() && i -> right == nullnode) throw ElementNotExist();
	}

	bool findValue(V x, Entry *i) const
	{
	    if (i == nullnode) return 0;
		if (i -> getValue() == x) return 1;
		else return (findValue(x, i -> left) || findValue(x, i -> right));
	}

    Entry* copy(Entry *x, Entry *nil)
    {
        if (x == nil) return nullnode;
        Entry *tmp = new Entry(x -> getKey(), x -> getValue());
        tmp -> Size = x -> Size;
        tmp -> left = copy(x -> left, nil);
        tmp -> right = copy(x -> right, nil);
        return tmp;
    }

public:

    class Iterator
    {
    private:
        int cur;
        TreeMap *location;
    public:
        Iterator(TreeMap *l):location(l)
        {
            cur = 0;
        }

        bool hasNext()
        {
            return (cur < location -> size());
        }

        const Entry &next()
        {
            if (!hasNext()) throw ElementNotExist();
            cur++;
            return location -> findRank(cur, location -> root);
        }
    };

	TreeMap()
	{
		srand(time(NULL));
		nullnode = new Entry();
		nullnode -> Size = 0;
		root = nullnode;
	}


	~TreeMap()
	{
		clear();
		delete nullnode;
	}

	TreeMap &operator = (const TreeMap &x)
	{
	    clear();
	    delete nullnode;
		nullnode = new Entry();
		nullnode -> Size = 0;
        root = copy(x.root, x.nullnode);
	}

	TreeMap(const TreeMap &x)
	{
		srand(time(NULL));
		nullnode = new Entry();
		nullnode -> Size = 0;
        root = copy(x.root, x.nullnode);
	}

	void clear()
	{
		clear(root);
	}

	bool containsKey(const K &key) const
	{
		return findKey(key, root);
	}

	bool containsValue(const V &value) const
	{
		return findValue(value, root);
	}

	const V &get(const K &key) const
	{
		return get(key, root);
	}

	bool isEmpty() const
	{
		return (root == nullnode );
	}

	void put(const K &key, const V& value)
	{
		insert(key, value, root);
	}

	void remove(const K &key)
	{
		remove(key, root);
	}

	int size() const
	{
		return root -> Size;
	}

	Iterator iterator()
	{
        return Iterator(this);
	}

    const Entry &findRank(int n, Entry *i)
    {
        if (n == i -> left -> Size + 1) return *i;
        if (n < i -> left -> Size + 1) return findRank(n, i -> left);
        if (n > i -> left -> Size + 1)
        {
            n -= i -> left -> Size + 1;
            return findRank(n, i -> right);
        }
    }

};

#endif
