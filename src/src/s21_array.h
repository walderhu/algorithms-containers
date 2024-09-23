#ifndef ARRAY_H
#define ARRAY_H

namespace s21 {

template <typename T, size_t Size>
class array {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = std::size_t;

        array() {}
        array(std::initializer_list<value_type> const &items)  {
            size_type index = 0;
            for (const_reference& item : items) {
                if (index >= Size) {
                    break;
                }
            items_[index++] = item;
    }
        }
        array(const array &a) {
            for (size_type i = 0; i < Size; i++) {
                items_[i] = a.items_[i];
            }
        }

        array(array &&a) noexcept {
            for (size_type i = 0; i < Size; i++) {
                items_[i] = a.items_[i];
                a.items_[i] = value_type{};
            }
        }

        ~array() {}

        array &operator=(array &&a) noexcept {
            for (size_type i = 0; i < Size; i++) {
                items_[i] = a.items_[i];
                a.items_[i] = value_type{};
            }
            return *this;
        }
        
        reference operator[](size_type pos) { return items_[pos]; }

        reference at(size_type pos) {
            return items_[pos];
        }

        const_reference front() const { 
            return items_[0]; 
        }

        const_reference back() const { 
            return items_[Size - 1]; 
        }

        iterator data() {
            return items_;
        }

        iterator begin() {
            return items_;
        }

        iterator end() {
            return items_ + Size;
        }

        bool empty() const {
            return Size == 0;
        }
        
        size_type size() const {
            return Size;
        }
        
        size_type max_size() const {
            return Size;
        }

        void swap(array &other) {
            for (size_type i = 0; i < Size; i++) {
                value_type buff = items_[i];
                items_[i] = other.items_[i];
                other.items_[i] = buff;
            }
        }

        void fill(const_reference value) {
            for (size_type i = 0; i < Size; i++) {
                items_[i] = value;
            }
        }

    private:
        value_type items_[Size];
};

}

#endif