//
// Created by Илья Ильич on 17.12.2023.
//

void fht(global int* input, int left, int right) {
    int inputLeft = input[left];
    input[left] = inputLeft + input[right];
    input[right] = input[right] - inputLeft;
}

int wordIndex(int i) {
    return i >> 5;
}

int wordBit(int i) {
    return i % 32;
}

bool getValue(int word, int wordIndex) {
    int mask = 1 << wordIndex;
    return word & mask;
}

void setValue(global int* arr, int wordIndex, int wordBit, bool value) {
    int word = arr[wordIndex];
    if (value) {
        int mask = 1 << wordBit;
        word |= mask;
    } else {
        int mask = ~(1 << wordBit);
        word &= mask;
    }
    arr[wordIndex] = word;
}

void fft(global int* input, int left, int right) {
    input[right] = (input[right] + input[left]) & 1;
//    int leftWord = wordIndex(left);
//    int leftWordBit = wordBit(left);
//    int rightWord = wordIndex(right);
//    int rightWordBit = wordBit(right);
//    setValue(output,leftWord, leftWordBit,
//             getValue(input[leftWord], leftWordBit));
//    setValue(output, rightWord, rightWordBit,
//             getValue(input[rightWord], rightWordBit) ^ getValue(input[leftWord], leftWordBit));
}

kernel void butterfly_fht(global int* input, int offset) {
    size_t left = get_global_id(0);
    size_t right = left + offset;
    fht(input, left, right);
}

kernel void butterfly_fft(global int* input, int offset) {
    size_t left = get_global_id(0);
    size_t right = left + offset;
    fft(input, left, right);
}

