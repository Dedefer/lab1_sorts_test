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
    static void generateLog(std::ostream&, std::size_t, std::size_t);

    template <class SequenceType>
    static void generateLogForOneSort(std::ostream&, std::string, std::size_t, std::size_t);


private:
    template<class SequenceType>
    static Sequence<int>* generateRandomSequence(std::size_t);

    constexpr static double computeInterval(std::clock_t, std::clock_t);

};

template <class SequenceType>
void SequenceSortsTester::generateLog(std::ostream& outputStream, std::size_t max, std::size_t step) {
    outputStream << "{size}\t{shakerSort time}\t{shellSort time}\t{countingSort time}\n";
    std::unique_ptr<Sequence<int>> sortedPtr;
    for (auto size = 0; size <= max; size += step) {
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
Sequence<int>* SequenceSortsTester::generateRandomSequence(std::size_t length) {
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

template<class SequenceType>
void SequenceSortsTester::generateLogForOneSort(std::ostream& outputStream, std::string sort, std::size_t max, std::size_t step) {
    if (sort == "shell") {
        outputStream << "{size}\t{time}\n";
        std::unique_ptr<Sequence<int>> sortedPtr;
        for (auto size = 0; size <= max; size += step) {
            outputStream << size << '\n';
            std::unique_ptr<Sequence<int>> seqPtr{generateRandomSequence<SequenceType>(size)};

            auto time1 = std::clock();
            sortedPtr.reset(SequenceSorts<int>::shellSort(seqPtr.get(), exampleFunctionsForSort::cmp, exampleFunctionsForSort::stepFunc));
            auto time2 = std::clock();
            outputStream << computeInterval(time1, time2) << '\t';
            sortedPtr.reset(nullptr);
        }
    } else if (sort == "shaker") {
        outputStream << "{size}\t{time}\n";
        std::unique_ptr<Sequence<int>> sortedPtr;
        for (auto size = 0; size <= max; size += step) {
            outputStream << size << '\n';
            std::unique_ptr<Sequence<int>> seqPtr{generateRandomSequence<SequenceType>(size)};

            auto time1 = std::clock();
            sortedPtr.reset(SequenceSorts<int>::shakerSort(seqPtr.get(), exampleFunctionsForSort::cmp));
            auto time2 = std::clock();
            outputStream << computeInterval(time1, time2) << '\t';
            sortedPtr.reset(nullptr);
        }
    } else if (sort == "counting") {
        outputStream << "{size}\t{time}\n";
        std::unique_ptr<Sequence<int>> sortedPtr;
        for (auto size = 0; size <= max; size += step) {
            outputStream << size << '\n';
            std::unique_ptr<Sequence<int>> seqPtr{generateRandomSequence<SequenceType>(size)};

            auto time1 = std::clock();
            sortedPtr.reset(SequenceSorts<int>::countingSort(seqPtr.get()));
            auto time2 = std::clock();
            outputStream << computeInterval(time1, time2) << '\t';
            sortedPtr.reset(nullptr);
        }
    } else {throw std::logic_error("wrong sort type");}
}


#endif //LAB1_SORTS_TEST_SEQUENCESORTSTESTER_H
