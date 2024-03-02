#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <vector>
#include <stdint.h>

#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/assign.hpp>

namespace rasterizerlib
{
    // boost geometry
    typedef boost::geometry::model::d2::point_xy<double> bg_point_xy;
    typedef boost::geometry::model::linestring<bg_point_xy> bg_linestring;
    typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > bg_polygon;

    // custom
    struct point2d
    {
        double x,y;
    };

    struct mbr2d
    {
        point2d minPoint, maxPoint;
    };

    enum rasterDataTypeE
    {
        RD_CELL,
        RD_INTERVAL
    };

    struct id_set
    {
        std::vector<uint32_t> listA;
        std::vector<uint32_t> listB;
    };

    struct raster_data
    {
        uint32_t minCellX, minCellY, maxCellX, maxCellY;
        uint32_t bufferWidth, bufferHeight;
        rasterDataTypeE type;
        id_set data;        // based on type, it either holds intervals (pairs of uint32_t ids) or cells (uin32_t ids)
    };

    struct polygon2d
    {
        std::vector<point2d> vertices;
        mbr2d mbr;
        bg_polygon bgPolygon;
        raster_data rasterData;
    };

    typedef enum CellType
    {
        EMPTY,
        UNCERTAIN,
        PARTIAL,
        FULL,
    } CellTypeE;

}

#endif