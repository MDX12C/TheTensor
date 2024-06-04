#include "../includes/basic.hpp"
namespace Basic_Math {
    std::atomic<bool> set_seed(false);
    float float_leak = 0;
    bool bool_leak = false;
    int int_leak = 0;
}
namespace Memory_Maintain {
    unsigned long long _mmy_heap = 0;
    int _mmy_block = 0;
    _mmy_node* _mmy_top;
    _mmy_node* _mmy_buttom;
}
namespace Linalg {
    /*MaShape operator==
    Enter: 1.MaShape 2.MaShape
    compare two MaShape
    return true if they are equal */
    bool operator==(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.rows == beta.rows) && (alpha.lines == beta.lines);
    }
    /*MaShape operator<<
    Enter: 1.ostream 2.MaShape
    show the MaShape's rows and lines
    return the ostream */
    std::ostream& operator<<(std::ostream& beta, MaShape const& alpha) {
        beta << std::noshowpos << "rows: " << alpha.rows << " lines: " << alpha.lines << '\n';
        return beta;
    }
    /*MaShape operator<
    Enter: 1.MaShape 2.MaShape
    compare two MaShape
    return true if the first one is smaller than the second one */
    bool operator<(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.lines < beta.lines) && (alpha.rows < beta.rows) && (alpha.lines > 0) && (alpha.rows > 0);
    }
    /*MaShape operator<=
    Enter: 1.MaShape 2.MaShape
    compare two MaShape
    return true if the first one is smaller than or equal to the second one */
    bool operator<=(MaShape const& alpha, MaShape const& beta)
    {
        return (alpha.lines <= beta.lines) && (alpha.rows <= beta.rows) && (alpha.lines > 0) && (alpha.rows > 0);
    }
}