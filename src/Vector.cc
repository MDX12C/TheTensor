#include"../includes/vector.hpp"

namespace Linalg {
    /*constructor with datas
    Enter: 1.size 2.datas array
    declare a vector and array into it
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha, Data* const& beta) {
        if constexpr (std::is_same_v<Data, bool>)
            int t = 0;
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            if (alpha <= 0) {
                this->_shape = 1;
                this->_real_shape = Basic_Math::vec_len;
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
                for (int i = 0; i < this->_real_shape; i++) {
                    this->storage_space[i] = static_cast<Data>(0);
                }
                return;
            }
            this->_shape = alpha;
            this->_real_shape = this->_shape / Basic_Math::vec_len;
            this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
            this->_real_shape *= Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = beta[i];
            }
            return;
        }
        else {
            if (alpha <= 0) {
                this->_shape = 1;
                this->storage_space = new Data[1];
                this->storage_space[0] = static_cast<Data>(0);
                return;
            }
            this->_shape = alpha;
            this->storage_space = new Data[alpha];
            for (int i = 0; i < alpha; i++) {
                this->storage_space[i] = beta[i];
            }
            return;
        }
    }
    /*constructor only size
    Enter: 1.size
    declare a vector filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector(int const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            if (alpha <= 0) {
                this->_shape = 1;
                this->_real_shape = Basic_Math::vec_len;
                this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
                for (int i = 0; i < this->_real_shape; i++) {
                    this->storage_space[i] = static_cast<Data>(0);
                }
                return;
            }
            this->_shape = alpha;
            this->_real_shape = this->_shape / Basic_Math::vec_len;
            this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
            this->_real_shape *= Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            for (int i = 0; i < this->_real_shape; i++)
                this->storage_space[i] = static_cast<Data>(0);
            return;
        }
        else {
            if (alpha <= 0) {
                this->_shape = 1;
                this->storage_space = new Data[1];
                this->storage_space[0] = static_cast<Data>(0);
                return;
            }
            this->_shape = alpha;
            this->storage_space = new Data[alpha];
            for (int i = 0; i < alpha; i++)
                this->storage_space[i] = static_cast<Data>(0);
            return;
        }
    }
    /*defult constructor
    Enter: none
    declare a vector of size 1 filled with 0
    no return*/
    template <typename Data>
    Vector<Data>::Vector() {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            this->_shape = 1;
            this->_real_shape = Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            for (int i = 0; i < this->_real_shape; i++) {
                this->storage_space[i] = static_cast<Data>(0);
            }
            return;
        }
        else {
            this->_shape = 1;
            this->storage_space = new Data[1];
            this->storage_space[0] = static_cast<Data>(0);
            return;
        }
    }
    /*copy constructor
    Enter: 1.vector
    declare a vector with same datas
    no return*/
    template <typename Data>
    Vector<Data>::Vector(Vector<Data> const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            this->_shape = alpha._shape;
            this->_real_shape = alpha._real_shape;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            for (int i = 0; i < this->_real_shape; i++) {
                this->storage_space[i] = alpha.storage_space[i];
            }
            return;
        }
        else {
            this->_shape = alpha._shape;
            this->storage_space = new Data[this->_shape];
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = alpha.storage_space[i];
            }
            return;
        }
    }
    /*destructor
    Enter: none
    delete vector
    no return*/
    template <typename Data>
    Vector<Data>::~Vector() {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            _mm_free(this->storage_space);
            return;
        }
        else {
            delete[] this->storage_space;
            return;
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            if (this->_shape)
                _mm_free(this->storage_space);
            this->_shape = alpha;
            this->_real_shape = this->_shape / Basic_Math::vec_len;
            this->_real_shape += (this->_shape % Basic_Math::vec_len) ? 1 : 0;
            this->_real_shape *= Basic_Math::vec_len;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            Data gamma = static_cast<Data>(0);
            for (int i = 0; i < this->_real_shape; i++) {
                if (i < temp._shape) {
                    this->storage_space[i] = temp.storage_space[i];
                }
                else {
                    this->storage_space[i] = gamma;
                }
            }
        }
        else {
            if (this->_shape)
                delete[] this->storage_space;
            this->_shape = alpha;
            this->storage_space = new Data[this->_shape];
            Data gamma = static_cast<Data>(0);
            for (int i = 0; i < this->_shape; i++) {
                if (i < temp._shape) {
                    this->storage_space[i] = temp.storage_space[i];
                }
                else {
                    this->storage_space[i] = gamma;
                }
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            if (this->_shape)
                _mm_free(this->storage_space);
            this->_shape = alpha._shape;
            this->_real_shape = alpha._real_shape;
            this->storage_space = (Data*) _mm_malloc(this->_real_shape * sizeof(Data), 16);
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                _mm_store_ps(&this->storage_space[i], _mm_load_ps(&alpha.storage_space[i]));
#else //_SIMD_02_
                _mm256_store_ps(&this->storage_space[i], _mm256_load_ps(&alpha.storage_space[i]));
#endif //_SIMD_01_/_SIMD_02_
            }
            return (*this);
        }
        else {
            if (this->_shape)
                delete[] this->storage_space;
            this->_shape = alpha._shape;
            this->storage_space = new Data[this->_shape];
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = alpha.storage_space[i];
            }
            return (*this);
        }
    }
    /*operator= value
    Enter: 1.vector 2.value
    copy the value into the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator=(Data const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                _mm_store_ps(&this->storage_space[i], _mm_set1_ps(alpha));
#else //_SIMD_02_
                _mm256_store_ps(&this->storage_space[i], _mm256_set1_ps(alpha));
#endif //_SIMD_01_
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++)
                this->storage_space[i] = alpha;
            return (*this);
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_add_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_add_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] += alpha.storage_space[i];
            }
        }
        return temp;
    }
    /*operator+ value
    Enter: 1.vector 2.value
    add the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+(Data const& alpha) {
        Vector<Data> temp(*this);
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_add_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_add_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] += alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_sub_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_sub_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha.storage_space[i]);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] -= alpha.storage_space[i];
            }
        }
        return temp;
    }
    /*operator- vlaue
    Enter: 1.vector 2.value
    subtract the value from the vector
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-(Data const& alpha) {
        Vector<Data> temp(*this);
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_sub_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_sub_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] || (!alpha);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] -= alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_mul_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_mul_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] && alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] *= alpha.storage_space[i];
            }
        }
        return temp;
    }
    /*operator* value
    Enter: 1.vector 2.value
    multiply every element in the vector and the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*(Data const& alpha) {
        Vector<Data> temp(*this);
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_mul_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_mul_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = this->storage_space[i] && alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] *= alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_div_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_div_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = (this->storage_space[i] || alpha.storage_space[i]) && (!(this->storage_space[i] && alpha.storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] /= alpha.storage_space[i];
            }
        }
        return temp;
    }
    /*operator/ value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    return the result*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/(Data const& alpha) {
        Vector<Data> temp(*this);
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_div_ps(vecA, vecB);
                _mm_store_ps(&temp.storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_div_ps(vecA, vecB);
                _mm256_store_ps(&temp.storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] = (this->storage_space[i] || alpha) && (!(this->storage_space[i] && alpha));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                temp.storage_space[i] /= alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_add_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_add_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] += alpha.storage_space[i];
            }
        }
        return (*this);
    }
    /*operator+= value
    Enter: 1.vector 2.value
    add the value into the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator+=(Data const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_add_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_add_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] || alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] += alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_sub_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_sub_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && (!alpha.storage_space[i]);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] -= alpha.storage_space[i];
            }
        }
        return (*this);
    }
    /*operator-= value
    Enter: 1.vector 2.value
    subtract the value from the vector
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator-=(Data const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_sub_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_sub_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && (!alpha);
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] -= alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_mul_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_mul_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && alpha.storage_space[i];
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] *= alpha.storage_space[i];
            }
        }
        return (*this);
    }
    /*operator*= value
    Enter: 1.vector 2.value
    multiply every element in the vector with the value
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator*=(Data const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_mul_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_mul_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = this->storage_space[i] && alpha;
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] *= alpha;
            }
        }
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
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_load_ps(&alpha.storage_space[i]);
                vecC = _mm_div_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_load_ps(&alpha.storage_space[i]);
                vecC = _mm256_div_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = (this->storage_space[i] || alpha.storage_space[i]) && (!(this->storage_space[i] && alpha.storage_space[i]));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] /= alpha.storage_space[i];
            }
        }
        return (*this);
    }
    /*operator/= value
    Enter: 1.vector 2.value
    divide every element in the vector by the value
    return this*/
    template <typename Data>
    Vector<Data> Vector<Data>::operator/=(Data const& alpha) {
        if constexpr ((std::is_same_v < Data, float>) && (Basic_Math::SIMD_ON)) {
#ifdef _SIMD_01_
            __m128 vecA, vecB, vecC;
#else //_SIMD_02_
            __m256 vecA, vecB, vecC;
#endif //_SIMD_01_
            for (int i = 0; i < this->_real_shape; i += Basic_Math::vec_len) {
#ifdef _SIMD_01_
                vecA = _mm_load_ps(&this->storage_space[i]);
                vecB = _mm_set1_ps(alpha);
                vecC = _mm_div_ps(vecA, vecB);
                _mm_store_ps(&this->storage_space[i], vecC);
#else //_SIMD_02_
                vecA = _mm256_load_ps(&this->storage_space[i]);
                vecB = _mm256_set1_ps(alpha);
                vecC = _mm256_div_ps(vecA, vecB);
                _mm256_store_ps(&this->storage_space[i], vecC);
#endif //_SIMD_01_
            }
        }
        else if constexpr (std::is_same_v<Data, bool>) {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] = (this->storage_space[i] || alpha) && (!(this->storage_space[i] && alpha));
            }
        }
        else {
            for (int i = 0; i < this->_shape; i++) {
                this->storage_space[i] /= alpha;
            }
        }
        return (*this);
    }
    /*freedom
    Enter: none
    free the space of the vector and set the shape to 1
    no return*/
    template <typename Data>
    void Vector<Data>::freedom_() {
        delete[] this->storage_space;
        this->_shape = 1;
        this->storage_space = new Data[1];
        this->storage_space[0] = static_cast<Data>(0);
        this->_sum = static_cast<Data>(0);
        return;
    }
    /*operator<<
    Enter: 1.ostream 2.vector
    print every element in the vector
    return the ostream*/
    template <typename Data>
    std::ostream& operator<<(std::ostream& beta, Vector<Data> const& alpha) {
        int digits = 1;
        for (int gamma = 0; gamma < alpha._shape; gamma++) {
            digits = std::max(digits, Basic_Math::Int_Digits(alpha.storage_space[gamma]));
        }
        beta << std::noshowpos << "size: " << alpha._shape << " total: " << alpha._sum << '\n';
        for (int i = 0; i < alpha._shape; i++) {
            beta << std::setprecision(Basic_Math::Float16_Accuracy) \
                << std::fixed << std::setfill(' ') << std::showpoint \
                << std::showpos << std::internal \
                << std::setw(Basic_Math::Float16_Accuracy + digits + 2) \
                << alpha.storage_space[i];
            if (i != alpha._shape - 1)
                beta << ' ';
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
        for (int i = 0; i < beta._shape; i++)
            gamma += beta.storage_space[i] * alpha.storage_space[i];
        return gamma;
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
            temp.endow_(i, Basic_Math::random(alpha, beta));
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