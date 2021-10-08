#include<bits/stdc++.h>

template<typename T,typename Cp=std::less<T>>
class pairing_heap
{
private:
	using value_type=T;
	using value_compare=Cp;
	struct Node;

public:
	struct iterator;

private:
	Cp cmp;
	Node*_root;
	size_t _size;

	Node*merge(Node*,Node*);

	Node*mergesons(Node*);

	iterator delete_top();

	void _destroy(Node*&);

public:

	pairing_heap():cmp(),_root(nullptr),_size(0) {}

	pairing_heap(const pairing_heap&o):cmp(o.cmp),_root(o._root),_size(o._size) {}

	iterator push(const T&);

	iterator merge(const pairing_heap&);

	iterator join(pairing_heap&);

	iterator pop();

	T top();

	size_t size();

	bool empty();

	void destroy();

	std::pair<iterator,bool> modify(const iterator&,const T&);
};

template<typename T,typename Cp>
struct pairing_heap<T,Cp>::Node
{
	Node*prv,*son,*bro;
	T val;

	Node():prv(nullptr),son(nullptr),bro(nullptr),val(T()) {}

	explicit Node(const T&v):prv(nullptr),son(nullptr),bro(nullptr),val(std::move(v)) {}

	explicit Node(const T&&v):prv(nullptr),son(nullptr),bro(nullptr),val(std::move(v)) {}
};

template<typename T,typename Cp>
struct pairing_heap<T,Cp>::iterator
{
private:
	Node*node;

	friend class pairing_heap;

public:
	T operator*() const { return node->val; }

	bool operator==(void*o) { return node==o; }

	bool operator!=(void*o) { return node!=o; }

	iterator(): node(nullptr) {}

	explicit iterator(Node*o):node(o) {}

	iterator(const iterator&&iter) noexcept :node(std::move(iter.node)) {}

	iterator(const iterator&iter):node(std::move(iter.node)) {}
};

// 合并两个配对堆，时间复杂度 O(1)

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::Node*
pairing_heap<T,Cp>::merge(pairing_heap::Node*a,pairing_heap::Node*b)
{
	if(a==nullptr) return b;
	if(b==nullptr) return a;
	if(cmp(a->val,b->val)) std::swap(a,b);
	b->prv=a;
	b->bro=a->son;
	if(a->son!=nullptr) a->son->prv=b;
	a->son=b;
	return a;
}

// 插入

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::iterator
pairing_heap<T,Cp>::push(const T&val)
{
	++_size;
	if(_root==nullptr) _root=new Node(val);
	else
	{
		Node*node=new Node(val);
		_root=merge(_root,node);
	}
	return iterator(_root);
}

// 合并两个配对堆，仅合并而不清空加入的配对堆

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::iterator
pairing_heap<T,Cp>::merge(const pairing_heap<T,Cp>&o)
{
	_root=merge(_root,o._root);
	_size+=o._size;
	return iterator(_root);
}

// 合并两个配对堆，并清空加入的配对堆

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::iterator
pairing_heap<T,Cp>::join(pairing_heap<T,Cp>&o)
{
	merge(o);
	o.destroy();
	return iterator(_root);
}

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::Node*
pairing_heap<T,Cp>::mergesons(pairing_heap::Node*x)
{
	if(x==nullptr||x->bro==nullptr) return x;
	Node*a=x->bro;
	Node*b=a->bro;
	a->prv=x->prv=x->bro=a->bro=nullptr;
	return merge(merge(x,a),mergesons(b));
}

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::iterator
pairing_heap<T,Cp>::delete_top()
{
	--_size;
	_root=mergesons(_root->son);
	return iterator(_root);
}

template<typename T,typename Cp>
typename pairing_heap<T,Cp>::iterator
pairing_heap<T,Cp>::pop()
{
	if(_root==nullptr) return;
	Node*rt=_root;
	delete_top();
	delete rt;
	rt=nullptr;
	return iterator(_root);
}

template<typename T,typename Cp>
size_t pairing_heap<T,Cp>::size()
{
	return _size;
}

template<typename T,typename Cp>
T pairing_heap<T,Cp>::top()
{
	return _root==nullptr?(std::cerr<<"error!"<<std::endl,-0x3f3f3f3f):_root->val;
}

template<typename T,typename Cp>
bool pairing_heap<T,Cp>::empty()
{
	return _root==nullptr;
}

template<typename T,typename Cp>
void
pairing_heap<T,Cp>::_destroy(pairing_heap::Node*&x)
{
	if(x==nullptr) return;
	_destroy(x->bro);
	_destroy(x->son);
	--_size;
	delete x;
	x=nullptr;
}

template<typename T,typename Cp>
void
pairing_heap<T,Cp>::destroy()
{
	_destroy(_root);
	assert(_size==0);
}

template<typename T,typename Cp>
std::pair<typename pairing_heap<T,Cp>::iterator,bool>
pairing_heap<T,Cp>::modify(const pairing_heap::iterator&iter,const T&val)
{
	if(iter.node==nullptr||cmp(val,*iter)) return {iter,false};
	Node*x=iter.node;
	x->val=val;
	if(x==_root) return {iter,true};
	if(x->prv->son==x) x->prv->son=x->bro;
	else x->prv->bro=x->bro;
	if(x->bro!=nullptr) x->bro->prv=x->prv;
	x->prv=x->bro=nullptr;
	_root=merge(_root,x);
	return {iter,true};
}

struct cmp
{
	bool operator()(double a,double b) { return a<b; }
};

int main()
{
	pairing_heap<int,std::less<>> h;

	for(int i=1; i<=100; i++) h.push(i);

	h.destroy();
	return 0;
}
