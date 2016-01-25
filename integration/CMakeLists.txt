find_package(Qt5Core 5.5 REQUIRED)

include(files.cmake)

add_library(angelscript-interaction ${SOURCE_FILES})

target_include_directories(angelscript-interaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(angelscript-interaction ${ANGELSCRIPT_TARGET} Qt5::Core angelscript-addons glm)
target_compile_definitions(angelscript-interaction PUBLIC
    GLM_FORCE_RADIANS
    GLM_SWIZZLE
)
target_compile_options(angelscript-interaction PUBLIC
  -std=c++11
  -Wall
  -Wextra
)
