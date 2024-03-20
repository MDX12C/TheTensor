namespace Linalg{
    typedef struct{
        int row;
        int lines;
    }MaShape;
    
    template <typename Data>
    class Matrix{
        private:
            Data *storage_space;
            MaShape shape;
        public:
            Matrix(Data* const&,MaShape const&);
            Matrix(Data const&,MaShape const&);
            ~Matrix();
            Data *item(MaShape const&);
            Matrix T();
            void operator=(Matrix const&);
            void operator=(Data const&);
            Matrix operator+(Matrix const&);
            Matrix operator+(Data const&);
            Matrix operator-(Matrix const&);
            Matrix operator-(Data const&);
            Matrix operator*(Matrix const&);
            Matrix operator*(Data const&);
            Matrix operator/(Data const&);
            void add_line_(Data const&);
    };
};