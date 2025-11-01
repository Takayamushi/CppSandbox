#pragma once

#include <iostream>
#include <algorithm>
#include "BasicTypes.h"

template<class T>
class Vector
{
public:

    // The explicit keyword prevents Vector from being initialized in the form:
    // Vector<T> v = x
    explicit Vector(int size); //Defined ctor
    Vector(int size, int length, T* array); //Defined ctor
    Vector(int size, std::initializer_list<T> list); //Defined ctor
    Vector(); //Default ctor
    Vector(const Vector<T>& other); //Copy ctor
    Vector& operator=(const Vector<T>& other); //Copy assignment
    Vector(Vector<T>&& other) noexcept; //Move ctor
    Vector& operator=(Vector&& other) noexcept; //Move assignment
    ~Vector();

    const T& operator[](int i) const;

    // The begin() and end() functions are required when we want to do
    // a range-based for loop.
    T* begin();
    T* end();
    
    inline int GetLength() const { return Length; }
    
    T Get(int aIndex) const;
    void Set(int aIndex, T aValue) const;
    void Append(T value);
    void InsertAt(int index, T value);
    int InsertSorted(T value);
    T Max() const;
    T Min() const;
    T Average() const;
    T Sum() const;
    T First() const;
    T Last() const;
    T Delete(int index);
    void Reverse();
    void ShiftRight();
    void RotateRight();
    void ShiftLeft();
    void RotateLeft();
    bool IsSorted() const;
    void Rearrange();
    int LinearSearch(T value) const;
    int BinarySearch(T value) const;
    
    void Print() const;
    
    static Vector* Merge(const Vector* a, const Vector* b);
    
    /* Set Operations */
    // Set Operations on integer arrays will usually have a complexity of O(n^2) when done on non sorted arrays.
    // We can reduce the complexity to O(n) by having the arrays sorted.
    static Vector* Union(const Vector* a, const Vector* b);
    static Vector* Intersection(const Vector* a, const Vector* b);
    static Vector* Subtract(const Vector* a, const Vector* b);
    
private:
    T* ArrayPtr;
    int Size;
    uint32 Length;
    
    bool IndexIsInRange(int aIndex) const;
};

template <class T>
Vector<T>::Vector(int size)
{
    Length = 0;
    Size = size;
    ArrayPtr = new T[size];
}

template <class T>
Vector<T>::Vector(int size, int length, T* array)
{
    Length = length;
    Size = size;
    ArrayPtr = array;
}

template <class T>
Vector<T>::Vector(int size, std::initializer_list<T> list)
{
    Size = size;
    ArrayPtr = new T[Size];
    std::copy(list.begin(), list.end(), ArrayPtr);
    Length = static_cast<uint32>(list.size());
}

template <class T>
Vector<T>::Vector()
{
    Length = 0;
    Size = 0;
    ArrayPtr = new T[0];
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    Length = other.Length;
    Size = other.Size;
    delete[] ArrayPtr;
    ArrayPtr = new T[Size];
    for (int i = 0; i < Size; i++)
    {
        ArrayPtr[i] = other[i];
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    if (this != &other)
    {
        T* newArray = new T[other.Size];
        Length = other.Length;
        Size = other.Size;
        for (int i = 0; i < Size; i++)
        {
            newArray[i] = other[i];
        }
        delete[] ArrayPtr;
        ArrayPtr = newArray;
    }
    
    return *this;
}

template <class T>
Vector<T>::Vector(Vector<T>&& other) noexcept
{
    //"Steal" the data from other
    Length = other.Length;
    Size = other.Size;
    ArrayPtr = other.ArrayPtr;
    
    //Cleanup other
    other.ArrayPtr = nullptr;
    other.Length = 0;
    other.Size = 0;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    //"Steal" the data from other
    Length = other.Length;
    Size = other.Size;
    ArrayPtr = other.ArrayPtr;
    
    //Cleanup other
    other.ArrayPtr = nullptr;
    other.Length = 0;
    other.Size = 0;
    return *this;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] ArrayPtr;
}

template <class T>
T Vector<T>::First() const
{
    return ArrayPtr[0];
}

template <class T>
T Vector<T>::Last() const
{
    int lastElement = Length > 0 ? Length - 1 : 0;
    return ArrayPtr[lastElement];
}

template<class T>
void Vector<T>::Print() const // O(n)
{
    const std::type_info& type = typeid(T);
    std::cout << "Array of " << type.name() << "\n";
    std::cout << "Size: " << Size << "\n";
    std::cout << "Length: " << Length << "\n";
    for (int i = 0; i < Length; i++)
    {
        std::cout << *(ArrayPtr + i) << ", ";
    }
    std::cout << "\n";
}

template<class T>
void Vector<T>::Append(T value) // O(1)
{
    if (Length < Size)
    {
        ArrayPtr[Length] = value;
        Length++;
    }
}

template<class T>
void Vector<T>::InsertAt(int index, T value) // O(n)
{
    if (IndexIsInRange(index))
    {
        if (Length < Size)
        {
            Length++;
        }
        for (int j = Length - 1; j > index; j--)
        {
            ArrayPtr[j] = ArrayPtr[j - 1];
        }
        
        ArrayPtr[index] = value;
    }
}

