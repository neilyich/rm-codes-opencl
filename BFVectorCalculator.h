//
// Created by Илья Ильич on 18.12.2023.
//

#ifndef UNTITLED_BFVECTORCALCULATOR_H
#define UNTITLED_BFVECTORCALCULATOR_H


#include "OpenCLExecutor.h"

class BFVectorCalculator : public OpenCLExecutor {
public:
    explicit BFVectorCalculator(const std::string& kernelCode, const std::string& name) : OpenCLExecutor(kernelCode, name) {}

    int* reversedBFVector(int* vector, int nbits, int a0, int* xCoefs, int xCount) {
        cl::Buffer vectorBuf(context,
                             CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                             sizeof(int) * nbits);
        cl_int exitCode = 0;
        exitCode |= kernel.setArg(0, vectorBuf);
        assert(exitCode == CL_SUCCESS);
        cl::Buffer xCoefsBuf(context,
                             CL_MEM_READ_ONLY,
                             sizeof(int) * xCount);
        exitCode |= queue.enqueueWriteBuffer(xCoefsBuf, CL_TRUE, 0, sizeof(int) * xCount, xCoefs);
        assert(exitCode == CL_SUCCESS);
        exitCode |= kernel.setArg(1, xCoefsBuf);
        assert(exitCode == CL_SUCCESS);
        exitCode |= kernel.setArg(2, sizeof(int), &xCount);
        assert(exitCode == CL_SUCCESS);
        exitCode |= kernel.setArg(3, sizeof(int), &a0);
        assert(exitCode == CL_SUCCESS);
        int nbitsMinus1 = nbits - 1;
        exitCode |= kernel.setArg(4, sizeof(int), &nbitsMinus1);
        assert(exitCode == CL_SUCCESS);
        //std::cout << "Prepared kernel, enqueueing" << std::endl;
        exitCode |= queue.enqueueNDRangeKernel(kernel, cl::NDRange(0), cl::NDRange(nbits));
        //std::cout << "Enqueued1" << std::endl;
        assert(exitCode == CL_SUCCESS);
        exitCode |= queue.enqueueReadBuffer(vectorBuf, CL_TRUE, 0, sizeof(int) * nbits, vector);
        //std::cout << exitCode << std::endl;
        assert(exitCode == CL_SUCCESS);
        return vector;
    }
};


#endif //UNTITLED_BFVECTORCALCULATOR_H
