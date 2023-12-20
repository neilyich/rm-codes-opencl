//
// Created by Илья Ильич on 17.12.2023.
//

#ifndef UNTITLED_REALANALOGTRANSFORMER_H
#define UNTITLED_REALANALOGTRANSFORMER_H


#include "OpenCLExecutor.h"

class RealAnalogTransformer : public OpenCLExecutor {
public:
    explicit RealAnalogTransformer(const std::string& kernelCode, const std::string& name) : OpenCLExecutor(kernelCode, name) {}

    // result is written in input
    int* transform(int* input, int length) {
        cl::Buffer inBuf(context,
                         CL_MEM_READ_WRITE,
                         sizeof(int) * length);
        queue.enqueueWriteBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
        cl_int exitCode = 0;
        exitCode |= kernel.setArg(0, inBuf);
        assert(exitCode == CL_SUCCESS);
        //std::cout << "Prepared kernel, enqueueing" << std::endl;
        exitCode |= queue.enqueueNDRangeKernel(kernel, cl::NDRange(0), cl::NDRange(length));
        //std::cout << "Enqueued1" << std::endl;
        assert(exitCode == CL_SUCCESS);
        exitCode |= queue.enqueueReadBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
        //std::cout << exitCode << std::endl;
        assert(exitCode == CL_SUCCESS);
        return input;
    }
};


#endif //UNTITLED_REALANALOGTRANSFORMER_H
