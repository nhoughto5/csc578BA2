set(SHADER_SOURCE
	"${LAGRANGE_SHADER_ROOT}/structure.fs.glsl"
	"${LAGRANGE_SHADER_ROOT}/structure.vs.glsl"
    "${LAGRANGE_SHADER_ROOT}/swing.fs.glsl"
    "${LAGRANGE_SHADER_ROOT}/swing.vs.glsl")

set_source_files_properties(${SHADER_SOURCE} 
    PROPERTIES HEADER_FILE_ONLY TRUE)

set(SHADER_INCLUDE "${LAGRANGE_GENERATED_ROOT}/ShaderPaths.hpp")

configure_file(
    "${LAGRANGE_SHADER_ROOT}/ShaderPaths.hpp.in"
    ${SHADER_INCLUDE})

set(SHADER_LIST
    ${SHADER_SOURCE}
    ${SHADER_INCLUDE}
    PARENT_SCOPE)

