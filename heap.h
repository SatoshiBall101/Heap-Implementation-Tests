#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator()); //

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap(); //

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

	std::vector<T> nodes_; // store all nodes_
	unsigned int arity_; // what is tree's arity
	PComparator minMax_; // whats the criteria for best node?
	unsigned int parentIdx(unsigned int childIdx); 
	bool leafNode(unsigned int nodeIdx); 
	void trickleUp(unsigned int idx); 
	void trickleDown(unsigned int idx);

};

// Ctor

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
 : arity_(m), minMax_(c)
{}

// Dtor

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
	nodes_.push_back(item); // add item to last node spot

	trickleUp(size()-1); // restore heap property
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){

    throw std::underflow_error("No root to return; empty heap");

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

	return nodes_[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){

    throw std::underflow_error("No root to pop; empty heap");

  }

	nodes_[0] = nodes_[nodes_.size()-1]; // replace the root node with the last node

	nodes_.pop_back(); // remove the last element

	if(!empty()) // if we did not remove the last element, we must restore heap property
	{
		trickleDown(0);
	}

}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
	if (size() > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
	return nodes_.size();
}

template <typename T, typename PComparator>
unsigned int Heap<T, PComparator>::parentIdx(unsigned int childIdx)
{
	if (childIdx == 0)
	{
		return 0;
	}

	return (childIdx - 1) / arity_;
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::leafNode(unsigned int nodeIdx)
{

	if (((arity_ * nodeIdx) + 1) < size())
	{
		return false;
	}
	
	return true;

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(unsigned int idx)
{
    // Base case: we have reached the root of the heap
    if (idx == 0) {
        return;
    }

    // Calculate the index of the parent node
    unsigned int parentIndex = parentIdx(idx);

    // Check if the parent node has a lower/higher priority than the current node
    if (minMax_(nodes_[idx], nodes_[parentIndex])) {
        // Swap the current node with its parent node
        std::swap(nodes_[idx], nodes_[parentIndex]);

        // Recursively trickle up the parent node
        trickleUp(parentIndex);
    }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(unsigned int idx)
{
    // Calculate the index of the first child node
    unsigned int firstChildIdx = idx * arity_ + 1;

    // Base case: the current node is a leaf node
    if (firstChildIdx >= size()) {
        return;
    }

    // Find the child node with the highest priority
    unsigned int bestChildIdx = firstChildIdx;
    for (unsigned int i = 1; i < arity_; i++) {
        unsigned int childIdx = firstChildIdx + i;
        if (childIdx < nodes_.size() && minMax_(nodes_[childIdx], nodes_[bestChildIdx])) {
            bestChildIdx = childIdx;
        }
    }

    if (minMax_(nodes_[bestChildIdx], nodes_[idx])) {
        // Swap the current node with the best child node
        std::swap(nodes_[idx], nodes_[bestChildIdx]);

        // Recursively trickle down the best child node
        trickleDown(bestChildIdx);
    }
}

#endif
