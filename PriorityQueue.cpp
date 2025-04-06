// yahelomessi@gmail.com

#include "PriorityQueue.hpp"
#include <stdexcept>

namespace graph{

    PriorityQueue::PriorityQueue(int numVertices):capacity(numVertices),size(0){
        data = new int[capacity];
        priorities = new int[capacity];
    }

    PriorityQueue::~PriorityQueue(){
        delete[] data;
        delete[] priorities;
    }

    void PriorityQueue::insert(int vertex, int priority){

        if(size >= capacity){
            throw std::overflow_error("the priority queue is full");
        }

        data[size] = vertex;
        priorities[size] = priority;
        size++;
    }

    //extraction of the node with lowest distance
    int PriorityQueue::extractMin(){
        if(isEmpty()){
            throw std::underflow_error("priority queue is empty");
        }

        int minIndex = 0;
        for(int i = 1; i < size; i++){ //find the node with lowest priority
            if(priorities[i] < priorities[minIndex]){
                minIndex = i;
            }
        }
        int minVertex = data[minIndex];

        //replace the last element in place of the element we removed
        data[minIndex] = data[size-1];
        priorities[minIndex] = priorities[size-1];
        size--;;

        return minVertex;

    }

    //if we found a better priority for the node
    void PriorityQueue::decreasePriority(int vertex, int newPriority){
        for(int i = 0; i < size; i++){
            if(data[i] == vertex && newPriority < priorities[i]){
                priorities[i] = newPriority;
                return;
            }
        }
    }

    bool PriorityQueue::isEmpty() const{
        return size == 0;
    }

    bool PriorityQueue::contains(int vertex) const {
        for(int i = 0; i < size; i++){
            if(data[i] == vertex){
                return true;
            }
        }
        return false;
    }
    }
