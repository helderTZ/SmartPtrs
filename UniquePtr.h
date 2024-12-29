#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <new>

template <typename T>
class UniquePtr {

    template <typename U, typename ...Args>
    friend UniquePtr<U> make_unique(Args... args); 

    T* data;

public:
    UniquePtr(T* ptr) : data(ptr) {}

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) {
        data = std::move(other.data);
        other.data = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        if (this == &other) {
            this->~UniquePtr();
            data = std::move(other.data);
            other.data = nullptr;
        }
    }

    ~UniquePtr() {
        if (data != nullptr) {
            delete data;
        }
    }

    T* get() const {
        return data;
    }

    T& operator*() {
        return *(T*)data;
    }

};

template <typename T, typename ...Args>
UniquePtr<T> make_unique(Args... args) {
    UniquePtr<T> sptr(new T(std::forward<Args>(args)...));
    return sptr;
}

#endif  // UNIQUE_PTR_H
