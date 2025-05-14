#include <iostream>
#include <string>
#include <array>
#include <map>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <chrono>
#include <vector>
#include <sstream>
#include <omp.h>
using namespace std::chrono;


extern "C" {
    
    // Read Numbers from File into a long long vector
    std::vector<long long> readFile(std::string& filename){
        // Read Input File
        std::vector<long long> allNumbers;
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return allNumbers;
        }
        std::string line;
        while (std::getline(inputFile, line)){
            std::stringstream ss(line);
            int number;
            if (ss >> number){
                allNumbers.push_back(number);
            }
        }
        inputFile.close();
        return allNumbers;
    }

    
    // T/F is this number prime 
    bool is_prime(long long number) {
        for (int i = 2; i <= sqrt(number); i++) {
            if (number % i == 0){
                return false;
            }
        }
        return true;
    }
    
    // Iterate all numbers in vector between ranks and add amount that are prime to global variable
    void count_primes(std::vector<long long> numbers, size_t start, size_t end, int& partial_sum) {
        partial_sum = 0;
        for (size_t i=start; i<end; i++) {
            int num = numbers[i];
            if (is_prime(num)){
                partial_sum ++; 
            }
        }
    }
    
    
    
    int main(int argc, char* argv[]) {
        // Validate Arguments
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " <number of threads> <input filepath>" << std::endl;
            return 1;
        }
        int p = std::stoi(argv[1]);
        if (p < 1){
            std::cerr << "Invalid input for arg2: number of threads should be at least 1" <<std::endl;
            return 1;
        }
        std::string filename = argv[2];
        
        // Read Input File
        std::vector<long long> allNumbers = readFile(filename);
        int primecount = 0;

        // Start timer
        auto start = high_resolution_clock::now();

        // Create p threads dynamically
        # pragma omp parallel for schedule(dynamic, 100) reduction(+:primecount) num_threads(p)
        for (size_t i = 0; i < allNumbers.size(); i+=100) {
            size_t start = i;
            size_t end = std::min(i + 100, allNumbers.size());
            int partial_sum = 0;
            count_primes(allNumbers, start, end, partial_sum);
            primecount += partial_sum;
        }

    
        // Stop timer
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(duration);
    
        // Output Times
        std::cout << "Prime Count: " << primecount << ", Time: " << duration_s.count() << std::endl;
        return duration_s.count();
    
    }
}

