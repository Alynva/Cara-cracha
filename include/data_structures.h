/*

  Gabriel Alves,
  São Carlos - SP, 2017.

  https://gist.github.com/CptSpookz/78b8e6394b250d45c859a0786fed787b

*/

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

template<class T>
class Node {
public:
	T value;
	Node* next;
	Node* previous;
	Node() :next(this), previous(this) {};
	Node(const T val) : value(val), next(this), previous(next) {};
	~Node() { next = nullptr; previous = nullptr; }
};

template<class T>
class Queue {
private:
	Node<T> header;
	int size;

public:
	Queue():size(0) {};
	~Queue() { this->clear(); };

	void enqueue(const T, bool&);
	bool dequeue(T&);

	bool isEmpty() const { bool check = (header.next == &header) ? true : false; return check; };
	int getSize() const { return this->size; };
	Node<T>* getFront() const { return this->header.next; };
	Node<T>* getBack() const { return this->header.previous; };

	void clear();

};

template<class T>
void Queue<T>::enqueue(const T element, bool& check) {
	check = false;
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->next = &header;
	aux->previous = header.previous;
	header.previous->next = aux;
	header.previous = aux;
	size++;
	check = true;
}


template<class T>
bool Queue<T>::dequeue(T& element) {
	if (!this->isEmpty()) {
		element = header.previous->value;
		Node<T>* aux = header.next;
		header.next = aux->next;
		aux->next->previous = &header;
		delete(aux);
		size--;
		return true;
	}
	return false;
}

template<class T>
void Queue<T>::clear() {
	T temp;
	while (this->dequeue(temp));
}

#endif