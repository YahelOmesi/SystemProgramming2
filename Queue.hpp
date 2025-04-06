// yahelomessi@gmail.com

namespace graph{
    class Queue{

        private:
        int* data;
        int firstIndex;
        int nextIndex;
        int totalCapacity;
        int currentCapacity;

        void resize();

        public:
        Queue(int capacity = 100);
        ~Queue();

        void enqueue(int value);
        int dequeue();
        int front() const;
        bool isEmpty() const;
    };

}