#ifndef GGMERGEDPARAM_H
#define GGMERGEDPARAM_H

#include <iostream>
#include <string>
#include <vector>

#include "GgParam.h"


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class GgMergedParam : public GgParam {

    using UniqueVals = std::vector<std::string>;

public:
    GgMergedParam(const std::string &name = "", const std::string &val = "") :
        GgParam(name, val),
        fullShare_(true), // Assume full share. Controlled by GgMergedParamSet
        mergeCnt_(0),
        unique_()
    {
        merge(val);
    }

    ~GgMergedParam()
    {
    }


    void merge(const std::string &val)
    {
        if (1 == ++mergeCnt_) {
            setValue(val); // first value
            unique_.push_back(val);
        }
        else if (unique_.end() == find(unique_.begin(), unique_.end(), val)) {
            setValue(""); // clear it - 2 or more ambiguous values!
            unique_.push_back(val);
        }
    }


    inline bool                 isAmbiguous() const {
                                    return 1 != unique_.size(); }


    inline bool                 isUniform() const {
                                    return !isAmbiguous(); }


    inline size_t               getMergeCnt() const {
                                    return mergeCnt_; }


    inline const UniqueVals&    getUniqueValues() const {
                                    return unique_; }


    inline size_t               getUniqueValueCnt() const {
                                    return unique_.size(); }


    inline void                 setFullShare(const bool full) {
                                    fullShare_ = full; }


    inline bool                 isFullShare() const {
                                    return fullShare_; }


    inline bool                 isPartialShare() const {
                                    return !isFullShare(); }


protected:
    friend std::ostream& operator<<(std::ostream& os, const GgMergedParam &p);


private:
    bool        fullShare_; // true if is defined by all merged param sets
    size_t      mergeCnt_;  // Total number of values merged
    UniqueVals  unique_;    // subset of merged values that are unique
};

using GgMergedParamArray1 = std::vector<GgMergedParam>;


std::ostream& operator<<(std::ostream& os, const GgMergedParam &p)
{
    const char *pfx = "";
    os << "{GgParam:" << static_cast<const GgParam&>(p) <<
        ", fullShare:" << std::boolalpha << utils::Quote(p.fullShare_) <<
        ", mergeCnt:" << utils::Quote(p.mergeCnt_) <<
        ", unique:[";
    for (const auto &uval : p.unique_) {
        os << pfx << utils::Quote(uval);
    }
    os << "]}";
    return os;
}

#endif  // GGMERGEDPARAM_H
