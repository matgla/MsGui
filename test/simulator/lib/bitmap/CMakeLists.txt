file(GLOB_RECURSE bitmap_srcs
    "bitmap/*.hpp"
    "bitmap/*.h"
)

set(BITMAP_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/test/simulator/lib/bitmap" CACHE STRING "path to Bitmap library sources" FORCE)
add_library(bitmap INTERFACE)
target_sources(bitmap INTERFACE ${bitmap_srcs})
target_include_directories(bitmap INTERFACE ${BITMAP_INCLUDE_DIR})

message("Bitmap library path: ${BITMAP_INCLUDE_DIR}")