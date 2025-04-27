#include <iostream>
#include <string>

int nearest_power2(int n) {
    int k = 0, res = 0;
    while (((1 << k) - k) < n + 1)
        ++k;
    return k;
}

unsigned int count_bits(unsigned int x) {
    unsigned int count = 0;
    for (; x > 0; x >>= 1) {
        if (x & 1)
            ++count;
    }
    return count;
}

std::string encode(std::string& s) {
    int k = nearest_power2(s.length());
    s.reserve(s.capacity() + k + 1);

    s.insert(s.begin(), '0');

    for (int i = 0; i < k; ++i)
        s.insert(s.begin() + (1 << i), '0');

    for (int i = 0; i < k; ++i) {
        unsigned int num_bits = 0;
        unsigned int control_pos = 1 << i;

        for (unsigned int j = control_pos + 1; j < s.length(); ++j) {
            unsigned int bit = static_cast<unsigned int>(s[j] - '0');
            if ((j & control_pos ? 1 : 0) & bit)
                ++num_bits;
        }
        s[control_pos] = (num_bits & 1) > 0 ? '0' : '1';
    }

    return s.substr(1);
}

std::string decode(std::string& s) {
    s.insert(s.begin(), '0');

    unsigned int broken_index = 0;

    for (unsigned int i = 0; (1 << i) < s.length(); ++i) {
        unsigned int num_bits = 0;
        unsigned int control_pos = 1 << i;

        for (unsigned int j = control_pos + 1; j < s.length(); ++j) {
            if (count_bits(j) == 1)
                continue;
            unsigned int bit = static_cast<unsigned int>(s[j] - '0');
            if ((j & control_pos ? 1 : 0) & bit)
                ++num_bits;
        }

        char control_bit = (num_bits & 1) > 0 ? '0' : '1';

        if (control_bit != s[control_pos])
            broken_index |= control_pos;
    }

    s[broken_index] = s[broken_index] == '1' ? '0' : '1';

    std::string res;

    for (unsigned int i = 3; i < s.length(); ++i) {
        if (count_bits(i) == 1) // skip control bits
            continue;
        res.push_back(s[i]);
    }

    return res;
}

int main() {
    int step;
    std::cin >> step;

    std::string bits;
    std::cin >> bits;

    switch (step) {
    case 1:
        std::cout << encode(bits) << std::endl;
        break;
    case 2:
        std::cout << decode(bits) << std::endl;
        break;
    default:
        throw "Unknown step number!\n";
    }

    return 0;
}
