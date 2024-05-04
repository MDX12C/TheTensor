#include<iostream>
#include<utility>
#include<x86intrin.h>
#include<immintrin.h>
using std::cout;
using std::cin;
#define SIMD
#define DEBUG
#ifdef DEBUG
#define sv(x){    \
    std::cout<<#x<<':'<<'\n';\
    show(x);\
}
#else
#define sv(x)
#endif
/*below are declaration*/
class vector {
private:
    float* storage_space = nullptr;
    int _size;
    int real__size;

    void friend show(vector const&);
    vector friend operator+(float const&, vector const&);
public:
    vector(int const&);
    vector();
    vector(vector const&);
    ~vector();
    inline int size() { return this->_size; }
    float& operator[](int const&);
    void operator=(vector const&);
    void operator=(float const&);
    void operator+=(float const&);
    void operator+=(vector const&);
    vector operator+(vector const&);
    vector operator+(float const&);
};
vector operator+(float const&, vector const&);
constexpr int vec_len = 4;
void show(vector const&);
#ifdef SIMD
inline void add(float* a, float* b, float* c) {
    __m128 vecA, vecB, vecC;
    vecA = _mm_load_ps(a);
    vecB = _mm_load_ps(b);
    vecC = _mm_add_ps(vecA, vecB);
    _mm_store_ps(c, vecC);
    return;
}
#endif
/*below are definations*/
//constructor _size
vector::vector(int const& alpha) {
    this->_size = alpha > 0 ? alpha : 1;
    this->real__size = this->_size / 4;
    this->real__size += this->_size % 4 ? 1 : 0;
    this->real__size *= 4;
    this->storage_space = (float*) _mm_malloc(this->real__size * sizeof(float), 16);
    for (int i = 0; i < this->real__size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector() {
    this->_size = 1;
    this->real__size = 4;
    this->storage_space = (float*) _mm_malloc(this->real__size * sizeof(float), 16);
    for (int i = 0; i < this->real__size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector(vector const& alpha) {
    this->_size = alpha._size;
    this->real__size = alpha.real__size;
    this->storage_space = (float*) _mm_malloc(this->real__size * sizeof(float), 16);
    for (int i = 0; i < this->real__size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
    return;
}
void vector::operator+=(float const& alpha) {
    for (int i = 0; i < this->_size; i++)
        this->storage_space[i] += alpha;
    return;
}
void vector::operator+=(vector const& alpha) {
    if (this->_size != alpha._size)
        return;
#ifndef SIMD
    for (int i = 0; i < this->_size; i++)
        this->storage_space[i] += alpha.storage_space[i];
#else
    for (int i = 0; i < this->real__size; i += vec_len) {
        add(&alpha.storage_space[i], &this->storage_space[i], &this->storage_space[i]);
    }
#endif
    return;
}
vector::~vector() {
    if (this->real__size)
        _mm_free(this->storage_space);
    return;
}
float& vector::operator[](int const& alpha) {
    if (alpha >= this->_size || alpha < 0)
        return this->storage_space[0];
    return this->storage_space[alpha];
}
void vector::operator=(vector const& alpha) {
    if (this == &alpha)
        return;
    if (this->_size != alpha._size) {
        if (this->real__size) {
            free(this->storage_space);
        }
        this->storage_space = (float*) _mm_malloc(this->real__size * sizeof(float), 16);
        this->_size = alpha._size;
        this->real__size = alpha.real__size;
    }
    for (int i = 0; i < this->real__size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
    return;
}
void vector::operator=(float const& alpha) {
    for (int i = 0; i < this->_size; i++)
        this->storage_space[i] = alpha;
    return;
}
vector vector::operator+(float const& alpha) {
    vector temp(*this);
    for (int i = 0; i < this->_size; i++)
        temp.storage_space[i] += alpha;
    return temp;
}
vector vector::operator+(vector const& alpha) {
    if (this->_size != alpha._size)
        return (*this);
    vector temp(*this);
    for (int i = 0; i < this->_size; i++)
        temp.storage_space[i] += alpha.storage_space[i];
    return temp;
}
void show(vector const& alpha) {
    cout << alpha._size << ' ' << alpha.real__size << '\n';
    for (int i = 0; i < alpha._size; i++) {
        cout << alpha.storage_space[i] << ' ';
    }
    cout << '\n';
}
vector operator+(float const& alpha, vector const& beta) {
    vector temp(beta);
    for (int i = 0; i < beta._size; i++)
        temp.storage_space[i] += alpha;
    return temp;
}
signed main() {
    int _size = 10;
    //cin >> _size;
    vector a(_size);
    for (int i = 0; i < _size; i++) {
        a[i] = i + 1;
    }
    sv(a);
    a = 1 + a;
    sv(a);
    return 0;
}