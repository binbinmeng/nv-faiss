
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cu)

# Build each source file independently
include_directories(../../)	# faiss root directory
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../test)
#file(GLOB src_files ${CMAKE_CURRENT_SOURCE_DIR}../test/*)

#set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-9.0")
include(FindCUDA)

find_package(CUDA REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})
# gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

foreach(source ${srcs})
    get_filename_component(name ${source} NAME_WE)

    # target
    cuda_add_executable(${name} ${source})# ${src_files})
    target_link_libraries(${name} ${faiss_lib_gpu} ${faiss_lib} ${BLAS_LIB} ${GTEST_BOTH_LIBRARIES} ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} gtest gflags)

    # Install
    install(TARGETS ${name} DESTINATION test)
endforeach(source)
