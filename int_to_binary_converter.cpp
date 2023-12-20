//
// Created by Илья Ильич on 18.12.2023.
//

kernel void convert(global int* target, int targetNbitsMinus1, int n) {
    int bitIndex = get_global_id(0);
    target[targetNbitsMinus1 - bitIndex] = (n >> bitIndex) & 1;
}
