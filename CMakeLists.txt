cmake_minimum_required(VERSION 3.8)
project(lab1_sorts_test)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Sequence.h ListSequence.h ArraySequence.h SequenceSorts.h SequenceSortsTester.h)
add_executable(lab1_sorts_test ${SOURCE_FILES})