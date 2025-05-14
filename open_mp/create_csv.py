import os
import csv
import subprocess


# Run Serial program on a primes file and return runtime
def run_serial(filename):
    result = subprocess.run(["./serial_primecount", filename], capture_output=True, text=True).stdout.strip()
    [primecount, time] = result.split(",")
    time = int(time.lstrip(" Time: "))
    return time

# Run C11 or OMPParallel program on a primes file using x threads and return runtime
def run_parallel(filename, suffix, thread_count):
    result = subprocess.run(["./parallel_primecount_"+ suffix, thread_count, filename], capture_output=True, text=True).stdout.strip()
    [primecount, time] = result.split(",")
    time = int(time.lstrip(" Time: "))
    return time

def load_files():
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
    return files


def run_timings1():
    
    # Save average timings for serial and parallel over 20 iterations
    iterations = [["Num Primes"], ["Avg Serial Time (seconds)"], ["Avg C11 Threads Time (seconds)"], ["Avg OpenMP Time (seconds)"]]

    thread_count = "4"

    # For each primes file:
    files = load_files()
    for file in files:
        num_primes = int(file.lstrip("primes_").rstrip(".txt"))
        # Get average of 20 timings for parallel and serial
        serial_time = sum([run_serial(file) for _ in range(20)])/20
        parallel_c11_time = sum([run_parallel(file, "c11", thread_count) for _ in range(20)])/20
        parallel_omp_time = sum([run_parallel(file, "omp", thread_count) for _ in range(20)])/20

        print(f"Average time for {num_primes} primes: \tSerial: {serial_time} \tC11: {parallel_c11_time} \tOMP: {parallel_omp_time}")
        
        iterations[0].append(num_primes)
        iterations[1].append(serial_time)
        iterations[2].append(parallel_c11_time)
        iterations[3].append(parallel_omp_time)

    # Format rows (swap rows and columns)
    rows = [list(row) for row in zip(*iterations)]

    # Save average values in a csv
    with open("timings1.csv", "w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerows(rows)

def run_timings2():
    values = [["Number of cores"], ["Time (seconds)"]]
    for i in range(2, 7):
        thread_count = str(i)
        print("threads: ", thread_count)
        time = sum(run_parallel("primes_500000.txt", "omp", thread_count) for _ in range(20)) / 20
        values[0].append(thread_count)
        values[1].append(time)
    
    rows = [list(row) for row in zip(*values)]

    with open("timings2.csv", "w", newline="") as csv_file:
        writer = csv.writer(csv_file)
        writer.writerows(rows)

if __name__=="__main__":
    run_timings1()
    run_timings2()