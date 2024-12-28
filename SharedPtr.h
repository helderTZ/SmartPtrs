#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <new>
#include <atomic>

template <typename T>
class SharedPtr;

class SharedPtrMetadata {

    template<typename T> friend class SharedPtr;

    template <typename T, typename ...Args>
    friend SharedPtr<T> make_shared(Args... args);

    std::atomic<int> refCount;
    SharedPtrMetadata() : refCount(1) {}
};

template <typename T>
class SharedPtr {

    template <typename U, typename ...Args>
    friend SharedPtr<U> make_shared(Args... args);

    SharedPtrMetadata* metadata;
    T* data;

    SharedPtr() : metadata(nullptr), data(nullptr) {}

public:
    SharedPtr(T* ptr)
        : metadata(new SharedPtrMetadata())
        , data(ptr)
    {}

    SharedPtr(const SharedPtr& other) {
        this->metadata = other.metadata;
        this->data = other.data;
        metadata->refCount.fetch_add(1);
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            if (metadata->refCount == 1) {
                this->~SharedPtr();
            }
            this->metadata = other.metadata;
            this->data = other.data;
            metadata->refCount.fetch_add(1);
        }
        return *this;
    }

    ~SharedPtr() {
        metadata->refCount.fetch_sub(1);
        if (metadata->refCount.load() == 0) {
            if (reinterpret_cast<char*>(data) == (reinterpret_cast<char*>(metadata) + sizeof(SharedPtrMetadata))) {
                delete[] metadata;
            } else {
                delete metadata;
                delete data;
            }
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
SharedPtr<T> make_shared(Args... args);

#endif  // SHARED_PTR_H

#ifdef SHARED_PTR_IMPL

template <typename T, typename ...Args>
SharedPtr<T> make_shared(Args... args) {
    char* chunk = new char[sizeof(SharedPtrMetadata) + sizeof(T)];

    SharedPtr<T> sptr;
    sptr.metadata = reinterpret_cast<SharedPtrMetadata*>(chunk);
    sptr.data = &chunk[sizeof(SharedPtrMetadata)];
    new(sptr.metadata) SharedPtrMetadata();
    new(sptr.data) T(std::forward<Args>(args)...);
    return sptr;
}

#endif  // SHARED_PTR_IMPL
