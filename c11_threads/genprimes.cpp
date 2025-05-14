#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void generate_random_primes(int num, const std::string& file_name) {
    std::ofstream file(file_name);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    int total = 0;
    int primes_generated = 0;
    std::srand(std::time(0));

    while (total < num) {
        int candidate = std::rand() % 10000000 + 2;
        if (total == 0 || static_cast<double>(primes_generated) / total < 0.5) {
            while (!is_prime(candidate)) {
                candidate = std::rand() % 10000000 + 2;
            }
            primes_generated++;
        }
        file << candidate << "\n";
        total++;
        std::cout << total << "\r" << std::flush;
    }
    file.close();
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_primes> <file_name>" << std::endl;
        return 1;
    }

    int num = std::stoi(argv[1]);
    std::string file_name = argv[2];
    generate_random_primes(num, file_name);

    return 0;
}