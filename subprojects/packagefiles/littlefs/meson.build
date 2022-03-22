project('littlefs', 'c')

littlefs_inc = include_directories('.')

littlefs_src = ['lfs.c']

littlefs = static_library('littlefs',
                          littlefs_src,
                          include_directories : littlefs_inc,
                          install : false)

littlefs_dep = declare_dependency(include_directories : littlefs_inc,
                                  link_with : littlefs)
