#include<iostream>
#include<type_traits>
using namespace std;
#define BA printf("bad alloc\n");exit(1);
#define BB printf("bad catch\n");exit(1);
typedef enum { i, b, f }data_type;
typedef union { int i; bool b; float f; }data_storage;
typedef struct { data_type type; data_storage storage; }node;
template <typename Data>
static inline bool mmy_order(node& alpha, Data const& beta) {
    if constexpr (is_same_v<Data, int>) { alpha.type = i; alpha.storage.i = beta; return true; }
    else if constexpr (is_same_v<Data, bool>) { alpha.type = b; alpha.storage.b = beta; return true; }
    else if constexpr (is_same_v<Data, float>) { alpha.type = f; alpha.storage.f = beta; return true; }
    else { return false; }
}
template <typename Data>
static inline bool mmy_ref(node const& alpha, Data& beta) {
    if (alpha.type == i) { beta = alpha.storage.i; return true; }
    else if (alpha.type == b) { beta = alpha.storage.b; return true; }
    else if (alpha.type == f) { beta = alpha.storage.f; return true; }
    else { return false; }
}
signed main() {
    node space;
    int a; bool b; float c; char x;
START:
    cout << "i:int b:bool f:float\n";
    cin.get(x); cin.get();
    if (x == 'i') {
        cin >> a;
        if (!mmy_order(space, a)) { BA }
        a = 0;
        if (!mmy_ref(space, a)) { BB }
        cout << a << '\n';
    }
    else if (x == 'b') {
        cin >> b;
        if (!mmy_order(space, b)) { BA }
        b = false;
        if (!mmy_ref(space, b)) { BB }
        cout << b << '\n';
    }
    else if (x == 'f') {
        cin >> c;
        if (!mmy_order(space, c)) { BA }
        c = 0;
        if (!mmy_ref(space, c)) { BB }
        cout << c << '\n';
    }
    else {
        goto START;
    }
    auto ans = mmy_ans(space);
    cout << ans << '\n';
    return 0;
}