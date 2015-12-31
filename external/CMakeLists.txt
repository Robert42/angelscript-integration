add_subdirectory(sdk/angelscript/projects/cmake)

if(TARGET angelscript)
  set(ANGELSCRIPT_TARGET angelscript)
else()
  set(ANGELSCRIPT_TARGET Angelscript)
endif()

target_include_directories(${ANGELSCRIPT_TARGET} PUBLIC sdk/angelscript/include)
target_compile_definitions(${ANGELSCRIPT_TARGET} PUBLIC AS_USE_NAMESPACE AS_CAN_USE_CPP11=1)
target_compile_options(${ANGELSCRIPT_TARGET} PUBLIC -std=c++11)
set(ANGELSCRIPT_TARGET ${ANGELSCRIPT_TARGET} PARENT_SCOPE)

add_library(angelscript-addons
  sdk/add_on/scriptstdstring/scriptstdstring.cpp
  sdk/add_on/scriptstdstring/scriptstdstring.h
  sdk/add_on/scriptstdstring/scriptstdstring_utils.cpp
  sdk/add_on/scriptbuilder/scriptbuilder.cpp
  sdk/add_on/scriptbuilder/scriptbuilder.h
  sdk/add_on/scriptarray/scriptarray.cpp
  sdk/add_on/scriptarray/scriptarray.h
)
target_link_libraries(angelscript-addons ${ANGELSCRIPT_TARGET})
target_include_directories(angelscript-addons PUBLIC .)
