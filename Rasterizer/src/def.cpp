#include "def.h"


namespace rasterizerlib
{
    configT g_config;
    
    void setDataspace(double xMin, double yMin, double xMax, double yMax){
        if (xMin >= xMax) {
            log_err("xMax can't be smaller than xMmin");
            return;
        }
        if (yMin >= yMax) {
            log_err("yMax can't be smaller than yMmin");
            return;
        }
        
        g_config.xMin = xMin;
        g_config.yMin = yMin;
        g_config.xMax = xMax;
        g_config.yMax = yMax;

        if (xMax - yMin != yMax - yMin) {
            g_config.areCellsSquare = false;
        } else {
            g_config.areCellsSquare = true;
        }
    }

    void printConfig() {
        printf("Dataspace MBR: (%f,%f) to (%f,%f)\n", g_config.xMin, g_config.yMin, g_config.xMax, g_config.yMax);
        switch (g_config.method) {
            case RM_INTERVALIZATION:
                printf("METHOD: INTERVALIZATION \n");
                break;
            case RM_RASTERIZATION:
                printf("METHOD: RASTERIZATION \n");
                break;
        }
        switch (g_config.celEnumType) {
            case CE_HILBERT:
                printf("CELL ENUM TYPE: HILBERT \n");
                break;
        }
    }

    void init(double xMin, double yMin, double xMax, double yMax) {

        setDataspace(xMin, yMin, xMax, yMax);

        g_config.method = RM_INTERVALIZATION;

        g_config.lib_init = true;
    }

    void log_err(std::string errorText) {
        std::string msg = "*** rasterizerlib fail: " + errorText + "\n";
        fprintf(stderr, msg.c_str());
    }

    void setMethod(RasterizerMethodE method) {
        g_config.method = method;
    }

    polygon2d createPolygon(std::vector<point2d> &vertices) {
        polygon2d polygon;
        if (vertices.size() < 3) {
            log_err("Polygon needs at least 3 points");
            return polygon;
        }
        
        polygon.vertices = vertices;
       
        polygon.mbr.minPoint.x = std::numeric_limits<int>::max();
		polygon.mbr.minPoint.y = std::numeric_limits<int>::max();
		polygon.mbr.maxPoint.x = -std::numeric_limits<int>::max();
		polygon.mbr.maxPoint.y = -std::numeric_limits<int>::max();

        for (auto &p : vertices) {
            polygon.bgPolygon.outer().push_back(bg_point_xy(p.x, p.y));

            polygon.mbr.minPoint.x = std::min(polygon.mbr.minPoint.x, p.x);
            polygon.mbr.minPoint.y = std::min(polygon.mbr.minPoint.y, p.y);
            polygon.mbr.maxPoint.x = std::max(polygon.mbr.maxPoint.x, p.x);
            polygon.mbr.maxPoint.y = std::max(polygon.mbr.maxPoint.y, p.y);
        }
        boost::geometry::correct(polygon.bgPolygon);

        return polygon;
    }
}

