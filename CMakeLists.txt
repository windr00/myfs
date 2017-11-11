cmake_minimum_required(VERSION 3.8)
project(myfs)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test/test.c imp/myfile.h imp/myfile.c imp/dentry.h imp/inode.h imp/dirdata.h imp/foperator.h imp/fs.h imp/fsop.c imp/inode.c)
add_executable(myfs ${SOURCE_FILES})