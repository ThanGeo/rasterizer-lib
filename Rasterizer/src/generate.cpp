#include "generate.h"


namespace rasterizerlib
{
    

    void generate(polygon2d &polygon, GenerateTypeE generateType) {
        // choose based on config and generate type
        if (generateType >= GT_APRIL_BEGIN && generateType < GT_APRIL_END) {
            // APRIL
            switch (generateType) {
                case GT_APRIL:
                    // complete APRIL
                    intervalizationBegin(polygon);
                    break;
                case GT_APRIL_ALL_ONLY:
                    // only ALL intervals of APRIL
                    break;
            }
        } else if (generateType >= GT_RASTER_BEGIN && generateType < GT_RASTER_END) {
            // RASTER
            switch (generateType) {
                case GT_RASTER:
                    // complete raster 
                    rasterizationBegin(polygon);
                    break;
                case GT_RASTER_PARTIAL_ONLY:
                    // only partial cell rasterization
                    break;
            }
        } else {
            // unknown generate type
            log_err("Unknown generate type.");
            return;
        }
    }
}