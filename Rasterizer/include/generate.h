#ifndef GENERATE_H
#define GENERATE_H

#include "def.h"
#include "rasterization.h"
#include "intervalization.h"

namespace rasterizerlib
{
    void generate(polygon2d &polygon, GenerateTypeE generateType);
}

#endif