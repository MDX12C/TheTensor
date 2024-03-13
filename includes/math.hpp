namespace Linear_Algebra{

    struct meta{
        int* shape=nullptr;
        int Dimensions=0;
    };

    class Matrix{
        private:
            int *storage_space;
            meta shape;
        public:
            Matrix(meta,int*);
            double *item(meta);
            Matrix T();
            Matrix L_inverse();
            Matrix R_inverse();
            Matrix operator=(Matrix const& Matrix);
            Matrix operator+(Matrix const& Matrix);
            Matrix operator-(Matrix const& Matrix);
            Matrix operator*(Matrix const& Matrix);
            
    };

};