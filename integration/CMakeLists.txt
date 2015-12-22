find_package(Qt5Core REQUIRED)

set(ANGELSCRIPT_INTEGRATION_SOURCE
  include/angelscript-integration/angelscript-integration.h
  src/angelscript-integration/angelscript-integration.cpp
)

add_library(angelscript-interaction ${ANGELSCRIPT_INTEGRATION_SOURCE})

target_include_directories(angelscript-interaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(angelscript-interaction ${ANGELSCRIPT_TARGET} Qt5::Core)
target_compile_options(angelscript-interaction PUBLIC -std=c++11)
