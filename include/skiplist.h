#pragma once
#include <utility>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::size_t;

template<typename T>
class Node
{
	std::pair<int, T> data;
	Node* next;
	Node* down;
public:
	Node(int key = -1, T val = T())
	{
		data = std::make_pair(key, val);
		next = nullptr;
		down = nullptr;
	}
	template<typename U>
	friend class SkipList;
};

template<typename T>
class SkipList
{
	std::vector<Node<T>*> heads;
	size_t max_lvls = 16;
	size_t get_rand_lvl()
	{
		int lvl = 1;
		while ((std::rand() % 2) && lvl < max_lvls) ++lvl;
		return lvl;
	}
public:
	SkipList(size_t max_levels = 16, int seed = std::time(0)) : max_lvls(max_levels)
	{
		std::srand(seed);
		heads.resize(max_lvls);
		for (size_t i = 0; i < max_lvls; ++i)
		{
			heads[i] = new Node<T>;
			if (i) heads[i]->down = heads[i - 1];
		}
	}
	~SkipList()
	{
		for (size_t i = 0; i < max_lvls; ++i)
		{
			Node<T>* current = heads[i];
			while (current)
			{
				Node<T>* tmp = current;
				current = current->next;
				delete tmp;
			}
		}
	}
	T* find(size_t key)
	{
		Node<T>* current = heads.back();
		while (current) 
		{
			while (current->next != nullptr && current->next->data.first <= key) 
			{
				current = current->next;
			}
			if (current->data.first == key) return &(current->data.second);
			else current = current->down;
		}
		return nullptr;
	}
	bool insert(size_t key, T data)
	{
		size_t node_height = get_rand_lvl();
		std::vector<Node<T>*> node_lvls(node_height);
		Node<T>* current = heads.back();
		if (find(key)) return false;
		int cur_lvl = max_lvls - 1;
		while (current)
		{
			while (current->next != nullptr && current->next->data.first < key)
			{
				current = current->next;
			}
			if (cur_lvl > node_height - 1) --cur_lvl;
			else
			{
				Node<T>* new_node = new Node<T>(key, data);
				new_node->next = current->next;
				current->next = new_node;
				node_lvls[cur_lvl] = new_node;
				--cur_lvl;
			}
			current = current->down;
		}
		for (size_t i = node_lvls.size() - 1; i > 0; --i)
			node_lvls[i]->down = node_lvls[i - 1];
		return true;
	}
	bool erase(size_t key)
	{
		if (!find(key)) return false;
		Node<T>* current = heads.back();
		while (current)
		{
			while (current->next != nullptr && current->next->data.first < key)
			{
				current = current->next;
			}
			if (current->next != nullptr && current->next->data.first == key)
			{
				Node<T>* tmp = current->next;
				current->next = tmp->next;
				delete tmp;
			}
			current = current->down;
		}
		return true;
	}
};