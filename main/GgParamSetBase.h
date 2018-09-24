#ifndef GGPARAMSETBASE_H
#define GGPARAMSETBASE_H

#include <iostream>
#include <string>
#include <vector>


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

template< typename ParamT_ >
class GgParamSetBase {
public:
    using ParamType     = ParamT_;
    using ParamVecType  = std::vector<ParamT_>;

public:
    GgParamSetBase(const std::string &name = "") :
        name_(name)
    {
    }

    ~GgParamSetBase()
    {
    }

    void const          setName(const std::string &name) {
                            name_ = name; }

    const std::string&  getName() const {
                            return name_; }

    const size_t        size() const {
                            return params_.size(); }

    const bool          empty() const {
                            return params_.empty(); }


    ParamT_* find(const std::string &paramName) {
        ParamT_* ret = nullptr;
        for (ParamT_ &param : params_) {
            if (paramName == param.getName()) {
                ret = &param;
                break;
            }
        }
        return ret;
    }


    const ParamT_* find(const std::string &paramName) const {
        const ParamT_* ret = nullptr;
        for (const ParamT_ &param : params_) {
            if (paramName == param.getName()) {
                ret = &param;
                break;
            }
        }
        return ret;
    }


    const bool find(const std::string &paramName, ParamT_ &param) const {
        const ParamT_ *p = find(paramName);
        return (nullptr == p) ? false : ((param = *p), true);
    }


    bool insert(const ParamT_ &param) {
        const ParamT_ *p = find(param.getName());
        if (nullptr == p) {
            params_.push_back(param);
        }
        return nullptr == p;
    }


    bool insert(const std::string &paramName, const std::string &val) {
        return insert(ParamT_(paramName, val));
    }


    ParamVecType &          params() {
                                return params_; }


    const ParamVecType &    params() const {
                                return params_; }


protected:
    template< typename ParamT_ >
    friend std::ostream& operator<<(std::ostream& os,
        const GgParamSetBase<ParamT_> &ps);


private:
    std::string     name_;
    ParamVecType    params_;
};


template< typename ParamT_ >
inline std::ostream&
operator<<(std::ostream& os, const GgParamSetBase<ParamT_> &ps)
{
    const char *pfx = "";
    os << "{name:" << utils::Quote(ps.name_) << ", params:[";
    for (const auto &param : ps.params_) {
        os << pfx << "\n  " << param;
        pfx = ",";
    }
    os << "]}";
    return os;
}

#endif // GGPARAMSETBASE_H
