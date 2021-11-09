template<class T>
class list {
    struct node {
        T value;
        node *next;
    };

public:
    list() = default;
    list(const list&) = delete;
    list(list&&) = delete;
    list operator=(const list&) = delete;
    list operator=(list&&) = delete;

    ~list() {
        while (head != nullptr) {
            node *old_head = head;
            head = head->next;
            delete old_head;
        }
    }

    void push_back(const T& value) {
        node *new_tail = new node();
        new_tail->value = value;
        new_tail->next = nullptr;

        if (empty()) {
            head = new_tail;
        } else {
            tail->next = new_tail;
        }

        tail = new_tail;
        size_++;
    }

    void push_front(const T& value) {
        node *new_head = new node();
        new_head->value = value;
        new_head->next = head;

        if (empty()) {
            tail = new_head;
        }

        head = new_head;
        size_++;
    }

    void insert(int position, const T& value) {
        if (position == 0) {
            push_front(value);
            return;
        }

        if (position == size_) {
            push_back(value);
            return;
        }

        // find the previous node
        node *current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }

        // create the new node
        node *new_node = new node();
        new_node->value = value;
        new_node->next = current->next;

        // repoint previous node
        current->next = new_node;
        size_++;
    }

    void pop_back() {
        size_--;
        delete tail;

        if (empty()) {
            head = nullptr;
            tail = nullptr;
            return;
        }

        // find the element before the last
        node *current = head;
        for (int i = 0; i < size_ - 1; i++) {
            current = current->next;
        }

        tail = current;
        current->next = nullptr;
    }

    void pop_front() {
        size_--;

        if (empty()) {
            tail = nullptr;
        }

        node *old_head = head;
        head = head->next;
        delete old_head;
    }

    void erase(int position) {

        // special cases:
        if (position == 0) {
            pop_front();
            return;
        }

        if (position == size_) {
            pop_back();
            return;
        }

        // for a arbitrary position:

        // find the node to be erased
        node *erased = head;
        for (int i = 0; i < position; i++) {
            erased = erased->next;
        }

        // find the previous node
        node *current = head;
        for (int i = 0; i < position - 1; i++) {
            current = current->next;
        }

        // repoint previous node
        current->next = erased->next;

        // erase node

        delete erased;

        size_--;
    }

    const T& front() const {
        return head->value;
    }

    const T& back() const {
        return tail->value;
    }

    const T& at(int position) const {
        node *current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        return current->value;
    }

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

private:
    node *head = nullptr;
    node *tail = nullptr;
    int size_ = 0;
};
