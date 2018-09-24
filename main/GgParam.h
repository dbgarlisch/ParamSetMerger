#ifndef GGPARAM_H
#define GGPARAM_H

#include <iostream>
#include <string>
#include <vector>

#include "utils.h"


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

class GgParam {
public:
    GgParam(const std::string &name = "", const std::string &val = "") :
        name_(utils::trim(name)),
        val_(val)
    {
    }

    ~GgParam()
    {
    }

    void                setName(const std::string &name) {
                            name_ = name; }

    const std::string&  getName() const {
                            return name_; }

    void                setValue(const std::string &val) {
                            val_ = val; }

    const std::string&  getValue() const {
                            return val_; }


protected:
    friend std::ostream& operator<<(std::ostream& os, const GgParam &p);


private:
    std::string name_;
    std::string val_;
};

using GgParamArray1 = std::vector<GgParam>;


std::ostream& operator<<(std::ostream& os, const GgParam &p)
{
    return os << "{name:\"" << p.name_ << "\", value:\"" << p.val_ << "\"}";
}

#endif  // GGPARAM_H
