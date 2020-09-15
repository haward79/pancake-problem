#include <iostream>

using std::cout;
using std::cin;

const int kMaxPancakes = 100;

int findIndexOfMax(int*, int*);
void reverseArray(int*, int*);
bool isContains(int, int*, int*);
void readPancakes(int&, int[]);
void sortPancakes(int&, int[], int&);
void printPancakes(const int&, int[]);

int main()
{
    int numPancake = 0;
    int pancakeSizes[kMaxPancakes];
    int countSteps = 0;

    readPancakes(numPancake, pancakeSizes);

    cout << ">> Input <<\n\n";
    printPancakes(numPancake, pancakeSizes);
    cout << "\n";

    cout << ">> Process <<\n\n";
    sortPancakes(numPancake, pancakeSizes, countSteps);

    cout << ">> Final <<\n";
    cout << "Total : " << countSteps << " steps.\n\n";
    printPancakes(numPancake, pancakeSizes);

    return 0;
}

int findIndexOfMax(int* startPtr, int* endPtr)
{
    int index = 1;
    int indexOfMax = 0;

    while(startPtr + index <= endPtr)
    {
        if(startPtr[index] > startPtr[indexOfMax])
            indexOfMax = index;

        ++index;
    }

    return indexOfMax;
}

void reverseArray(int* startPtr, int* endPtr)
{
    int size = endPtr - startPtr + 1;
    int tmp = 0;

    for(int i=0; i<(size+1)/2; ++i)
    {
        tmp = startPtr[i];
        startPtr[i] = *(endPtr-i);
        *(endPtr-i) = tmp;
    }
}

bool isContains(int target, int* startPtr, int* endPtr)
{
    int index = 0;

    while(startPtr + index <= endPtr)
    {
        if(startPtr[index] == target)
            return true;
        else
            ++index;
    }

    return false;
}

void readPancakes(int& numPancake, int pancakeSizes[])
{
    bool isInvalidValue = false;

    // Read the number of pancakes.
    do
    {
        cout << "Please input the number of pancake : ";
        cin >> numPancake;

        // Invalid input.
        if(numPancake <= 0 || numPancake > kMaxPancakes)
        {
            isInvalidValue = true;
            cout << "Invalid input. Input value should between 1 and " << kMaxPancakes << ".\n\n";
        }
        // valid input.
        else
        {
            isInvalidValue = false;
            cout << "\n";
        }

    } while(isInvalidValue);

    // Read pancake sizes for each pancake.
    cout << "Input pancake sizes from bottom to top.\n\n";

    for(int i=0; i<numPancake; )
    {
        cout << "Please input size of [" << i << "] pancake : ";
        cin >> pancakeSizes[i];

        // Invalid input.
        if(pancakeSizes[i] <= 0)
            cout << "Invalid input. pancake size should be greater than 0 without duplication value.\n";
        else if(isContains(pancakeSizes[i], pancakeSizes, pancakeSizes+i-1))
            cout << "Invalid input. Duplicated value !!!\n";
        // Valid input.
        else
            ++i;

        cout << "\n";
    }
}

void sortPancakes(int& numPancake, int pancakeSizes[], int& countSteps)
{
    int startFlag = 0;
    int endFlag = numPancake - 1;
    int index = 0;

    for(int i=0; i<numPancake-1; ++i)
    {
        index = i + findIndexOfMax(pancakeSizes+i, pancakeSizes+numPancake-1);

        // Max size pancake is at the right place, at the bottom of the unsorted range.
        if(index == i)
            continue;

        // Bring max to top.
        if(index != numPancake-1)
        {
            reverseArray(pancakeSizes+index, pancakeSizes+numPancake-1);

            cout << "Step " << ++countSteps << " : \n";
            cout << "Reverse between value[" << pancakeSizes[index] << "] and value[" << pancakeSizes[numPancake-1] << "].\n\n";
            printPancakes(numPancake, pancakeSizes);
            cout << "\n\n";
        }

        // Bring max from top to bottom of the unsorted range.
        reverseArray(pancakeSizes+i, pancakeSizes+numPancake-1);

        cout << "Step " << ++countSteps << " : \n";
        cout << "Reverse between value[" << pancakeSizes[i] << "] and value[" << pancakeSizes[numPancake-1] << "].\n\n";
        printPancakes(numPancake, pancakeSizes);
        cout << "\n\n";
    }
}

void printPancakes(const int& numPancake, int pancakeSizes[])
{
    cout << "Total : " << numPancake << " pancake(s).\n";
    cout << "==========\n";

    for(int i=numPancake-1; i>=0; --i)
    {
        if(i != numPancake - 1)
            cout << "----------\n";

        cout << "  " << pancakeSizes[i] << "\n";
    }

    cout << "==========\n";
}

