#include <stdio.h>

void firstFit(int block[], int blockCount, int process[], int processCount)
{
    int alloc[processCount];
    int used[blockCount];

    for(int i = 0; i < processCount; i++)
    {
        alloc[i] = -1;
    }

    for(int i = 0; i < blockCount; i++)
    {
        used[i] = 0;
    }

    for (int i = 0; i < processCount; i++)
    {
        for (int j = 0; j < blockCount; j++) 
        { 
            if (!used[j] && block[j] >= process[i])
            {
                alloc[i] = j;
                used[j] = 1;
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processCount; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n",alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void bestFit(int block[], int blockCount, int process[], int processCount)
{
    int alloc[processCount];

    for(int i = 0; i < processCount; i++)
    {
        alloc[i] = -1;
    }

    for (int i=0; i<processCount; i++)
    {
        int bestIndex = -1;
        for (int j=0; j<blockCount; j++) 
        { 
            if (block[j] >= process[i])
            {
                if (bestIndex == -1)
                    bestIndex = j;
                else if (block[j] < block[bestIndex])
                    bestIndex = j;
            }
        }

        if (bestIndex != -1)
        {
            alloc[i] = bestIndex;
            block[bestIndex] -= process[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processCount; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n",alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void worstFit(int block[], int blockCount, int process[], int processCount)
{
    int alloc[processCount];
    int used[blockCount];

    for(int i = 0; i < processCount; i++)
    {
        alloc[i] = -1;
    }

    for(int i = 0; i < blockCount; i++)
    {
        used[i] = 0;
    }

    for (int i=0; i < processCount; i++)
    {
        int worstIndex = -1;
        for(int j = 0; j < blockCount; j++)
        {
            if(block[j] >= process[i] && !used[j])
            {
                if (worstIndex == -1)
                    worstIndex = j;
                else if (block[worstIndex] < block[j])
                    worstIndex = j;
            }
        }

        if (worstIndex != -1)
        {
            alloc[i] = worstIndex;
            used[worstIndex] = 1;
            block[worstIndex] -= process[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processCount; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, process[i]);
        if (alloc[i] != -1)
            printf("%d\n",alloc[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main()
{
    int block[] = {100, 50, 30, 120, 35};
    int process[] = {40, 10, 30, 60};
    int blockCount = sizeof(block)/sizeof(block[0]);
    int processCount = sizeof(process)/sizeof(process[0]);

    int choice;
    printf("Enter your choice:\n1. First Fit\n2. Best Fit\n3. Worst Fit\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            firstFit(block, blockCount, process, processCount);
            break;
        case 2:
            bestFit(block, blockCount, process, processCount);
            break;
        case 3:
            worstFit(block, blockCount, process, processCount);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}
/*int block[20], process[20], fragment[20]; // Add fragment array
    printf("\nEnter the size of the blocks:\n");
    for (int i = 0; i < numBlocks; i++)
        scanf("%d", &block[i]);

    printf("\nEnter the size of the processes:\n");
    for (int i = 0; i < numProcesses; i++)
        scanf("%d", &process[i]);*/