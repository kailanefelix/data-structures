namespace kai {

template<class T>
class vector {
public:
    vector(): data{new T[1]}, size_{0}, capacity{1} {}
    ~vector() {
        delete[] data;
    }

    void push_back(const T &value) {
        // if vector is full, double its capacity
        if (size_ == capacity) {
            T* new_data = new T[capacity * 2];

            for (int i = 0; i < size_; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
            capacity = capacity * 2;
        }

        data[size_] = value;
        ++size_;
    }

    void pop_back() {
        --size_;
    }

    int size() const {
        return size_;
    }

    T *begin() {
        return data;
    }

    T *end() {
        return data + size_;
    }

private:
    T *data;
    int size_;
    int capacity;
};

}