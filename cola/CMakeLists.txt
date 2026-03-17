
set(COMMON_COMPILE_DEFINITIONS
    # $<$<PLATFORM_ID:Windows>:_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS>
    $<$<PLATFORM_ID:Windows>:_CRT_SECURE_NO_WARNINGS>
    # $<$<PLATFORM_ID:Windows>:LIBAVOID_NO_DLL>
    # $<$<PLATFORM_ID:Windows>:_WIN32_WINNT=0x0501>
    $<$<PLATFORM_ID:Windows>:_USE_MATH_DEFINES>

    $<$<PLATFORM_ID:Windows>:NOMINMAX>
    # LIBAVOID_EXPORTS and _USRDLL are PRIVATE to libavoid only - see cola/libavoid/CMakeLists.txt
)

add_subdirectory(libvpsc)
add_subdirectory(libavoid)
add_subdirectory(libcola)
add_subdirectory(libproject)
add_subdirectory(libtopology)
add_subdirectory(libdialect)
