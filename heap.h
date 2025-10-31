//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    // Adds an int element `idx` to the min heap
    // Uses int `weightArr[idx]` as a key
    // Restores min heap with `upheap()`
    // Increments `size`
    void push(int idx, int weightArr[]) {
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    // Removes and returns the int element at the root of the min heap
    // Uses int[] `weightArr[]` for keys
    // Restores min heap with `downheap()`
    // Decrements `size`
    int pop(int weightArr[]) {
        int root = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);
        return root;
    }

    // Swaps a node at int index `pos` with its parent as long as node weight is smaller than parent weight
    // Uses int[] `weightArr[]` for keys
    // Called from `push()` to restore heap
    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            int idx = data[pos];
            int parentIdx = data[parent];

            if (weightArr[idx] >= weightArr[parentIdx]) break;
            data[pos] = parentIdx;
            data[parent] = idx;
            pos = parent;
        }
    }

    // Swaps a node at int index `pos` with its smallest child as long as the node is larger than its smallest child weight
    // Uses int[] `weightArr[]` for keys
    // Called in `pop()` to restore heap
    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = left + 1;

            int smallest = pos;
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) smallest = left;
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) smallest = right;
            if (smallest == pos) break;

            int idx = data[pos];
            data[pos] = data[smallest];
            data[smallest] = idx;
            pos = smallest;
        }
    }
};

#endif