template<class T>
int Vector<T>::InsertSorted(T value)
{
    if (Length < Size)
    {
        if (IsSorted())
        {
            int i = Length - 1;
            while (i >= 0 && value < ArrayPtr[i])
            {
                ArrayPtr[i + 1] = ArrayPtr[i];
                i--;
            }
            ArrayPtr[i + 1] = value;
            Length++;
            return 0;
        }
    }

    return -1;
}

template<class T>
T Vector<T>::Delete(int index) // O(n)
{
    int returnValue = 0;
    if (IndexIsInRange(index))
    {
        returnValue = ArrayPtr[index];
        for (int j = index; j < Length - 1; j++)
        {
            ArrayPtr[j] = ArrayPtr[j + 1];
        }
        Length--;
    }
    return returnValue;
}

// It is possible to improve Linear search by using two different techniques:
//     - Transposition: Swap the found element with the previous one.
//     - Move To Front: Move the element to the front of the array
// In both cases, this would change the order of the elements as a side effect.
template<class T>
int Vector<T>::LinearSearch(T value) const // O(n)
{
    for (int i = 0; i < Length; i++)
    {
        if (ArrayPtr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

// Binary search requires less operations than a linear search but requires an array to be sorted
template<class T>
int Vector<T>::BinarySearch(T value) const
{
    int low = 0;
    int high = Length - 1;
    int mid = 0;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (value == ArrayPtr[mid])
        {
            return mid;
        }
        else if (value > ArrayPtr[mid])
        {
            low = mid + 1;
        }
        else if (value < ArrayPtr[mid])
        {
            high = mid - 1;
        }
    }
    return -1;
}

template<class T>
T Vector<T>::Get(int aIndex) const
{
    if (IndexIsInRange(aIndex))
    {
        return ArrayPtr[aIndex];
    }
    return -1;
}

template<class T>
void Vector<T>::Set(int aIndex, T aValue) const
{
    if (IndexIsInRange(aIndex))
    {
        ArrayPtr[aIndex] = aValue;
    }
}

template<class T>
T Vector<T>::Max() const
{
    T max = ArrayPtr[0];
    for (int i = 1; i < Length; i++)
    {
        max = std::max(ArrayPtr[i], max);
    }
    return max;
}

template<class T>
T Vector<T>::Min() const
{
    T min = ArrayPtr[0];
    for (int i = 1; i < Length; i++)
    {
        min = std::min(ArrayPtr[i], min);
    }
    return min;
}

template<class T>
T Vector<T>::Average() const
{
    T sum = Sum();
    return sum / Length;
}

template<class T>
T Vector<T>::Sum() const
{
    T sum = 0;
    for (int i = 0; i < Length; i++)
    {
        sum += ArrayPtr[i];
    }
    return sum;
}

template<class T>
void Vector<T>::Reverse()
{
    for (int i = 0, j = Length - 1; i < j; i++, j--)
    {
        std::swap(ArrayPtr[i], ArrayPtr[j]);
    }
}

template<class T>
void Vector<T>::ShiftRight()
{
    for (int i = Length - 2; i >= 0; i--)
    {
        ArrayPtr[i + 1] = ArrayPtr[i];
    }
    ArrayPtr[0] = 0;
}

template<class T>
void Vector<T>::RotateRight()
{
    int firstValue = ArrayPtr[Length - 1];
    for (int i = Length - 2; i >= 0; i--)
    {
        ArrayPtr[i + 1] = ArrayPtr[i];
    }
    ArrayPtr[0] = firstValue;
}

template<class T>
void Vector<T>::ShiftLeft()
{
    for (int i = 1; i < Length; i++)
    {
         ArrayPtr[i - 1] = ArrayPtr[i];
    }
    ArrayPtr[Length - 1] = 0;
}

template<class T>
void Vector<T>::RotateLeft()
{
    int firstValue = ArrayPtr[0];
    for (int i = 1; i < Length; i++)
    {
        ArrayPtr[i - 1] = ArrayPtr[i];
    }
    ArrayPtr[Length - 1] = firstValue;
}

template<class T>
bool Vector<T>::IsSorted() const
{
    for (int i = 0; i < Length - 1; i++)
    {
        if (ArrayPtr[i] > ArrayPtr[i + 1])
        {
            return false;
        }
    }
    return true;
}

template<class T>
void Vector<T>::Rearrange()
{
    int i = 0;
    int j = Length - 1;
    while (i < j)
    {
        while (ArrayPtr[i] < 0) { i++; }
        while (ArrayPtr[j] >= 0) { j--; }
        if (i < j)
        {
            std::swap(ArrayPtr[i], ArrayPtr[j]);
        }
    }
}

template<class T>
Vector<T>* Vector<T>::Merge(const Vector* a, const Vector* b)
{
    int i = 0; int j = 0; int k = 0;
    Vector* c = new Vector(a->Length + b->Length);
    while (i < a->Length && j < b->Length)
    {
        if (a->ArrayPtr[i] < b->ArrayPtr[j])
        {
            c->ArrayPtr[k++] = a->ArrayPtr[i++];
        }
        else
        {
            c->ArrayPtr[k++] = b->ArrayPtr[j++];
        }
    }

    for (; i < a->Length; i++)
    {
        c->ArrayPtr[k++] = a->ArrayPtr[i];
    }

    for (; j < b->Length; j++)
    {
        c->ArrayPtr[k++] = b->ArrayPtr[j];
    }
    c->Length = a->Length + b->Length;
    return c;
}

template<class T>
Vector<T>* Vector<T>::Union(const Vector* a, const Vector* b)
{
    Vector* c = new Vector(a->Length + b->Length);
    if (a->IsSorted() && b->IsSorted())
    {
        //The time complexity is reduced to O(n) when both arrays are sorted.
        int i = 0; int j = 0; int k = 0;
        while (i < a->Length && j < b->Length)
        {
            if (a->ArrayPtr[i] < b->ArrayPtr[j])
            {
                c->ArrayPtr[k++] = a->ArrayPtr[i++];
            }
            else if (a->ArrayPtr[i] > b->ArrayPtr[j])
            {
                c->ArrayPtr[k++] = b->ArrayPtr[j++];
            }
            else
            {
                c->ArrayPtr[k++] = a->ArrayPtr[i];
                i++;
                j++;
            }
        }
        for (; i < a->Length; i++)
        {
            c->ArrayPtr[k++] = a->ArrayPtr[i];
        }

        for (; j < b->Length; j++)
        {
            c->ArrayPtr[k++] = b->ArrayPtr[j];
        }
        c->Length = k;
    }
    else
    {
        int k = 0;
        for (int i = 0; i < a->Length; i++)
        {
            c->Append(a->ArrayPtr[i]);
        }
        
        for (int i = 0; i < b->Length; i++)
        {
            bool duplicateFound = false;
            for (int j = 0; j < c->Length; j++)
            {
                if (b->ArrayPtr[i] == c->ArrayPtr[j])
                {
                    duplicateFound = true;
                }
            }
            if (!duplicateFound)
            {
                c->Append(b->ArrayPtr[i]);
            }
        }
    }
    return c;
}

template<class T>
Vector<T>* Vector<T>::Intersection(const Vector* a, const Vector* b)
{
    Vector* c = new Vector(a->Length + b->Length);
    if (a->IsSorted() && b->IsSorted())
    {
        //The time complexity is reduced to O(n) when both arrays are sorted.
        int i = 0; int j = 0; int k = 0;
        while (i < a->Length && j < b->Length)
        {
            if (a->ArrayPtr[i] < b->ArrayPtr[j])
            {
                i++;
            }
            else if (a->ArrayPtr[i] > b->ArrayPtr[j])
            {
                j++;
            }
            else
            {
                c->ArrayPtr[k++] = a->ArrayPtr[i];
                i++;
                j++;
            }
        }
        c->Length = k;
    }
    else
    {
        for (int i = 0; i < a->Length; i++)
        {
            for (int j = 0; j < b->Length; j++)
            {
                if (a->ArrayPtr[i] == b->ArrayPtr[j])
                {
                    c->Append(a->ArrayPtr[i]);
                }
            }
        }
    }

    return c;
}

template<class T>
Vector<T>* Vector<T>::Subtract(const Vector* a, const Vector* b)
{
    Vector* c = new Vector(a->Length + b->Length);
    if (a->IsSorted() && b->IsSorted())
    {
        //The time complexity is reduced to O(n) when both arrays are sorted.
        int i = 0; int j = 0; int k = 0;
        while (i < a->Length && j < b->Length)
        {
            if (a->ArrayPtr[i] < b->ArrayPtr[j])
            {
                c->ArrayPtr[k++] = a->ArrayPtr[i];
            }
            else if (a->ArrayPtr[i] > b->ArrayPtr[j])
            {
                j++;
            }
            else
            {
                i++;
                j++;
            }
        }
        c->Length = k;
    }
    else
    {
        for (int i = 0; i < a->Length; i++)
        {
            bool elementFound = false;
            for (int j = 0; j < b->Length; j++)
            {
                if (a->ArrayPtr[i] == b->ArrayPtr[j])
                {
                    elementFound = true;
                }
            }
            if (!elementFound)
            {
                c->Append(a->ArrayPtr[i]);
            }
        }
    }
    return c;
}

template <class T>
const T& Vector<T>::operator[](int i) const
{
    {
        if (IndexIsInRange(i)) return ArrayPtr[i];
        //TODO Throw exception or handle error
        throw std::out_of_range("Array index out of range");
    }
}

template <class T>
T* Vector<T>::begin()
{
    return Length >= 0? &ArrayPtr[0] : nullptr;
}

template <class T>
T* Vector<T>::end()
{
    return Length >= 0? &ArrayPtr[0] + Length : nullptr;
}

template<class T>
bool Vector<T>::IndexIsInRange(int aIndex) const
{
    return aIndex >= 0 && aIndex < Length;
}
