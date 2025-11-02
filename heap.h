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
        if (size < 2) return; // zero/one node
        if (pos < 0 || pos >= size) pos = size - 1; // OOB, default to last

        int parent = (pos - 1) / 2;
        while (weightArr[data[pos]] < weightArr[data[parent]])
        {
            // Swap current and parent if current < parent
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
        if (size < 2) return;                // zero/one node
        if (pos < 0 || pos >= size) pos = 0; // OOB, default to root

        while (true)
        {
            // Set left and right children (because there's 2 per household or whatever)
            int left  = (2 * pos) + 1;
            int right = (2 * pos) + 2;
            int smallest = pos; // plus for now, assume the smallest idx is the root

            // then check if root is larger than either child, and set the smallest accordingly
            if ( left < size && weightArr[data[left ]] < weightArr[data[smallest]])
                smallest = left;
            if (right < size && weightArr[data[right]] < weightArr[data[smallest]])
                smallest = right;

            // if the root is the smallest, then we've finished
            if (smallest == pos) break;

            // Swap root and smallest
            int temp       = data[pos];
            data[pos]      = data[smallest];
            data[smallest] = temp;

            pos = smallest;
        }
    }
};

#endif
