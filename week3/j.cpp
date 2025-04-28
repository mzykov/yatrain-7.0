#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

std::vector<std::pair<unsigned int, char>> pack(const std::string &s) {
    std::vector<std::pair<unsigned int, char>> res;
    std::unordered_map<std::string, unsigned int> dict { { "", 0 } };
    std::string curr_word = "", prev_word = "";

    for (const char c : s) {
        curr_word += c;
        if (dict.count(curr_word) == 0) {
            res.push_back({ dict[prev_word], c });
            dict[curr_word] = dict.size();
            curr_word = "";
        }
        prev_word = curr_word;
    }

    if (prev_word != "") {
        res.push_back({ dict[prev_word], '\0' });
    }

    return res;
}

std::string unpack(const std::vector<std::pair<unsigned int, char>> &packed) {
    std::string res;
    std::vector<std::string> dict { "" };

    for (const auto [num, c] : packed) {
        auto word = dict[num];
        word += c;
        dict.push_back(word);
        res += word;
    }

    return res;
}

std::pair<std::string, unsigned int> int_as_bytes(unsigned int num) {
    unsigned int bytes_count = 0;
    unsigned char *p = reinterpret_cast<unsigned char*>(&num);
    std::string res;
    for (int i = 0; i < sizeof(unsigned int); ++i) {
        if (auto b = static_cast<unsigned int>(*p)) {
            if (b > 0) {
                ++bytes_count;
                res += std::to_string(b);
                res += " ";
            }
        }
        ++p;
    }

    if (bytes_count == 0) {
        return { "0 ", 1 };
    } else {
        return { res, bytes_count };
    }
}

unsigned int get_length_in_bits(unsigned int num) {
    unsigned int count = 0;
    while (num) {
        num >>= 1;
        ++count;
    }
    return count;
}

void print_packed(const std::vector<std::pair<unsigned int, char>> &packed) {
    unsigned int total_bytes = 0;
    std::stringstream sout;

    for (const auto [num, c] : packed) {
        unsigned int packed_num = (num << 5) | (static_cast<unsigned int>(c - 'a'));
        unsigned int len = get_length_in_bits(packed_num);
        packed_num |= (1 << (len + 2)); // 1-byte data
        len = get_length_in_bits(packed_num);

        if (len > 8)
            packed_num |= (1 << (len - 2));

        if (len > 16)
            packed_num |= (1 << (len - 3));

        const auto& [str, bytes_count] = int_as_bytes(packed_num);
        sout << str;
        total_bytes += bytes_count;
        if (c != '\0') {
            ++total_bytes;
            sout << static_cast<unsigned int>(c) << " ";
        }
    }
    std::cout << total_bytes << "\n" << sout.str() << std::endl;
}

std::vector<std::pair<unsigned int, char>> convert_bytes(const std::vector<unsigned int> &bytes) {
    std::vector<std::pair<unsigned int, char>> res;
    return res;
}

int main() {
    std::string cmd;
    std::cin >> cmd;

    if (cmd == "pack") {
        std::string text;
        std::cin >> text;
        const auto packed = pack(text);
        print_packed(packed);
    }
    else if (cmd == "unpack") {
        unsigned int n = 0;
        std::cin >> n;
        std::vector<unsigned int> bytes(n, 0);
        for (int i = 0; i < n; ++i)
            std::cin >> bytes[i];
        const auto packed = convert_bytes(bytes);
        std::cout << unpack(packed) << std::endl;
    }
    else {
        throw "Unknown command!\n";
    }

    return 0;
}
