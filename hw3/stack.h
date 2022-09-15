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

template<typename T> Stack<T>::Stack(){
    
}

template<typename T> Stack<T>::~Stack(){
    for(int i = 0; i < (int)this->size(); i++){
        this->pop_back();
    }
}

template<typename T> bool Stack<T>::empty() const{
    //if empty return true if not return false
    if(this->size() == 0){
        return true;
    }
    else{
        return false;
    }
    return false;
}

template<typename T> size_t Stack<T>::size() const{
    //return the size of the stack
    return std::vector<T>::size();
}

template<typename T> void Stack<T>::push(const T& item){
    //add an item into the stack
    this->push_back(item);
}

template<typename T> void Stack<T>::pop(){
    //remove last added item from the stack
    if(this->empty()){
        throw std::underflow_error("The stack is empty");
    }
    else{
        this->pop_back();
    }
}

template<typename T> const T& Stack<T>::top() const{
    //return the most recently added item into the stack
    if(this->empty()){
        throw std::underflow_error("The stack is empty");
    }    
    return this->back();
}



#endif