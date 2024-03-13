namespace Linear_Algebra{

    enum Tenser_type{zero,identity};

    struct level{
        int* shape=nullptr;
        int Dimensions=0;
    };

    class Tenser{
        private:
            double *storage_space;
            level shape;
        public:
            Tenser(level,Tenser_type);
            void reset(level,Tenser_type);
            double *item(level);
            Tenser T();
            Tenser inverse();
            Tenser operator=(Tenser const& tensor);
            Tenser operator+(Tenser const& tensor);
            Tenser operator-(Tenser const& tensor);
            Tenser operator*(Tenser const& tensor);
    };

};