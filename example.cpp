#include <Rasterizer.h>

int main(){
    // init dataspace with default settings
    rasterizerlib::init(-500,-400, 500, 400);

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
    printf("%d ALL intervals: \n", polygon.rasterData.allIntervals.size()/2);
    for(int i=0; i<polygon.rasterData.allIntervals.size()-1; i+=2) {
        printf("    [%d,%d)\n", polygon.rasterData.allIntervals.at(i), polygon.rasterData.allIntervals.at(i+1));
    }

    printf("%d FULL intervals: \n", polygon.rasterData.fullIntervals.size()/2);
    for(int i=0; i<polygon.rasterData.fullIntervals.size()-1; i+=2) {
        printf("    [%d,%d)\n", polygon.rasterData.fullIntervals.at(i), polygon.rasterData.fullIntervals.at(i+1));
    }

    return 0;
}