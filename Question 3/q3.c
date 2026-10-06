#include <stdio.h>

struct Edge
{
    char from;
    char to;
    int cost;
};

int group[7];

int root(int x)
{
    while (group[x] != x)
        x = group[x];

    return x;
}

int main()
{
    struct Edge edges[10] = {
        {'A', 'B', 6}, {'A', 'D', 12}, {'B', 'D', 5}, {'B', 'C', 11},
        {'C', 'D', 17}, {'C', 'G', 25}, {'D', 'E', 22}, {'D', 'F', 15},
        {'E', 'F', 10}, {'F', 'G', 22}};
    struct Edge chosen[6];
    struct Edge temp;
    int matrix[7][7] = {0};
    int i, j;
    int count = 0;
    int total = 0;
    int a, b;

    for (i = 0; i < 10; i++)
    {
        a = edges[i].from - 'A';
        b = edges[i].to - 'A';
        matrix[a][b] = edges[i].cost;
        matrix[b][a] = edges[i].cost;
    }

    printf("Adjacency matrix:\n  ");

    for (i = 0; i < 7; i++)
        printf("%3c", 'A' + i);

    printf("\n");

    for (i = 0; i < 7; i++)
    {
        printf("%c ", 'A' + i);

        for (j = 0; j < 7; j++)
            printf("%3d", matrix[i][j]);

        printf("\n");
    }

    // bubble sort by cost
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9 - i; j++)
        {
            if (edges[j].cost > edges[j + 1].cost)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < 7; i++)
        group[i] = i;

    printf("\nEdges in order of cost:\n");

    for (i = 0; i < 10; i++)
    {
        a = root(edges[i].from - 'A');
        b = root(edges[i].to - 'A');

        printf("%c - %c : %2d  ", edges[i].from, edges[i].to, edges[i].cost);

        if (a != b)
        {
            group[a] = b;
            chosen[count] = edges[i];
            count++;
            total += edges[i].cost;
            printf("accepted\n");
        }
        else
        {
            printf("rejected (cycle)\n");
        }
    }

    printf("\nSelected Connections:\n");

    for (i = 0; i < count; i++)
        printf("Station %c - Station %c : %d\n", chosen[i].from, chosen[i].to, chosen[i].cost);

    printf("\nTotal Installation Cost: %d thousand dollars\n", total);

    return 0;
}