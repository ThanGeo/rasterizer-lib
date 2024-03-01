# rasterizer-lib
A portable polygon rasterization library

## Requirements
- Boost Geometry

## Version 1.0.0
- supports direct build of the APRIL approximation for polygons
- identifies Partial (<100% coverage with polygon) and Full (100% covered by polygon) cells

## Build
'''
mkdir build
cd build
cmake ..
make
'''
Make sure to include Rasterizer in your cmake file

### APRIL
Method described in paper "APRIL: Approximating Polygons as Raster Interval Lists" (paper link: https://arxiv.org/abs/2307.01716)