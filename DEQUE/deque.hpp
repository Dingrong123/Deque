    #ifndef SJTU_DEQUE_HPP
    #define SJTU_DEQUE_HPP

    #include "exceptions.hpp"
    #include <malloc.h>
    #include <cstddef>

    namespace sjtu {

    const int allLength=1500;

    template<class T>
    	class deque {
    	private:
    		struct Node {

    			T * data[allLength];
    			int currentLength;//现有长度
    			Node *prev;
    			Node *next;
    			Node(int n = 2500)
    			{
    				prev = NULL, next = NULL, currentLength = 0;
    				memset(data, 0, sizeof(data));
    			}

    			~Node()
    			{

    			    for(int i=0;i<currentLength;++i)
                    {
                        delete data[i];
                    }

    			}

    		};


    		Node *head=new Node, *tail;
    		int allNum, perLength;

    	public:

    		class const_iterator;
    		class iterator //finished
    		{
    			friend deque;
    		private:
    			Node * idxNode;//存放数据的节点
    			Node* h;//存放头节点的位置
    			int idxNum;//数据的下标
    		public:
    			/**
    			* return a new iterator which pointer n-next elements
    			*   even if there are not enough elements, the behaviour is **undefined**.
    			* as well as operator-
    			*/
    			iterator(Node *i1 = NULL, Node *i2 = NULL, int i3 = 0)
    			{
    				idxNode = i1;
    				h = i2;
    				idxNum = i3;
    			};

    			iterator &operator=(const iterator &rhs)//finished
    			{
    				if (this == &rhs)
    					return *this;
    				else
    				{
    					idxNode = rhs.idxNode;
    					h = rhs.h;
    					idxNum = rhs.idxNum;

    				}

    				return *this;
    			}
    			iterator operator+(const int &n) const //finished
    			{
    				iterator tmp = *this;
    				return tmp += n;
    			}

    			iterator operator-(const int &n) const//finished
    			{
    				iterator tmp = *this;
    				return tmp -= n;

    			}
    			// return th distance between two iterator,
    			// if these two iterators points to different vectors, throw invaild_iterator.
    			int operator-(const iterator &rhs) const//finished
    			{
    				int m = 0;
    				if (h != rhs.h) throw sjtu::invalid_iterator();
    				iterator tmp = *this;
    				while (tmp.idxNode)
    				{
    					if (tmp.idxNode == rhs.idxNode)
    					{
    						return (-m +tmp.idxNum - rhs.idxNum);
    					}
    					else
    					{
    						m += (tmp.idxNode->currentLength - tmp.idxNum);
    						tmp.idxNode = tmp.idxNode->next;
    						tmp.idxNum = 0;
    					}
    				}
    				iterator tmp1 = rhs;
    				tmp = *this;
    				m = 0;
    				while (tmp1.idxNode)
    				{
    					if (tmp1.idxNode == tmp.idxNode)
    					{
    						return m + tmp.idxNum - tmp1.idxNum;
    					}
    					else
    					{
    						m += (tmp1.idxNode->currentLength - tmp1.idxNum);
    						tmp1.idxNode = tmp1.idxNode->next;
    						tmp1.idxNum = 0;
    					}
    				}

    			}

    			iterator operator+=(const int &n)//finished
    			{
    			    if(n<0)
                        return operator-=(-n);
                        int tmp=n;
    				if(tmp+idxNum<idxNode->currentLength)
                    {
                        idxNum+=tmp;return *this;
                    }

                    else
                    {
                        if(idxNode->next)
                        {
                            tmp-=idxNode->currentLength-idxNum;
                            idxNode=idxNode->next;
                        }
                        while(idxNode&&tmp-idxNode->currentLength>=0&&idxNode->next!=NULL)
                        {
                            tmp-=idxNode->currentLength;
                            idxNode=idxNode->next;
                        }
                        idxNum=tmp;
                        return *this;
                    }

    			}

    			iterator operator-=(const int &n)//finished
    			{
    			    if(n<0)
                        return operator+=(-n);
    				int tmp=n;
    				if(idxNum-n>=0)
                        idxNum-=n;
                    else
                    {
                        if(idxNode->prev)
                        {
                            tmp-=(idxNum+1);
                            idxNode=idxNode->prev;
                        }
                    while(idxNode&&idxNode->currentLength<=tmp && idxNode->prev)
    				{
    					tmp -= idxNode->currentLength;
    					idxNode = idxNode->prev;
    				}
                    idxNum=idxNode->currentLength - tmp - 1;
                    }

                    return *this;
    			}

    			iterator operator++(int) //finished
    			{
    				iterator tmp = *this;
    				++*this;
    				return tmp;
    			}

    			iterator& operator++()//finished
    			{
    				if (idxNode->next&&idxNum < idxNode->currentLength - 1)
    					++idxNum;
                    else if (!idxNode->next&&idxNum < idxNode->currentLength)
    					++idxNum;
    				else
    				{
    					if (!idxNode->next)
    						throw sjtu::invalid_iterator();
    					idxNode = idxNode->next;
    					idxNum = 0;

    				}
    				return *this;
    			}

    			iterator operator--(int)//finished
    			{
    				iterator tmp = *this;
    				--*this;
    				return tmp;
    			}

    			iterator& operator--()//finished
    			{
    				if (idxNum > 0)
    					--idxNum;
    				else
    				{
    					if (idxNode->prev == h)
    						throw sjtu::invalid_iterator();
    					idxNode = idxNode->prev;
    					idxNum = idxNode->currentLength - 1;
    				}

    				return *this;
    			}

    			T& operator*() const //finished
    			{
    			    if(idxNode->currentLength<=idxNum)
                        throw sjtu::invalid_iterator();
    				return *(idxNode->data[idxNum]);
    			}

    			T* operator->() const noexcept {
    				T *tmp;
    				tmp = idxNode->data[idxNum];
    				return tmp;
    			}
    			bool operator==(const iterator &rhs) const //finished
    			{
    				if (rhs.idxNode == this->idxNode&&rhs.h == this->h&&rhs.idxNum == this->idxNum)
    					return true;
    				return false;
    			}
    			bool operator==(const const_iterator &rhs) const //finished
    			{
    				if (rhs.idxNode == this->idxNode&&rhs.h == this->h&&rhs.idxNum == this->idxNum)
    					return true;
    				return false;
    			}
    			bool operator!=(const iterator &rhs) const//finished
    			{
    				return !(*this == rhs);
    			}
    			bool operator!=(const const_iterator &rhs) const//finished
    			{
    				return !(*this == rhs);
    			}

    			Node* idn()   {return idxNode;};
    		};
    		class const_iterator //finished
    		{
    			friend deque;
    		private:
    			Node * idxNode;//存放数据的节点
    			Node *h;//存放头节点的位置
    			int idxNum;//数据的下标
    		public:
    			const_iterator(Node *i1 = NULL, Node *i2 = NULL, int i3 = 0) :idxNode(i1), h(i2), idxNum(i3) {};

    			const_iterator operator=(const const_iterator &rhs)//finished
    			{
    				if (this == &rhs)
    					return *this;
    				else
    				{
    					idxNode = rhs.idxNode;
    					h = rhs.h;
    					idxNum = rhs.idxNum;
    				}
    				return *this;
    			}
    			const_iterator operator=(const iterator &rhs)//finished
    			{
    				idxNode = rhs.idxNode;
    				h = rhs.h;
    				idxNum = rhs.idxNum;
    				return *this;
    			}
    			// return th distance between two iterator,
    			// if these two iterators points to different vectors, throw invaild_iterator.
    			const_iterator operator+(const int &n) const //finished
    			{
    				const_iterator tmp = *this;
    				return tmp += n;
    			}

    			const_iterator operator-(const int &n) const//finished
    			{
    				const_iterator tmp = *this;
    				return tmp -= n;

    			}
    			// return th distance between two iterator,
    			// if these two iterators points to different vectors, throw invaild_iterator.
    			int operator-(const const_iterator &rhs) const//finished
    			{
    				int m = 0;
    				if (h != rhs.h) throw sjtu::invalid_iterator();
    				const_iterator tmp = *this;
    				while (tmp.idxNode)
    				{
    					if (tmp.idxNode == rhs.idxNode)
    					{
    						return (-m +tmp.idxNum - rhs.idxNum);
    					}
    					else
    					{
    						m += (tmp.idxNode->currentLength - tmp.idxNum);
    						tmp.idxNode = tmp.idxNode->next;
    						tmp.idxNum = 0;
    					}
    				}
    				const_iterator tmp1 = rhs;
    				tmp = *this;
    				m = 0;
    				while (tmp1.idxNode)
    				{
    					if (tmp1.idxNode == tmp.idxNode)
    					{
    						return m + tmp.idxNum - tmp1.idxNum;
    					}
    					else
    					{
    						m += (tmp1.idxNode->currentLength - tmp1.idxNum);
    						tmp1.idxNode = tmp1.idxNode->next;
    						tmp1.idxNum = 0;
    					}
    				}

    			}

    			const_iterator operator+=(const int &n)//finished
    			{
    			    if(n<0)
                        return operator-=(-n);
                        int tmp=n;
    				if(tmp+idxNum<idxNode->currentLength)
                    {
                        idxNum+=tmp;return *this;
                    }
    				/*for (int i = 0; i < n; ++i)
    				{
    					if (idxNum < idxNode->currentLength - 1)
    						++idxNum;
    					else
    					{

    						if (idxNode->next)
                            {
                                idxNum = 0;
                                idxNode = idxNode->next;
                            }
                            else
                                ++idxNum;

    					}
    				}
    				return *this;*/
                    else
                    {
                        if(idxNode->next)
                        {
                            tmp-=idxNode->currentLength-idxNum;
                            idxNode=idxNode->next;
                        }
                        while(idxNode&&tmp-idxNode->currentLength>=0&&idxNode->next!=NULL)
                        {
                            tmp-=idxNode->currentLength;
                            idxNode=idxNode->next;
                        }
                        idxNum=tmp;
                        return *this;
                    }

    			}

    			const_iterator operator-=(const int &n)//finished
    			{
    			    if(n<0)
                        return operator+=(-n);
    				int tmp=n;
    				if(idxNum-n>=0)
                        idxNum-=n;
                    else
                    {
                        if(idxNode->prev)
                        {
                            tmp-=(idxNum+1);
                            idxNode=idxNode->prev;
                        }
                    while(idxNode&&idxNode->currentLength<=tmp && idxNode->prev)
    				{
    					tmp -= idxNode->currentLength;
    					idxNode = idxNode->prev;
    				}
                    idxNum=idxNode->currentLength - tmp - 1;
                    }

                    return *this;
    			}

    			const_iterator operator++(int) //finished
    			{
    				const_iterator tmp = *this;
    				++*this;
    				return tmp;
    			}

    			const_iterator& operator++()//finished
    			{
    				if (idxNode->next&&idxNum < idxNode->currentLength - 1)
    					++idxNum;
                    else if (!idxNode->next&&idxNum < idxNode->currentLength)
    					++idxNum;
    				else
    				{
    					if (!idxNode->next)
    						throw sjtu::invalid_iterator();
    					idxNode = idxNode->next;
    					idxNum = 0;

    				}
    				return *this;
    			}

    			const_iterator operator--(int)//finished
    			{
    				const_iterator tmp = *this;
    				--*this;
    				return tmp;
    			}

    			const_iterator& operator--()//finished
    			{
    				if (idxNum > 0)
    					--idxNum;
    				else
    				{
    					if (idxNode->prev == h)
    						throw sjtu::invalid_iterator();
    					idxNode = idxNode->prev;
    					idxNum = idxNode->currentLength - 1;
    				}

    				return *this;
    			}

    			const T& operator*() const//finished
    			{
    				return *(idxNode->data[idxNum]);
    			}

    			const T* operator->() const noexcept {
    				T *tmp;
    				tmp = idxNode->data[idxNum];
    				return tmp;
    			}

    			bool operator==(const iterator &rhs) const//finished
    			{
    				if (rhs.idxNode == this->idxNode&&rhs.idxNum == this->idxNum)
    					return true;
    				return false;
    			}
    			bool operator==(const const_iterator &rhs) const //finished
    			{
    				if (rhs.idxNode == this->idxNode&&rhs.idxNum == this->idxNum)
    					return true;
    				return false;
    			}

    			bool operator!=(const iterator &rhs) const { return !(*this == rhs); }//finished
    			bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }//finished
    		};
    		/**
    		* TODO Constructors
    		*/
    		deque()//finished
    		{
    			tail=head;
    			allNum = 0;
    		}

    		deque(const deque &other)//finished
    		{
    			tail = head;
    			allNum = other.allNum;
    			Node  *q;
    			q = other.head->next;

    			while (q != NULL)
    			{
    				Node *tmp = new Node;
    				for (int i = 0; i < q->currentLength; ++i)
    					tmp->data[i]=new T(*(q->data[i]));
    				tail->next = tmp; tmp->prev = tail;
    				tail = tmp;
    				tmp->currentLength = q->currentLength;
    				q = q->next;
    			}
    		}
    		~deque()
    		{
    			clear();
    			delete head;
    		}
    		/**
    		* TODO assignment operator
    		*/
    		deque &operator=(const deque &other)//finished
    		{
    			if (this == &other)
    				return *this;
    			clear();

    			tail = head;
    			allNum = other.allNum;
    			Node *q = other.head->next;
    			while (q != NULL)
    			{
    				Node *tmp = new Node;
    				for (int i = 0; i < q->currentLength; ++i)
    					tmp->data[i]=new T(*(q->data[i]));
    				tail->next = tmp; tmp->prev = tail;
    				tail = tmp;
    				tmp->currentLength = q->currentLength;
    				q = q->next;
    			}
    			return *this;
    		}
    		/**
    		* access specified element with bounds checking
    		* throw index_out_of_bound if out of bound.
    		*/
    		T & at(const size_t &pos)//finished
    		{
    			if (pos >= allNum)
    				throw sjtu::index_out_of_bound();
    			Node *tmp = head->next;
    			size_t m = pos+1;
    			while (tmp)
    			{
    				if (tmp->currentLength < m)
    				{
    					m -= tmp->currentLength;
    					tmp = tmp->next;
    				}

    				else
    				{
    					return *(tmp->data[m-1]);
    				}

    			}
    		}

    		const T & at(const size_t &pos) const //finished
    		{

    			if (pos > allNum)
    				throw sjtu::index_out_of_bound();
    			Node *tmp = head->next;
    			size_t m = pos+1;
    			while (tmp)
    			{
    				if (tmp->currentLength < m)
    				{
    					m -= tmp->currentLength;
    					tmp = tmp->next;
    				}

    				else
    				{
    					return *(tmp->data[m-1]);
    				}

    			}
    		}
    		T&  operator[](const size_t &pos)
    		{
    			if (pos > allNum)
    				throw sjtu::index_out_of_bound();
    			return at(pos);
    		}

    		const T & operator[](const size_t &pos) const
    		{
    			if (pos > allNum)
    				throw sjtu::index_out_of_bound();
    			return at(pos);
    		}
    		/**
    		* access the first element
    		* throw container_is_empty when the container is empty.
    		*/
    		const T & front() const//finished
    		{

    			if(allNum==0)
                    throw sjtu::container_is_empty();
                const_iterator it = cbegin();
    			return (*it);
    		}
    		/**
    		* access the last element
    		* throw container_is_empty when the container is empty.
    		*/
    		const T & back() const //finished
    		{
    		    if(allNum==0)
                    throw sjtu::container_is_empty();
    			const_iterator it = cend();
    			--it;
    			return(*it);
    		}
    		/**
    		* returns an iterator to the beginning.
    		*/
    		iterator begin()//finished
    		{
    			Node *tmp = head->next;

                if(tmp)
                {
                    iterator p(tmp, head, 0);
    				return p;
                }
                else
                {
                    iterator p(head, head, 0);
    				return p;
                }


    		}
    		const_iterator cbegin() const //finished
    		{
    		    Node *tmp = head->next;
    				if(tmp)
                {
                    const_iterator p(tmp, head, 0);
    				return p;
                }
                else
                {
                    const_iterator p(head, head, 0);
    				return p;
                }
    		}
    		/**
    		* returns an iterator to the end.
    		*/
    		iterator end()
    		{

    				iterator p(tail, head, tail->currentLength);
    				return p;
    		}
    		const_iterator cend() const//finished
    		{
    				const_iterator p(tail, head, tail->currentLength);
    				return p;
    		}

    		bool empty() const { return allNum == 0; }//finished

    		size_t size() const { return allNum; }//finished

    		void clear()
    		{
    			Node *tmp ,*q=head->next;
    			while (q)
    			{
    				tmp = q;
    				q = tmp->next;
    				delete tmp;
    			}
    			tail=head;
    			head->next=NULL;
    			allNum = 0;
    		}
    		/**
    		* inserts elements at the specified locat on in the container.
    		* inserts value before pos
    		* returns an iterator pointing to the inserted value
    		*     throw if the iterator is invalid or it point to a wrong place.
    		*/
    		iterator insert(iterator pos, const T &value) //finished
    		{
    			if ((pos.h != head)||(pos.idxNode!=tail&&pos.idxNode->currentLength<=pos.idxNum)||(pos.idxNode==tail&&pos.idxNode->currentLength<pos.idxNum))
                {
                    throw sjtu::invalid_iterator();
                }
               if(pos.idxNode==head)
                 {
                     Node* tmp=new Node;
                     tmp->data[0]=new T(value);
                     tmp->prev=head;
                     head->next=tmp;
                     tail=tmp;
                     tmp->currentLength=1;
                     allNum+=1;
                     iterator p(head->next,head,0); return p;
                 }

    			Node *p = pos.idxNode;
    			if (p->currentLength ==allLength)
    			{
    			    if(pos==end())
                    {
                        Node *tmp=new Node;
                        tmp->data[0]=new T(value);
                        tail->next=tmp; tmp->prev=tail; tail=tmp;
                        tmp->currentLength=1;
                        ++allNum;
                        iterator q(tmp,head,0);
                        return q;
                    }
    				int tmp = pos.idxNum;
    				T* da = p->data[allLength - 1];
    				for (int i = allLength - 1; i > tmp; --i)
    					p->data[i] = p->data[i - 1];
    				p->data[tmp] = new T(value);
    				if (p->next&&p->next->currentLength == allLength)
    				{
    					Node *q = new Node;
    					q->data[0]=da;
    					q->currentLength = 1;
    					p->next->prev = q;
    					q->next = p->next;
    					q->prev = p;
    					p->next = q;
    				}
    				else if(p->next&&p->next->currentLength <allLength)
    				{
    					Node *pn = p->next;
    					for (int i = pn->currentLength; i > 0; --i)
    						pn->data[i] = pn->data[i - 1];
    					pn->data[0] = da;
    					++pn->currentLength;
    				}

    				else
                    {
                        Node *pn=new Node;
                        pn->data[0]=da;
                        pn->prev=tail;
                        tail->next=pn;
                        tail=pn;
                        pn->currentLength=1;
                    }
    			 }
    			else
    			{

    				int tmp = pos.idxNum;
    				if(tmp<=p->currentLength)
                    {
    				for (int i = p->currentLength; i > tmp; --i)
    					p->data[i] = p->data[i - 1];
    				p->data[tmp] = new T(value);
    				++p->currentLength;
                    }

    			}
    			allNum += 1;

    			return pos;
    		}
    		/**
    		* removes specified element at pos.
    		* removes the element at pos.
    		* returns an iterator pointing to the following element, if pos pointing to the last element, end() will be returned.
    		* throw if the container is empty, the iterator is invalid or it points to a wrong place.
    		*/
    		iterator erase(iterator pos)
    		{
    			if (allNum == 0)
    				throw sjtu::container_is_empty();
    			if (pos.h != head || !pos.idxNode->data)
    				throw sjtu::invalid_iterator();
    			Node *p = pos.idxNode;
    			int tmp = pos.idxNum;
    			if (p->currentLength == 1)
    			{
    				if (p->next)
    				{
    					iterator q(p->next, head, 0);
    					p->prev->next = p->next;
    					p->next->prev = p->prev;
    					delete p;
    					allNum-=1;
    					return q;
    				}
    				else
    				{
                        tail=p->prev;
                        p->prev->next=NULL;
    					delete p;
    					allNum-=1;
    					iterator q=end();
    					return q;

    				}
    			}
    			else
    			{
    			    delete p->data[tmp];
    				for (int i = tmp; i < p->currentLength - 1; ++i)
    					p->data[i] = p->data[i + 1];
                     p->data[p->currentLength-1]=NULL;

    				if (p!=tail&&tmp == p->currentLength - 1)
    					++pos;

    				--p->currentLength;

    				if(p==tail&&tmp == p->currentLength)
                    {
                        allNum -= 1;return end();
                    }

    			}
    			allNum -= 1;

    			return pos;
    		}
    		/**
    		* adds an element to the end
    		*/
    		void push_back(const T &value)//finished
    		{

    			if (tail->currentLength >= allLength/2 || tail == head)
    			{
    				Node *tmp = new Node;
    				tmp->prev = tail; tail->next = tmp; tail = tmp;
    				tmp->currentLength = 1;
    				tmp->data[0]=new T(value);
    			}
    			else
    			{
                tail->data[tail->currentLength++]=new T(value);
    			}
    			allNum += 1;
    		}
    		/**
    		* removes the last element
    		*     throw when the container is empty.
    		*/
    		void pop_back() //finished
    		{
    			if (allNum == 0)
    				throw sjtu::container_is_empty();
    			if (tail->currentLength == 1)
    			{
    				Node *tmp = tail;
    				tail->prev->next=NULL;
    				tail = tail->prev;
    				delete tmp;
    			}
    			else
    			{
    			   // tail->allo.destroy(tail->data+tail->currentLength-1);
    			   delete tail->data[tail->currentLength-1];
    			   tail->data[tail->currentLength-1]=NULL;
    			    tail->currentLength -= 1;
    			}

    			allNum -= 1;
    		}
    		/**
    		* inserts an element to the beginning.
    		*/
    		void push_front(const T &value) //finished
    		{
    			Node *p = head->next;
    			if (p&&p->currentLength <allLength/2)
    			{

    				for (int i = p->currentLength; i > 0; --i)
    					p->data[i] = p->data[i - 1];

    				p->data[0]=new T(value);
    				++p->currentLength;
    			}
    			else
    			{
    				Node *tmp = new Node;
    				//tmp->allo.construct(tmp->data,value);
    				tmp->data[0]=new T(value);
    				tmp->currentLength = 1;

    				if(head->next)
    				{
    				    head->next->prev=tmp;
    				    tmp->next=head->next;
    				    tmp->prev = head;
    				    head->next = tmp;
    				}
    				else
                    {
                     tmp->prev = head;
    				 head->next = tmp;
    				 tail=tmp;
                    }

    			}

    			allNum += 1;
    		}
    		/**
    		* removes the first element.
    		*     throw when the container is empty.
    		*/
    		void pop_front()
    		{
    			if (allNum == 0)
    				throw sjtu::container_is_empty();
    			Node *p = head->next;
    			if (p->currentLength != 1)
    			{
    			    delete p->data[0];
    				for (int i = 0; i < p->currentLength - 1; ++i)
    					p->data[i] = p->data[i + 1];
                    p->data[p->currentLength-1]=NULL;
    				p->currentLength -= 1;
    			}
    			else
    			{
    				Node *q = p;
    				p = p->next;

    				delete q;

    				if(p!=NULL)
    				   p->prev = head;
    				head->next = p;
    				if(p==NULL)
                        tail=head;
    			}
    			--allNum;
    		}

    	};
    }
    #endif;
