#ifndef LL_H
#define LL_H

#include<iostream>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <memory>
#include <unordered_map>


template <typename T>
class Node {
	T data;
public:
	std::unique_ptr<Node> next;
	Node(T &value) : data(value), next(nullptr) {}
	~Node() {
	}
	T getData() const {
		return data;
	}
	
	
};
template <typename T>
class LinkedList {
private:
	std::unique_ptr<Node<T>> head;
	std::unordered_map<T,size_t> uniques;
public:
	LinkedList() : head(nullptr) {}
	void insert(T &value) {
		auto it = uniques.find(value);
		if (it == uniques.end())
			uniques.insert(std::make_pair(value, 1));
		else
			it->second++;
		auto temp = std::make_unique<Node<T>>(value);
		if (head) {
			temp->next = std::move(head);
			head = std::move(temp);
		}
		else {
			head = std::move(temp);
		}
	}

	void pushBack(T& value) {
		auto it = uniques.find(value);
		if (it == uniques.end())
			uniques.insert(std::make_pair(value, 1));
		else
			it->second++;
		auto temp = std::make_unique<Node<T>>(value);
		if (!head) {
			head = std::move(temp);
		}
		else {
			Node<T>* dummy = head.get();
			while (dummy->next.get() != nullptr) {
				dummy = dummy->next.get();
			}
			dummy->next.swap(temp);
		}
	}
	LinkedList(std::initializer_list<T> list) {
		int n = list.size();
		for (auto it = list.begin(); it != list.end(); ++it) {
			T value = *it;
			pushBack(value);
		}
	}
	void removeDuplicates() {
		for (auto it = uniques.begin(); it != uniques.end(); ++it) {
			if (it->second > 1)
				remove(it->first);
		}
	}
	void remove(const T& value) {
		bool found = false;
		Node<T> *temp = head.get();
		Node<T> *prev = nullptr;
		while (temp != nullptr) {
			if (temp->getData() == value) {
				found = true;
				prev->next.swap(temp->next);
				break;
			}
			prev = temp;
			temp = temp->next.get();
		}
		if (found)
			std::cout << "Found value " << value << " and deleted it" << std::endl;
		else
			std::cout << "Value " << value << " was not in list" << std::endl;
	}

	void printAll() {
		Node<T> *temp = head.get();
		std::cout << "Printing the list" << std::endl;
		while (temp) {
			std::cout << temp->getData() << std::endl;
			temp = temp->next.get();
		}
	}
};

#endif // !LL_H

