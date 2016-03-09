#================================
# Directory variables.
#================================
set(LAGRANGE_ROOT "${ANIM_SOURCE_DIR}/Lagrange")
set(LAGRANGE_INCLUDE_ROOT "${LAGRANGE_ROOT}/include")
set(LAGRANGE_SOURCE_ROOT "${LAGRANGE_ROOT}/source")
set(LAGRANGE_SHADER_ROOT "${LAGRANGE_ROOT}/shaders")
set(LAGRANGE_GENERATED_ROOT "${LAGRANGE_ROOT}/generated")

#================================
# Add subdirectories.
#================================
add_subdirectory(${LAGRANGE_INCLUDE_ROOT})
add_subdirectory(${LAGRANGE_SOURCE_ROOT})
add_subdirectory(${LAGRANGE_SHADER_ROOT})

#================================
# Include directories.
#================================
include_directories(
    ${ATLAS_INCLUDE_DIRS}
    ${LAGRANGE_INCLUDE_ROOT}
    ${LAGRANGE_GENERATED_ROOT})

#================================
# Source groups.
#================================
source_group("include" FILES ${INCLUDE_LIST})
source_group("source" FILES ${SOURCE_LIST})
source_group("shaders" FILES ${SHADER_LIST})

add_executable(Lagrange ${SOURCE_LIST} ${INCLUDE_LIST} ${SHADER_LIST})
target_link_libraries(Lagrange ${ATLAS_LIBRARIES})

