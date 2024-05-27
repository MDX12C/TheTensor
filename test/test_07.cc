#include<iostream>
#include<type_traits>
using namespace std;
enum data_trait { V_int, V_bool, V_float };
union data_pointer {
    int* V_int;
    bool* V_bool;
    float* V_float;
};
typedef struct {
    data_trait type;
    data_pointer pointer;
}data_node;
data_node public_variable;
#define VTF(x) V_##x
#define _TF(x) pointer.V_##x
template <typename Data>
class storage {
private:
    Data* ans;
    template <typename T>
    friend istream& operator>>(istream&, storage<T>&);
    template <typename T>
    friend ostream& operator<<(ostream&, storage<T> const&);
public:
    storage();
    ~storage();
};
template<typename Data>
storage<Data>::storage() {
    public_variable.type = VTF(Data);
    this->ans = (Data*) malloc(sizeof(Data));
    public_variable._TF(Data) = this->ans;
    *this->ans = static_cast<Data>(0);
    return;
}
template<typename Data>
storage<Data>::~storage() {
    free(this->ans);
    return;
}
template <typename Data>
istream& operator>>(istream& alpha, storage<Data>& beta) {
    alpha >> *(beta.ans);
    return alpha;
}
template <typename Data>
ostream& operator<<(ostream& alpha, storage<Data> const& beta) {
    alpha << *(beta.ans);
    return alpha;
}
signed main() {
    storage<int> a;
    cin >> a;
    cout << a << '\n';
    if (public_variable.type == data_trait::V_int)
        cout << true << '\n';
    cout << public_variable._TF(int) << '\n';
    return 0;
}