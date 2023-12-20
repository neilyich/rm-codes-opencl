#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120

#define ITERATIONS_CОUNT 1

#include <OpenCL/opencl.hpp>
#include <iostream>
#include <cassert>
#include <numeric>
#include <random>
#include <chrono>
#include "Butterfly.h"
#include "RealAnalogTransformer.h"
#include "BFVectorCalculator.h"
#include "utils.h"
#include "VectorExpander.h"
#include "LinearCoefsExtractor.h"
#include "RMCode.h"
#include "IntToBinaryConverter.h"

#define ITERATIONS_COUNT 1000
#define MAX_M 16

void measureTime() {
    IntToBinaryConverter intToBinaryConverter{readFile("../int_to_binary_converter.cpp"), "convert"};
    RMCode code;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<int> dist(0, INT_MAX);
    for (int m = 1; m <= MAX_M; m++) {
        int aLen = m + 1;
        int cLen = 1 << m;
        std::vector<int> aVector(aLen);
        std::vector<int> cVector(cLen);
        long double avgEncodeDuration = 0;
        long double avgDecodeDuration = 0;
        for (int i = 0; i < ITERATIONS_CОUNT; i++) {
            auto a = intToBinaryConverter.convert(aVector.data(), aLen, dist(mt));
            auto startEncode = std::chrono::high_resolution_clock::now();
            auto encoded = code.encode(cVector.data(), cLen, a, aLen);
            auto endEncode = std::chrono::high_resolution_clock::now();
            auto decoded = code.decode(encoded, cLen, aVector.data(), aLen);
            auto endDecode = std::chrono::high_resolution_clock::now();
            auto encodeDuration = duration_cast<std::chrono::milliseconds>(endEncode - startEncode);
            auto decodeDuration = duration_cast<std::chrono::milliseconds>(endDecode - endEncode);
            avgEncodeDuration = (avgEncodeDuration * i + encodeDuration.count()) / (i + 1);
            avgDecodeDuration = (avgDecodeDuration * i + decodeDuration.count()) / (i + 1);
        }
        std::cout << "m=" << m << ":" << std::endl;
        std::cout << "encode: " << (avgEncodeDuration) << std::endl;
        std::cout << "decode: " << (avgDecodeDuration) << std::endl;
        std::cout << "sum: " << (avgEncodeDuration + avgDecodeDuration) << std::endl << std::endl;
    }

}

