template<class T>
class stack {
    struct node {
        T value;
        node *next;
    };

public:
    stack() = default;
    stack(const stack&) = delete;
    stack(stack&&) = delete;
    stack operator=(const stack&) = delete;
    stack operator=(stack&&) = delete;

    ~stack() {
        while (head != nullptr) {
            node *old_head = head;
            head = head->next;
            delete old_head;
        }
    }

    void push(const T& value) {
        node *new_head = new node();
        new_head->value = value;
        new_head->next = head;
        head = new_head;
        size_++;
    }

    void pop() {
        node *old_head = head;
        head = head->next;
        delete old_head;
        size_--;
    }

    const T& top() const {
        return head->value;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return size_;
    }

private:
    node *head = nullptr;
    int size_ = 0;
};
