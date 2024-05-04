#include<iostream>
#include<functional>
#include<thread>
#include<cstdlib>
#include<ctime>
#include<atomic>
using namespace std;
constexpr int max_len = 100;
constexpr int len = 4;
constexpr int imx = static_cast<int>(200);
constexpr int imn = static_cast<int>(-200);
constexpr float fmx = static_cast<float>(200);
constexpr float fmn = static_cast<float>(-200);
static std::atomic<int> tuple_counter(0);
template <typename Data>
Data random(Data const& alpha, Data const& beta) {
    Data range = beta - alpha;
    if constexpr (std::is_same_v<Data, int>) {
        return alpha + rand() % range;
    }
    else if constexpr (std::is_same_v<Data, float>) {
        return alpha + static_cast<float>(rand()) / RAND_MAX * range;
    }
    else {
        return 0;
    }
}
template <typename Data>
void tuple_add(Data* const&, Data* const&, Data* const&);
signed main() {
    srand(time(0));
    int* alpha, * beta, * gamma;
    alpha = new int[max_len];
    beta = new int[max_len];
    gamma = new int[max_len];
    for (int i = 0; i < max_len; i++) {
        alpha[i] = random(imn, imx);
        beta[i] = (-1) * alpha[i];
    }
    int run_times = max_len / len;
    thread run_arry[run_times];
    for (int i = 0, j = 0; i < max_len; i += len, j++) {
        cout << "the " << j + 1 << " th run queue\n";
        run_arry[j] = thread(tuple_add<int>, &alpha[i], &beta[i], &gamma[i]);
    }
    for (int i = 0; i < run_times; i++) {
        run_arry[i].join();
        cout << "finish " << i + 1 << '\n';
    }
    for (int i = 0; i < max_len; i++) {
        if (gamma[i] != 0) {
            cout << i + 1 << "error\n";
            delete[] alpha;
            delete[] beta;
            delete[] gamma;
            return 1;
        }
    }
    cout << "success\n";
    delete[] alpha;
    delete[] beta;
    delete[] gamma;
    return 0;
}
template <typename Data>
void tuple_add(Data* const& alpha, Data* const& beta, Data* const& gamma) {
    tuple_counter.fetch_add(1);
    cout << tuple_counter.load() << " run\n";
    for (int i = 0; i < len; i++) {
        gamma[i] = alpha[i] + beta[i];
    }
    return;
}