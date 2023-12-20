//
// Created by Илья Ильич on 18.12.2023.
//

#ifndef UNTITLED_INTTOBINARYCONVERTER_H
#define UNTITLED_INTTOBINARYCONVERTER_H

#include "OpenCLExecutor.h"

class IntToBinaryConverter : public OpenCLExecutor {
public:
    explicit IntToBinaryConverter(const std::string& kernelCode, const std::string& name) : OpenCLExecutor(kernelCode, name) {}

    int* convert(int* target, int targetNbits, int n) {
        cl::Buffer targetBuf(context,
                         CL_MEM_WRITE_ONLY,
                         sizeof(int) * targetNbits);
        cl_int exitCode = 0;
        exitCode |= kernel.setArg(0, targetBuf);
        assert(exitCode == CL_SUCCESS);
        int targetNbitsMinus1 = targetNbits - 1;
        exitCode |= kernel.setArg(1, sizeof(int), &targetNbitsMinus1);
        assert(exitCode == CL_SUCCESS);
        exitCode |= kernel.setArg(2, sizeof(int), &n);
        assert(exitCode == CL_SUCCESS);
        //std::cout << "Prepared kernel, enqueueing" << std::endl;
        exitCode |= queue.enqueueNDRangeKernel(kernel, cl::NDRange(0), cl::NDRange(targetNbits));
        //std::cout << "Enqueued1" << std::endl;
        assert(exitCode == CL_SUCCESS);
        exitCode |= queue.enqueueReadBuffer(targetBuf, CL_TRUE, 0, sizeof(int) * targetNbits, target);
        //std::cout << exitCode << std::endl;
        assert(exitCode == CL_SUCCESS);
        return target;
    }
};


#endif //UNTITLED_INTTOBINARYCONVERTER_H
