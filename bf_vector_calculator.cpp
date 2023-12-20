//
// Created by Илья Ильич on 18.12.2023.
//

kernel void reversedBFVector(global int* vector, global int* xCoefs, int xCount, int a0, int nbitsMinus1) {
    int gid = get_global_id(0);
    int i = gid;
    int value = a0;
    for (int x = xCount - 1; x >= 0; x--) {
        value = ( value + (xCoefs[x] * (i & 1)) ) & 1;
        i = i >> 1;
    }
    vector[nbitsMinus1 - gid] = value;
}
