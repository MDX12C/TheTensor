#include"../includes/vector.hpp"
#define _DEBUG_MODE_
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
            Basic_Math::tuple_set(static_cast<Data>(0), this->storage_space);
#else
            this->storage_space = new Data[1];
            Basic_Math::memory_heap.fetch_add(sizeof(Data));
            this->storage_space[0] = static_cast<Data>(0);
#endif
            return;
        }
        this->_shape = alpha;
#ifdef _THREAD_MODE_
        this->_real_shape = Basic_Math::size_check(alpha);
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        int run_num = (this->_real_shape / Basic_Math::vec_len) - 1;
        std::thread run_arry[run_num];
        for (int i = 0, j = 0; j < run_num; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &beta[i], &this->storage_space[i]);
        }
        for (int i = 0; i < run_num; i++) {
            run_arry[i].join();
        }
        for (int j = this->_real_shape - Basic_Math::vec_len; j < this->_real_shape; j++) {
            if (j < this->_shape)
                this->storage_space[j] = beta[j];
            else
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
            Basic_Math::tuple_set(static_cast<Data>(0), this->storage_space);
#else
            this->storage_space = new Data[1];
            Basic_Math::memory_heap.fetch_add(sizeof(Data));
            this->storage_space[0] = static_cast<Data>(0);
#endif
            return;
        }
        this->_shape = alpha;
#ifdef _THREAD_MODE_
        this->_real_shape = Basic_Math::size_check(alpha);
#ifdef _DEBUG_MODE_
        std::cout << "rs=" << this->_real_shape << '\n';
#endif
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
#ifdef _DEBUG_MODE_
        if (this->storage_space == nullptr) {
            std::cout << "~bad alloc~\n";
            exit(1);
        }
        std::cout << "~finish alloc~\n";
        Basic_Math::status();
#endif
        int run_time = this->_real_shape / Basic_Math::vec_len;
        Data omega = static_cast<Data>(0);
        std::thread run_arry[run_time];
#ifdef _DEBUG_MODE_
        std::cout << "~run_time= " << run_time << "~\n";
#endif
        for (int i = 0, j = 0; j < run_time; i += Basic_Math::vec_len, j++) {
#ifdef _DEBUG_MODE_
            std::cout << "i=" << i << " j=" << j << '\n';
#endif
            run_arry[j] = std::thread(Basic_Math::tuple_set<Data>, omega, &this->storage_space[i]);
        }
        for (int i = 0; i < run_time; i++) {
            run_arry[i].join();
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++)
            this->storage_space[i] = static_cast<Data>(0);
#endif
#ifdef _DEBUG_MODE_
        std::cout << "~finish construct~\n";
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
        Basic_Math::tuple_set(static_cast<Data>(0), this->storage_space);
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
#ifdef _DEBUG_MODE_
        std::cout << "~copy constructor~\n";
#endif
        this->_shape = alpha._shape;
