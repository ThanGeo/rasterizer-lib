#include "rasterization.h"

#include <iostream>

namespace rasterizerlib
{
    static inline bool checkY(double &y1, double &OGy1, double &OGy2, uint32_t &startCellY, uint32_t &endCellY){
        if(OGy1 < OGy2){
            return (startCellY <= y1 && y1 <= endCellY + 1);
        }else{
            return (endCellY <= y1 && y1 <= startCellY + 1);
        }
    }

    uint32_t** calculatePartialAndUncertain(polygon2d &polygon, uint32_t &cellsPerDim){
        //create empty matrix
        uint32_t **M = new uint32_t*[polygon.rasterData.bufferWidth]();
        for(uint32_t i=0; i<polygon.rasterData.bufferWidth; i++){
            M[i] = new uint32_t[polygon.rasterData.bufferHeight]();		
            for(uint32_t j=0; j<polygon.rasterData.bufferHeight; j++){
                M[i][j] = UNCERTAIN;
            }
        }

        // local scope variables
        uint32_t startCellX, startCellY, endCellX, endCellY;;
        uint32_t currentCellX, currentCellY;
        double x1, y1, x2, y2;
        double ogy1, ogy2;
        int stepX, stepY;
        uint32_t verticalStartY, verticalEndY, horizontalY;
        double tMaxX, tMaxY;
        double tDeltaX, tDeltaY;
        double edgeLength;
        std::deque<bg_point_xy> output;
        double error_margin = 0.00001;

        //loop points
        for (auto it = polygon.vertices.begin(); it != polygon.vertices.end()-1; it++) {
            //set points x1 has the lowest x
            if(it->x < (it+1)->x){
                x1 = it->x;
                y1 = it->y;
                x2 = (it+1)->x;
                y2 = (it+1)->y;
            }else{
                x2 = it->x;
                y2 = it->y;
                x1 = (it+1)->x;
                y1 = (it+1)->y;
            }

            //keep original values of y1,y2
            ogy1 = y1;
            ogy2 = y2;	

            //set endpoint hilbert cells
            startCellX = (int)x1;
            startCellY = (int)y1;
            endCellX = (int)x2;
            endCellY = (int)y2;

            if(startCellX == endCellX && startCellY == endCellY){
                //label the cell in the partially covered matrix
                M[startCellX-polygon.rasterData.minCellX][startCellY-polygon.rasterData.minCellY] = PARTIAL;
            }else{
                //set step (based on direction)
                stepX = x2 > x1 ? 1 : -1;
                stepY = y2 > y1 ? 1 : -1;

                //define the polygon edge
                bg_linestring ls{{x1, y1},{x2, y2}};
                edgeLength = boost::geometry::length(ls);

                //define NEAREST VERTICAL grid line
                bg_linestring vertical{{startCellX+1, 0},{startCellX+1, cellsPerDim}};
                
                //define NEAREST HORIZONTAL grid line
                y1 < y2 ? horizontalY = int(y1) + 1 : horizontalY = int(y1);
                bg_linestring horizontal{{0, horizontalY},{cellsPerDim, horizontalY}};

                //get intersection points with the vertical and nearest lines
                boost::geometry::intersection(ls, vertical, output);
                bg_point_xy intersectionPointVertical = output[0];
                output.clear();
                boost::geometry::intersection(ls, horizontal, output);
                bg_point_xy intersectionPointHorizontal = output[0];
                output.clear();

                // //keep in mind: the line segment may not intersect a vertical or horizontal line!!!!!!!!
                if(boost::geometry::distance(intersectionPointVertical, ls) <= error_margin && boost::geometry::distance(intersectionPointVertical, vertical) <= error_margin){
                    bg_linestring tXMaxline{{x1,y1},intersectionPointVertical};
                    tMaxX = boost::geometry::length(tXMaxline);
                }else{
                    tMaxX = edgeLength;
                }
                if(boost::geometry::distance(intersectionPointHorizontal, ls) <= error_margin && boost::geometry::distance(intersectionPointHorizontal, horizontal) <= error_margin){
                    bg_linestring tYMaxline{{x1,y1},intersectionPointHorizontal};
                    tMaxY = boost::geometry::length(tYMaxline);
                }else{
                    tMaxY = edgeLength;
                }

                //deltas
                tDeltaX = edgeLength / (x2 - x1);
                tDeltaY = edgeLength / abs(y2 - y1);
                
                //loop (traverse ray)
                while(startCellX <= x1 && x1 < endCellX+1 && checkY(y1, ogy1, ogy2, startCellY, endCellY)){
                    M[(int)x1-polygon.rasterData.minCellX][(int)y1-polygon.rasterData.minCellY] = PARTIAL;
                    if(tMaxX < tMaxY){
                        x1 = x1 + stepX;
                        tMaxX = tMaxX + tDeltaX;
                    }else{
                        y1 = y1 + stepY;
                        tMaxY = tMaxY + tDeltaY;
                    }
                }
            }
        }
        return M;
    }


    






    

} 
