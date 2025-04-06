// yahelomessi@gmail.com

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace graph{
    class PriorityQueue{

    private:
        int* data; //node IDs
        int* priorities; //approximate distances
        int capacity; 
        int size; //#current element

    public:
    PriorityQueue(int numVertices);
    ~PriorityQueue();

    void insert(int vrtex, int priority);
    int extractMin();
    void decreasePriority(int vertex, int newPriority);
    bool isEmpty() const;
    bool contains(int vertex) const;

    };
}

#endif