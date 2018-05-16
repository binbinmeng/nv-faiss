list(APPEND srcs
    ${CMAKE_CURRENT_SOURCE_DIR}/demo_ivfpq_indexing_gpu.cpp)

#set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-9.0")
include(FindCUDA)

find_package(CUDA REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})

foreach(source ${srcs})
    get_filename_component(name ${source} NAME_WE)
    cuda_add_executable(${name} ${source})
    target_link_libraries(${name}  ${faiss_lib_gpu} ${faiss_lib} ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES})
endforeach(source)
