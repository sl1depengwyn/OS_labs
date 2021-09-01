#include <stdio.h>

void bubble_sort(int *arr, int size);
void swap(int *left, int *right);

int main(){
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

    bubble_sort(arr, sizeOfArr);

    printf("Sorted array:\n");
    for (int i = 0; i < sizeOfArr; ++i) {
        printf("%d ", arr[i]);
    }

}

void bubble_sort(int *arr, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size- i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void swap(int *left, int *right) {
    *right = *left + *right;
    *left = *right - *left;
    *right = *right - *left;
}