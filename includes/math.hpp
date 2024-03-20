namespace Linalg{

    struct meta{
        int* shape=nullptr;
        int Dimensions=0;
    };

    template <typename T>
    class Matrix{
        private:
            T *storage_space;
            meta meta;

        public:
            Matrix(meta,T*);
            ~Matrix();
            T *item(meta);
            Matrix T();
            Matrix L_inverse();
            Matrix R_inverse();
            Matrix operator=(Matrix const& Matrix);
            Matrix operator+(Matrix const& Matrix);
            Matrix operator-(Matrix const& Matrix);
            Matrix operator*(Matrix const& Matrix);
            
    };
};