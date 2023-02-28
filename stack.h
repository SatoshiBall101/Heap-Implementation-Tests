#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack : private std::vector<T>
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
};

template <typename T>
Stack<T>::Stack()
{
}

template <typename T>
Stack<T>::~Stack()
{
}

template <typename T>
bool Stack<T>::empty() const
{
	if(Stack<T>::size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
size_t Stack<T>::size() const
{
	return std::vector<T>::size();
}

template <typename T>
void Stack<T>::push(const T& item)
{
    std::vector<T>::push_back(item);
    return;
}

template <typename T>
void Stack<T>::pop()  // throws std::underflow_error if empty
{
    if(Stack<T>::empty())
    {
        throw std::underflow_error("Can't pop; stack is empty");
    }
    else
    {
        std::vector<T>::pop_back();
    }
}

template <typename T>
const T& Stack<T>::top() const  
{
    if(Stack<T>::empty())
    {
        throw std::underflow_error("Can't return value; stack is empty");
    }
    else
    {
        return std::vector<T>::at(size()-1);
    }
}


#endif