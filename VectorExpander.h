//
// Created by Илья Ильич on 18.12.2023.
//

#ifndef UNTITLED_VECTOREXPANDER_H
#define UNTITLED_VECTOREXPANDER_H


#include "OpenCLExecutor.h"

class VectorExpander : public OpenCLExecutor {
public:
    explicit VectorExpander(const std::string& kernelCode, const std::string& name) : OpenCLExecutor(kernelCode, name) {}

    int* expand(int* target, int targetNbits, int* source, int sourceNbits) {
        cl::Buffer targetBuf(context,
                             CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                             sizeof(int) * targetNbits);
        cl_int exitCode = 0;
        exitCode |= kernel.setArg(0, targetBuf);
        assert(exitCode == CL_SUCCESS);
        cl::Buffer sourceBuf(context,
                             CL_MEM_READ_ONLY,
                             sizeof(int) * sourceNbits);
        exitCode |= queue.enqueueWriteBuffer(sourceBuf, CL_TRUE, 0, sizeof(int) * sourceNbits, source);
        assert(exitCode == CL_SUCCESS);
        exitCode |= kernel.setArg(1, sourceBuf);
        assert(exitCode == CL_SUCCESS);
        //std::cout << "Prepared kernel, enqueueing" << std::endl;
        exitCode |= queue.enqueueNDRangeKernel(kernel, cl::NDRange(1), cl::NDRange(sourceNbits - 1));
        //std::cout << "Enqueued1" << std::endl;
        assert(exitCode == CL_SUCCESS);
        exitCode |= queue.enqueueReadBuffer(targetBuf, CL_TRUE, 0, sizeof(int) * targetNbits, target);
        //std::cout << exitCode << std::endl;
        assert(exitCode == CL_SUCCESS);
        target[0] = source[0];
        return target;
    }
};


#endif //UNTITLED_VECTOREXPANDER_H
