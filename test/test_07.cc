#include<iostream>
#include<type_traits>
using namespace std;
typedef enum { i, b, f }data_type;
typedef union { int i; bool b; float f }data_storage;
typedef struct { data_type type; data_storage storage }node;
template <typename Data>
static inline bool mmy_order(node& alpha, Data const& beta) {
    if constexpr (is_same_v<Data, int>) { alpha.type = i; alpha.storage.i = beta; return true; }
    else if constexpr (is_same_v<Data, bool>) { alpha.type = b; alpha.storage.b = beta; return true; }
    else if constexpr (is_same_v<Data, float>) { alpha.type = f; alpha.storage.f = beta; return true; }
    else { return false; }
}
template <typename Data>
static inline Data& mmy_ref(node& alpha) {
    if (alpha.type == i) { return alpha.storage.i; }
    else if (alpha.type == b) { return alpha.storage.b; }
    else if (alpha.type == f) { return alpha.storage.f; }
}
signed main() {
    node space;
    int a = 15;
    if (!mmy_order(space, a)) {
        ptrintf("bad alloc\n");
        exit(1);
    }
    cout << mmy_ref(space) << '\n';
    return 0;
}