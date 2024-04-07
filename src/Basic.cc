#include"../includes/basic.hpp"
namespace Basic_Math {
    /*Interface Digits
    Enter: 1.value
    count how many numbers before the point
    return the number*/
    template <typename Data>
    int Int_Digits(Data const& alpha) {
        return (std::floor(std::log10(alpha)) + 1);
    }
    /*constructor with Dimansion
    Enter: 1.Dimansion
    construct a Teshape with the Dimansion but the shape is 1
    no return*/
    Teshape::Teshape(int const& alpha) {
        this->_dimansion = alpha > 0 ? alpha : 1;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = 1;
        return;
    }
    /*constructor with inited shape
    Enter: 1.Dimansion 2.inited shape array
    construct a Teshape with the Dimansion and the inited shape
    no return*/
    Teshape::Teshape(int const& alpha, int* const& beta) {
        this->_dimansion = alpha > 0 ? alpha : 1;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = beta[i] > 0 ? beta[i] : 1;
        return;
    }
    /*copy constructor
    Enter: 1.Teshape
    copy the Teshape
    no return*/
    Teshape::Teshape(Teshape const& alpha) {
        this->_dimansion = alpha._dimansion;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return;
    }
    /*defult constructor
    Enter: none
    construct a Teshape with the Dimansion is 1 and the shape is 1
    no return*/
    Teshape::Teshape() {
        this->_dimansion = 1;
        this->shape = new int[1];
        this->shape[0] = 1;
        return;
    }
    /*destructor
    Enter: none
    destruct the Teshape
    no return*/
    Teshape::~Teshape() {
        delete[] this->shape;
        return;
    }
    /*endow    Warning!!!
    Enter: 1.coordinate 2.value
    endow the value at the coordinate
    no return*/
    void Teshape::endow_(int const& alpha, int const& beta) {
        if (alpha < 0 || alpha >= this->_dimansion)
            return;
        this->shape[alpha] = beta > 0 ? beta : 1;
        return;
    }
    /*operator[]
    Enter: 1.coordinate
    do nothing
    return the data in the coordinate*/
    int Teshape::operator[](int const& alpha) {
        if (alpha < 0 || alpha >= this->_dimansion)
            return 0;
        return this->shape[alpha];
    }
    /*operator=
    Enter: 1.Teshape
    copy the Teshape
    no return*/
    void Teshape::operator=(Teshape const& alpha) {
        if (this->_dimansion)
            delete[] this->shape;
        this->_dimansion = alpha._dimansion;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return;
    }
    /*operator==
    Enter: 1.Teshape 2.Teshape
    compare the Teshape
    return true if they are equal*/
    bool Teshape::operator==(Teshape const& alpha) {
        if (this->_dimansion != alpha._dimansion)
            return false;
        for (int i = 0; i < this->_dimansion; i++)
            if (this->shape[i] != alpha.shape[i])
                return false;
        return true;
    }
    /*size
    Enter: none
    count there are how many numbers in total
    return the number*/
    int Teshape::size() {
        int alpha = 1;
        for (int i = 0; i < this->_dimansion; i++)
            alpha *= this->shape[i];
        return alpha;
    }
    /*reshape
    Enter: 1.Teshape
    reshape this through the Teshape
    return true if the shape is reshaped*/
    bool Teshape::reshape_(Teshape& alpha) {
        if (this->size() != alpha.size())
            return false;
        if ((*this) == alpha)
            return true;
        if (this->_dimansion)
            delete[] this->shape;
        this->_dimansion = alpha._dimansion;
        this->shape = new int[this->_dimansion];
        for (int i = 0; i < this->_dimansion; i++)
            this->shape[i] = alpha.shape[i];
        return true;
    }
    /*operator>>
    Enter: 1.istream 2.Teshape
    read the Teshape from the istream
    return the istream*/
    std::istream& operator>>(std::istream& alpha, Teshape& beta) {
        int gamma;
        if (beta._dimansion)
            delete[] beta.shape;
        alpha >> gamma;
        beta._dimansion = gamma > 0 ? gamma : 1;
        beta.shape = new int[beta._dimansion];
        for (int i = 0; i < beta._dimansion; i++) {
            alpha >> gamma;
            beta.shape[i] = gamma > 0 ? gamma : 1;
        }
        return alpha;
    }
    /*operator<<
    Enter: 1.ostream 2.Teshape
    print the Teshape in the ostream
    return the ostream*/
    std::ostream& operator<<(std::ostream& alpha, Teshape const& beta) {
        alpha << beta._dimansion << " : ";
        for (int i = 0; i < beta._dimansion; i++) {
            alpha << beta.shape[i];
            if (i != beta._dimansion - 1)
                alpha << ' ';
        }
        return alpha;
    }
    /*belongs
    Enter: 1.coordinate 2.Teshape
    check if the coordinate is in the Teshape
    return true if it is*/
    bool belongs(Teshape const& alpha, Teshape const& beta) {
        if (alpha._dimansion != beta._dimansion)
            return false;
        for (int i = 0; i < alpha._dimansion; i++)
            if (alpha.shape[i] != beta.shape[i])
                return false;
        return true;
    }
}