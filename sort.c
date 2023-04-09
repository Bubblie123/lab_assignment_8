#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void heapify(int arr[], int i, int n) {
    int max = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if(leftChild < n && arr[leftChild] > arr[max])
        max = leftChild;

    if(rightChild < n && arr[rightChild] > arr[max])
        max = rightChild;

    if(max != i) {
        int temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
        heapify(arr, max, n);
    }
}
// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void heapSort(int arr[], int n)
{
    for(int i = (n/2)-1; i >= 0; i--) {
        heapify(arr, i, n);
    }

    for(int i = n-1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr,0,i);
    }
}

void merge(int pData[], int l, int mid, int r) {
    int leftIndex, rightIndex, middleIndex;
    int leftSize = mid-l+1;
    int rightSize = r-mid;

    int leftArr[leftSize];
    int rightArr[rightSize];

    for(int i = 0; i < leftSize; i++) {
        leftArr[i] = pData[l+i];
    }
    for(int j = 0; j < rightSize; j++) {
        rightArr[j] = pData[mid + 1 + j];
    }

    leftIndex = 0;
    rightIndex = 0;
    middleIndex = l;

    while(leftIndex < leftSize && rightIndex < rightSize) {
        if(leftArr[leftIndex] <= rightArr[rightIndex]) {
            pData[middleIndex] = leftArr[leftIndex];
            ++leftIndex;
        }
        else {
            pData[middleIndex] = rightArr[rightIndex];
            ++rightIndex;
        }
        ++middleIndex;
    }

    while(leftIndex < leftSize) {
        pData[middleIndex] = leftArr[leftIndex];
        ++leftIndex;
        ++middleIndex;
    }

    while(rightIndex < rightSize) {
        pData[middleIndex] = rightArr[rightIndex];
        ++rightIndex;
        ++middleIndex;
    }

}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    if(l<r) {
        int mid=(l+(r-1))/2;
        mergeSort(pData, l, mid);
        mergeSort(pData, mid+1, r);
        merge(pData, l, mid, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}