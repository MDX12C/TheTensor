#include<iostream>
#include<utility>
using std::cout;
using std::cin;
class vector {
private:
    int* storage_space = nullptr;
    int size = 0;
public:
    vector();
    vector(int);
    ~vector();
    void endow_(int, int);
    int operator[](int);
    void operator=(vector const&);
};

vector::vector(int alpha) {
    size = alpha;
    storage_space = new int[size];
    for (int i = 0; i < size; i++) {
        storage_space[i] = 0;
    }
    return;
}
vector::vector() {
    size = 0;
    storage_space = nullptr;
    return;
}
vector::~vector() {
    printf("destructor\n");
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
    this->size = alpha.size;
    if (this->size)
        delete[] this->storage_space;
    this->storage_space = new int[this->size];
    for (int i = 0; i < size; i++) {
        this->storage_space[i] = alpha.storage_space[i];
    }
    return;
}
vector memory(int);

signed main() {
    int size = 5, times = 2, index, value;
    //cin >> size;
    vector a = memory(size);
    for (int i = 0; i < size; i++)
        cout << a[i] << ' ';
    cout << '\n';
    //cin >> times;
    for (int i = 5; i < times+5; i++) {
        //cin >> index >> value;
        index = i; value = index - 1;
        a.endow_(index, value);
    }
    for (int i = 0; i < size; i++)
        cout << a[i] << ' ';
    cout << '\n';
    printf("main function ended\n");
    return 0;
}
vector memory(int alpha) {
    vector temp(alpha);
    for (int i = 0; i < alpha; i++)
        temp.endow_(i, i + 1);
    printf("memory function ended\n");
    return temp;
}