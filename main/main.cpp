#include <iostream>

#include<string>

#include "GgParam.h"
#include "GgParamSet.h"
#include "GgMergedParam.h"
#include "GgMergedParamSet.h"


int main()
{
    //std::cout << "Hello World!\n"; 
    GgParam p1("Hello", "World");
    std::cout << "p1:" << p1 << std::endl;

    GgParamSet ps1("ps1");
    ps1.insert(p1);
    ps1.insert("p2", "p2val");
    ps1.insert("p3", "p3val");
    ps1.insert("p4", "p4val");
    std::cout << "\nps1:" << ps1 << std::endl;

    GgParamSet ps2("ps2");
    ps2.insert(p1);
    ps2.insert("p2", "p2val");
    ps2.insert("p3", "p3valX");
    ps2.insert("p4", "p4val");
    std::cout << "\nps2:" << ps2 << std::endl;

    GgParamSet ps3("ps3");
    ps3.insert(p1);
    ps3.insert("p2", "p2val");
    ps3.insert("p3", "p3valX");
    ps3.insert("p5", "p5val");
    std::cout << "\nps3:" << ps3 << std::endl;

    GgMergedParam mp1("mp1", "mp1val1");
    mp1.merge("mp1val1");
    mp1.merge("mp1val2");
    std::cout << "\nmp1:" << mp1 << std::endl;

    GgMergedParamSet mps1("mps1");
    mps1.merge(ps1);
    mps1.merge(ps1);
    mps1.merge(ps2);
    mps1.merge(ps3);
    std::cout << "\nmps1:" << mps1 << std::endl;
}
