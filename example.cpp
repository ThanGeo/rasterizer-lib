#include <Rasterizer.h>

int main(){
    // init dataspace with default settings
    rasterizerlib::init(-500,-400, 500, 400);

    // set rasterization method to return raster cells instead of default intervals
    rasterizerlib::setMethod(rasterizerlib::RM_RASTERIZATION);

    // print configuration
    rasterizerlib::printConfig();

    // create list of points
    std::vector<rasterizerlib::point2d> vertices;
    rasterizerlib::point2d p;
    p.x = -200.83735;
    p.y = -100.83464;
    vertices.emplace_back(p);
    p.x = -200.84574;
    p.y = -100.89238;
    vertices.emplace_back(p);
    p.x = -200.89687;
    p.y = -100.87333;
    vertices.emplace_back(p);
    p.x = -200.84587;
    p.y = -100.83366;
    vertices.emplace_back(p);
    p.x = -200.83735;
    p.y = -100.63464;
    vertices.emplace_back(p);

    // create a polygon
    rasterizerlib::polygon2d polygon = rasterizerlib::createPolygon(vertices);

    // generate the raster based on the configuration
    rasterizerlib::generate(polygon);

    // print
    printf("%ld ALL intervals: \n", polygon.rasterData.data.listA.size()/2);
    for(int i=0; i<polygon.rasterData.data.listA.size()-1; i+=2) {
        printf("    [%u,%u)\n", polygon.rasterData.data.listA.at(i), polygon.rasterData.data.listA.at(i+1));
    }

    printf("%ld FULL intervals: \n", polygon.rasterData.data.listB.size()/2);
    for(int i=0; i<polygon.rasterData.data.listB.size()-1; i+=2) {
        printf("    [%u,%u)\n", polygon.rasterData.data.listB.at(i), polygon.rasterData.data.listB.at(i+1));
    }

    return 0;
}