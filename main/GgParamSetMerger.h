#ifndef GGPARAMSETMERGER_H
#define GGPARAMSETMERGER_H

#include <iostream>
#include <string>
#include <vector>

#include "GgMergedParam.h"
#include "GgMergedParamSet.h"
//#include "GgParam.h"
#include "GgParamSet.h"
//#include "GgParamSetBase.h"
//#include "utils.h"


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class GgParamSetMerger {
public:
    GgParamSetMerger() :
        merged_()
    {
    }

    ~GgParamSetMerger()
    {
    }


    void merge(const GgParamSet &paramSet)
    {
        if (!paramSet.empty()) {
            GgMergedParamSet *mps = find(paramSet.getName());
            if (nullptr == mps) {
                merged_.push_back(GgMergedParamSet(paramSet.getName()));
                mps = &(merged_.back());
            }
            mps->merge(paramSet);
        }
    }


protected:
    friend std::ostream& operator<<(std::ostream& os, const GgParamSetMerger &p);


    GgMergedParamSet* find(const std::string &psName) {
        GgMergedParamSet* ret = nullptr;
        for (GgMergedParamSet &mps : merged_) {
            if (psName == mps.getName()) {
                ret = &mps;
                break;
            }
        }
        return ret;
    }


private:
    GgMergedParamSetArray1  merged_;
};


std::ostream& operator<<(std::ostream& os, const GgParamSetMerger &p)
{
    os << "{";
    for (const GgMergedParamSet &ms : p.merged_) {
        os << "\n  " << ms;
    }
    os << "\n}";
    return os;
}

#endif // GGPARAMSETMERGER_H