void encodeAndDecode(std::vector<int> a) {
    auto start = std::chrono::high_resolution_clock::now();
    RMCode code;
    std::vector<int> aCopy(a);
    int aLen = a.size();
    int cLen = 1 << (aLen - 1);
    std::vector<int> c(cLen);
    std::cout << "aLen: " << aLen << std::endl;
    std::cout << "cLen: " << cLen << std::endl;
    std::cout << "Encoding: " << std::endl;
    for (int i = 0; i < aLen; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    auto encoded = code.encode(c.data(), cLen, a.data(), aLen);
    //std::cout << "Encoded: " << std::endl;
    for (int i = 0; i < cLen; i++) {
        //std::cout << encoded[i] << ' ';
    }
    std::cout << std::endl;
    auto decoded = code.decode(encoded, cLen, a.data(), aLen);
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Decoded: " << std::endl;
    for (int i = 0; i < aLen; i++) {
        std::cout << decoded[i] << ' ';
    }
    for (int i = 0; i < aLen; i++) {
        if (aCopy[i] != decoded[i]) {
            std::cout << "Diff at index " << i << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Duration: " << duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {

    PRINT_ENABLED = false;

    measureTime();
    //encodeAndDecode(std::vector<int>{1,0,1,1,1,0,0,1,0,0,1,1,0,1,1,0,1,1});

    return 0;

    cl_int exitcode = 0;

    if (false) {
        IntToBinaryConverter itbc{readFile("../int_to_binary_converter.cpp"), "convert"};
        int target[4];
        auto result = itbc.convert(target, 4, 2);
        for (int i = 0; i < 4; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }

    if (true) {

        if (true) {
            return 0;
        }
    }

    if (false) {
        LinearCoefsExtractor lce{readFile("../linear_coefs_extractor.cpp"), "extract"};
        //int input[8]{1,0,1,0,0,0,0,0};
        int input[8]{1,1,1,0,1,0,0,0};
        int linear[4];
        for (int i : input)
            std::cout << i << ' ';
        std::cout << std::endl;
        auto result = lce.extract(linear, 4, input, 8);
        for (int i = 0; i < 4; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }

    if (false) {
        VectorExpander ve{readFile("../vector_expander.cpp"), "expand"};
        int input[4]{1,0,1, 0};
        int expanded[8];

        for (int i : input)
            std::cout << i << ' ';
        std::cout << std::endl;
        auto result = ve.expand(expanded, 8, input, 4);
        for (int i = 0; i < 8; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }


    if (true) {
        BFVectorCalculator bf{readFile("../bf_vector_calculator.cpp"), "reversedBFVector"};
        //int input[3]{0,1,0};
        //int a0 = 1;
        int input[3]{0,1,0};
        int a0 = 0;
        int vector[8];
        for (int i : input)
            std::cout << i << ' ';
        std::cout << std::endl;
        auto result = bf.reversedBFVector(vector, 8, a0, input, 3);
        std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }

    if (true) {
        RealAnalogTransformer rat{readFile("../real_analog_transformer.cpp"), "transform"};
        //int input[8]{1,0,1,0,0,0,0,0};
        int input[8]{1,1,1,0,1,0,0,0};
        for (int i : input)
            std::cout << i << ' ';
        std::cout << std::endl;
        auto result = rat.transform(input, 8);
        std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }

    if (true) {
        Butterfly fft{readFile("../butterfly.cpp"), "butterfly_fft"};
        int input[8]{1,0,1,0,0,0,0,0};
        //int input[8]{1,1,1,0,1,0,0,0};
        for (int i : input)
            std::cout << i << ' ';
        std::cout << std::endl;
        auto result = fft.calculate(input, 8);
        std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }
    if (false) {
        Butterfly fht{readFile("../butterfly.cpp"), "butterfly_fht"};
        std::cout << "Aboba: " << exitcode << std::endl;
        assert(exitcode == CL_SUCCESS);
        //int input[8]{-1,1,1,-1,1,-1,-1,1};
        int input[8]{-1,-1,1,1,-1,-1,1,1};
        //int input[8]{0,0,0,0,0,0,0,0};
        //std::vector<int> inputVector{-1,1,1,-1,1,-1,-1,1};
        for (int i = 0; i < 8; ++i)
            std::cout << input[i] << ' ';
        std::cout << std::endl;
        auto result = fht.calculate(input, 8);
        std::cout << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << result[i] << ' ';
        }
        std::cout << std::endl;
        if (true) {
            return 0;
        }
    }

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    assert(platforms.size() > 0);

    auto platform = platforms.front();

    std::vector<cl::Device> devices;
    platforms.front().getDevices(CL_DEVICE_TYPE_GPU, &devices);

    assert(devices.size() > 0);

    auto device = devices.front();
    auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
    auto version = device.getInfo<CL_DEVICE_VERSION>();

    std::cout << "Devices count: " << devices.size() << std::endl;
    std::cout << "Device Vendor: " << vendor << std::endl;
    std::cout << "Device Version: " << version << std::endl;

    cl::Context context(device);
    cl::Program::Sources sources;

    std::string kernelCode = ""
                             "kernel void squareArray(global int* input, global int* output) {"
                             "  size_t gid = get_global_id(0);"
                             "  output[gid] = input[gid] * input[gid] + output[gid];"
                             "}";
    kernelCode = readFile("../fft.cpp");
    sources.push_back({kernelCode.c_str(), kernelCode.length()});

    int abc = ITERATIONS_COUNT;

    cl::Program program(context, sources, &exitcode);
    program.build();
    assert(exitcode == CL_SUCCESS);
    std::cout << exitcode << std::endl;

    cl::Kernel kernel(program, "butterfly_fht", &exitcode);
    std::cout << exitcode << std::endl;
    assert(exitcode == CL_SUCCESS);

    auto workGroupSize = kernel.getWorkGroupInfo<CL_KERNEL_WORK_GROUP_SIZE>(device);
    std::cout << "Kernel Work Group Size: " << workGroupSize << std::endl;

    //std::vector<int> outVec(8);
    int* outVec1 = new int[8];
    //std::vector<int> inVec{-1,1,1,-1,1,-1,-1,1};
    int inVec1[8]{-1,1,1,-1,1,-1,-1,1};
    //std::iota(inVec.begin(), inVec.end(), 1);

    int length = 8;
    int count = 4;

    cl::Buffer inBuf(context,
                     CL_MEM_READ_ONLY | CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
                     sizeof(int) * length,
                     inVec1);
    cl::Buffer outBuf(context,
                      CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
                      sizeof(int) * length);
    assert(kernel.setArg(0, inBuf) == CL_SUCCESS);
    assert(kernel.setArg(1, outBuf) == CL_SUCCESS);
    assert(kernel.setArg(2, sizeof(int), &count) == CL_SUCCESS);

    //std::cout << "Size: " << outVec.size() << std::endl;
    for (int i = 0; i < length; ++i)
        std::cout << outVec1[i] << std::endl;
    std::cout << std::endl;

    cl::CommandQueue queue(context, device);

    for (int i = 0; i < length; ++i)
        std::cout << inVec1[i] << std::endl;
    std::cout << std::endl;

    queue.enqueueNDRangeKernel(kernel, cl::NDRange(0), cl::NDRange(4));
    queue.enqueueReadBuffer(outBuf, CL_TRUE, 0, sizeof(int) * length, outVec1);

    for (int i = 0; i < length; ++i)
        std::cout << outVec1[i] << std::endl;

    return 0;
}
