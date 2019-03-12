add_executable(fast_memcpy memcpy.cpp test_memcpy.cpp)
set_property(TARGET fast_memcpy PROPERTY COMPILE_FLAGS "${NT2_FLAGS} -fno-builtin-memcpy")

add_executable(fast_memcpy_inline test_memcpy.cpp)
set_property(TARGET fast_memcpy_inline PROPERTY COMPILE_FLAGS "${NT2_FLAGS} -fno-builtin-memcpy -DMEMCPY_INLINE")
