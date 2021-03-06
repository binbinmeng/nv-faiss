# configure cuda

find_package(CUDA QUIET REQUIRED)
if(CUDA_FOUND)
    include_directories(SYSTEM ${CUDA_INCLUDE_DIRS})
    list(APPEND CUDA_LINKER_LIBS ${CUDA_CUDART_LIBRARY} ${CUDA_curand_LIBRARY} ${CUDA_CUBLAS_LIBRARIES})
else(CUDA_FOUND)
    message(STATUS "Could not locate cuda, disabling cuda support.")
    set(BUILD_WITH_GPU OFF)
    return()
endif(CUDA_FOUND)

# set cuda flags
LIST(APPEND CUDA_NVCC_FLAGS --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_52,code=sm_52)
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#    list(APPEND CUDA_NVCC_FLAGS "-arch=sm_60;-std=c++11;-DVERBOSE;-g;-lineinfo;-Xcompiler;-ggdb")
#else()
#    list(APPEND CUDA_NVCC_FLAGS "-arch=sm_60;-std=c++11;-DVERBOSE;-O3;-DNDEBUG;-Xcompiler;-DNDEBU")
#endif()
set(CUDA_PROPAGATE_HOST_FLAGS OFF)
