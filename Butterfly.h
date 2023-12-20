//
// Created by Илья Ильич on 17.12.2023.
//

#ifndef UNTITLED_BUTTERFLY_H
#define UNTITLED_BUTTERFLY_H


#include <string>
#include <utility>
#include <OpenCL/opencl.hpp>
#include "OpenCLExecutor.h"

class Butterfly : public OpenCLExecutor {
public:
    explicit Butterfly(const std::string& kernelCode, const std::string& name) : OpenCLExecutor(kernelCode, name) {}

    // result is written in input
    int* calculate(int* input, int length) {
        cl::Buffer inBuf(context,
                         CL_MEM_READ_WRITE,
                         sizeof(int) * length);
        queue.enqueueWriteBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
        int blockSize = length;
        int blocksCount = 1;
        while (blockSize > 1) {
            int offset = 0;
            int count = blockSize >> 1;
            for (int i = 0; i < blocksCount; i++) {
                cl_int exitCode = 0;
                exitCode |= kernel.setArg(0, inBuf);
                assert(exitCode == CL_SUCCESS);
                exitCode |= kernel.setArg(1, sizeof(int), &count);
                assert(exitCode == CL_SUCCESS);
                exitCode |= queue.enqueueNDRangeKernel(kernel, cl::NDRange(offset), cl::NDRange(count));
                assert(exitCode == CL_SUCCESS);
                offset += blockSize;
//                exitCode |= queue.enqueueReadBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
//                std::cout << "Enqueued2 " << exitCode << std::endl;
//                for (int j = 0; j < length; j++) {
//                    std::cout << input[j] << ' ';
//                }
//                std::cout << std::endl;
//                exitCode |= queue.enqueueWriteBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
//                assert(exitCode == CL_SUCCESS);
            }
            blocksCount <<= 1;
            blockSize = count;
        }
        auto exitCode = queue.enqueueReadBuffer(inBuf, CL_TRUE, 0, sizeof(int) * length, input);
        assert(exitCode == CL_SUCCESS);
        return input;
    }
};


#endif //UNTITLED_BUTTERFLY_H
