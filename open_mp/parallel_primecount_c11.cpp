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
#include <thread>
#include <mutex>
using namespace std::chrono;


extern "C" {
    std::mutex totalsMutex;
    int primecount;
    
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

    std::map<int, std::array<int, 2>> getRankIndices(int n, int p){
        
        std::map<int, std::array<int, 2>> rank_i;
        const int even_value = n - n%p;
        int rank = 0;

        // Add evenly divisible ranges to map
        for (int i = 0; i < even_value; i += even_value/p-1){
            rank_i[rank][0] = rank * (even_value/p);
            rank_i[rank][1] = (rank+1) * (even_value/p) - 1;
            if (rank==p-1){rank=0;}
            else {rank+=1;}
        }

        // Add leftover values to map
        rank = 0;
        for (int i = n%p; i >= 0; i -= 1){
            rank_i[rank][0] += rank;
            rank_i[rank][1] += rank+1;
            if (rank==p-1){rank = 0;}
            else {rank += 1;}
        }
        // Shift the remainder of the core intervals to account for the change
        const int shift = rank;
        do {
            rank_i[rank][0] += shift;
            rank_i[rank][1] += shift;
            rank += 1;
        } while (rank < p);
    return rank_i;
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
    void count_primes(std::vector<long long> numbers, int start_idx, int end_idx) {
        int total = 0;
        for (int i=start_idx; i<=end_idx; i++) {
            int num = numbers[i];
            if (is_prime(num)){
                total ++; 
            }
        }
        {
            std::lock_guard<std::mutex> lock(totalsMutex);
            primecount += total;
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
    
        // Start timer
        auto start = high_resolution_clock::now();
    
        // Map core rank keys to 2-int arrays representing first and last i
        std::map<int, std::array<int, 2>> rank_i = getRankIndices(allNumbers.size(), p);
    
        // Create p threads
        std::thread threads[p];
        for (int i = 0; i < p; i++) {
            threads[i] = std::thread(count_primes, std::ref(allNumbers), rank_i[i][0], rank_i[i][1]);
        }
    
        // Join p threads
        for (int i = 0; i < p; i++){
            threads[i].join();
        }
    
        // Stop timer
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);
        auto duration_s = std::chrono::duration_cast<std::chrono::seconds>(duration);
    
        // Output Times
        std::cout << "Prime Count: " << primecount << ", Time: " << duration_s.count() << "\n"<< std::endl;
        return duration_s.count();
    
    }
}

