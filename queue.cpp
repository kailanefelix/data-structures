template<class T>
class queue {
    struct node {
        T value;
        node *next;
    };

public:
    queue() = default;
    queue(const queue&) = delete;
    queue(queue&&) = delete;
    queue operator=(const queue&) = delete;
    queue operator=(queue&&) = delete;

    ~queue() {
        while (head != nullptr) {
            node *old_head = head;
            head = head->next;
            delete old_head;
        }
    }

    void push(const T& value) {
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

    void pop() {
        size_--;

        if (empty()) {
            tail = nullptr;
        }

        node *old_head = head;
        head = head->next;
        delete old_head;
    }

    const T& front() const {
        return head->value;
    }

    const T& back() const {
        return tail->value;
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
