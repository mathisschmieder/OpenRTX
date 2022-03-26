project('littlefs', 'c')

littlefs_inc = include_directories(['.', 'bd'])

littlefs_src = ['lfs.c',
                'lfs_util.c',
                'bd/lfs_filebd.c',
                'bd/lfs_rambd.c',
                'bd/lfs_testbd.c']

littlefs = static_library('littlefs',
                          littlefs_src,
                          include_directories : littlefs_inc,
                          install : false)

littlefs_dep = declare_dependency(include_directories : littlefs_inc,
                                  link_with : littlefs)
