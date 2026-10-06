#include <stdio.h>
#include <string.h>

int main()
{
    char one[10] = {'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'F'};
    char two[10] = {'B', 'D', 'D', 'C', 'D', 'G', 'E', 'F', 'F', 'G'};
    int time[10] = {6, 12, 5, 11, 17, 25, 22, 15, 10, 22};
    int matrix[7][7] = {0};
    int visited[7] = {0};
    int queue[7];
    int front = 0;
    int rear = 0;
    int start, current, i;
    int maxTime = 0;
    int maxGate = -1;
    char input[20];

    for (i = 0; i < 10; i++)
    {
        matrix[one[i] - 'A'][two[i] - 'A'] = time[i];
        matrix[two[i] - 'A'][one[i] - 'A'] = time[i];
    }

    printf("Enter starting gateway (capital letters only): ");
    scanf("%19s", input);

    if (strlen(input) == 1 && input[0] >= 'a' && input[0] <= 'z')
    {
        printf("Please use a capital letter.\n");
        return 0;
    }

    if (strlen(input) != 1 || input[0] < 'A' || input[0] > 'G')
    {
        printf("Gateway %s does not exist in the network.\n", input);
        return 0;
    }

    start = input[0] - 'A';
    queue[rear] = start;
    rear++;
    visited[start] = 1;

    printf("\nGateways directly connected to %c (BFS order):\n", 'A' + start);

    while (front < rear)
    {
        current = queue[front];
        front++;

        for (i = 0; i < 7; i++)
        {
            if (matrix[current][i] != 0 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[rear] = i;
                rear++;

                // only the start gateway's neighbours are one hop away
                if (current == start)
                {
                    printf("%c (%d ms)\n", 'A' + i, matrix[current][i]);

                    if (matrix[current][i] > maxTime)
                    {
                        maxTime = matrix[current][i];
                        maxGate = i;
                    }
                }
            }
        }
    }

    printf("\nHighest transfer time: Gateway %c - %d ms\n", 'A' + maxGate, maxTime);

    return 0;
}