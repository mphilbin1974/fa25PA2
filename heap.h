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

    // almost done, but not quite
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int idx = data[pos];

            int left = 2 * pos + 1;
            int right = left + 1;

            int leftIdx = data[left];
            int rightIdx =data[right];

            int min; // position of smallest child
            if (left > size) break; // CASE: node has 0 children
            if (right > size) min = left; // CASE: node has only a left child
            else { // CASE: node has two children --> take the smaller one
                min = left;
                if (weightArr[leftIdx] > weightArr[rightIdx])
                    min = rightIdx;
            }

            int minIdx = data[min];
            if (weightArr[idx] < weightArr[minIdx]) break;
            data[pos] = minIdx;
            data[min] = idx;
            pos = min;
        }
    }
};

#endif