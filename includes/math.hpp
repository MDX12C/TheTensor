namespace Linear_Algebra{
    
    enum Matrix_type{zero,identity};

    struct level{
        int* shape=nullptr;
        int Dimensions=0;
    };

    class Matrix{
        private:
            int *storage_space;
            level shape;
        public:
            Matrix(level,Matrix_type);
            void reset(level,Matrix_type);
            double *item(level);
            Matrix T();
            Matrix inverse();
            Matrix operator=(Matrix const& Matrix);
            Matrix operator+(Matrix const& Matrix);
            Matrix operator-(Matrix const& Matrix);
            Matrix operator*(Matrix const& Matrix);
    };

};