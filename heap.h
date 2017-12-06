//
// Created by lucian on 02.12.2017.
//

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

typedef long int key_type;

template <typename T, int CAPACITY>
class heap {

    struct Node {
        T value;
        key_type key;

        Node(T value, key_type key) : value(value), key(key) {}
    };

    int capacity;
    int size;
    Node* heap_queue[CAPACITY];

    bool (*comp)(key_type n1, key_type n2);

    void swap(Node* &n1, Node* &n2) {
        Node* temp = n1;
        n1 = n2;
        n2 = temp;
    }

    int position_check(int position) {
        if (position < 0) return 0;
        if (position >= capacity) return capacity - 1;
        return position;
    }

    int left(int i) {
        return position_check(2 * i + 1);
    }

    int right(int i) {
        return position_check(2 * i + 2);
    }

    int parent(int i) {
        return position_check((i - 1) / 2);
    }

    void heapify_down(int position) {
        if (position >= size) return;

        int l = left(position);
        int r = right(position);

        int pos = heap_queue[l] != nullptr && comp(heap_queue[l]->key, heap_queue[position]->key) ? l : position;
        pos = heap_queue[r] != nullptr && comp(heap_queue[r]->key, heap_queue[pos]->key) ? r : pos;

        if (pos != position) {
            swap(heap_queue[position], heap_queue[pos]);
            heapify_down(pos);
        }
    }

    void heapify_up(int position) {
        int p = parent(position);

        if (p == position) return;

        if (comp(heap_queue[position]->key, heap_queue[p]->key)) {
            swap(heap_queue[p], heap_queue[position]);
            heapify_up(p);
        }
    }

public:

    explicit heap(bool (*compFunc)(key_type , key_type)) : size(0), comp(compFunc), capacity(CAPACITY) {
        for (int i = 0; i < capacity; i++) {
            heap_queue[i] = nullptr;
        }
    }

    int get_capacity() const {
        return capacity;
    }

    int get_size() const {
        return size;
    }

    Node** get_array() {
        return heap_queue;
    }

    bool insert(T el, key_type priority) {
        if (size >= capacity) return false;
        heap_queue[size++] = new Node(el, priority);
        heapify_up(size - 1);
        return true;
    }

    bool get_first(T &resp) {
        if (size == 0) return false;
        resp = heap_queue[0]->value;
        return true;
    }

    bool get_first_priority(key_type &priority) {
        if (size == 0) return false;
        priority = heap_queue[0]->key;
        return true;
    }

    bool remove_first(T &resp) {
        if (!get_first(resp)) return false;
        return remove_first();
    }

    bool remove_first() {
        if (size == 0) return false;
        swap(heap_queue[0], heap_queue[size - 1]);
        delete heap_queue[size - 1];
        heap_queue[size - 1] = nullptr;
        size--;
        heapify_down(0);
        return true;
    }

    virtual ~heap() {
        while (remove_first()) {
            // the remove_first function does all the job, so the loop can remain empty
        }
    }
};


#endif //HEAP_HEAP_H
