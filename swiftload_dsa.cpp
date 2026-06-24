/*
 * ============================================================
 *  Swift-Load Logistics — Data Structures & Algorithms
 *  Unit 19 | Task 1 & Task 2
 *  Academic Year:2026
 * ============================================================
 */

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <chrono>
#include <stdexcept>
#include <algorithm>
using namespace std;
using namespace std::chrono;

// ============================================================
// TASK 1.1 — Goods Struct (Plain version)
// ============================================================

struct Goods {
    string name;    // Name of the cargo item
    string type;    // Category (e.g. Electronics, Food, Machinery)
    double weight;  // Weight in kilograms
};

void demonstrateGoodsStruct() {
    cout << "\n--- 1.1 Goods Data Structure ---\n";

    // Initialize
    Goods g1 = {"Laptop", "Electronics", 2.5};
    cout << "Item: " << g1.name << " | Type: " << g1.type << " | Weight: " << g1.weight << "kg\n";

    // Update weight
    g1.weight = 3.0;
    cout << "Updated weight: " << g1.weight << "kg\n";
}


// ============================================================
// TASK 1.2 — FIFO Queue for Truck Loading Bay
// ============================================================

struct Truck {
    string id;
    string destination;
};

void demonstrateFIFOQueue() {
    cout << "\n--- 1.2 FIFO Queue — Loading Bay ---\n";

    queue<Truck> loadingBay;

    // EnQueue — trucks arrive
    loadingBay.push({"Truck A", "District 1"});
    loadingBay.push({"Truck B", "District 7"});
    loadingBay.push({"Truck C", "Binh Duong"});

    cout << "Trucks in queue: Truck A -> Truck B -> Truck C\n";
    cout << "Loading order (FIFO):\n";

    // DeQueue — load in arrival order
    while (!loadingBay.empty()) {
        Truck t = loadingBay.front();
        cout << "  Loading: " << t.id << " -> " << t.destination << "\n";
        loadingBay.pop();
    }
}


// ============================================================
// TASK 1.3 — Bubble Sort and QuickSort (Descending)
// ============================================================

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Descending: swap if left element is smaller
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        // Descending: move elements larger than pivot to the left
        if (arr[j] > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "\n";
}

void demonstrateSorting() {
    cout << "\n--- 1.3 Sorting 12 Cargo Weights ---\n";

    int weights1[] = {120, 55, 87, 200, 33, 145, 99, 66, 180, 75, 90, 130};
    int weights2[] = {120, 55, 87, 200, 33, 145, 99, 66, 180, 75, 90, 130};
    int n = 12;

    cout << "Original: ";
    printArray(weights1, n);

    // Time Bubble Sort
    auto start = high_resolution_clock::now();
    bubbleSort(weights1, n);
    auto stop  = high_resolution_clock::now();
    auto bubbleDuration = duration_cast<microseconds>(stop - start).count();

    cout << "Bubble Sort result: ";
    printArray(weights1, n);
    cout << "Bubble Sort time: " << bubbleDuration << " microseconds\n";

    // Time QuickSort
    start = high_resolution_clock::now();
    quickSort(weights2, 0, n - 1);
    stop  = high_resolution_clock::now();
    auto quickDuration = duration_cast<microseconds>(stop - start).count();

    cout << "QuickSort result:  ";
    printArray(weights2, n);
    cout << "QuickSort time:    " << quickDuration << " microseconds\n";

    cout << "\nComplexity comparison:\n";
    cout << "  Bubble Sort: O(n^2)     -> " << n * n << " max comparisons for n=" << n << "\n";
    cout << "  QuickSort:   O(n log n) -> ~" << (int)(n * 3.58) << " comparisons for n=" << n << "\n";
}


// ============================================================
// TASK 1.4 — Encapsulation: Goods Class with Private Weight
// ============================================================

class GoodsSecure {
private:
    string name;
    string type;
    double weight;

public:
    GoodsSecure(string n, string t, double w) {
        name = n;
        type = t;
        setWeight(w);
    }

    // Setter with validation — prevents invalid weight
    void setWeight(double w) {
        if (w > 0) {
            weight = w;
        } else {
            cout << "  Error: Weight must be positive. Value '" << w << "' rejected.\n";
        }
    }

    double getWeight() const { return weight; }
    string getName()   const { return name;   }
    string getType()   const { return type;   }

    void display() const {
        cout << "  Item: " << name << " | Type: " << type << " | Weight: " << weight << "kg\n";
    }
};

void demonstrateEncapsulation() {
    cout << "\n--- 1.4 Encapsulation and Information Hiding ---\n";

    GoodsSecure g1("Laptop", "Electronics", 2.5);
    g1.display();

    cout << "Attempting to set weight to -10:\n";
    g1.setWeight(-10);  // Rejected

    cout << "Attempting to set weight to 4.2:\n";
    g1.setWeight(4.2);  // Accepted
    g1.display();
}


// ============================================================
// TASK 2.1 — Memory Stack and Function Calls
// ============================================================

double calculateWeight(double items[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += items[i];
    }
    return total;  // Stack frame popped, returns to loadTruck()
}

void loadTruck(double items[], int count) {
    double total = calculateWeight(items, count);
    cout << "  Total cargo weight: " << total << "kg\n";
    // Stack frame popped, returns to main()
}

