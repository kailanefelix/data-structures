#include <algorithm>
#include <iostream>

namespace kai {

template<class It>
void push_heap(It first, It last) {
    // std::cout << "push heap!\n";
    while (first != last - 1) {
        int current = std::distance(first, last) - 1;

        auto parent = std::next(first, (current - 1) / 2);

        // std::cout << "comparing v[" << (current - 1) / 2 << "] = " << std::string(*parent) << " vs v[" << current << "] = " << std::string(*(last - 1)) << "\n";

        if (*parent < *(last - 1)) {
            std::iter_swap(last - 1, parent);
            last = parent + 1;
        } else {
            break;
        }
    }
    // std::cout << '\n';
}

template<class It>
void bubble_down(const It first, It current, const It last) {
    // std::cout << "bubble down!\n";
    while (current != last - 1) {
        int i = std::distance(first, current);

        auto left_child = std::next(first, (i * 2) + 1);
        auto right_child = left_child + 1;

        It largest_child;
        if (left_child < last and right_child < last) {
            // std::cout << "comparing v[" << i << "] = " << std::string(*current) << " vs v[" << (i * 2) + 1 << "] = " << std::string(*left_child) << " & v[" << (i * 2) + 2 << "] = " << std::string(*right_child) << "\n";

            if (*right_child < *left_child) {
                largest_child = left_child;
            }
            else {
                largest_child = right_child;
            }
        }

        // node has only left child
        else if (left_child < last) {
            // std::cout << "comparing v[" << i << "] = " << std::string(*current) << " vs v[" << (i * 2) + 1 << "] = " << std::string(*left_child) << "\n";

            largest_child = left_child;
        }

        // node has no child
        else {
            break;
        }

        if (*current < *largest_child) {
            std::iter_swap(current, largest_child);
            current = largest_child;
        } else {
            break;
        }
    }

    // std::cout << '\n';
}

}