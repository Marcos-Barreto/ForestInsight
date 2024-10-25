#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <filesystem>  // Biblioteca para manipulação de arquivos e diretórios

namespace fs = std::filesystem;  // Definindo um namespace mais curto

// Função para o Selection Sort
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        std::swap(arr[i], arr[minIdx]);
    }
}

// Função para o Shell Sort
void shellSort(std::vector<int>& arr) {
    int n = arr.size();
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

// Função para o Quick Sort
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para leitura de números do arquivo
std::vector<int> readNumbersFromFile(const std::string& filename) {
    std::vector<int> numbers;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        exit(1);
    }

    int number;
    while (file >> number) {
        numbers.push_back(number);
    }
    file.close();
    return numbers;
}

// Função para obter o caminho da pasta raiz do projeto
fs::path getProjectRoot() {
    // Obtém o caminho do diretório atual (onde o executável está rodando)
    fs::path currentPath = fs::current_path();

    // Volta um diretório para simular que o executável está, por exemplo, na pasta "build"
    fs::path projectRoot = currentPath.parent_path();

    return projectRoot;
}

// Exibir menus de escolha para o usuário
void displayMenu() {
    std::cout << "Escolha o método de ordenação:\n";
    std::cout << "1. Shell Sort\n";
    std::cout << "2. Selection Sort\n";
    std::cout << "3. Quick Sort\n";
}

void displayQuantityMenu() {
    std::cout << "Escolha a quantidade de números:\n";
    std::cout << "1. 10\n";
    std::cout << "2. 50\n";
    std::cout << "3. 100\n";
    std::cout << "4. 500\n";
    std::cout << "5. 1k\n";
    std::cout << "6. 5k\n";
    std::cout << "7. 10k\n";
    std::cout << "8. 50k\n";
    std::cout << "9. 100k\n";
}

void displayTypeMenu() {
    std::cout << "Escolha o tipo de duplicidade:\n";
    std::cout << "1. Com duplicidade\n";
    std::cout << "2. Sem duplicidade\n";
}

void displayPatternMenu() {
    std::cout << "Escolha o padrão de ordenação dos números:\n";
    std::cout << "1. Aleatórios\n";
    std::cout << "2. Concavo-DecresceCresce\n";
    std::cout << "3. Convexo-CresceDescresce\n";
    std::cout << "4. Crescente\n";
    std::cout << "5. Decrescente\n";
}

// Constrói o nome do arquivo de acordo com as escolhas do usuário (sem o nome do método)
std::string constructFilename(int quantity, int duplication, int pattern) {
    std::stringstream ss;

    // Seleciona a quantidade de números
    switch (quantity) {
    case 1: ss << "10"; break;
    case 2: ss << "50"; break;
    case 3: ss << "100"; break;
    case 4: ss << "500"; break;
    case 5: ss << "1k"; break;
    case 6: ss << "5k"; break;
    case 7: ss << "10k"; break;
    case 8: ss << "50k"; break;
    case 9: ss << "100k"; break;
    }

    // Seleciona se é com ou sem duplicidade
    if (duplication == 1) ss << "_duplicidade";
    else ss << "_semduplicidade";

    // Seleciona o padrão dos números
    switch (pattern) {
    case 1: ss << "_aleatorio"; break;
    case 2: ss << "_concavo"; break;
    case 3: ss << "_convexo"; break;
    case 4: ss << "_crescente"; break;
    case 5: ss << "_decrescente"; break;
    }

    ss << ".txt";

    return ss.str();
}

int main() {
    int method, quantity, duplication, pattern;

    // Exibe menus para o usuário fazer as escolhas
    displayMenu();
    std::cin >> method;
    displayQuantityMenu();
    std::cin >> quantity;

    std::string quantityString;
    switch (quantity)
    {
    case 1:
        quantityString = "10";
        break;
    case 2:
        quantityString = "50";
        break;
    case 3:
        quantityString = "100";
        break;
    case 4:
        quantityString = "500";
        break;
    case 5:
        quantityString = "1k";
        break;
    case 6:
        quantityString = "5k";
        break;
    case 7:
        quantityString = "10k";
        break;
    case 8:
        quantityString = "50k";
        break;
    case 9:
        quantityString = "100k";
        break;
    }

    displayTypeMenu();
    std::cin >> duplication;
    displayPatternMenu();
    std::cin >> pattern;

    // Constrói o nome do arquivo com base nas escolhas do usuário (sem o nome do método de ordenação)
    std::string filename = constructFilename(quantity, duplication, pattern);

    // Obtenha o caminho da raiz do projeto
    fs::path projectRoot = getProjectRoot();

    // Concatene o caminho da raiz com o nome do arquivo usando fs::path
    fs::path fullPath = projectRoot / "ForestInsight" /quantityString /filename;

    // Lê os números do arquivo concatenado com o caminho da pasta raiz
    std::vector<int> numbers = readNumbersFromFile(fullPath.string());

    // Medição de tempo
    clock_t start = clock();

    // Aplica o método de ordenação escolhido
    if (method == 1)
        shellSort(numbers);
    else if (method == 2)
        selectionSort(numbers);
    else
        quickSort(numbers, 0, numbers.size() - 1);

    // Calcula o tempo de execução
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;

    // Exibe os resultados
    std::cout << "Arquivo: " << fullPath << std::endl;
    std::cout << "Método de ordenação: ";
    if (method == 1)
        std::cout << "Shell Sort";
    else if (method == 2)
        std::cout << "Selection Sort";
    else
        std::cout << "Quick Sort";

    std::cout << "\nTempo de execução: " << std::fixed << std::setprecision(8) << elapsed << " segundos" << std::endl;

    return 0;
}
