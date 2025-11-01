#pragma once

#include "Vector.h"

namespace
{
    int FindSingleMissingElement(const Vector<int>* array)
    {
        //Given an array of subsequent numbers, we want to find the missing number in the sequence.
        int first = array->First();
        int last = array->Last();
        int n = last - first;
        for (int i = 0; i < n; i++)
        {
            if (array->Get(i) - i != first)
            {
                return i + first;
            }
        }
        return -1;
    }

    Vector<int> FindMultipleMissingElements(const Vector<int>* array)
    {
        //Give an array of subsequent numbers, we want to find all missing elements in the array.
        Vector<int> result(array->GetLength());
        int first = array->First();
        int offset = first;
        int last = array->Last();
        int n = last - first;
        for (int i = 0; i < n; i++)
        {
            int arrayValue = array->Get(i);
            int x = arrayValue - i;
            if (x > offset)
            {
                int diff = x - (offset);
                for (int j = 0; j < diff; j++)
                {
                    result.Append(offset + j + i);
                }
                offset += diff;
            }
        }
        return result;
    }
    
    Vector<int> FindMultipleMissingElementsAlternate(const Vector<int>* array)
    {
        //Give an array of subsequent numbers, we want to find all missing elements in the array.
        Vector<int> result(array->GetLength());
        int first = array->First();
        int last = array->Last();
        int n = last - first;
        Vector<char> elementsBitset(n, n, new char[n]);
        for (int i = 0; i < array->GetLength(); i++)
        {
            int arrayValue = array->Get(i);
            elementsBitset.Set(arrayValue - first, 1);
        }

        for (int i = 0; i < elementsBitset.GetLength(); i++)
        {
            if (elementsBitset.Get(i) != 1)
            {
                result.Append(first + i);
            }
        }
        return result;
    }
}
