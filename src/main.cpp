#include <iostream>

#include "sequence.hpp"
#include "mutable_array_sequence.hpp"
#include "immutable_array_sequence.hpp"
#include "mutable_list_sequence.hpp"
#include "immutable_list_sequence.hpp"

const int MAX_SEQS = 50;
Sequence<int>* registry[MAX_SEQS];
int registry_count = 0;

int map_square(const int& x) { return x * x; }
bool where_positive(const int& x) { return x > 0; }
int reduce_sum(const int& a, const int& b) { return a + b; }

void print_sequence(Sequence<int>* seq) {
    if (!seq) return;
    IEnumerator<int>* it = seq->get_enumerator();
    std::cout << "[ ";
    while (it->move_next()) {
        std::cout << it->get_current() << " ";
    }
    std::cout << "]";
    delete it;
}

void add_to_registry(Sequence<int>* seq) {
    if (registry_count < MAX_SEQS) {
        registry[registry_count] = seq;
        registry_count++;
        std::cout << "  -> Saved as ID " << registry_count << "\n";
    }
    else {
        std::cout << "  [!] Registry is full!\n";
    }
}

void create_ui() {
    std::cout << "\n--- Create New Sequence ---\n";
    std::cout << "1. Mutable Array      2. Immutable Array\n";
    std::cout << "3. Mutable List       4. Immutable List\n";
    std::cout << "Choice: ";
    int type; std::cin >> type;

    std::cout << "How many elements to enter? ";
    int count; std::cin >> count;

    int* temp = new int[count];
    for (int i = 0; i < count; i++) {
        std::cout << "  [" << i << "]: ";
        std::cin >> temp[i];
    }

    Sequence<int>* new_seq = nullptr;
    if (type == 1)      new_seq = new MutableArraySequence<int>(temp, count);
    else if (type == 2) new_seq = new ImmutableArraySequence<int>(temp, count);
    else if (type == 3) new_seq = new MutableListSequence<int>(temp, count);
    else if (type == 4) new_seq = new ImmutableListSequence<int>(temp, count);

    delete[] temp;
    if (new_seq) add_to_registry(new_seq);
}

void operations_ui() {
    if (registry_count == 0) {
        std::cout << "Create an object first!\n";
        return;
    }

    std::cout << "\nEnter ID (1-" << registry_count << "): ";
    int idx; std::cin >> idx;
    if (idx < 1 || idx > registry_count) return;

    Sequence<int>* current = registry[idx - 1];
    std::cout << "\nSelected: "; print_sequence(current);

    std::cout << "\n--- Elements ---      --- Mutations ---      --- Transformations ---\n";
    std::cout << "1. Get(index)         4. Append              7. Map (x^2)\n";
    std::cout << "2. Get First/Last     5. Prepend             8. Where (>0)\n";
    std::cout << "3. Get Size           6. Remove At           9. Reduce (Sum)\n";
    std::cout << "Choice: ";
    int op; std::cin >> op;

    Sequence<int>* result = nullptr;

    try {
        switch (op) {
        case 1: {
            int i; std::cout << "Index: "; std::cin >> i;
            std::cout << "Result: " << current->get(i) << "\n";
            break;
        }
        case 2: {
            std::cout << "First: " << current->get_first() << "\n";
            std::cout << "Last: " << current->get_last() << "\n";
            break;
        }
        case 3: {
            std::cout << "Size: " << current->get_size() << "\n";
            break;
        }
        case 4: {
            int val; std::cout << "Value: "; std::cin >> val;
            result = current->append(val);
            break;
        }
        case 5: {
            int val; std::cout << "Value: "; std::cin >> val;
            result = current->prepend(val);
            break;
        }
        case 6: {
            int i; std::cout << "Index to remove: "; std::cin >> i;
            result = current->remove_at(i);
            break;
        }
        case 7: result = current->map(map_square); break;
        case 8: result = current->where(where_positive); break;
        case 9: {
            std::cout << "Sum: " << current->reduce(reduce_sum, 0) << "\n";
            break;
        }
        default: std::cout << "Invalid operation!\n";
        }

        if (result && result != current) {
            std::cout << "Operation created a new object.\n";
            add_to_registry(result);
        }
        else if (result == current) {
            std::cout << "Object modified in-place.\n";
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << "\n";
    }
}

int main() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== MAIN MENU (Objects: " << registry_count << ") ===\n";
        for (int i = 0; i < registry_count; i++) {
            std::cout << i + 1 << ". ";
            print_sequence(registry[i]);
            std::cout << "\n";
        }
        std::cout << "--------------------\n";
        std::cout << "1. Create   2. Operation   0. Exit\n> ";
        std::cin >> choice;

        if (choice == 1) create_ui();
        else if (choice == 2) operations_ui();
    }

    for (int i = 0; i < registry_count; i++) delete registry[i];
    return 0;
}