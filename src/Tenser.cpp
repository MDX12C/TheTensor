#include"../head/number.hpp"
namespace Line=Linear_Algebra;

Line::Tenser::Tenser(Line::level alpha,Line::Tenser_type beta){
    shape=alpha;
    int lenth=1;
    for(int i=0;i<shape.Dimensions;i++){
        lenth*=shape.shape[i];
    }
    storage_space=new double[lenth];
    /**/
}
