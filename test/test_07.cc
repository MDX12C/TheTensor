#include<iostream>
enum data_trait { V_int, V_bool, V_float };
union data_pointer {
    int* V_int;
    bool* V_bool;
    float* V_float;
};
typedef struct data_node {
    data_trait type;
    data_pointer pointer;
};
data_node public_variable;
#define VTF(x) V_##x
template <typename Data>
class storage {
private:
    Data ans;
public:
    storage();
    ~storage();
};
template<typename Data>
storage<Data>::storage() {

}