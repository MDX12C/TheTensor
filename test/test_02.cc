#include<iostream>
#include<utility>
#include<x86intrin.h>
#include<immintrin.h>
using std::cout;
using std::cin;
//#define DEBUG
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
void show(vector const&);
/*below are definations*/
//constructor size
vector::vector(unsigned int const& alpha) {
    this->size = alpha > 0 ? alpha : 1;
    this->real_size = this->size / 4;
    this->real_size += this->size % 4 ? 1 : 0;
    this->real_size *= 4;
    this->storage_space = (int*) malloc(this->real_size * sizeof(int));
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector() {
    this->size = 1;
    this->real_size = 4;
    this->storage_space = (int*) malloc(this->real_size * sizeof(int));
    for (int i = 0; i < this->real_size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector(vector const& alpha) {
    this->size = alpha.size;
    this->real_size = alpha.real_size;
    this->storage_space = (int*) malloc(this->real_size * sizeof(int));
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
    for (int i = 0; i < this->size; i++)
        this->storage_space[i] += alpha.storage_space[i];
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
#ifdef DEBUG
    printf("operator= function ended\n");
#endif
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
#ifdef DEBUG
    printf("operator+ function ended\n");
#endif
    return temp;
}
vector vector::operator+(vector const& alpha) {
    if (this->size != alpha.size)
        return (*this);
    vector temp(*this);
    for (int i = 0; i < this->size; i++)
        temp.storage_space[i] += alpha.storage_space[i];
#ifdef DEBUG
    printf("operator+ function ended\n");
#endif
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
    //vector b(size);
    for (int i = 0; i < size; i++)
        a[i] = i + 1;
    sv(a);
    show(a);
    return 0;
}