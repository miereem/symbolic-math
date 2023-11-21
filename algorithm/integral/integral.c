//
// Created by yfcni on 11/21/2023.
//

#include "integral.h"
#include <stdio.h>
#include "integral_operation.h"

ExpressionNode * make_integral(ExpressionNode * node){
    if(isIntegralType1(node)){
        return getIntegralType1(node);
    } else if(isIntegralType2(node)){
        return getIntegralType2(node);
    } else if (isIntegralType3(node)){
        return getIntegralType3(node);
    } else if (isIntegralType4(node)){
        return getIntegralType4(node);
    } else if (isIntegralType5(node)){
        return getIntegralType5(node);
    }else if(isIntegralType6(node)){
        return getIntegralType6(node);
    } else if (isIntegralType7(node)){
        return getIntegralType7(node);
    } else if (isIntegralType8(node)){
        return getIntegralType8(node);
    } else if (isIntegralType9(node)){
        return getIntegralType9(node);
    }else if(isIntegralType10(node)){
        return getIntegralType10(node);
    } else if (isIntegralType11(node)){
        return getIntegralType11(node);
    } else if (isIntegralType12(node)){
        return getIntegralType12(node);
    }
    else{
        printf("there is no this type of integral in programm");
        return NULL;
    }
}