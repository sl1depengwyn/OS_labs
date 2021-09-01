#include <stdio.h>
#include <stdlib.h>

void quickSort(int *arr, int size);

void swap(int *left, int *right);

int main() {
    int sizeOfArr;

    printf("Write the size of the array: ");
    scanf("%d", &sizeOfArr);

    while (sizeOfArr < 0) {
        printf("Write the size that greater than 0: ");
        scanf("%d", &sizeOfArr);
    }

    int arr[sizeOfArr];

    printf("Input the array:");
    for (int i = 0; i < sizeOfArr; ++i) {
        scanf("%d", &arr[i]);
    }

    quickSort(arr, sizeOfArr);

    printf("Sorted array:\n");
    for (int i = 0; i < sizeOfArr; ++i) {
        printf("%d ", arr[i]);
    }

}

void quickSort(int *arr, int size) {
    if (size <= 1) {
        return;
    }

    int *leftPart = malloc(sizeof(int) * (size - 1));
    int leftSize = 0;
    int *rightPart = malloc(sizeof(int) * (size - 1));
    int rightSize = 0;

    int pivotIndex = rand() % size;
    int pivot = arr[pivotIndex];

    for (int i = 0; i < size; ++i) {
        if (i == pivotIndex) continue;
        if (arr[i] < pivot) {
            leftPart[leftSize++] = arr[i];
        } else {
            rightPart[rightSize++] = arr[i];
        }
    }

    quickSort(leftPart, leftSize);
    quickSort(rightPart, rightSize);

    for (int i = 0; i < leftSize; ++i) {
        arr[i] = leftPart[i];
    }
    arr[leftSize] = pivot;
    for (int i = leftSize + 1; i < size; ++i) {
        arr[i] = rightPart[i - (leftSize + 1)];
    }

    free(leftPart);
    free(rightPart);
}
