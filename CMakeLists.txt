cmake_minimum_required(VERSION 3.8)
project(myfs)

set(CMAKE_CXX_STANDARD 11)

set(HEADER declare/dentry.h
        declare/dirdata.h
        declare/errnum.h
        declare/foperator.h
        declare/fs.h
        declare/inode.h
        declare/myfile.h
        )

set(IMPL imp/fsop.c
        imp/inode.c
        imp/myfile.c)

set(TEST test/test.c)

add_library(myfs ${HEADER} ${IMPL})

add_executable(myfs_test ${TEST})
target_link_libraries(myfs_test myfs)
