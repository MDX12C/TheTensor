#include"../includes/vector.hpp"
namespace Linalg {
    /*constructor with datas
    Enter: 1.size 2.datas array
    declare a vector and array into it
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha, Data* const& beta) {
#ifdef _DEBUG_MODE_
        printf("~Data constructor~\n");
#endif
        if (alpha <= 0) {
            this->_shape = 1;
#ifdef _THREAD_MODE_
            this->_real_shape = Basic_Math::vec_len;
            if constexpr (std::is_same_v<Data, float>) {
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            }
            else {
                this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
            }
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
            Basic_Math::tuple_set<Data>(this->storage_space, static_cast<Data>(0));
            if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
            }
            else {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
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
        this->_real_shape = Basic_Math::size_check(alpha);
        this->_real_shape = Basic_Math::vec_len;
        if constexpr (std::is_same_v<Data, float>) {
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        int run_num = (this->_real_shape / Basic_Math::vec_len) - 1;
        std::thread run_arry[run_num];
        for (int i = 0, j = 0; j < run_num; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &beta[i], &this->storage_space[i]);
            run_arry[j].detach();
        }
        for (int j = run_num * Basic_Math::vec_len; j < this->_real_shape; j++) {
            if (j < this->_shape)
                this->storage_space[j] = beta[j];
            else
                this->storage_space[j] = static_cast<Data>(0);
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = beta[i];
        }
#endif
#ifdef _DEBUG_MODE_
        printf("~Data constructor end~\n");
#endif
        return;
    }
    /*constructor only size
    Enter: 1.size
    declare a vector filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha) {
#ifdef _DEBUG_MODE_
        printf("~size constructor~\n");
#endif
        if (alpha <= 0) {
            this->_shape = 1;
#ifdef _THREAD_MODE_
            this->_real_shape = Basic_Math::vec_len;
            if constexpr (std::is_same_v<Data, float>) {
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            }
            else {
                this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
            }
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
            Basic_Math::tuple_set<Data>(this->storage_space, static_cast<Data>(0));
            if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
            }
            else {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
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
        this->_real_shape = Basic_Math::size_check(alpha);
#ifdef _DEBUG_MODE_
        printf("rs= %d\n", this->_real_shape);
#endif
        if constexpr (std::is_same_v<Data, float>) {
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
#ifdef _DEBUG_MODE_
        if (this->storage_space == nullptr) {
            printf("BAD ALLOC\n");
            exit(1);
        }
        printf("SUCCESS ALLOC\n");
#endif
        int run_time = this->_real_shape / Basic_Math::vec_len;
        std::thread run_arry[run_time];
#ifdef _DEBUG_MODE_
        printf("run times = %d\n", run_time);
#endif
        for (int i = 0, j = 0; j < run_time; i += Basic_Math::vec_len, j++) {
#ifdef _DEBUG_MODE_
            printf("i= %d j= %d\npointer= %p\n", i, j, &this->storage_space[i]);
#endif
            run_arry[j] = std::thread(Basic_Math::tuple_set<Data>, &this->storage_space[i], static_cast<Data>(0));
            run_arry[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++)
            this->storage_space[i] = static_cast<Data>(0);
#endif
#ifdef _DEBUG_MODE_
        printf("~size constructor end~\n");
#endif
        return;
    }
    /*defult constructor
    Enter: none
    declare a vector of size 1 filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector() {
#ifdef _DEBUG_MODE_
        printf("~defult constructor~\n");
#endif
        this->_shape = 1;
#ifdef _THREAD_MODE_
        this->_real_shape = Basic_Math::size_check(this->_shape);
        if constexpr (std::is_same_v<Data, float>) {
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
#ifdef _DEBUG_MODE_
        if (this->storage_space == nullptr) {
            printf("BAD ALLOC\n");
            exit(1);
        }
        printf("SUCCESS ALLOC\n");
        printf("to set at %p\n", this->storage_space);
#endif
        Basic_Math::tuple_set<Data>(&this->storage_space[0], static_cast<Data>(0));
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        this->storage_space = new Data[1];
        Basic_Math::memory_heap.fetch_add(sizeof(Data));
        this->storage_space[0] = static_cast<Data>(0);
#endif
#ifdef _DEBUG_MODE_
        printf("~defult constructor end~\n");
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
        printf("~copy constructor~\n");
#endif
        this->_shape = alpha._shape;
#ifdef _THREAD_MODE_
        this->_real_shape = alpha._real_shape;
        if constexpr (std::is_same_v<Data, float>) {
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
#ifdef _DEBUG_MODE_
        if (this->storage_space == nullptr) {
            printf("BAD ALLOC\n");
            exit(1);
        }
        printf("SUCCESS ALLOC\n");
#endif
        int run_time = this->_real_shape / Basic_Math::vec_len;
        std::thread run_arry[run_time];
        for (int i = 0, j = 0; i < this->_real_shape && j < run_time; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &alpha.storage_space[i], &this->storage_space[i]);
            run_arry[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        this->storage_space = new Data[this->_shape];
        Basic_Math::memory_heap.fetch_add(this->_shape * sizeof(Data));
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = alpha.storage_space[i];
        }
#endif
#ifdef _DEBUG_MODE_
        printf("~copy constructor end~\n");
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
        printf("~destructor~\n");
#endif
#ifdef _THREAD_MODE_
        Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        if constexpr (std::is_same_v<Data, float>) {
            _mm_free(this->storage_space);
        }
        else {
            free(this->storage_space);
        }
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
        if (this->_real_shape == Basic_Math::size_check(alpha)) {
            this->_shape = alpha;
            for (int i = this->_shape; i < this->_real_shape; i++) {
                this->storage_space[i] = static_cast<Data>(0);
            }
            return true;
        }
        if (this->_shape) {
            if constexpr (std::is_same_v<Data, float>) {
                _mm_free(this->storage_space);
            }
            else {
                free(this->storage_space);
            }
            Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
        }
        this->_shape = alpha;
        this->_real_shape = Basic_Math::size_check(alpha);
        if constexpr (std::is_same_v<Data, float>) {
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            if (i < temp._real_shape) {
                run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &temp.storage_space[i], &this->storage_space[i]);
                run_arry[j].detach();
            }
            else {
                run_arry[j] = std::thread(Basic_Math::tuple_set<Data>, &this->storage_space[i], static_cast<Data>(0));
                run_arry[j].detach();
            }
        }
        if constexpr (std::is_same_v<Data, float>) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        Data gamma = static_cast<Data>(0);
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
        if (this->_real_shape == Basic_Math::size_check(alpha)) {
            this->_shape = alpha;
            for (int i = this->_shape; i < this->_real_shape; i++) {
                this->storage_space[i] = static_cast<Data>(0);
            }
        }
        else {
            Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
            if constexpr (std::is_same_v<Data, float>) {
                _mm_free(this->storage_space);
            }
            else {
                free(this->storage_space);
            }
            this->_shape = alpha;
            this->_real_shape = Basic_Math::size_check(alpha);
            if constexpr (std::is_same_v<Data, float>) {
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            }
            else {
                this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
            }
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        }
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &beta[i], &this->storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_real_shape; i++) {
            if (i < this->_shape) {
                this->storage_space[i] = beta[i];
            }
            else {
                this->storage_space[i] = static_cast<Data>(0);
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
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
        if (alpha < 0 || alpha >= this->_shape) {
            if constexpr (std::is_same_v<Data, float>) {
                return Basic_Math::float_leak;
            }
            else if constexpr (std::is_same_v<Data, int>) {
                return Basic_Math::int_leak;
            }
            else {
                return Basic_Math::bool_leak;
            }
        }
        return this->storage_space[alpha];
    }
    /*operator=
    Enter: 1.vector 2.vector
    copy the second vector into the first one
    return this*/
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Vector<Data> const& alpha) {
#ifdef _DEBUG_MODE_
        printf("~operator=~\n");
#endif
#ifdef _THREAD_MODE_
        if (this->_real_shape == alpha._real_shape) {
            this->_shape = alpha._shape;
        }
        else {
            if (this->_shape) {
                if constexpr (std::is_same_v<Data, float>) {
                    _mm_free(this->storage_space);
                }
                else {
                    free(this->storage_space);
                }
                Basic_Math::memory_heap.fetch_sub(this->_real_shape * sizeof(Data));
            }
            this->_shape = alpha._shape;
            this->_real_shape = alpha._real_shape;
            if constexpr (std::is_same_v<Data, float>) {
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
            }
            else {
                this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
            }
            Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        }
        int runtime = this->_real_shape / Basic_Math::vec_len;
        std::thread run_arry[runtime];
        for (int i = 0, j = 0; j < runtime; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_load<Data>, &alpha.storage_space[i], &this->storage_space[i]);
            run_arry[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#ifdef _DEBUG_MODE_
        printf("~operator= end~\n");
#endif
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
#ifdef _DEBUG_MODE_
        printf("~operator= end~\n");
#endif
        return (*this);
#endif
    }
    /*operator= value
    Enter: 1.vector 2.value
    copy the value into the vector
    return this*/
    template <typename Data>
    Vector<Data>& Vector<Data>::operator=(Data const& alpha) {
#ifdef _THREAD_MODE_
        int runtime = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[runtime];
        for (int i = 0, j = 0; j < runtime; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_set<Data>, &this->storage_space[i], alpha);
            run_arry[j].detach();
        }
        for (int i = runtime * Basic_Math::vec_len; i < this->_shape; i++) {
            this->storage_space[i] = alpha;
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
#else
        for (int i = 0; i < this->_shape; i++) {
            this->storage_space[i] = alpha;
        }
#endif
        return (*this);
    }
    /*operator+
    Enter: 1.vector 2.vector
    add the two vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Vector<Data> const& alpha) {
#ifdef _DEBUG_MODE_
        printf("~operator+ with 1.vector 2.vector ~\n");
#endif
        if (this->_shape != alpha._shape)
            return *this;
        Vector<Data> temp(*this);
#ifdef _THREAD_MODE_
        std::thread run_arry[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
#ifdef _DEBUG_MODE_
        printf("~operator+ end~\n");
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add_s_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                temp.storage_space[i] = this->storage_space[i] || alpha;
            }
            else {
                temp.storage_space[i] = this->storage_space[i] + alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha.storage_space[i]);
            }
            else {
                temp.storage_space[i] = this->storage_space[i] - alpha.storage_space[i];
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub_sb_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha);
            }
            else {
                temp.storage_space[i] = this->storage_space[i] - alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div_sb_<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                temp.storage_space[i] = (this->storage_space[i] || alpha) && (!(alpha && this->storage_space[i]));
            }
            else {
                temp.storage_space[i] = this->storage_space[i] / alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator+=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_add<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator+=(Data const& alpha) {
#ifdef _THREAD_MODE_
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_add_s_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                this->storage_space[i] = this->storage_space[i] || alpha;
            }
            else {
                this->storage_space[i] += alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator-=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                this->storage_space[i] = this->storage_space[i] || (!alpha.storage_space[i]);
            }
            else {
                this->storage_space[i] -= alpha.storage_space[i];
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator-=(Data const& alpha) {
#ifdef _THREAD_MODE_
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sub_sb_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                this->storage_space[i] = this->storage_space[i] || (!alpha);
            }
            else {
                this->storage_space[i] -= alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator*=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator*=(Data const& alpha) {
#ifdef _THREAD_MODE_
        std::thread run_array[this->_real_shape / Basic_Math::vec_len];
        for (int i = 0, j = 0; i < this->_real_shape; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul_s_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
            run_array[j].detach();
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator/=(Vector<Data> const& alpha) {
        if (this->_shape != alpha._shape)
            return (*this);
#ifdef _THREAD_MODE_
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div<Data>, &this->storage_space[i], &alpha.storage_space[i], &this->storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                this->storage_space[i] = (this->storage_space[i] || alpha.storage_space[i]) && (!(alpha.storage_space[i] && this->storage_space[i]));
            }
            else {
                this->storage_space[i] /= alpha.storage_space[i];
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Vector<Data>& Vector<Data>::operator/=(Data const& alpha) {
#ifdef _THREAD_MODE_
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_div_sb_<Data>, &this->storage_space[i], alpha, &this->storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            if constexpr (std::is_same_v<Data, bool>) {
                this->storage_space[i] = (this->storage_space[i] || alpha) && (!(alpha && this->storage_space[i]));
            }
            else {
                this->storage_space[i] /= alpha;
            }
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        if constexpr (std::is_same_v<Data, float>) {
            _mm_free(this->storage_space);
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), Basic_Math::align_size);
        }
        else {
            free(this->storage_space);
            this->storage_space = (Data*) malloc(this->_real_shape * sizeof(Data));
        }
        Basic_Math::memory_heap.fetch_add(this->_real_shape * sizeof(Data));
        Basic_Math::tuple_set<Data>(this->storage_space, static_cast<Data>(0));
        if  constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::set_delay));
        }
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_eq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] == alpha.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_eq_s<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] == alpha;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
#else
        for (int i = 0; i < this->_shape; i++)
            temp.storage_space[i] = this->storage_space[i] == alpha;
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bg_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] > alpha.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bg_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] > alpha;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] >= alpha.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_bq_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] >= alpha;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sm_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] < alpha.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sm_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] < alpha;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sq_v<Data>, &this->storage_space[i], &alpha.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] <= alpha.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = this->_real_shape / Basic_Math::vec_len - 1;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_sq_sb<Data>, &this->storage_space[i], alpha, &temp.storage_space[i]);
            run_array[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < this->_shape; i++) {
            temp.storage_space[i] = this->storage_space[i] <= alpha;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << t << " real size: " << alpha._real_shape << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << alpha.storage_space[i];
                if (i != alpha._real_shape - 1)
                    beta << ' ';
            }
#else
            beta << std::noshowpos << "size: " << alpha._shape << " total: " << t << '\n';
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
            beta << std::noshowpos << "size: " << alpha._shape << " real size: " << alpha._real_shape \
                << std::setprecision(Basic_Math::Float16_Accuracy)\
                << std::fixed << std::setfill(' ') << std::showpoint \
                << std::showpos << std::internal << " total: " << sum << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << std::setw(digits) << alpha.storage_space[i];
                if (i != alpha._real_shape - 1)
                    beta << ' ';
            }
#else 
            beta << std::noshowpos << "size: " << alpha._shape  \
                << std::setprecision(Basic_Math::Float16_Accuracy)\
                << std::fixed << std::setfill(' ') << std::showpoint \
                << std::showpos << std::internal << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setw(digits) << alpha.storage_space[i];
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
            beta << std::noshowpos << "size: " << alpha._shape << " real size: " << alpha._real_shape << std::setfill(' ') \
                << std::showpos << std::internal << " total: " << sum << '\n';
            for (int i = 0; i < alpha._real_shape; i++) {
                beta << std::setw(digits) << alpha.storage_space[i];
                if (i != alpha._real_shape - 1)
                    beta << ' ';
            }
#else
            beta << std::noshowpos << "size: " << alpha._shape << std::setfill(' ') \
                << std::showpos << std::internal << " total: " << sum << '\n';
            for (int i = 0; i < alpha._shape; i++) {
                beta << std::setw(digits) << alpha.storage_space[i];
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
        int run_times = beta._real_shape / Basic_Math::vec_len;
        std::thread run_array[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_array[j] = std::thread(Basic_Math::tuple_mul<Data>, &alpha.storage_space[i], &beta.storage_space[i], &temp.storage_space[i]);
            run_array[j].detach();
        }
        if (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_add_s_<op_pls>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int j = run_times * Basic_Math::vec_len; j < beta._shape; j++) {
            if constexpr (std::is_same_v<op_pls, bool>) {
                temp.storage_space[j] = alpha || beta.storage_space[j];
            }
            else {
                temp.storage_space[j] = alpha + beta.storage_space[j];
            }
        }
        if (std::is_same_v<op_pls, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_sub_sf_<op_mns>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int j = run_times * Basic_Math::vec_len; j < beta._shape; j++) {
            if constexpr (std::is_same_v<op_mns, bool>) {
                temp.storage_space[j] = alpha || (!beta.storage_space[j]);
            }
            else {
                temp.storage_space[j] = alpha - beta.storage_space[j];
            }
        }
        if (std::is_same_v<op_mns, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
            run_arry[j].detach();
        }
        if (std::is_same_v<op_mul, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_div_sf_<op_div>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int j = run_times * Basic_Math::vec_len; j < beta._shape; j++) {
            if constexpr (std::is_same_v<Data, bool>) {
                temp.storage_space[j] = (alpha || beta.storage_space[j]) && (!(alpha && beta.storage_space[j]));
            }
            else {
                temp.storage_space[j] = alpha / beta.storage_space[j];
            }
        }
        if (std::is_same_v<op_div, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_eq_s<Data>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < beta._shape; i++) {
            temp.storage_space[i] = alpha == beta.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_ne_s<Data>, &beta.storage_space[i], alpha, &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < beta._shape; i++) {
            temp.storage_space[i] = alpha != beta.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_bg_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < beta._shape; i++) {
            temp.storage_space[i] = alpha > beta.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_bq_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < beta._shape; i++) {
            temp.storage_space[i] = alpha >= beta.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
        int run_times = beta._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_sm_sf<Data>, alpha, &beta.storage_space[i], &temp.storage_space[i]);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < beta._shape; i++) {
            temp.storage_space[i] = alpha < beta.storage_space[i];
        }
        std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::operate_delay));
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
    Enter: 1.Vector size 2.min value Basic_Math::set_delay.max value
    random a vector
    return the vector*/
    template <typename Data>
    Linalg::Vector<Data> random(int const& gamma, Data const& alpha, Data const& beta) {
#ifdef _DEBUG_MODE_
        printf("~vector random~\n");
#endif
        Linalg::Vector<Data> temp(gamma);
#ifdef _THREAD_MODE_
        int run_times = temp._real_shape / Basic_Math::vec_len - 1;
        std::thread run_arry[run_times];
        for (int i = 0, j = 0; j < run_times; i += Basic_Math::vec_len, j++) {
            run_arry[j] = std::thread(Basic_Math::tuple_rand<Data>, &temp.storage_space[i], alpha, beta);
            run_arry[j].detach();
        }
        for (int i = run_times * Basic_Math::vec_len; i < gamma; i++) {
            temp.storage_space[i] = Basic_Math::random(alpha, beta);
        }
        if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
        }
        else {
            std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::function_delay));
        }
#else
        for (int i = 0; i < temp._shape; i++) {
            temp.storage_space[i] = Basic_Math::random(alpha, beta);
        }
#endif
#ifdef _DEBUG_MODE_
        printf("~vector random end~\n");
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
        printf("~vector absolute~\n");
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
                run_arry[j].detach();
            }
            for (int j = run_times * Basic_Math::vec_len; j < alpha._shape; j++) {
                if constexpr (std::is_same_v<Data, int>) {
                    alpha.storage_space[j] = std::abs(alpha.storage_space[j]);
                }
                else {
                    alpha.storage_space[j] = std::fabs(alpha.storage_space[j]);
                }
            }
            if constexpr (std::is_same_v<Data, float> && Basic_Math::SIMD_ON) {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time));
            }
            else {
                std::this_thread::sleep_for(std::chrono::microseconds(Basic_Math::wait_time * Basic_Math::function_delay));
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
#ifdef _DEBUG_MODE_
            printf("~vector absolute end~\n");
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