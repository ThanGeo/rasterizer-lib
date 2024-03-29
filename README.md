# rasterizer-lib
A portable polygon rasterization library

## Description
Polygons are rasterized using a global grid of pre-defined granularity. The grid is overlayed in a pre-defined data-space.

## Requirements
- Boost Geometry

## Version 1.0.0
- supports direct build of the APRIL approximation for polygons
- supports cell-based rasterization instead of APRIL intervals for polygons
    - allows the generation of only the partial cells if needed
- identifies Partial (<100% coverage with polygon) and Full (100% covered by polygon) cells
- uses a 2^N x 2^N grid, where cells are enumarated by the Hilbert Curve

## Build
```
mkdir build
cd build
cmake ..
make
```
Make sure to include Rasterizer in your cmake file

### APRIL
Method described in paper "APRIL: Approximating Polygons as Raster Interval Lists" (paper link: https://arxiv.org/abs/2307.01716)