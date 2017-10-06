//
// Created by ddf19 on 03.10.2017.
//

#ifndef LAB1_BACKEND_SEQUENCESORTS_H
#define LAB1_BACKEND_SEQUENCESORTS_H

#include <stdexcept>
#include <type_traits>
#include "Sequence.h"

template <class ElementType>
class SequenceSorts {
public:
    typedef Sequence<ElementType> CollectionType;
    typedef const ElementType& constElemRef;
    typedef bool(*cmpFuncType)(constElemRef, constElemRef);
    typedef std::ptrdiff_t (*stepFuncType)(std::ptrdiff_t);

    static CollectionType* shakerSort(const CollectionType* collection, cmpFuncType cmp) {
        if (collection) {
            auto newCollection = collection -> copy();
            std::ptrdiff_t leftEdge = 0;
            std::ptrdiff_t rigthEdge = (newCollection-> getLength()) - 1;
            while (leftEdge < rigthEdge) {
                for (auto i = leftEdge; i < rigthEdge; ++i) {
                    if (cmp(newCollection -> getConst(i + 1), newCollection -> getConst(i))) {
                        newCollection -> swap(i + 1, i);
                    }
                }
                --rigthEdge;
                for (auto i = rigthEdge; i > leftEdge; --i) {
                    if (cmp(newCollection -> getConst(i), newCollection -> getConst(i - 1))) {
                        newCollection -> swap(i, i - 1);
                    }
                }
                ++leftEdge;
            }
            return newCollection;
        }
        throw std::logic_error("sequence pointer equals nullptr");
    }

    static CollectionType* shellSort(const CollectionType* collection, cmpFuncType cmp, stepFuncType stepFunc) {
        if (collection) {
            auto newCollection = collection -> copy();
            auto size = newCollection -> getLength();
            if (size) {
                auto iteration = 1;
                auto step = stepFunc(iteration);
                while (step > 0) {
                    for (auto i = step; i < size; ++i) {
                        for (auto j = i; (j >= step) && cmp(newCollection->getConst(j),
                                                            newCollection->getConst(j - step)); j -= step) {
                            newCollection->swap(j, j - step);
                        }
                    }
                    step = stepFunc(++iteration);
                }
            }
            return newCollection;
        }
        throw std::logic_error("sequence pointer equals nullptr");
    }

    static CollectionType* countingSort(const CollectionType* collection) {
        if (std::is_integral<ElementType>()) {
            if (collection) {
                auto newCollection = collection -> copy();
                auto size = newCollection -> getLength();
                if (size) {
                    int min = newCollection -> getFirst();
                    int max = min;

                    for (auto i = 1; i < size; ++i) {
                        int tempInt = newCollection -> get(i);
                        if (min > tempInt) {min = tempInt;}
                        if (tempInt > max) {max = tempInt;}
                    }

                    auto countArraySize = max - min + 1;
                    int* countArray = new int[countArraySize];
                    for (auto i = 0; i < countArraySize; ++i) {countArray[i] = 0;}

                    for (auto i = 0; i < size; ++i) {++countArray[(newCollection -> get(i)) - min];}
                    newCollection -> clear();

                    for (auto i = 0; i < countArraySize; ++i) {
                        while(countArray[i]--) {newCollection -> append(min + i);}
                    }
                }
                return newCollection;
            }
            throw std::logic_error("sequence pointer equals nullptr");
        } else {throw std::logic_error("unsupported type");}
    }
};

namespace exampleFunctionsForSort {
    template<class T>
    constexpr bool cmp(const T& lhs, const T& rhs) {return lhs < rhs;}
    constexpr std::ptrdiff_t stepFunc(std::ptrdiff_t iteration) {return (1 << (5 - iteration));}
}

#endif //LAB1_BACKEND_SORTS_H
