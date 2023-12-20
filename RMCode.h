//
// Created by Илья Ильич on 18.12.2023.
//

#ifndef UNTITLED_RMCODE_H
#define UNTITLED_RMCODE_H

#include "BFVectorCalculator.h"
#include "RealAnalogTransformer.h"
#include "Butterfly.h"
#include "utils.h"
#include "VectorExpander.h"
#include "LinearCoefsExtractor.h"
#include "IntToBinaryConverter.h"
#include <math.h>

class RMCode {
private:
    BFVectorCalculator bf{readFile("../bf_vector_calculator.cpp"), "reversedBFVector"};
    RealAnalogTransformer rat{readFile("../real_analog_transformer.cpp"), "transform"};
    Butterfly fft{readFile("../butterfly.cpp"), "butterfly_fft"};
    Butterfly fht{readFile("../butterfly.cpp"), "butterfly_fht"};
    VectorExpander ve{readFile("../vector_expander.cpp"), "expand"};
    LinearCoefsExtractor lce{readFile("../linear_coefs_extractor.cpp"), "extract"};
    IntToBinaryConverter itbc{readFile("../int_to_binary_converter.cpp"), "convert"};

public:
    // writes encoded into c
    int* encode(int* c, int cLen, int* a, int aLen) {
        auto expanded = ve.expand(c, cLen, a, aLen);
        return fft.calculate(expanded, cLen);
    }

    // writes decoded into a
    int* decode(int* c, int cLen, int* a, int aLen) {
        print("Decoding", c, cLen);
        auto real = rat.transform(c, cLen);
        print("Real analog", real, cLen);
        auto statAnalogs = fht.calculate(real, cLen);
        print("Stat analogs", statAnalogs, cLen);
        int max = 0;
        int maxABS = 0;
        int statAnalogCoefs = -1;
        int notZeroCount = 0;
        long sum = 0;
        for (int i = 0; i < cLen; i++) {
            int _abs = abs(statAnalogs[i]);
            if (maxABS < _abs) {
                maxABS = _abs;
                max = statAnalogs[i];
                statAnalogCoefs = i;
            }
            if (_abs != 0) {
                notZeroCount++;
                sum += _abs * _abs;
            }
        }
//        if (notZeroCount > 1) {
//            std::cout << "There are " << notZeroCount << " elements." << std::endl;
//        }
        int xCount = aLen - 1;
//        if (sum != (1 << (2*xCount))) {
//            std::cout << "sum != 2^(2*xCount) " << sum << " != " << (1 << (2*xCount)) << std::endl;
//        }
        int* xCoefs = itbc.convert(a, xCount, statAnalogCoefs);
        print("xCoefs", xCoefs, xCount);
        int a0 = max > 0 ? 0 : 1;
        print("a0", new int[1]{a0}, 1);
        auto bfReversed = bf.reversedBFVector(c, cLen, a0, xCoefs, xCount);
        print("Reversed BF", bfReversed, cLen);
        auto allCoefs = fft.calculate(bfReversed, cLen);
        print("All coefs", allCoefs, cLen);
        return lce.extract(a, aLen, allCoefs, cLen);
    }
};


#endif //UNTITLED_RMCODE_H
