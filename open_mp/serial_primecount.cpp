#include <iostream>
#include <map>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <sstream>
using namespace std::chrono;


extern "C" {

    // Read Numbers from File into an int vector
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
    bool is_prime(int number) {
        for (int i = 2; i <= sqrt(number); i++) {
            if (number % i == 0){
                return false;
            }
        }
        return true;
    }

    // Iterate all numbers in vector and return amount that are prime
    int count_primes(std::vector<long long> numbers) {
        int total = 0;
        for (int num : numbers) {
            if (is_prime(num)){
                total ++;
            }
        }
        return total;
        
    }

    int main(int argc, char* argv[]) {

        // Validate Arguments
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <input filepath>" << std::endl;
            return 1;
        }

        std::string filename = argv[1];

        // Read Input File
        std::vector<long long> allNumbers = readFile(filename); 

        // Start Timer
        auto start = high_resolution_clock::now();

        // Count all primes serially
        int primecount = count_primes(allNumbers);

        // Stop timer
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(duration);

        // Output Times
        std::cout << "Prime Count: " << primecount << ", Time: " << duration_s.count() << std::endl;
        return duration_s.count();  

    }


}

