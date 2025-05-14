import os
import csv
import subprocess


# Run Serial program on a primes file and return runtime
def run_serial(filename):
    result = subprocess.run(["./serial_primecount", filename], capture_output=True, text=True).stdout.strip()
    [primecount, time] = result.split(",")
    print("serial primes: ", primecount)
    time = int(time.lstrip(" Time: "))
    return time

# Run Parallel program on a primes file using 4 threads and return runtime
def run_parallel(filename):
    result = subprocess.run(["./parallel_primecount", "4", filename], capture_output=True, text=True).stdout.strip()
    [primecount, time] = result.split(",")
    print("serial primes: ", primecount)
    time = int(time.lstrip(" Time: "))
    return time

if __name__=="__main__":

    # Read in primes filenames from local dir
    current_dir = os.getcwd()
    files = []
    for file in os.listdir(current_dir):
        filepath = os.path.join(current_dir, file)
        if os.path.isfile(filepath) and file.startswith("primes_") and file.endswith(".txt"):
            if file=="primes_1000000.txt":
                continue
            files.append(file)
    files.append("primes_1000000.txt")


    # Save average timings for serial and parallel over 20 iterations
    iterations = [["Num Primes"], ["Avg Serial Time (seconds)"], ["Avg Parallel Time (seconds)"]]

    # For each primes file:
    for file in files:
        num_primes = int(file.lstrip("primes_").rstrip(".txt"))
        # Get average of 20 timings for parallel and serial
        serial_time = sum([run_serial(file) for _ in range(20)])/20
        parallel_time = sum([run_parallel(file) for _ in range(20)])/20
        
        print(f"Average time for {num_primes} primes: \tSerial: {serial_time} \tParallel: {parallel_time}")
        
        iterations[0].append(num_primes)
        iterations[1].append(serial_time)
        iterations[2].append(parallel_time)

    # Format rows (swap rows and columns)
    rows = [list(row) for row in zip(*iterations)]

    # Save average values in a csv
    with open("timings.csv", "w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerows(rows)