void demonstrateCallStack() {
    cout << "\n--- 2.1 Memory Stack and Function Calls ---\n";
    cout << "Call order: main() -> loadTruck() -> calculateWeight()\n";

    double cargo[] = {120, 55, 87, 200, 33, 145};
    loadTruck(cargo, 6);

    cout << "Stack unwinds: calculateWeight() returns -> loadTruck() returns -> main() continues\n";
}


// ============================================================
// TASK 2.2 — Formal Stack ADT Implementation
// ============================================================

template <typename T>
class Stack {
private:
    vector<T> data;

public:
    // PRE: none | POST: item added to top, size increases by 1
    void push(T item) {
        data.push_back(item);
    }

    // PRE: stack is not empty | POST: top item removed, size decreases by 1
    void pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow: cannot pop from empty stack");
        }
        data.pop_back();
    }

    // PRE: stack is not empty | POST: returns top item, stack unchanged
    T top() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow: cannot read top of empty stack");
        }
        return data.back();
    }

    // PRE: none | POST: returns true if size == 0, else false
    bool isEmpty() {
        return data.empty();
    }

    // PRE: none | POST: returns current number of elements
    int size() {
        return (int)data.size();
    }
};

void demonstrateStackADT() {
    cout << "\n--- 2.2 Formal Stack ADT (LIFO Cargo Loading) ---\n";

    Stack<string> cargoStack;

    // Load cargo onto truck (LIFO — last in, first unloaded)
    cargoStack.push("Pallet A - Electronics");
    cargoStack.push("Pallet B - Food");
    cargoStack.push("Pallet C - Machinery");

    cout << "Cargo loaded. Items on truck: " << cargoStack.size() << "\n";
    cout << "Next to unload (top): " << cargoStack.top() << "\n";

    cout << "Unloading at destination:\n";
    while (!cargoStack.isEmpty()) {
        cout << "  Unloaded: " << cargoStack.top() << "\n";
        cargoStack.pop();
    }

    // Test error handling
    try {
        cargoStack.pop();  // Should throw
    } catch (const runtime_error& e) {
        cout << "Caught expected error: " << e.what() << "\n";
    }
}


// ============================================================
// TASK 2.3 — Big O / Asymptotic Analysis
// ============================================================

// O(n) — Linear Search
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// O(log n) — Binary Search (requires sorted array)
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == target)      return mid;
        else if (arr[mid] > target)  high = mid - 1;
        else                         low  = mid + 1;
    }
    return -1;
}

void demonstrateBigO() {
    cout << "\n--- 2.3 Big O / Asymptotic Analysis ---\n";

    int sorted[] = {33, 55, 66, 75, 87, 90, 99, 120, 130, 145, 180, 200};
    int n = 12;
    int target = 145;

    cout << "Searching for " << target << " in the sorted cargo list:\n";

    // Linear search
    auto start = high_resolution_clock::now();
    int linResult = linearSearch(sorted, n, target);
    auto linTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    cout << "  Linear Search O(n):     found at index " << linResult << " | " << linTime << " ns\n";

    // Binary search
    start = high_resolution_clock::now();
    int binResult = binarySearch(sorted, n, target);
    auto binTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start).count();
    cout << "  Binary Search O(log n): found at index " << binResult << " | " << binTime << " ns\n";

    cout << "\nFor n=10,000 items:\n";
    cout << "  O(n)     = up to 10,000 steps\n";
    cout << "  O(log n) = up to ~14 steps\n";
}


// ============================================================
// TASK 2.4 — Two Ways to Measure Efficiency
// ============================================================

void demonstrateEfficiencyMeasurement() {
    cout << "\n--- 2.4 Two Ways to Measure Algorithm Efficiency ---\n";

    int weights[] = {120, 55, 87, 200, 33, 145, 99, 66, 180, 75, 90, 130};
    int n = 12;

    // TIME EFFICIENCY — using std::chrono
    auto start = high_resolution_clock::now();
    bubbleSort(weights, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << "Time Efficiency  — Bubble Sort on 12 items: " << duration << " microseconds\n";

    // SPACE EFFICIENCY — using sizeof
    GoodsSecure sample("Test", "Type", 1.0);
    cout << "Space Efficiency — Size of one Goods object: " << sizeof(GoodsSecure) << " bytes\n";
    cout << "Space Efficiency — Size of cargo int array:  " << sizeof(weights) << " bytes\n";
    cout << "\nConclusion:\n";
    cout << "  Time Complexity  = how execution time grows as n increases\n";
    cout << "  Space Complexity = how memory usage grows as n increases\n";
}


// ============================================================
// MAIN — Run all demonstrations
// ============================================================

int main() {
    cout << "====================================================\n";
    cout << " Swift-Load Logistics — DSA Assignment\n";
    cout << " Task 1 & Task 2 Demonstration\n";
    cout << "====================================================\n";

    demonstrateGoodsStruct();
    demonstrateFIFOQueue();
    demonstrateSorting();
    demonstrateEncapsulation();
    demonstrateCallStack();
    demonstrateStackADT();
    demonstrateBigO();
    demonstrateEfficiencyMeasurement();

    cout << "\n====================================================\n";
    cout << " All demonstrations complete.\n";
    cout << "====================================================\n";

    return 0;
}
