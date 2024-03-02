#ifndef DEF_H
#define DEF_H

#include "datatypes.h"

#include <cmath>
#include <cstdio>
#include <string>
#include <algorithm>
#include <limits>

namespace rasterizerlib
{
    typedef enum CellEnumerationType{
        CE_HILBERT,
    }CellEnumerationTypeE;

    typedef enum RasterizerMethod{
        RM_RASTERIZATION,
        RM_INTERVALIZATION,
    }RasterizerMethodE;

    typedef struct config
    {
        // init
        bool lib_init = false;

        // dataspace related
        double xMin, yMin, xMax, yMax;

        // rasterization related
        RasterizerMethodE method = RM_INTERVALIZATION;
        CellEnumerationTypeE celEnumType = CE_HILBERT;
        bool isGridSymmetrical = true;      // number of cells on X and Y axis is the same
        bool areCellsSquare;                // the cells of the grid are square (instead of rectangle)

        // for hilbert
        uint32_t orderN = 16;
        uint32_t cellsPerDim = pow(2,16);

    }configT;

    extern configT g_config;
    
    void setDataspace(double xMin, double yMin, double xMax, double yMax);
    
    polygon2d createPolygon(std::vector<point2d> &vertices);

    void init(double xMin, double yMin, double xMax, double yMax);

    void setMethod(RasterizerMethodE method);

    void log_err(std::string errorText);

    
    void printConfig();
}



#endif