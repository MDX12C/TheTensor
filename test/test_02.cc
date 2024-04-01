#include<iostream>
#include<utility>
using std::cout;
using std::cin;
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
    int size = 1;

    void friend show(vector const&);
public:
    vector(int);
    vector(const vector&);
    ~vector();
    void endow_(int, int);
    int operator[](int);
    void operator=(vector const&);
    void operator=(int const&);
    void operator+=(int const&);
    void operator+=(vector const&);
    vector operator+(vector const&);
    vector operator+(int const&);
};
vector identity(int const&);
void show(vector const&);
/*below are definations*/
vector::vector(int alpha) {
    this->size = alpha > 0 ? alpha : 1;
    this->storage_space = new int[size];
    for (int i = 0; i < this->size; i++) {
        this->storage_space[i] = 0;
    }
    return;
}
vector::vector(const vector& alpha) {
    this->size = alpha.size;
    this->storage_space = new int[this->size];
    for (int i = 0; i < this->size; i++) {
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
    if (this->size)
        delete[] storage_space;
    return;
}
void vector::endow_(int alpha, int beta) {
    storage_space[alpha] = beta;
    return;
}
int vector::operator[](int alpha) {
    return storage_space[alpha];
}
void vector::operator=(vector const& alpha) {
    if (this == &alpha)
        return;
    if (this->size != alpha.size) {
        if (this->size) {
            delete[] this->storage_space;
        }
        this->storage_space = new int[alpha.size];
        this->size = alpha.size;
    }
    for (int i = 0; i < this->size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
#ifdef DEBUG
    printf("operator= function ended\n");
#endif
    return;
}
void vector::operator=(int const& alpha) {
    if (this->size < 1) {
        this->storage_space = new int[1];
        this->size = 1;
    }
    for (int i = 0; i < this->size; i++)
        this->storage_space[i] = alpha;
    return;
}
vector vector::operator+(int const& alpha) {
    vector temp(this->size);
    for (int i = 0; i < this->size; i++)
        temp.storage_space[i] = this->storage_space[i] + alpha;
#ifdef DEBUG
    printf("operator+ function ended\n");
#endif
    return temp;
}
vector vector::operator+(vector const& alpha) {
    if (this->size != alpha.size)
        return alpha;
    vector temp(this->size);
    for (int i = 0; i < this->size; i++)
        temp.storage_space[i] = this->storage_space[i] + alpha.storage_space[i];
#ifdef DEBUG
    printf("operator+ function ended\n");
#endif
    return temp;
}
void show(vector const& alpha) {
    for (int i = 0; i < alpha.size; i++) {
        cout << alpha.storage_space[i] << ' ';
    }
    cout << '\n';
}
vector identity(int const& alpha) {
    vector temp(alpha);
    for (int i = 0; i < alpha; i++)
        temp.endow_(i, 1);
#ifdef DEBUG
    printf("identity function ended\n");
#endif
    return temp;
}
signed main() {
    int size = 10, times = 8;
    //cin >> size;
    vector a(size);
    //vector b(size);
    for (int i = 0; i < size; i++)
        a.endow_(i, i + 1);
    sv(a);
    //cin >> times;
    for (int i = 1; i <= times; i++) {
        sv(identity(size));
        a = a + identity(size);
        sv(a);
    }
    show(a);
    return 0;
}