#ifdef _THREAD_MODE_
        this->_real_shape = alpha._real_shape;
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &alpha.storage_space[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
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
#ifdef _DEBUG_MODE_
        std::cout << "~destructor~\n";
#endif
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
        this->_real_shape = Basic_Math::size_check(alpha);
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        Data gamma = static_cast<Data>(0);
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            if (i < temp._real_shape)
                run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &temp.storage_space[i], &this->storage_space[i]);
            else
                run_arry[j] = std::thread(Basic_Math::tuple_set<Data>, gamma, &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
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
    /*load
    Enter: 1.size 2.Data pointer
    load the data into the vector
    return if load successfully*/
    template <typename Data>
    bool Vector<Data>::load_(int const& alpha, Data* const& beta) {
        if (alpha < 0 || alpha >= this->_shape)
            return false;
#ifdef _THREAD_MODE_
        Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        _mm_free(this->storage_space);
        this->_shape = alpha;
        this->_real_shape = Basic_Math::size_check(alpha);
        this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &beta[i], &this->storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        Basic_Math::memory_heap.fetch_sub(this->_shape * sizeof(Data));
        delete[] this->storage_space;
        this->_shape = alpha;
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = beta[i];
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
    /*operator=
    Enter: 1.vector 2.vector
    copy the second vector into the first one
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator=(Vector<Data> const& alpha) {
#ifdef _DEBUG_MODE_
        std::cout << "~operator=~\n";
#endif
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
    /*operator+
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
    /*operator+ value back
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
    /*operator-
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
    /*operator- vlaue back
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
    /*operator*
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
    /*operator* value back
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
    /*operator/
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
    /*operator/ value back
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
    /*operator+=
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
    /*operator-=
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
    /*operator*=
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
    /*operator/=
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
    /*operator==
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator==(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_eq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] == alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator== value back
    Enter: 1.Vector 2.value
    compare the value with every element in the vector
    return the bool Vector meaning equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator==(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_eq_s<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] == alpha;
#endif
        return temp;
        }
    /*operator==
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning unequal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator!=(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_ne_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] != alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator== value back
    Enter: 1.Vector 2.value
    compare each element in the vector and the value
    return the bool Vector meaning unequal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator!=(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_ne_s<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else 
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] != alpha;
#endif
        return temp;
        }
    /*operator>
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning larger*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator>(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bg_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] > alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator> value back
    Enter: 1.Vector 2.value
    compare each element in the vector and the value
    return the bool Vector meaning larger*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator>(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bg_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] > alpha;
#endif
        return temp;
        }
    /*operator>=
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning larger or equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator>=(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] >= alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator>= value back
    Enter: 1.Vector 2.value
    compare each element in the vector and the value
    return the bool Vector meaning larger or equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator>=(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bq_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] >= alpha;
#endif
        return temp;
        }
    /*operator<
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning smaller*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator<(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sm_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] < alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator< value back
    Enter: 1.Vector 2.value
    compare each element in the vector and the value
    return the bool Vector meaning smaller*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator<(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sm_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] < alpha;
#endif
        return temp;
        }
    /*operator<=
    Enter: 1.Vector 2.Vector
    compare each element in two vector
    return the bool Vector meaning smaller or equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator<=(Vector<Data> const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_ 
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] <= alpha.storage_space[i];
#endif
        return temp;
        }
    /*operator<= value back
    Enter: 1.Vector 2.value
    compare each element in the vector and the value
    return the bool Vector meaning smaller or equal*/
    template <typename Data>
    Vector<bool> Vector<Data>::operator<=(Data const& alpha) {
        Vector<bool> temp(this->_shape);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sq_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < this->_real_shape / Basic_Math::vec_len; i++) {
            run_array[i].join();
        }
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] <= alpha;
#endif
        return temp;
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
#if  defined(_DEBUG_MODE_) && defined(_THREAD_MODE_)
            beta << "size: " << alpha._shape << " total: " << t << " real size: " << alpha._real_shape << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << alpha.storage_space[i];
                if (i != alpha._real_shape - 1)
                    beta << ' ';
            }
#else
            beta << "size: " << alpha._shape << " total: " << t << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
#endif 
        }
        else if constexpr (std::is_same_v<Data, float>) {
            int digits = 1;
            Data sum = static_cast<Data>(0);
            for (int gamma = 0; gamma < alpha._shape; gamma++) {
                digits = std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
                sum += alpha.storage_space[gamma];
            }
            digits += 2 + Basic_Math::Float16_Accuracy;
#if defined(_DEBUG_MODE_) && defined(_THREAD_MODE_)
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << " real size: " << alpha._real_shape << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << std::setprecision(Basic_Math::Float16_Accuracy) \
                    << std::fixed << std::setfill(' ') << std::showpoint \
                    << std::showpos << std::internal \
                    << std::setw(digits) \
                    << alpha.storage_space[i];
                if (i != alpha._real_shape - 1)
                    beta << ' ';
            }
#else 
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setprecision(Basic_Math::Float16_Accuracy) \
                    << std::fixed << std::setfill(' ') << std::showpoint \
                    << std::showpos << std::internal \
                    << std::setw(digits) \
                    << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
#endif
        }
        else {
            int digits = 1;
            Data sum = static_cast<Data>(0);
            for (int gamma = 0; gamma < alpha._shape; gamma++) {
                digits = std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
                sum += alpha.storage_space[gamma];
            }
            digits += 1;
#if defined(_DEBUG_MODE_) && defined(_THREAD_MODE_)
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << " real size: " << alpha._real_shape << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << std::setfill(' ') \
                    << std::showpos << std::internal \
                    << std::setw(digits) \
                    << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
#else
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setfill(' ') \
                    << std::showpos << std::internal \
                    << std::setw(digits) \
                    << alpha.storage_space[i];
                if (i != alpha._shape - 1)
                    beta << ' ';
            }
#endif
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
    /*operator+ value front
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
    /*operator- value front
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
    /*operator* value front
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
    /*operator/ value front
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
    /*operator== value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning equal*/
    template <typename Data>
    Vector<bool> operator==(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_eq_s<Data>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha == beta.storage_space[i];
        }
