#include <cassert>
#include <iomanip>
#include <iostream>
#include <tuple>

namespace bst {

template<class T>
struct node {
    explicit node(const T& value): value{value} {}
    ~node() {
        delete left;
        delete right;
    }

    node<T> *left, *right;
    T value;
};

template<class T>
[[nodiscard]] node<T> *insert(node<T> *root, const T &value) {

    if (root == nullptr) {
        return new node<T>(value);
    }

    if (value > root->value) {
        root->right = insert(root->right, value);
    }

    else if (value < root->value) {
        root->left = insert(root->left, value);
    }

    return root;
}

template<class T>
[[nodiscard]] node<T> *rotate_left(node<T> *root) {
    node<T> *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    return new_root;
}

template<class T>
[[nodiscard]] node<T> *rotate_right(node<T> *root) {
    node<T> *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    return new_root;
}


template<class T>
[[nodiscard]] std::tuple<node<T> *, int> to_left_spine(node<T> *root) {
    int left = 0;
    while (root->right != nullptr) {
        root = rotate_left(root);
        left = left + 1;
    }

    if (root->left != nullptr) {
        int left_2 = 0;
        std::tie(root->left, left_2) = to_left_spine(root->left);
        left = left + left_2;
    }

    return std::make_tuple(root, left);
}

template<class T>
[[nodiscard]] std::tuple<node<T> *, int, int> turn_into_left(node<T> *root_s, node<T> *root_t) {
    int left = 0, right = 0;

    while (root_s->value != root_t->value) {
        root_s = rotate_right(root_s);
        right = right + 1;
    }

    if (root_s->left != nullptr) {
        int l, r;
        std::tie(root_s->left, l, r) = turn_into_left(root_s->left, root_t->left);
        left = left + l;
        right = right + r;
    }

    if (root_s->right != nullptr) {
        int l, r;
        std::tie(root_s->right, l, r) = turn_into_right(root_s->right, root_t->right);
        left = left + l;
        right = right + r;
    }

    return std::make_tuple(root_s, left, right);
}


template<class T>
[[nodiscard]] std::tuple<node<T> *, int, int> turn_into_right(node<T> *root_s, node<T> *root_t) {
    int left = 0, right = 0;

    while (root_s->value != root_t->value) {
        root_s = rotate_left(root_s);
        left = left + 1;
    }

    if (root_s->left != nullptr) {
        int l, r;
        std::tie(root_s->left, l, r) = turn_into_left(root_s->left, root_t->left);
        left = left + l;
        right = right + r;
    }

    if (root_s->right != nullptr) {
        int l, r;
        std::tie(root_s->right, l, r) = turn_into_right(root_s->right, root_t->right);
        left = left + l;
        right = right + r;
    }

    return std::make_tuple(root_s, left, right);
}

template<class T>
int height(node<T> *root) {

    if (root == nullptr) {
        return 0;
    }

    int height_right = height(root->right);
    int height_left = height(root->left);
    return 1 + std::max(height_left, height_right);
}

template<class T>
bool is_avl(node<T> *root) {
    if (root == nullptr) {
        return true;
    }

    int diff = height(root->left) - height(root->right);
    return diff >= -1 and diff <= 1 and is_avl(root->left) and is_avl(root->right);
}

template<bool TrailingSpace = false, class T>
void print_post_order(node<T> *root) {
    if (root != nullptr) {
        print_post_order<true>(root->left);
        print_post_order<true>(root->right);
        std::cout << root->value;
        if (TrailingSpace) {
            std::cout << ' ';
        }
    }
}

}

int main() {
    int N;

    while (std::cin >> N) {
        bst::node<int> *source = nullptr, *target = nullptr;

        for (int i=0; i < N; ++i) {
            int value;
            std::cin >> value;
            source = insert(source, value);
        }

        int first_left = 0;
        std::tie(source, first_left) = to_left_spine(source);

        for (int i=0; i < N; ++i) {
            int value;
            std::cin >> value;
            target = insert(target, value);
        }

        int left, right;
        std::tie(std::ignore, left, right) = bst::turn_into_left(source, target);
        std::cout << first_left + left << ' ' << right << "\n";
        print_post_order(target);
        std::cout << "\n" << std::boolalpha << is_avl(target) << "\n\n";

        std::string s;
        std::getline(std::cin, s);
    }

    return 0;
}