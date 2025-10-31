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

        data[size++] = idx;

        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[])
    {
        if (size == 0) return -1;

        int minIdx = data[0];

        if (--size > 0)
        {
            data[0] = data[size];
            downheap(0, weightArr);
        }

        return minIdx;
    }

    void upheap(int pos, int weightArr[])
    {
        // TODO: swap child upward while smaller than parent
    }

    void downheap(int pos, int weightArr[])
    {
        // TODO: swap parent downward while larger than any child
    }
};

#endif
