#include <stdio.h>
#include <string.h>

#define INF 9999

struct Edge
{
    char from;
    char to;
    int cost;
};

int prev[10];

void showPath(int v)
{
    if (prev[v] != -1)
    {
        showPath(prev[v]);
        printf(" -> ");
    }

    printf("%c", 'A' + v);
}

int main()
{
    struct Edge edges[15] = {
        {'A', 'B', 6}, {'A', 'D', 16}, {'B', 'C', 6}, {'B', 'D', 6},
        {'B', 'J', 7}, {'C', 'G', -9}, {'D', 'E', 7}, {'D', 'J', 8},
        {'E', 'F', 10}, {'E', 'I', -2}, {'F', 'G', 4}, {'F', 'I', 2},
        {'G', 'H', 13}, {'I', 'F', 2}, {'J', 'E', 3}};
    int dist[10];
    int pass, i, u, v;
    int start;
    int negative = 0;
    char input[20];

    printf("Enter source data center (capital letters only): ");
    scanf("%19s", input);

    if (strlen(input) == 1 && input[0] >= 'a' && input[0] <= 'z')
    {
        printf("Please use a capital letter.\n");
        return 0;
    }

    if (strlen(input) != 1 || input[0] < 'A' || input[0] > 'J')
    {
        printf("Data center %s does not exist in the network.\n", input);
        return 0;
    }

    start = input[0] - 'A';

    for (i = 0; i < 10; i++)
    {
        dist[i] = INF;
        prev[i] = -1;
    }

    dist[start] = 0;

    for (pass = 1; pass < 10; pass++)
    {
        for (i = 0; i < 15; i++)
        {
            u = edges[i].from - 'A';
            v = edges[i].to - 'A';

            if (dist[u] != INF && dist[u] + edges[i].cost < dist[v])
            {
                dist[v] = dist[u] + edges[i].cost;
                prev[v] = u;
            }
        }
    }

    // one more pass, any change means a negative cycle
    for (i = 0; i < 15; i++)
    {
        u = edges[i].from - 'A';
        v = edges[i].to - 'A';

        if (dist[u] != INF && dist[u] + edges[i].cost < dist[v])
            negative = 1;
    }

    printf("\nSource: %c\n\n", input[0]);

    if (negative == 1)
    {
        printf("Negative-weight cycle detected.\n");
        printf("Shortest-path results may be undefined.\n");
        return 0;
    }

    printf("No negative-weight cycle detected.\n\n");
    printf("%-13s%-15s%s\n", "Destination", "Shortest Cost", "Path");

    for (i = 0; i < 10; i++)
    {
        if (i == start)
            continue;

        if (dist[i] == INF)
        {
            printf("%-13c%-15s%s\n", 'A' + i, "-", "unreachable");
        }
        else
        {
            printf("%-13c%-15d", 'A' + i, dist[i]);
            showPath(i);
            printf("\n");
        }
    }

    return 0;
}