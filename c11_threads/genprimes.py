import random
import sympy
import sys

def generate_random_primes(num, file_name):
    total = 0
    primes_generated = 0
    with open(file_name, 'w') as f:
        while total < num:
            candidate = random.randint(2, 10000000)
            if total == 0 or primes_generated/total < .5:
                while not sympy.isprime(candidate):
                    candidate = random.randint(2, 10000000)
                primes_generated += 1
            f.write(f"{candidate}\n")
            total += 1 
            print(total, "\r", end="", flush=True)
    print("")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python generate_primes.py <num_primes> <file_name>")
    else:
        num = int(sys.argv[1])
        file_name = sys.argv[2]
        generate_random_primes(num, file_name)