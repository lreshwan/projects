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
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

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

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int mm;
  PComparator cc;
  void trickleDown(int i);

};

// Add implementation of member functions here
template<typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : mm(m), cc(c)
{
  
}

template<typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
  for(int i = 0; i < (int)data.size(); i++){
        data.pop_back();
  }
}

//adds an item into the heap and properly positions it
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  data.push_back(item);
  if(data.size() > 1){
    int size = data.size() - 1;
    int biggest = (size - 1) / mm;
    while(biggest >= 0 && cc(data[size], data[biggest])){
      std::swap(data[size], data[biggest]);
      size = biggest;
      biggest = (size - 1) / mm;
    }
  }
  
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");
  }
  //returns the element at the top of the heap
  else{
    return data[0];
  }
}


// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("The heap is empty");
  }
  //removes the most recently added item to the heap
  else{
    data[0] = data[data.size() - 1];
    data.pop_back();
    if(data.size() > 1){
      trickleDown(0);
    }
  }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const{
  //if the heap is empty returns true, else returns false
  if(data.size() == 0){
    return true;
  }
  else{
    return false;
  }
}

//reorganizes items in the heap when an item is popped
template<typename T, typename PComparator>
void Heap<T,PComparator>::trickleDown(int i){
  //array to store all the kids of the parent
  int kids[1 + mm];
  int biggest = mm * i + 1;

  if(i * mm + 1 >= (int)data.size()){
    return;
  }

  //fill in the kid array with kids
  for(int it = 1; it <= mm; it++){
    int pos = i * mm + it;
    if(pos < (int)data.size()){
      kids[it] = pos;
    }
    else{
      kids[it] = -1;
    }
  }

  //if the kid has more priority than the parent, set the parent to be that child
  for(int it = 1; it <= mm; it++){
    if(kids[it] != - 1 && cc(data[kids[it]] ,data[biggest])){
      biggest = kids[it];
    }
  }

  //if parent is bigger than the current index, swap the two items and recall trickle down
  if(cc(data[biggest], data[i])){
    std::swap(data[i], data[biggest]);
    trickleDown(biggest);
  }
}
#endif


