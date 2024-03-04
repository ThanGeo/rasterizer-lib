#include <Rasterizer.h>

int main(){
    // init dataspace with default settings
    rasterizerlib::init(-500,-400, 500, 400);

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

    // generate the raster
    rasterizerlib::generate(polygon, rasterizerlib::GT_RASTER);

    // print
    // todo: draw for double check
    printf("%ld Partial cells: \n", polygon.rasterData.data.listA.size());
    for(int i=0; i<polygon.rasterData.data.listA.size(); i++) {
        printf("%u,", polygon.rasterData.data.listA.at(i));
    }
    printf("\n");

    printf("%ld Full cells: \n", polygon.rasterData.data.listB.size());
    for(int i=0; i<polygon.rasterData.data.listB.size(); i++) {
        printf("%u,", polygon.rasterData.data.listB.at(i));
    }
    printf("\n");

    return 0;
}