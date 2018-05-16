
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build each source file independently
include_directories(../../)	# faiss root directory

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
    cuda_add_executable(${name} ${source})
    target_link_libraries(${name} ${faiss_lib_gpu} ${faiss_lib} ${BLAS_LIB} ${GTEST_BOTH_LIBRARIES} ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES} gtest gflags)

    # Install
    install(TARGETS ${name} DESTINATION test)
endforeach(source)
