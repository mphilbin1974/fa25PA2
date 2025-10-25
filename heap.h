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

    void push(int idx, int weightArr[]) {
        // Completed TO DO: insert index at end of heap, restore order using upheap()
        data[size] = idx; // insert global index of node at end of heap
        upheap(size, weightArr); // restore heap - takes size as index of new node in heap and weightArr to access key value
        size++;
    }

    int pop(int weightArr[]) {
        // Completed TO DO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int root = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return root; // placeholder
    }

    // Parent: (i - 1) / 2
    // Children: 2*i + 1 & 2*i + 2.

    void upheap(int pos, int weightArr[]) {
        // Completed TO DO: swap child upward while smaller than parent
        while (pos > 0) { // each successive position is the parent of the last
            int idx = data[pos];
            int parentPos = (pos - 1) / 2;
            int parentIdx = data[parentPos];

            if (weightArr[idx] >= weightArr[parentIdx]) break;
            data[pos] = parentIdx;
            data[parentPos] = idx;
            pos = parentPos;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif