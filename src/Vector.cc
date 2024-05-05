#include"../includes/vector.hpp"

namespace Linalg {
    /*constructor with datas
    Enter: 1.size 2.datas array
    declare a vector and array into it
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha, Data* const& beta) {
        if (alpha <= 0) {
            this->_shape = 1;
#ifdef _THREAD_MODE_
            this->_real_shape = Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
            for (int i = 0; i < this->_real_shape; i++) {
                this->storage_space[i] = static_cast<Data>(0);
            }
#else
            this->storage_space = new Data[1];
            Basic_Math::memory_heap.fetch_add(sizeof(Data));
            this->storage_space[0] = static_cast<Data>(0);
#endif
            return;
        }
        this->_shape = alpha;
#ifdef _THREAD_MODE_
        this->_real_shape = this->_shape / Basic_Math::vec_len;
        this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
        this->_real_shape *= Basic_Math::vec_len;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = beta[i];
        }
        for (int j = this->_shape; j < this->_real_shape; j++) {
            this->storage_space[j] = static_cast<Data>(0);
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = beta[i];
        }
#endif
        return;
    }
    /*constructor only size
    Enter: 1.size
    declare a vector filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha) {
        if (alpha <= 0) {
            this->_shape = 1;
#ifdef _THREAD_MODE_
            this->_real_shape = Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
            for (int i = 0; i < this->_real_shape; i++) {
                this->storage_space[i] = static_cast<Data>(0);
            }
#else
            this->storage_space = new Data[1];
            Basic_Math::memory_heap.fetch_add(sizeof(Data));
            this->storage_space[0] = static_cast<Data>(0);
#endif
            return;
        }
        this->_shape = alpha;
#ifdef _THREAD_MODE_
        this->_real_shape = this->_shape / Basic_Math::vec_len;
        this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
        this->_real_shape *= Basic_Math::vec_len;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_real_shape; i++)
            this->storage_space[i] = static_cast<Data>(0);
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++)
            this->storage_space[i] = static_cast<Data>(0);
#endif
        return;
    }
    /*defult constructor
    Enter: none
    declare a vector of size 1 filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector() {
        this->_shape = 1;
#ifdef _THREAD_MODE_
        this->_real_shape = Basic_Math::vec_len;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_real_shape; i++) {
            this->storage_space[i] = static_cast<Data>(0);
        }
#else
        this->storage_space = new Data[1];
        Basic_Math::memory_heap.fetch_add(sizeof(Data));
        this->storage_space[0] = static_cast<Data>(0);
#endif
        return;
    }
    /*copy constructor
    Enter: 1.vector
    declare a vector with same datas
    no return*/
    template <typename Data>
    Vector<Data>::Vector(Vector<Data> const& alpha) {
        this->_shape = alpha._shape;
#ifdef _THREAD_MODE_
        this->_real_shape = alpha._real_shape;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_real_shape; i++) {
            this->storage_space[i] = alpha.storage_space[i];
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = alpha.storage_space[i];
        }
#endif
        return;
    }
    /*destructor
    Enter: none
    delete vector
    no return*/
    template <typename Data>
    Vector<Data>::~Vector() {
#ifdef _THREAD_MODE_
        Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        _mm_free(this->storage_space);
#else
        Basic_Math::memory_heap.fetch_sub(this->_shape * sizeof(Data));
        delete[] this->storage_space;
#endif
        return;
    }
    /*endow
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    return if endow successfully*/
    template <typename Data>
    bool Vector<Data>::endow_(int const& alpha, Data const& beta) {
        if (alpha < 0 || alpha >= this->_shape)
            return false;
        this->storage_space[alpha] = beta;
        return true;
    }
    /*sum
    Enter: none
    count the summer of vector
    return the summer*/
    template <typename Data>
    Data Vector<Data>::sum() {
        if (!std::is_same_v < Data, bool>) {
            Data gamma = static_cast<Data>(0);
            for (int i = 0; i < this->_shape; i++) {
                gamma += this->storage_space[i];
            }
            return gamma;
        }
        else {
            int gamma = 0;
            for (int i = 0; i < this->_shape; i++) {
                gamma += this->storage_space[i] ? 1 : -1;
            }
            return static_cast<Data>(gamma > 0);
        }
    }
    /*resize
    Enter: 1.new size
    resize the vector. the beyond data will be deleted
    return if resize successfully*/
    template <typename Data>
    bool Vector<Data>::resize_(int const& alpha) {
        if (alpha <= 0)
            return false;
        if (alpha == this->_shape)
            return true;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        if (this->_shape) {
            _mm_free(this->storage_space);
            Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        }
        this->_shape = alpha;
        this->_real_shape = this->_shape / Basic_Math::vec_len;
        this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
        this->_real_shape *= Basic_Math::vec_len;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        Data gamma = static_cast<Data>(0);
        for (int i = 0; i < this->_real_shape; i++) {
            if (i < temp._shape) {
                this->storage_space[i] = temp.storage_space[i];
            }
            else {
                this->storage_space[i] = gamma;
            }
        }
#else
        if (this->_shape) {
            delete[] this->storage_space;
            Basic_Math::memory_heap.fetch_sub(this->_shape * sizeof(Data));
        }
        this->_shape = alpha;
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        Data gamma = static_cast<Data>(0);
        for (int i = 0; i < this->_shape; i++) {
            if (i < temp._shape) {
                this->storage_space[i] = temp.storage_space[i];
            }
            else {
                this->storage_space[i] = gamma;
            }
        }
#endif
        return true;
    }
    /*operator[]
    Enter: 1.coordinate
    do nothing
    return the data in the coordinate*/
    template <typename Data>
    Data& Vector<Data>::operator[](int const& alpha) {
        if (alpha < 0 || alpha >= this->_shape)
            return this->storage_space[0];
        return this->storage_space[alpha];
    }
    /*operator= Vector
    Enter: 1.vector 2.vector
    copy the second vector into the first one
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator=(Vector<Data> const& alpha) {
#ifdef _THREAD_MODE_
        if (this->_shape) {
            _mm_free(this->storage_space);
            Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        }
        this->_shape = alpha._shape;
        this->_real_shape = alpha._real_shape;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_real_shape; i++) {
            this->storage_space[i] = alpha.storage_space[i];
        }
        return (*this);
#else
        if (this->_shape) {
            Basic_Math::memory_heap.fetch_sub(this->_shape * sizeof(Data));
            delete[] this->storage_space;
        }
        this->_shape = alpha._shape;
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++)
            this->storage_space[i] = alpha.storage_space[i];
        return (*this);
#endif
    }
    /*operator= value
    Enter: 1.vector 2.value
    copy the value into the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator=(Data const& alpha) {
        for (int i = 0; i < this->_shape; i++)
            this->storage_space[i] = alpha;
        return (*this);
    }
    /*operator+ Vector
    Enter: 1.vector 2.vector
    add the two vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] + alpha.storage_space[i];
        }
#endif
        return temp;
    }
    /*operator+ value
    Enter: 1.vector 2.value
    add the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Data const& alpha) {
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add_s_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] + alpha;
        }
#endif
        return temp;
    }
    /*operator- Vector
    Enter: 1.vector 2.vector
    subtract the first vector from the second
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha.storage_space[i]);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] - alpha.storage_space[i];
        }
#endif
        return temp;
    }
    /*operator- vlaue
    Enter: 1.vector 2.value
    subtract the value from the vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-(Data const& alpha) {
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub_sb_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] - alpha;
        }
#endif
        return temp;
    }
    /*operator* Vector
    Enter: 1.vector 2.vector
    multiply every element in the two vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] && alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] * alpha.storage_space[i];
        }
#endif
        return temp;
    }
    /*operator* value
    Enter: 1.vector 2.value
    multiply every element in the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*(Data const& alpha) {
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul_s_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] && alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] * alpha;
        }
#endif
        return temp;
    }
    /*operator/ Vector
    Enter: 1.vector 2.vector
    divide every element in the first vector by the second vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = (this->storage_space[i] || alpha.storage_space[i]) && (!(alpha.storage_space[i] && this->storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] / alpha.storage_space[i];
        }
#endif
        return temp;
    }
    /*operator/ value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/(Data const& alpha) {
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div_sb_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = (this->storage_space[i] || alpha) && (!(alpha && this->storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                temp.storage_space[i] = this->storage_space[i] / alpha;
        }
#endif
        return temp;
    }
    /*operator+= vector
    Enter: 1.vector 2.vector
    add the second vector into the first one
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_add<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] += alpha.storage_space[i];
        }
#endif
        return (*this);
    }
    /*operator+= value
    Enter: 1.vector 2.value
    add the value into the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+=(Data const& alpha) {
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_add_s_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] += alpha;
        }
#endif
        return (*this);
    }
    /*operator-= vector
    Enter: 1.vector 2.vector
    subtract the second vector from the first one
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || (!alpha.storage_space[i]);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] -= alpha.storage_space[i];
        }
#endif
        return (*this);
    }
    /*operator-= value
    Enter: 1.vector 2.value
    subtract the value from the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-=(Data const& alpha) {
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub_sb_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || (!alpha);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] -= alpha;
        }
#endif
        return (*this);
    }
    /*operator*= vector
    Enter: 1.vector 2.vector
    multiply every element in the second vector into the first one
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] *= alpha.storage_space[i];
        }
#endif
        return (*this);
    }
    /*operator*= value
    Enter: 1.vector 2.value
    multiply every element in the vector with the value
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*=(Data const& alpha) {
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul_s_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] *= alpha;
        }
#endif
        return (*this);
    }
    /*operator/= vector
    Enter: 1.vector 2.vector
    divide every element in the first vector by the second vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = (this->storage_space[i] || alpha.storage_space[i]) && (!(alpha.storage_space[i] && this->storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] /= alpha.storage_space[i];
        }
#endif
        return (*this);
    }
    /*operator/= value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/=(Data const& alpha) {
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div_sb_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        if constexpr (is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = (this->storage_space[i] || alpha) && (!(alpha && this->storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] /= alpha;
        }
#endif
        return (*this);
    }
    /*freedom
    Enter: none
    free the space of the vector and set the shape to 1
    no return*/
    template <typename Data>
    void Vector<Data>::freedom_() {
        this->_shape = 1;
#ifdef _THREAD_MODE_
        Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        this->_real_shape = Basic_Math::vec_len;
        _mm_free(this->storage_space);
        this->storage_space = (Data*) _mm_malloc(sizeof(Data) * this->_real_shape, Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        for (int i = 0; i < this->_real_shape; i++)
            this->storage_space[i] = static_cast<Data>(0);
#else
        delete[] this->storage_space;
        Basic_Math::memory_heap.fetch_sub(this->_shape * sizeof(Data));
        this->storage_space = new Data[1];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        this->storage_space[0] = static_cast<Data>(0);
#endif
        return;
    }
    /*operator<<
    Enter: 1.ostream 2.vector
    print every element in the vector
    return the ostream*/
    template <typename Data>
    std::ostream& operator<<(std::ostream& beta, Vector<Data> const& alpha) {
        if constexpr (std::is_same_v<Data, bool>) {
            int t = 0;
            for (int i = 0; i < alpha._shape; i++) {
                t += alpha.storage_space[i] ? 1 : -1;
            }
            t = t > 0 ? 1 : 0;
            beta << "size: " << alpha._shape << " total: " << t << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
        }
        else if constexpr (std::is_same_v<Data, float>) {
            int digits = 1;
            Data sum = static_cast<Data>(0);
            for (int gamma = 0; gamma < alpha._shape; gamma++) {
                digits = std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
                sum += alpha.storage_space[gamma];
            }
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setprecision(Basic_Math::Float16_Accuracy) \
                    << std::fixed << std::setfill(' ') << std::showpoint \
                    << std::showpos << std::internal \
                    << std::setw(Basic_Math::Float16_Accuracy + digits + 2) \
                    << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
        }
        else {
            int digits = 1;
            Data sum = static_cast<Data>(0);
            for (int gamma = 0; gamma < alpha._shape; gamma++) {
                digits = std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
                sum += alpha.storage_space[gamma];
            }
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setfill(' ') \
                    << std::showpos << std::internal \
                    << std::setw(digits + 1) \
                    << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
        }
        beta << '\n';
        return beta;
    }
    /*dot
    Enter: 1.vector 2.vector
    dot every element in the vector
    return the result*/
    template <typename Data>
    Data dot(Vector<Data> const& beta, Vector<Data> const& alpha) {
        if (beta._shape != alpha._shape)
            return static_cast<Data>(0);
        Data gamma = static_cast<Data>(0);
        Vector<Data> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_array[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul<Data>, &alpha.storage_space[i], &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha.storage_space[i] * beta.storage_space[i];
        }
#endif
        if constexpr (std::is_same_v<Data, bool>) {
            int t = 0;
            for (int i = 0; i < temp._shape; i++) {
                t += temp.storage_space[i] ? 1 : -1;
            }
            gamma = t > 0 ? 1 : 0;
        }
        else {
            for (int i = 0; i < temp._shape; i++) {
                gamma += temp.storage_space[i];
            }
        }
        return gamma;
    }
    /*operator+
    Enter: 1.value 2.Vector
    add the value into the vector
    return the answer vector*/
    template <typename op_pls>
    Vector<op_pls> operator+(op_pls const& alpha, Vector<op_pls> const& beta) {
        Vector<op_pls> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add_s_<op_pls>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (std::is_same_v<op_pls, bool>) {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha || beta.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha + beta.storage_space[i];
            }
        }
#endif
        return temp;
    }
    /*operator-
    Enter: 1.value 2.Vector
    minus the Vector from the value
    return the answer vector*/
    template <typename op_mns>
    Vector<op_mns> operator-(op_mns const& alpha, Vector<op_mns> const& beta) {
        Vector<op_mns> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_sub_sf_<op_mns>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (std::is_same_v<op_mns, bool>) {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha || (!beta.storage_space[i]);
            }
        }
        else {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha - beta.storage_space[i];
            }
        }
