#include <stdio.h>
#include <vector>

constexpr size_t BYTE_SIZE = 1 << 16;

int main(int argc, const char** argv) {
    if (argc < 2) {
        printf("Please provide code as an argument\n");
        return 0;
    }

    std::vector<size_t> loops;

    size_t code_index = 0;
    const char* code = argv[1];

    size_t index = 0;

    std::vector<char> bytes;
    bytes.resize(BYTE_SIZE, 0);

    while (char c = code[code_index]) {
        switch (c) {
        case '>':
            index++;
            code_index++;
            break;
        case '<':
            index--;
            code_index++;
            break;
        case '+':
            bytes[index]++;
            code_index++;
            break;
        case '-':
            bytes[index]--;
            code_index++;
            break;
        case '.':
            putchar(bytes[index]);
            code_index++;
            break;
        case ',':
            bytes[index] = getchar();
            code_index++;
            break;
        case '[':
            if (bytes[index]) {
                loops.push_back(code_index);
                code_index++;
            } else {
                size_t loop_count = 0;
                while (char c = code[++code_index]) {
                    if (c == '[') {
                        loop_count++;
                    } else if (c == ']') {
                        if (loop_count) {
                            loop_count--;
                        } else {
                            code_index++;
                            break;
                        }
                    }
                }
            }
            break;
        case ']':
            if (bytes[index]) {
                code_index = loops.back() + 1;
            } else {
                loops.pop_back();
                code_index++;
            }
            break;
        default:
            code_index++;
            break;
        }
    }

    return 0;
}