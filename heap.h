//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap
{
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[])
    {
        // Avoid overflow
        if (size > 63) return;

        data[size++] = idx;              // Add to end
        upheap(size - 1, weightArr); // and then heapify
    }

    int pop(int weightArr[])
    {
        // Avoid underflow
        if (size == 0) return -1;

        int minIdx = data[0]; // Save the root
        if (--size > 0)       // and then set root to last
        {                     // and then heapify
            data[0] = data[size];
            downheap(0, weightArr);
        }

        return minIdx;
    }

    void upheap(int pos, int weightArr[])
    {
        if (pos < 0 || size < 2) return; // OOB or zero/one node
        if (pos >= size) pos = size - 1; // OOB, default to last

        int parent = (pos - 1) / 2;
        while (weightArr[data[pos]] < weightArr[data[parent]])
        {
            // Swap idx at pos and parent if pos < parent
            int temp     = data[pos];
            data[pos]    = data[parent];
            data[parent] = temp;

            // Set child and parent
            pos = parent;
            parent = (pos - 1) / 2;
        }
    }

    void downheap(int pos, int weightArr[])
    {
        // TODO: swap parent downward while larger than any child
    }
};

#endif
