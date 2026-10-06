#include <stdio.h>

struct Container
{
    char id;
    int priority;
};

struct Container heap[20];
int size = 0;

void swap(struct Container *a, struct Container *b)
{
    struct Container temp = *a;
    *a = *b;
    *b = temp;
}

// moves a small parent down
void fixDown(int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].priority > heap[largest].priority)
        largest = left;

    if (right < size && heap[right].priority > heap[largest].priority)
        largest = right;

    if (largest != i)
    {
        swap(&heap[i], &heap[largest]);
        fixDown(largest);
    }
}

// moves a big child up
void fixUp(int i)
{
    int parent = (i - 1) / 2;

    if (i > 0 && heap[i].priority > heap[parent].priority)
    {
        swap(&heap[i], &heap[parent]);
        fixUp(parent);
    }
}

void insertContainer(char id, int priority)
{
    heap[size].id = id;
    heap[size].priority = priority;
    size++;
    fixUp(size - 1);
}

void removeContainer(char id)
{
    int i;
    int found = -1;

    for (i = 0; i < size; i++)
    {
        if (heap[i].id == id)
            found = i;
    }

    if (found == -1)
    {
        printf("Container %c not found.\n", id);
        return;
    }

    swap(&heap[found], &heap[size - 1]);
    size--;

    if (found < size)
    {
        fixDown(found);
        fixUp(found);
    }
}

void showHeap()
{
    int i;
    int levelEnd = 0;
    int width = 1;

    for (i = 0; i < size; i++)
    {
        printf("%c:%d  ", heap[i].id, heap[i].priority);

        if (i == levelEnd)
        {
            printf("\n");
            width = width * 2;
            levelEnd = levelEnd + width;
        }
    }

    printf("\n\n");
}

int main()
{
    int scores[11] = {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    int i;

    for (i = 0; i < 11; i++)
    {
        heap[i].id = 'A' + i;
        heap[i].priority = scores[i];
    }

    size = 11;

    for (i = size / 2 - 1; i >= 0; i--)
        fixDown(i);

    printf("Initial Max-Heap:\n");
    showHeap();

    insertContainer('X', 100);
    printf("After inserting X (100):\n");
    showHeap();

    removeContainer('X');
    printf("After removing X:\n");
    showHeap();

    return 0;
}