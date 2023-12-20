//
// Created by Илья Ильич on 17.12.2023.
//

#ifndef UNTITLED_OPENCLEXECUTOR_H
#define UNTITLED_OPENCLEXECUTOR_H

#include <string>
#include <iostream>
#include <OpenCL/opencl.hpp>

class OpenCLExecutor {
protected:
    explicit OpenCLExecutor(const std::string& kernelCode, const std::string& name) {
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);

        assert(!platforms.empty());

        auto platform = platforms.front();

        std::vector<cl::Device> devices;
        auto exitCode = platforms.front().getDevices(CL_DEVICE_TYPE_ALL, &devices);
        assert(exitCode == CL_SUCCESS);

        assert(!devices.empty());

        std::cout << "Devices count: " << devices.size() << std::endl;

        for (const auto& device : devices) {
            auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
            auto version = device.getInfo<CL_DEVICE_VERSION>();
            std::cout << "Device Vendor: " << vendor << std::endl;
            std::cout << "Device Version: " << version << std::endl;
        }

        auto device = devices.front();
        auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
        auto version = device.getInfo<CL_DEVICE_VERSION>();

        //std::cout << "Devices count: " << devices.size() << std::endl;
        //std::cout << "Device Vendor: " << vendor << std::endl;
        //std::cout << "Device Version: " << version << std::endl;

        context = cl::Context{device};
        cl::Program::Sources sources;

        sources.emplace_back(kernelCode.c_str(), kernelCode.length());

        cl_int exitcode = 0;

        cl::Program program{context, sources, &exitcode};
        program.build();
        //std::cout << exitcode << std::endl;
        assert(exitcode == CL_SUCCESS);
        //std::cout << exitcode << std::endl;

        kernel = cl::Kernel{program, name.c_str(), &exitcode};
        //std::cout << exitcode << std::endl;
        assert(exitcode == CL_SUCCESS);

        queue = cl::CommandQueue{context, device};
        //std::cout << exitcode << std::endl;
        assert(exitcode == CL_SUCCESS);
    }

    cl::Context context;
    cl::CommandQueue queue;
    cl::Kernel kernel;
};


#endif //UNTITLED_OPENCLEXECUTOR_H
