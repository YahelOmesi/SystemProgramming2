// yahelomessi@gmail.com

#include "Queue.hpp"
#include <stdexcept>

namespace graph{
    Queue::Queue(int capacity):firstIndex(0), nextIndex(0), totalCapacity(capacity), currentCapacity(0){
        data = new int[totalCapacity];
    }

    Queue::~Queue(){
        delete[] data;
    }

    //add an element to the queue
    void Queue::enqueue(int value){
        if(currentCapacity == totalCapacity){
            resize();
        }

        data[nextIndex] = value; //insert the new value to next available index
        nextIndex++;
        currentCapacity++;
    }

    //remove an element from the haed of the queue
    int Queue::dequeue(){
        if(isEmpty()){
            throw std::underflow_error("queue is empty");
        }
        int val = data[firstIndex];//head of the queue
        firstIndex++; //"skip" to the next element
        currentCapacity--;
        return val;
    }

    //peek at the first element (without removing it)
    int Queue::front() const{
        if(isEmpty()){
            throw std::underflow_error("queue is empty");
        }
        return data[firstIndex];
    }

    bool Queue::isEmpty() const{
        return currentCapacity == 0;
    }

    void Queue::resize(){
        int newCapacity = totalCapacity*2; //double the capacity
        int* newData = new int[newCapacity]; //to store the new array

        for(int i=0; i<currentCapacity; i++){
            newData[i] = data[firstIndex+i];
        }

        delete[] data; //release the old array
        data = newData; //point to the new array
        totalCapacity = newCapacity;
        firstIndex = 0;
        nextIndex = currentCapacity;
     }
}