#endif
        return temp;
        }
    /*operator!= value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning unequal*/
    template <typename Data>
    Vector<bool> operator!=(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_ne_s<Data>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha != beta.storage_space[i];
        }
#endif 
        return temp;
        }
    /*operator> value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning greater*/
    template <typename Data>
    Vector<bool> operator>(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_bg_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha > beta.storage_space[i];
        }
#endif 
        return temp;
        }
    /*operator>= value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning greater or equal*/
    template <typename Data>
    Vector<bool> operator>=(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_bq_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha >= beta.storage_space[i];
        }
#endif
        return temp;
        }
    /*operator< value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning less*/
    template <typename Data>
    Vector<bool> operator<(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_sm_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha < beta.storage_space[i];
        }
#endif
        return temp;
        }
    /*operator<= value front
    Enter: 1.value 2.Vector
    compare each element in the vector and the value
    return the answer vector meaning less or equal*/
    template <typename Data>
    Vector<bool> operator<=(Data const& alpha, Vector<Data> const& beta) {
        Vector<bool> temp(beta._shape);
#ifdef _THREAD_MODE_
        std::thread run_arry[beta._real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < beta._real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_sq_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
        }
        for (int i = 0; i < beta._real_shape / Basic_Math::vec_len; i++) {
            run_arry[i].join();
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = alpha <= beta.storage_space[i];
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
#ifdef _DEBUG_MODE_
        std::cout << "~vector random~\n";
#endif
        Linalg::Vector<Data> temp(gamma);
#ifdef _THREAD_MODE_
        int run_times = temp._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_rand<Data>, &temp.storage_space[i], alpha, beta);
        }
        for (int i = 0; i < run_times; i++) {
            run_arry[i].join();
        }
        for (int i = run_times * Basic_Math::vec_len; i < gamma; i++) {
            temp.storage_space[i] = Basic_Math::random(alpha, beta);
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = Basic_Math::random(alpha, beta);
        }
#endif
#ifdef _DEBUG_MODE_
        std::cout << "~vector random end~\n";
#endif
        return temp;
        }
    /*absolute
    Enter: 1.Vector
    check each element in the vector
    return the vector with the absolute value*/
    template <typename Data>
    Linalg::Vector<Data> absolute(Linalg::Vector<Data> const& alpha) {
#ifdef _DEBUG_MODE_
        std::cout << "~vector absolute~\n";
#endif
        Linalg::Vector<Data> temp(alpha);
        if constexpr (std::is_same_v<Data, bool>) {
            return temp;
        }
        else {
#ifdef _THREAD_MODE_
            int run_times = alpha._real_shape / Basic_Math::vec_len - 1;
            std::thread run_arry[run_times];
            for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
                run_arry[j] = std::thread(Basic_Math::tuple_abs<Data>, &alpha.storage_space[i], &temp.storage_space[i]);
            }
            for (int i = 0; i < run_times; i++) {
                run_arry[i].join();
            }
            for (int j = run_times * Basic_Math::vec_len; j < alpha._shape; j++) {
                if constexpr (std::is_same_v<Data, int>) {
                    alpha.storage_space[j] = std::abs(alpha.storage_space[j]);
                }
                else {
                    alpha.storage_space[j] = std::fabs(alpha.storage_space[j]);
                }
            }
#else
            for (int i = 0; i < alpha._shape; i++) {
                if constexpr (std::is_same_v<Data, int>) {
                    temp._storage_space[i] = std::abs(alpha._storage_space[i]);
                }
                else {
                    temp._storage_space[i] = std::fabs(alpha._storage_space[i]);
                }
            }
#endif
            return temp;
        }
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
template Linalg::Vector<bool> Linalg::operator/(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator==(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator==(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator==(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator!=(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator!=(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator!=(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator<=(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator<=(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator<=(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator>=(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator>=(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator>=(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator>(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator>(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator>(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<bool> Linalg::operator<(int const&, Linalg::Vector<int> const&);
template Linalg::Vector<bool> Linalg::operator<(float const&, Linalg::Vector<float> const&);
template Linalg::Vector<bool> Linalg::operator<(bool const&, Linalg::Vector<bool> const&);
template Linalg::Vector<int> Basic_Math::absolute(Linalg::Vector<int> const&);
template Linalg::Vector<float> Basic_Math::absolute(Linalg::Vector<float> const&);
template Linalg::Vector<bool> Basic_Math::absolute(Linalg::Vector<bool> const&);