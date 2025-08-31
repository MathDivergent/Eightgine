set(CORE_SRCS
    lapi.c lcode.c lctype.c ldebug.c ldo.c ldump.c lfunc.c lgc.c llex.c lmem.c
    lobject.c lopcodes.c lparser.c lstate.c lstring.c ltable.c ltm.c lundump.c
    lvm.c lzio.c
)

set(LIB_SRCS
    lauxlib.c lbaselib.c lcorolib.c ldblib.c liolib.c lmathlib.c loadlib.c loslib.c
    lstrlib.c ltablib.c lutf8lib.c linit.c
)

set(LUA_SRCS ${CORE_SRCS} ${LIB_SRCS})

add_library(lua ${LUA_SRCS})

set_target_properties(lua PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

if(BUILD_SHARED_LIBS)
    if(WIN32)
        add_compile_definitions(LUA_BUILD_AS_DLL)
        set_target_properties(lua PROPERTIES
            WINDOWS_EXPORT_ALL_SYMBOLS ON
        )
    endif()
endif()

if(LINUX)
    target_compile_definitions(lua PRIVATE LUA_USE_LINUX)
elseif(APPLE)
    target_compile_definitions(lua PRIVATE LUA_USE_MACOSX)
endif()
