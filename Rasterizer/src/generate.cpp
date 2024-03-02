#include "generate.h"


namespace rasterizerlib
{
    

    void generate(polygon2d &polygon) {
        // choose based on config
        switch (g_config.method) {
            case (RM_INTERVALIZATION):
                intervalizationBegin(polygon);
                return;
            case (RM_RASTERIZATION):
            
                return;
        }
    }
}