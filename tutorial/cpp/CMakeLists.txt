file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build each source file independently
include_directories(../../../)	# faiss root directory

set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-9.0")
include(FindCUDA)

find_package(CUDA REQUIRED)

include_directories(${CUDA_INCLUDE_DIRS})

foreach(source ${srcs})
    get_filename_component(name ${source} NAME_WE)

    # target
    add_executable(${name} ${source})
    target_link_libraries(${name} /workspace/faiss/build/lib/libgpufaiss.a /workspace/faiss/build/lib/libfaiss.a ${faiss_lib}  ${CUDA_LIBRARIES} ${CUDA_CUBLAS_LIBRARIES}) 

    # Install
    install(TARGETS ${name} DESTINATION bin)
endforeach(source)
