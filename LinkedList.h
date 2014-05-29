#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H

#include "IndexOutOfBound.h"
#include "ElementNotExist.h"
#define debug cout<<"not here\n"

using namespace std;

template <class T>
class LinkedList
{
	private:
		struct node
		{
			T data;
			node *pre, *next;
			node(const T x, node *p = NULL)
			{
				data = x; pre = p; next = NULL;
			}
			node()
			{
			    pre = next = NULL;
			}
		} *head, *tail;

    int Size;

	public:
		class Iterator
		{
        private:
            LinkedList *location;
            node *cur;
            bool last;
        public:
            Iterator(LinkedList *l):location(l)
            {
                cur = location -> head;
                last = false;
            }

            bool hasNext()
            {
                return (cur -> next != NULL);
            }

            const T& next()
            {
                if (!hasNext()) throw ElementNotExist();
                cur = cur -> next;
                last = true;
                return cur -> data;
            }

            void remove()
            {
                if (last == false) throw ElementNotExist();
                last = false;
                //node *tmp = cur;
                node *tmp2 = cur -> pre;
                if (cur -> next != NULL)
                    cur -> next -> pre = cur -> pre;
                cur -> pre -> next = cur -> next;
                delete cur;
                cur = tmp2;
                location -> Size--;
            }
		};

		LinkedList()
		{
			head = new node();
			tail = head;
			Size = 0;
		}

		LinkedList (const LinkedList<T> &c)
		{
		    Size = c.Size;
			node *tmp1 = c.head;
			head = new node();
			node *tmp2 = head;
			while (tmp1 -> next != NULL)
			{
				tmp2 -> next = new node(tmp1 -> next -> data, tmp2);  //RE here
				tmp1 = tmp1 -> next;
				tmp2 = tmp2 -> next;
			}
			tail = tmp2;
		}

		LinkedList<T> & operator = (const LinkedList<T> &c)
		{
		    clear();
		    Size = c.Size;
            node *tmp1 = c.head;
			node *tmp2 = head;
			while (tmp1 -> next != NULL)
			{
				tmp2 -> next = new node(tmp1 -> next -> data, tmp2);
				tmp1 = tmp1 -> next;
				tmp2 = tmp2 -> next;
			}
			tail = tmp2;
			return *this;
		}

		~LinkedList()
		{
			clear();
			delete head;
		}

		bool add(const T &e)
		{
			node *tmp = tail;
			tmp -> next = new node(e, tmp);
			tail = tmp -> next;
			Size++;
			return 1;
		}

		void addFirst(const T& elem)
		{
			node *tmp = new node(elem, head);
			if (head -> next != NULL)
				head -> next -> pre = tmp;
            else
                tail = tmp;
            tmp -> next = head -> next;
			head -> next = tmp;
            Size++;
		}

		void addLast(const T &elem)
		{
		    add(elem);
		}

		void add(int index, const T& element)
		{
		    if (!(index >= 0 && index <= Size)) throw ElementNotExist();
			node *tmp = head;
			int len = 0;
			while (len < index && tmp -> next != NULL)
			{
				tmp = tmp -> next;
				len++;
			}
			node *n = new node(element, tmp);
			if (tmp -> next != NULL)
				tmp -> next -> pre = n;
			n -> next = tmp -> next;
			tmp -> next = n;
			if (n -> next == NULL) tail = n;
			Size++;
		}

		void clear()
		{
			node *tmp1, *tmp2;
			tmp1 = head -> next;
			while  (tmp1 !=  NULL)
			{
				tmp2 = tmp1 -> next;
				delete tmp1;
				tmp1 = tmp2;
			}
			head -> next = NULL;
			tail = head;
			Size = 0;
		}

		bool contains(const T &e) const
		{
			node *tmp =head;
			while (tmp -> next != NULL)
			{
				tmp = tmp -> next;
				if (tmp -> data == e ) return 1;
			}
			return 0;
		}

		const T& get(int index) const
		{
		    if (!(index >= 0 && index < Size)) throw IndexOutOfBound();
            node *tmp = head -> next;
            while (index > 0)
            {
                tmp = tmp -> next;
                index--;
            }
            return tmp -> data;
		}

		const T& getFirst() const
		{
			if (head -> next == NULL) throw ElementNotExist();
			else return head -> next -> data;
		}

		const T& getLast() const
		{
			if (head -> next == NULL) throw ElementNotExist();
			else return (tail -> data);
        }

		bool isEmpty() const
		{
			return (head -> next == NULL);
		}

		void removeIndex(int index)
		{
		    if (!(index >= 0 && index < Size))
                throw IndexOutOfBound();
			node *tmp = head;
			int len = -1;
			while (len < index && tmp != NULL)
            {
                tmp = tmp -> next;
                len++;
            }
			tmp -> pre -> next = tmp -> next;
			if (tmp -> next != NULL) tmp -> next -> pre = tmp -> pre;
			if (index == Size - 1) tail = tmp -> pre;
			Size--;
            delete tmp;
		}

		bool remove(const T &e)
		{
			node *tmp = head;
			while (tmp -> data != e && tmp -> next != NULL)
				tmp = tmp -> next;
			if (tmp -> data == e)
			{
				tmp -> pre -> next = tmp -> next;
				if (tmp -> next != NULL) tmp -> next -> pre = tmp -> pre;
				if (tmp -> next == NULL) tail = tmp -> pre;
				delete tmp;
				Size--;
				return 1;
			}
			return 0;
		}

		void removeFirst()
		{
			node *tmp = head -> next;
			if (tmp == NULL) throw ElementNotExist();
			head -> next = tmp -> next;
			if (tmp -> next != NULL)
				tmp -> next -> pre = head;
            if (tmp -> next == NULL)
                tail = tmp -> pre;
			delete tmp;
			Size--;
		}

		void removeLast()
		{
			node *tmp = tail;
			if (head -> next == NULL) throw ElementNotExist();
            tail -> pre -> next = NULL;
            tail = tmp -> pre;
			delete tmp;
			Size--;
		}

		void set(int index, const T &element)
		{
		    if (!(index >= 0 && index < Size))
                throw IndexOutOfBound();
			node *tmp = head;
			int len = -1;
			while (len < index && tmp != NULL)
			{
				tmp = tmp -> next;
				len++;
			}
			tmp -> data = element;
		}

		int size() const
		{
			return Size;
		}

		Iterator iterator()
		{
			return Iterator(this);
		}
};
#endif


