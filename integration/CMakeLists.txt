find_package(Qt5Core REQUIRED)

include(files.cmake)

add_library(angelscript-interaction ${SOURCE_FILES})

target_include_directories(angelscript-interaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${GLM_INCLUDE_DIR})
target_link_libraries(angelscript-interaction ${ANGELSCRIPT_TARGET} Qt5::Core angelscript-addons)
target_compile_definitions(angelscript-interaction PUBLIC
    GLM_FORCE_RADIANS
    GLM_SWIZZLE
)
target_compile_options(angelscript-interaction PUBLIC
  -std=c++11
  -Wall
  -Wextra
)
