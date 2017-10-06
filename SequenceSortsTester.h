//
// Created by ddf19 on 07.10.2017.
//

#ifndef LAB1_SORTS_TEST_SEQUENCESORTSTESTER_H
#define LAB1_SORTS_TEST_SEQUENCESORTSTESTER_H


#include <memory>
#include <ostream>
#include "SequenceSorts.h"
#include "Sequence.h"
#include "ListSequence.h"
#include "ArraySequence.h"
#include <cstdlib>
#include <ctime>

class SequenceSortsTester {
public:
    template <class SequenceType>
    static void generateLog(std::ostream&, int, int);

private:
    template<class SequenceType>
    static Sequence<int>* generateRandomSequence(int);

    constexpr static double computeInterval(std::clock_t, std::clock_t);

};

template <class SequenceType>
void SequenceSortsTester::generateLog(std::ostream& outputStream, int max, int step) {
    outputStream << "{size}\t{shakerSort time}\t{shellSort time}\t{countingSort time}\n";
    std::unique_ptr<Sequence<int>> sortedPtr;
    for (int size = 0; size <= max; size += step) {
        outputStream << size << '\t';
        std::unique_ptr<Sequence<int>> seqPtr{generateRandomSequence<SequenceType>(size)};

        auto time1 = std::clock();
        sortedPtr.reset(SequenceSorts<int>::shakerSort(seqPtr.get(), exampleFunctionsForSort::cmp));
        auto time2 = std::clock();
        outputStream << computeInterval(time1, time2) << '\t';
        sortedPtr.reset(nullptr);

        time1 = std::clock();
        sortedPtr.reset(SequenceSorts<int>::shellSort(seqPtr.get(), exampleFunctionsForSort::cmp, exampleFunctionsForSort::stepFunc));
        time2 = std::clock();
        outputStream << computeInterval(time1, time2) << '\t';
        sortedPtr.reset(nullptr);

        time1 = std::clock();
        sortedPtr.reset(SequenceSorts<int>::countingSort(seqPtr.get()));
        time2 = std::clock();
        outputStream << computeInterval(time1, time2) << std::endl;
        sortedPtr.reset(nullptr);
    }
}

template<class SequenceType>
Sequence<int>* SequenceSortsTester::generateRandomSequence(int length) {
    std::srand(std::time(nullptr));
    std::unique_ptr<Sequence<int>> tempPtr{new SequenceType};
    for (auto i = 0; i < length; ++i) {
        tempPtr -> append(std::rand()%std::numeric_limits<int>::max());
    }
    return tempPtr.release();
}

constexpr double SequenceSortsTester::computeInterval(std::clock_t time1, std::clock_t time2) {
    return 1000.0*(time2 - time1)/CLOCKS_PER_SEC;
}


#endif //LAB1_SORTS_TEST_SEQUENCESORTSTESTER_H
