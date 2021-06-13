add_library(cstring cstring.c allocator.c number.c)
set_target_properties(cstring PROPERTIES PUBLIC_HEADER
                                         ../include/cstring/cstring.h)
install(TARGETS cstring DESTINATION "${CMAKE_INSTALL_BINDIR}")
