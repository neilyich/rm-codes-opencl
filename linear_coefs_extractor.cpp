//
// Created by Илья Ильич on 18.12.2023.
//

kernel void extract(global int* target, global int* source) {
    int targetIndex = get_global_id(0);
    int sourceIndex = 1 << (targetIndex - 1);
    target[targetIndex] = source[sourceIndex];
}
