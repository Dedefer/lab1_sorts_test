#include <fstream>
#include "SequenceSortsTester.h"

int main() {
    std::fstream logFile("logForArraySequence.txt", std::ios::out);
    if (logFile) {
        SequenceSortsTester::generateLog<ArraySequence<int>>(logFile, 3000, 50);
    }
    logFile.close();

    logFile.open("logForListSequence.txt", std::ios::out);
    if (logFile) {
        SequenceSortsTester::generateLog<ListSequence<int>>(logFile, 3000, 50);
    }
    logFile.close();
    return 0;
}