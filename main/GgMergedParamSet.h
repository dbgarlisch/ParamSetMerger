#ifndef GGMERGEDPARAMSET_H
#define GGMERGEDPARAMSET_H

#include <iostream>
#include <string>
#include <vector>

#include "GgMergedParam.h"
#include "GgParam.h"
#include "GgParamSet.h"
#include "GgParamSetBase.h"
#include "utils.h"


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class GgMergedParamSet : public GgParamSetBase<GgMergedParam> {
public:

    using BaseType = GgParamSetBase<GgMergedParam>;

public:
    GgMergedParamSet(const std::string &name = "") :
        GgParamSetBase(name),
        mergedSetCnt_(0)
    {
    }

    ~GgMergedParamSet()
    {
    }

    void merge(const GgParamSet &paramSet, const bool allowEmpty = false)
    {
        if (allowEmpty || !paramSet.empty()) {
            ++mergedSetCnt_;
            for (const GgParam &param : paramSet.params()) {
                GgMergedParam *mp = find(param.getName());
                if (nullptr == mp) {
                    // add a new merged param to set
                    insert(param.getName(), param.getValue());
                }
                else {
                    mp->merge(param.getValue());
                }
            }
            // After processing paramSet, run through the accumulated merged
            // params and set the full share flags as needed. Must be a
            // post-processing step to be sure flags are correct.
            for (GgMergedParam &mp : params()) {
                if (mp.isFullShare() && (mp.getMergeCnt() != mergedSetCnt_)) {
                    mp.setFullShare(false);
                }
            }
        }
    }


protected:
    friend std::ostream& operator<<(std::ostream& os, const GgMergedParamSet &p);


private:
    size_t  mergedSetCnt_;
};

using GgMergedParamSetArray1 = std::vector<GgMergedParamSet>;


std::ostream& operator<<(std::ostream& os, const GgMergedParamSet &p)
{
    os << "{GgParamSetBase:" << static_cast<const GgMergedParamSet::BaseType&>(p) <<
          ", mergedSetCnt:" << utils::Quote(p.mergedSetCnt_); os << "}";
    return os;
}

#endif // GGMERGEDPARAMSET_H
