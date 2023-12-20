//
// Created by Илья Ильич on 18.12.2023.
//

kernel void transform(global int* input) {
    size_t gid = get_global_id(0);
    input[gid] = input[gid] == 0 ? 1 : -1;
}
