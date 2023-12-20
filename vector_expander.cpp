//
// Created by Илья Ильич on 18.12.2023.
//

kernel void expand(global int* target, global int* source) {
    int sourceIndex = get_global_id(0);
    int targetIndex = 1 << (sourceIndex - 1);
    target[targetIndex] = source[sourceIndex];
}
