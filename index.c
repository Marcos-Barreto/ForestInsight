#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selectionSort(int arr[], int n) {
    int i, j, minIdx, temp;

    for (i = 0; i < n - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j; 
            }
        }
        // Troque o elemento encontrado com o primeiro elemento
        temp = arr[minIdx];
        arr[minIdx] = arr[i];
        arr[i] = temp;
    }
}

// Função para realizar o Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high]; // Escolhe o último elemento como pivô
        int i = (low - 1); // Índice do menor elemento

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                // Troca arr[i] e arr[j]
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // Troca arr[i + 1] e arr[high] (ou pivô)
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;

        // Chama recursivamente os elementos antes e depois da partição
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para realizar o Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


// Função principal para testar os algoritmos
int main() {
    const int n = 1000; // Tamanho do array
    int arr[n];

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o array com números aleatórios
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Números entre 0 e 9999
    }

    // Para o Selection Sort
    int arr1[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = arr[i]; // Copia o array original
    }
    clock_t start = clock();
    selectionSort(arr1, n);
    clock_t end = clock();
    printf("Tempo de ordenação com Selection Sort: %f segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Array ordenado (Selection Sort): ");
    printArray(arr1, n);

    // Para o Quick Sort
    int arr2[n];
    for (int i = 0; i < n; i++) {
        arr2[i] = arr[i]; // Copia o array original
    }
    start = clock();
    quickSort(arr2, 0, n - 1);
    end = clock();
    printf("Tempo de ordenação com Quick Sort: %f segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Array ordenado (Quick Sort): ");
    printArray(arr2, n);

    // Para o Shell Sort
    int arr3[n];
    for (int i = 0; i < n; i++) {
        arr3[i] = arr[i]; // Copia o array original
    }
    start = clock();
    shellSort(arr3, n);
    end = clock();
    printf("Tempo de ordenação com Shell Sort: %f segundos\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    printf("Array ordenado (Shell Sort): ");
    printArray(arr3, n);

    return 0;
}
