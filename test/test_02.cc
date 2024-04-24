#include<iostream>
#include<utility>
#include<x86intrin.h>
#include<immintrin.h>
using std::cout;
using std::cin;
//#define SIMD
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
    int* storage_space = nullptr;
    unsigned int size;
    unsigned int real_size;

    void friend show(vector const&);
public:
    vector(unsigned int const&);
    vector();
    vector(vector const&);
    ~vector();
    int& operator[](unsigned int const&);
    void operator=(vector const&);
    void operator=(int const&);
    void operator+=(int const&);
    void operator+=(vector const&);
    vector operator+(vector const&);
    vector operator+(int const&);
};
constexpr int vec_len = 4;
void show(vector const&);
#ifdef SIMD
inline void add(int const* a, int const* b, int* c) {
    __m128i vecA, vecB, vecC;
    vecA = _mm_load_epi32(a);
    vecB = _mm_load_epi32(b);
    vecC = _mm_add_epi32(vecA, vecB);
    _mm_store_epi32(c, vecC);
    return;
}
#endif
/*below are definations*/
//constructor size
vector::vector(unsigned int const& alpha) {
    this->size = alpha > 0 ? alpha : 1;
    this->real_size = this->size / 4;
    this->real_size += this->size % 4 ? 1 : 0;
    this->real_size *= 4;
    this->storage_space = (int*) _mm_malloc(this->real_size * sizeof(int), 32);
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector() {
    this->size = 1;
    this->real_size = 4;
    this->storage_space = (int*) _mm_malloc(this->real_size * sizeof(int), 32);
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector(vector const& alpha) {
    this->size = alpha.size;
    this->real_size = alpha.real_size;
    this->storage_space = (int*) _mm_malloc(this->real_size * sizeof(int), 32);
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
    return;
}
void vector::operator+=(int const& alpha) {
    for (int i = 0; i < this->size; i++)
        this->storage_space[i] += alpha;
    return;
}
void vector::operator+=(vector const& alpha) {
    if (this->size != alpha.size)
        return;
#ifndef SIMD
    for (int i = 0; i < this->size; i++)
        this->storage_space[i] += alpha.storage_space[i];
#else
    for (int i = 0; i < this->real_size; i += vec_len) {
        add(&alpha.storage_space[i], &this->storage_space[i], &this->storage_space[i]);
    }
#endif
    return;
}
vector::~vector() {
    if (this->real_size)
        free(this->storage_space);
    return;
}
int& vector::operator[](unsigned int const& alpha) {
    if (alpha >= this->size)
        return this->storage_space[0];
    return this->storage_space[alpha];
}
void vector::operator=(vector const& alpha) {
    if (this == &alpha)
        return;
    if (this->size != alpha.size) {
        if (this->real_size) {
            free(this->storage_space);
        }
        this->storage_space = (int*) malloc(this->real_size * sizeof(int));
        this->size = alpha.size;
        this->real_size = alpha.real_size;
    }
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
    return;
}
void vector::operator=(int const& alpha) {
    for (int i = 0; i < this->size; i++)
        this->storage_space[i] = alpha;
    return;
}
vector vector::operator+(int const& alpha) {
    vector temp(*this);
    for (int i = 0; i < this->size; i++)
        temp.storage_space[i] += alpha;
    return temp;
}
vector vector::operator+(vector const& alpha) {
    if (this->size != alpha.size)
        return (*this);
    vector temp(*this);
    for (int i = 0; i < this->size; i++)
        temp.storage_space[i] += alpha.storage_space[i];
    return temp;
}
void show(vector const& alpha) {
    cout << alpha.size << ' ' << alpha.real_size << '\n';
    for (int i = 0; i < alpha.size; i++) {
        cout << alpha.storage_space[i] << ' ';
    }
    cout << '\n';
}
signed main() {
    int size = 10, times = 8;
    //cin >> size;
    vector a(size);
    vector b(size);
    for (int i = 0; i < size; i++) {
        a[i] = i + 1;
        b[i] = 1;
    }
    sv(a);
    sv(b);
    return 0;
}