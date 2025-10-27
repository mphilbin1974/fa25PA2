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
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // Completed TO DO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int root = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);
        return root;
    }

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
        // Completed TO DO: swap parent downward while larger than any child
        while (true) {
            int left = 2 * pos + 1;
            int right = left + 1;

            int smallest = pos;
            if (left < size && weightArr[data[left]] < weightArr[data[smallest]]) smallest = left;
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]]) smallest = right;
            if (smallest == pos) break;

            int idx = data[pos];
            int smallestIdx = data[smallest];
            data[pos] = smallestIdx;
            data[smallest] = idx;
            pos = smallest;
        }
    }
};

#endif