#endif
        return temp;
    }
    /*operator*
    Enter: 1.value 2.Vector
    mutiply the value and the Vector
    return the answer vector*/
    template <typename op_mul>
    Vector<op_mul> operator*(op_mul const& alpha, Vector<op_mul> const& beta) {
        Vector<op_mul> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_mul_s_<op_mul>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (std::is_same_v<op_mul, bool>) {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha && beta.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha * beta.storage_space[i];
            }
        }
#endif
        return temp;
    }
    /*operator/
    Enter: 1.value 2.Vector
    divide the Vector from the value
    return the answer vector*/
    template <typename op_div>
    Vector<op_div> operator/(op_div const& alpha, Vector<op_div> const& beta) {
        Vector<op_div> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_div_sf_<op_div>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        if constexpr (std::is_same_v<op_div, bool>) {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = (alpha || beta.storage_space[i]) && (!(alpha && beta.storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < temp._shape; i++) {
                temp.storage_space[i] = alpha / beta.storage_space[i];
            }
        }
#endif
        return temp;
    }
}

namespace Basic_Math {
    /*random Vector
    Enter: 1.Vector size 2.min value 3.max value
    random a vector
    return the vector*/
    template <typename Data>
    Linalg::Vector<Data> random(int const& gamma, Data const& alpha, Data const& beta) {
        Linalg::Vector<Data> temp(gamma);
        for (int i = 0; i < gamma; i++) {
            temp[i] = Basic_Math::random(alpha, beta);
        }
        return temp;
    }
}
template class Linalg::Vector<int>;
template class Linalg::Vector<float>;
template class Linalg::Vector<bool>;
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<int> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<float> const&);
template std::ostream& Linalg::operator<<(std::ostream&, Linalg::Vector<bool> const&);
template int Linalg::dot(Linalg::Vector<int> const&, Linalg::Vector<int> const&);
template float Linalg::dot(Linalg::Vector<float> const&, Linalg::Vector<float> const&);
template bool Linalg::dot(Linalg::Vector<bool> const&, Linalg::Vector<bool> const&);
template Linalg::Vector<int> Basic_Math::random(int const&, int const&, int const&);
template Linalg::Vector<float> Basic_Math::random(int const&, float const&, float const&);
template Linalg::Vector<bool> Basic_Math::random(int const&, bool const&, bool const&);
template Linalg::Vector<int> Linalg::operator+(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<float> Linalg::operator+(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator+(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<int> Linalg::operator-(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<float> Linalg::operator-(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator-(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<int> Linalg::operator*(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<float> Linalg::operator*(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator*(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<int> Linalg::operator/(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<float> Linalg::operator/(float const&, Linalg::Vector<float> const&);