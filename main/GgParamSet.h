#ifndef GGPARAMSET_H
#define GGPARAMSET_H

#include <iostream>
#include <string>
#include <vector>

#include "GgParam.h"
#include "GgParamSetBase.h"


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
using GgParamSet = GgParamSetBase<GgParam>;
using GgParamSetArray1 = std::vector<GgParamSet>;

#endif // GGPARAMSET_H
