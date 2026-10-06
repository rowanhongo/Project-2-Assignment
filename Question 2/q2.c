#include <stdio.h>
#include <string.h>

struct Patient
{
    char id[5];
    char name[20];
    int priority;
};

void swap(struct Patient *a, struct Patient *b)
{
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// push the patient at i down the tree
void fixDown(struct Patient heap[], int size, int i)
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
        fixDown(heap, size, largest);
    }
}

// push the patient at i up the tree
void fixUp(struct Patient heap[], int i)
{
    int parent = (i - 1) / 2;

    if (i > 0 && heap[i].priority > heap[parent].priority)
    {
        swap(&heap[i], &heap[parent]);
        fixUp(heap, parent);
    }
}

void addPatient(struct Patient heap[], int *size, struct Patient p)
{
    heap[*size] = p;
    (*size)++;
    fixUp(heap, *size - 1);
}

struct Patient takeTop(struct Patient heap[], int *size)
{
    struct Patient top = heap[0];

    heap[0] = heap[*size - 1];
    (*size)--;
    fixDown(heap, *size, 0);

    return top;
}

void removePatient(struct Patient heap[], int *size, char id[])
{
    int i;
    int found = -1;

    for (i = 0; i < *size; i++)
    {
        if (strcmp(heap[i].id, id) == 0)
            found = i;
    }

    if (found == -1)
    {
        printf("Patient %s not found.\n", id);
        return;
    }

    swap(&heap[found], &heap[*size - 1]);
    (*size)--;

    if (found < *size)
    {
        fixDown(heap, *size, found);
        fixUp(heap, found);
    }
}

void showHeap(struct Patient heap[], int size)
{
    int i;
    int levelEnd = 0;
    int width = 1;

    for (i = 0; i < size; i++)
    {
        printf("%s %s %d   ", heap[i].id, heap[i].name, heap[i].priority);

        if (i == levelEnd && i < size - 1)
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
    struct Patient heap[20] = {
        {"P01", "Amina", 72},
        {"P02", "Daniel", 45},
        {"P03", "Eric", 91},
        {"P04", "Grace", 63},
        {"P05", "Hassan", 88},
        {"P06", "Irene", 54},
        {"P07", "Jean", 76}};
    struct Patient copy[20];
    struct Patient p;
    struct Patient kofi = {"P08", "Kofi", 98};
    int size = 7;
    int copySize;
    int i;

    for (i = size / 2 - 1; i >= 0; i--)
        fixDown(heap, size, i);

    printf("Initial Max-Heap:\n");
    showHeap(heap, size);

    // extract from a copy so the real heap is kept
    for (i = 0; i < size; i++)
        copy[i] = heap[i];

    copySize = size;

    printf("Treatment order:\n");

    while (copySize > 0)
    {
        p = takeTop(copy, &copySize);
        printf("Patient %s (%s) - Priority %d\n", p.id, p.name, p.priority);
    }

    printf("\n");

    addPatient(heap, &size, kofi);
    printf("After inserting Kofi (P08):\n");
    showHeap(heap, size);

    removePatient(heap, &size, "P08");
    printf("After removing P08:\n");
    showHeap(heap, size);

    return 0;
}