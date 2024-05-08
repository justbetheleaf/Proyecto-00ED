#pragma once //incluye solo uan vez el .h en la compilación

template <typename E> //que funcione con cualquier tipo de dato
class List {
private:
	List(const List<E>& other) {} //copy consturctor 
	void operator = (const List<E>& other) {} //assign operator 

public: //funciones puramente virtuales que solo tienen implementacion en los subclases que hereden
	List() {}
	virtual ~List() {}
	virtual void insert(E element) = 0;
	virtual void append(E element) = 0;
	virtual void set(E element) = 0;
	virtual E remove() = 0;
	virtual void clear() = 0;
	virtual E& getElement() = 0;
	virtual void goToStart() = 0;
	virtual void goToEnd() = 0;
	virtual void goToPos(int pos) = 0;
	virtual void next() = 0;
	virtual void previous() = 0;
	virtual bool atStart() = 0;
	virtual bool atEnd() = 0;
	virtual int getSize() = 0;
	virtual int getPos() = 0;
	virtual void print(string titulo) = 0;
	virtual int indexOf(E element) = 0;
	virtual bool contains(E element) = 0;
};

