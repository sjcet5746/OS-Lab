#!/usr/bin/env python
# coding: utf-8

# In[ ]:


import os
import subprocess

def main():
    # Fork a child process
    pid = os.fork()
    
    if pid < 0:
        # Fork failed
        print("Fork failed")
        exit(1)
    elif pid == 0:
        # Child process
        print("Child process: PID =", os.getpid(), ", Parent PID =", os.getppid())
        
        # Execute a new program using exec
        try:
            subprocess.run(["ls", "-l"])
        except FileNotFoundError:
            print("Exec failed")
            exit(1)
    else:
        # Parent process
        print("Parent process: PID =", os.getpid(), ", Child PID =", pid)
        
        # Wait for the child process to finish
        pid, status = os.wait()
        if os.WIFEXITED(status):
            print("Child process exited with status:", os.WEXITSTATUS(status))
        else:
            print("Child process exited abnormally")
        
        # Open a directory
        dir_fd = os.open(".", os.O_RDONLY)
        
        # Read directory contents
        print("Directory contents:")
        with os.fdopendir(dir_fd) as dirp:
            for entry in iter(lambda: os.readdir(dirp), None):
                print(entry.name)
        
        # Close the directory
        os.close(dir_fd)

if __name__ == "__main__":
    main()


# In[2]:


import os

def ls():
    for item in os.listdir('.'):
        print(item)

ls()


# In[ ]:


import shutil

def cp(source, destination):
    shutil.copyfile(source, destination)

cp('source.txt', 'destination.txt')


# In[ ]:


import re

def grep(pattern, filename):
    with open(filename, 'r') as file:
        for line in file:
            if re.search(pattern, line):
                print(line)

grep('pattern', 'file.txt')


# In[4]:


def round_robin(processes, quantum):
    remaining_burst_time = [process[1] for process in processes]
    n = len(processes)
    time = 0
    while True:
        done = True
        for i in range(n):
            if remaining_burst_time[i] > 0:
                done = False
                if remaining_burst_time[i] > quantum:
                    time += quantum
                    remaining_burst_time[i] -= quantum
                    print(f"Process {processes[i][0]} executed with remaining burst time {remaining_burst_time[i]}")
                else:
                    time += remaining_burst_time[i]
                    print(f"Process {processes[i][0]} executed with remaining burst time 0")
                    remaining_burst_time[i] = 0
        if done:
            break

# Example usage
processes = [
    (1, 10),  # Process ID, Burst Time
    (2, 5),
    (3, 8)
]
quantum = 2
print("Round Robin Scheduling:")
round_robin(processes, quantum)


# In[5]:


def sjf(processes):
    processes.sort(key=lambda x: x[1])
    time = 0
    for process in processes:
        print(f"Process {process[0]} executed with remaining burst time {process[1]}")
        time += process[1]

# Example usage
processes = [
    (1, 10),  # Process ID, Burst Time
    (2, 5),
    (3, 8)
]
print("Shortest Job First (SJF) Scheduling:")
sjf(processes)


# In[6]:


def fcfs(processes):
    time = 0
    for process in processes:
        print(f"Process {process[0]} executed with remaining burst time {process[1]}")
        time += process[1]

# Example usage
processes = [
    (1, 10),  # Process ID, Burst Time
    (2, 5),
    (3, 8)
]
print("First-Come, First-Served (FCFS) Scheduling:")
fcfs(processes)


# In[7]:


def priority(processes):
    processes.sort(key=lambda x: x[2])
    time = 0
    for process in processes:
        print(f"Process {process[0]} executed with remaining burst time {process[1]}")
        time += process[1]

# Example usage
processes = [
    (1, 10, 2),  # Process ID, Burst Time, Priority
    (2, 5, 1),
    (3, 8, 3)
]
print("Priority Scheduling:")
priority(processes)


# In[8]:


#Program-5
class Process:
    def __init__(self, pid, burst_time, priority):
        self.pid = pid
        self.burst_time = burst_time
        self.priority = priority
        self.remaining_time = burst_time

def dynamic_priority_scheduling(processes):
    current_time = 0
    total_burst_time = sum(process.burst_time for process in processes)

    while total_burst_time > 0:
        # Find the highest priority process that is ready
        highest_priority_process = None
        for process in processes:
            if process.remaining_time > 0:
                if highest_priority_process is None or process.priority > highest_priority_process.priority:
                    highest_priority_process = process

        if highest_priority_process is not None:
            print(f"Executing Process {highest_priority_process.pid} (Priority: {highest_priority_process.priority}) at Time {current_time}")
            highest_priority_process.remaining_time -= 1
            total_burst_time -= 1
            current_time += 1
        else:
            current_time += 1

        # Update priorities dynamically
        for process in processes:
            if process.remaining_time > 0:
                process.priority -= 1
                if process.priority < 0:
                    process.priority = 0

# Example usage
processes = [
    Process(1, 10, 5),
    Process(2, 5, 3),
    Process(3, 8, 7)
]

print("Dynamic Priority Scheduling:")
dynamic_priority_scheduling(processes)


# In[9]:


#Program-6
class Job:
    def __init__(self, id, weight):
        self.id = id
        self.weight = weight
        self.remaining_time = weight

def round_robin(jobs):
    total_remaining_time = sum(job.weight for job in jobs)
    current_time = 0
    index = 0

    while total_remaining_time > 0:
        if jobs[index].remaining_time > 0:
            print(f"Executing Job {jobs[index].id} with weight {jobs[index].weight} at time {current_time}")
            if jobs[index].remaining_time > jobs[index].weight:
                current_time += jobs[index].weight
                jobs[index].remaining_time -= jobs[index].weight
                total_remaining_time -= jobs[index].weight
            else:
                current_time += jobs[index].remaining_time
                total_remaining_time -= jobs[index].remaining_time
                jobs[index].remaining_time = 0
        index = (index + 1) % len(jobs)

# Example jobs
jobs = [
    Job(1, 1),  # Job ID, Weight
    Job(2, 2),
    Job(3, 3),
    Job(4, 4),
    Job(5, 5)
]

print("Round Robin Scheduling with Time Slice Equivalent to Weight:")
round_robin(jobs)


# In[ ]:


#Program-7
import heapq
import time

class Process:
    def __init__(self, pid, priority, remaining_time):
        self.pid = pid
        self.priority = priority
        self.remaining_time = remaining_time

    def __lt__(self, other):
        # Custom comparison to prioritize processes with higher priority
        return self.priority < other.priority

def priority_scheduling(processes):
    priority_queue = []
    heapq.heapify(priority_queue)
    timer = 0

    while processes or priority_queue:
        # Insert processes into the priority queue based on their arrival time
        for process in processes[:]:
            if process.remaining_time > 0 and process.remaining_time <= 10:
                heapq.heappush(priority_queue, process)
                processes.remove(process)

        # Execute processes with priority <= 10 for at least 1 second
        while priority_queue and priority_queue[0].priority <= 10:
            process = heapq.heappop(priority_queue)
            print(f"Executing Process {process.pid} with priority {process.priority} at time {timer}")
            time.sleep(1)  # Simulate process execution for 1 second
            timer += 1
            process.remaining_time -= 1
            if process.remaining_time > 0:
                heapq.heappush(priority_queue, process)  # Reinsert the process into the queue if it's not finished

        # Check if all processes are executed
        all_executed = all(process.remaining_time <= 0 for process in processes)
        if all_executed:
            break

        # Increment timer
        timer += 1

# Example processes
processes = [
    Process(1, 1, 15),  # Process ID, Priority, Remaining Time
    Process(2, 2, 5),
    Process(3, 5, 8),
    Process(4, 8, 20),
    Process(5, 10, 3)
]

print("Priority Scheduling with Maximum Waiting Time Constraint:")
priority_scheduling(processes)


# In[1]:


#Program-8(1)
import threading
import time

NUM_PORTS = 5
port_sem = threading.Semaphore(NUM_PORTS)

def open_port(port_num):
    print(f"Thread {port_num} is trying to open port {port_num}")
    port_sem.acquire()  # Decrement semaphore value
    print(f"Thread {port_num} has opened port {port_num}")
    time.sleep(2)  # Simulating usage of the port
    print(f"Thread {port_num} is releasing port {port_num}")
    port_sem.release()  # Increment semaphore value

# Create threads to open ports
threads = []
for i in range(NUM_PORTS):
    t = threading.Thread(target=open_port, args=(i + 1,))
    threads.append(t)
    t.start()

# Join threads
for t in threads:
    t.join()


# In[2]:


#Program-8(2)
import threading
import time

NUM_PORTS = 5
port_lock = threading.Lock()
port_available = threading.Condition(port_lock)
available_ports = NUM_PORTS

def open_port(port_num):
    global available_ports
    print(f"Thread {port_num} is trying to open port {port_num}")
    with port_lock:
        while available_ports == 0:
            port_available.wait()  # Wait if no ports available
        available_ports -= 1
        print(f"Thread {port_num} has opened port {port_num}")
    time.sleep(2)  # Simulating usage of the port
    with port_lock:
        available_ports += 1
        print(f"Thread {port_num} is releasing port {port_num}")
        port_available.notify()  # Signal that port is available

# Create threads to open ports
threads = []
for i in range(NUM_PORTS):
    t = threading.Thread(target=open_port, args=(i + 1,))
    threads.append(t)
    t.start()

# Join threads
for t in threads:
    t.join()


# In[3]:


#Program-9
import multiprocessing
import os

def child_process(shared_value):
    print("Child process (PID {}) writing to shared memory: {}".format(os.getpid(), shared_value.value))
    shared_value.value = 20

if __name__ == "__main__":
    # Create a shared value
    shared_value = multiprocessing.Value('i', 10)

    print("Parent process (PID {}) reading from shared memory: {}".format(os.getpid(), shared_value.value))

    # Create a child process
    child = multiprocessing.Process(target=child_process, args=(shared_value,))
    child.start()
    child.join()

    print("Parent process (PID {}) reading from shared memory after child process: {}".format(os.getpid(), shared_value.value))


# In[ ]:


#Program-10
import threading
import time
import random

NUM_CHAIRS = 5
NUM_CUSTOMERS = 20
num_waiting = 0
num_served = 0
mutex = threading.Semaphore(1)
barber_sem = threading.Semaphore(0)
customer_sem = threading.Semaphore(0)

def barber():
    global num_served
    while num_served < 10:  # Serve 10 customers
        customer_sem.acquire()  # Wait for a customer
        mutex.acquire()
        num_waiting -= 1
        mutex.release()
        barber_sem.release()  # Signal that the barber is ready
        print("Barber is cutting hair")
        time.sleep(2)  # Simulate cutting hair
        num_served += 1
    print("Barber is going home")

def customer(customer_id):
    global num_waiting
    mutex.acquire()
    if num_waiting < NUM_CHAIRS:
        print(f"Customer {customer_id} is waiting")
        num_waiting += 1
        mutex.release()
        customer_sem.release()  # Signal that a customer has arrived
        barber_sem.acquire()  # Wait for the barber
        print(f"Customer {customer_id} is getting a haircut")
    else:
        print(f"Customer {customer_id} left - no chairs available")
        mutex.release()

# Create barber thread
barber_thread = threading.Thread(target=barber)
barber_thread.start()

# Create customer threads
customer_threads = []
for i in range(NUM_CUSTOMERS):
    customer_thread = threading.Thread(target=customer, args=(i + 1,))
    customer_threads.append(customer_thread)
    customer_thread.start()
    time.sleep(random.uniform(0.1, 1))  # Random delay between customer arrivals

# Join threads
barber_thread.join()
for thread in customer_threads:
    thread.join()


# In[ ]:


#Program-11
import threading
import time
import random

NUM_PHILOSOPHERS = 5

class Philosopher(threading.Thread):
    def __init__(self, index, left_fork, right_fork):
        super().__init__()
        self.index = index
        self.left_fork = left_fork
        self.right_fork = right_fork

    def run(self):
        while True:
            print(f"Philosopher {self.index} is thinking")
            time.sleep(random.uniform(1, 3))  # Simulate thinking

            # Acquire both forks or wait until available
            with self.left_fork:
                with self.right_fork:
                    print(f"Philosopher {self.index} is eating")
                    time.sleep(random.uniform(1, 3))  # Simulate eating

def main():
    forks = [threading.Lock() for _ in range(NUM_PHILOSOPHERS)]

    philosophers = []
    for i in range(NUM_PHILOSOPHERS):
        left_fork = forks[i]
        right_fork = forks[(i + 1) % NUM_PHILOSOPHERS]
        philosopher = Philosopher(i, left_fork, right_fork)
        philosophers.append(philosopher)
        philosopher.start()

    for philosopher in philosophers:
        philosopher.join()

if __name__ == "__main__":
    main()


# In[ ]:


#Program-12
import threading
import queue
import random
import time

NUM_PRODUCERS = 2
NUM_CONSUMERS = 3
BUFFER_SIZE = 5

buffer = queue.Queue(BUFFER_SIZE)

def producer():
    for i in range(10):  # Produce 10 items
        item = random.randint(1, 100)  # Generate a random item
        buffer.put(item)  # Put the item into the buffer
        print(f"Producer produced item {item}")
        time.sleep(random.uniform(0.1, 1))  # Simulate production time

def consumer():
    for i in range(10):  # Consume 10 items
        item = buffer.get()  # Take an item from the buffer
        print(f"Consumer consumed item {item}")
        time.sleep(random.uniform(0.1, 1))  # Simulate consumption time

# Create producer threads
producers = [threading.Thread(target=producer) for _ in range(NUM_PRODUCERS)]

# Create consumer threads
consumers = [threading.Thread(target=consumer) for _ in range(NUM_CONSUMERS)]

# Start producer threads
for producer_thread in producers:
    producer_thread.start()

# Start consumer threads
for consumer_thread in consumers:
    consumer_thread.start()

# Join producer threads
for producer_thread in producers:
    producer_thread.join()

# Join consumer threads
for consumer_thread in consumers:
    consumer_thread.join()


# In[1]:


#Program-13
class Partition:
    def __init__(self, start_address, size):
        self.start_address = start_address
        self.size = size
        self.is_allocated = False

class MemoryManager:
    def __init__(self, num_partitions, memory_size):
        self.num_partitions = num_partitions
        self.memory_size = memory_size
        self.partitions = [Partition(i * (memory_size // num_partitions), memory_size // num_partitions) for i in range(num_partitions)]

    def display_partitions(self):
        print("Partitions:")
        for i, partition in enumerate(self.partitions):
            print(f"Partition {i + 1}: Start Address: {partition.start_address}, Size: {partition.size}, Allocated: {'Yes' if partition.is_allocated else 'No'}")

    def allocate_first_fit(self, size):
        for partition in self.partitions:
            if not partition.is_allocated and partition.size >= size:
                partition.is_allocated = True
                return partition.start_address
        return -1  # No suitable partition found

    def allocate_worst_fit(self, size):
        max_size = -1
        max_index = -1
        for i, partition in enumerate(self.partitions):
            if not partition.is_allocated and partition.size >= size and partition.size > max_size:
                max_size = partition.size
                max_index = i
        if max_index != -1:
            self.partitions[max_index].is_allocated = True
            return self.partitions[max_index].start_address
        return -1  # No suitable partition found

    def allocate_best_fit(self, size):
        min_size = self.memory_size + 1
        min_index = -1
        for i, partition in enumerate(self.partitions):
            if not partition.is_allocated and partition.size >= size and partition.size < min_size:
                min_size = partition.size
                min_index = i
        if min_index != -1:
            self.partitions[min_index].is_allocated = True
            return self.partitions[min_index].start_address
        return -1  # No suitable partition found

memory_manager = MemoryManager(5, 1000)

print("Initial State:")
memory_manager.display_partitions()

size = 300
print(f"\nAllocating memory of size {size} using First Fit...")
first_fit_address = memory_manager.allocate_first_fit(size)
if first_fit_address != -1:
    print(f"Memory allocated at address: {first_fit_address}")
else:
    print("Memory allocation failed. No suitable partition found.")
memory_manager.display_partitions()

size = 400
print(f"\nAllocating memory of size {size} using Worst Fit...")
worst_fit_address = memory_manager.allocate_worst_fit(size)
if worst_fit_address != -1:
    print(f"Memory allocated at address: {worst_fit_address}")
else:
    print("Memory allocation failed. No suitable partition found.")
memory_manager.display_partitions()

size = 200
print(f"\nAllocating memory of size {size} using Best Fit...")
best_fit_address = memory_manager.allocate_best_fit(size)
if best_fit_address != -1:
    print(f"Memory allocated at address: {best_fit_address}")
else:
    print("Memory allocation failed. No suitable partition found.")
memory_manager.display_partitions()


# In[2]:


#Program-14
from collections import deque, Counter
import heapq

class PageReplacement:
    def __init__(self, num_frames):
        self.num_frames = num_frames
        self.frames = deque(maxlen=num_frames)
        self.page_faults = 0

    def display_frames(self):
        print("Frames:", list(self.frames))

    def fifo(self, pages):
        self.frames.clear()
        self.page_faults = 0
        for page in pages:
            if page not in self.frames:
                if len(self.frames) == self.num_frames:
                    self.frames.popleft()
                self.frames.append(page)
                self.page_faults += 1
            self.display_frames()
        print("Total page faults:", self.page_faults)

    def lru(self, pages):
        self.frames.clear()
        self.page_faults = 0
        access_times = {}
        for page in pages:
            if page not in self.frames:
                if len(self.frames) == self.num_frames:
                    oldest_page = min(self.frames, key=lambda x: access_times[x])
                    self.frames.remove(oldest_page)
                self.frames.append(page)
                self.page_faults += 1
            access_times[page] = access_times.get(page, 0) + 1
            self.display_frames()
        print("Total page faults:", self.page_faults)

    def lfu(self, pages):
        self.frames.clear()
        self.page_faults = 0
        access_counts = Counter()
        for page in pages:
            if page not in self.frames:
                if len(self.frames) == self.num_frames:
                    least_frequent_page = min(self.frames, key=lambda x: (access_counts[x], pages.index(x)))
                    self.frames.remove(least_frequent_page)
                self.frames.append(page)
                self.page_faults += 1
            access_counts[page] += 1
            self.display_frames()
        print("Total page faults:", self.page_faults)

# Test with sample pages
pages = [1, 3, 2, 4, 5, 1, 6, 3, 7, 8]
num_frames = 3

page_replacement = PageReplacement(num_frames)

print("FIFO Page Replacement Algorithm:")
page_replacement.fifo(pages)

print("\nLRU Page Replacement Algorithm:")
page_replacement.lru(pages)

print("\nLFU Page Replacement Algorithm:")
page_replacement.lfu(pages)


# In[ ]:


#Program-15
import random

NUM_FRAMES = 4
FRAME_SIZE = 1024  # in bytes
PAGE_SIZE = 256  # in bytes
NUM_PAGES = 16

class PageTableEntry:
    def __init__(self):
        self.frame_number = -1
        self.is_valid = False

page_table = [PageTableEntry() for _ in range(NUM_PAGES)]
memory = [['' for _ in range(FRAME_SIZE)] for _ in range(NUM_FRAMES)]

def initialize_page_table():
    for entry in page_table:
        entry.frame_number = -1
        entry.is_valid = False

def display_page_table():
    print("Page Table:")
    for i, entry in enumerate(page_table):
        print(f"Page {i} -> Frame {entry.frame_number}, Valid: {'Yes' if entry.is_valid else 'No'}")

def display_memory():
    print("Memory:")
    for i, frame in enumerate(memory):
        print(f"Frame {i}: {''.join(frame)}")

def simulate_paging(pages):
    initialize_page_table()

    for page_number in pages:
        if not page_table[page_number].is_valid:  # Page fault
            frame_number = random.randint(0, NUM_FRAMES - 1)  # Select a frame randomly
            page_table[page_number].frame_number = frame_number
            page_table[page_number].is_valid = True

            # Simulate loading page data into memory
            for j in range(PAGE_SIZE):
                memory[frame_number][j] = chr(ord('A') + page_number)  # Assigning some data for demonstration

        display_page_table()
        display_memory()
        print()

def main():
    pages = list(range(NUM_PAGES))

    simulate_paging(pages)

if __name__ == "__main__":
    main()


# In[1]:


#Program-16
class BankersAlgorithm:
    def __init__(self, available, max, allocation):
        self.available = available
        self.max = max
        self.allocation = allocation
        self.need = [[max[i][j] - allocation[i][j] for j in range(len(available))] for i in range(len(max))]
        self.num_processes = len(max)
        self.num_resources = len(available)
        self.finished = [False] * self.num_processes

    def is_safe_state(self):
        work = self.available[:]
        finish = self.finished[:]
        safe_sequence = []

        while True:
            found = False
            for i in range(self.num_processes):
                if not finish[i] and all(need <= work for need, work in zip(self.need[i], work)):
                    work = [work[j] + self.allocation[i][j] for j in range(self.num_resources)]
                    finish[i] = True
                    safe_sequence.append(i)
                    found = True
                    break
            if not found:
                break

        return all(finish)

    def request_resources(self, process, request):
        if all(request[i] <= self.need[process][i] for i in range(self.num_resources))                 and all(request[i] <= self.available[i] for i in range(self.num_resources)):

            for i in range(self.num_resources):
                self.available[i] -= request[i]
                self.allocation[process][i] += request[i]
                self.need[process][i] -= request[i]

            if self.is_safe_state():
                return f"Request from process {process} granted. Safe state reached."
            else:
                for i in range(self.num_resources):
                    self.available[i] += request[i]
                    self.allocation[process][i] -= request[i]
                    self.need[process][i] += request[i]
                return f"Request from process {process} denied. Unsafe state."

        else:
            return f"Request from process {process} denied. Request exceeds maximum or available resources."

    def display_state(self):
        print("Available resources:", self.available)
        print("Maximum resources:")
        for i in range(self.num_processes):
            print(f"Process {i}: {self.max[i]}")
        print("Allocated resources:")
        for i in range(self.num_processes):
            print(f"Process {i}: {self.allocation[i]}")
        print("Need resources:")
        for i in range(self.num_processes):
            print(f"Process {i}: {self.need[i]}")

# Example usage
available_resources = [3, 3, 2]
maximum_resources = [
    [7, 5, 3],
    [3, 2, 2],
    [9, 0, 2],
    [2, 2, 2],
    [4, 3, 3]
]
allocated_resources = [
    [0, 1, 0],
    [2, 0, 0],
    [3, 0, 2],
    [2, 1, 1],
    [0, 0, 2]
]

banker = BankersAlgorithm(available_resources, maximum_resources, allocated_resources)
banker.display_state()

print(banker.request_resources(1, [0, 1, 0]))
print(banker.request_resources(4, [2, 0, 0]))
print(banker.request_resources(0, [3, 0, 2]))
print(banker.request_resources(2, [2, 1, 1]))
print(banker.request_resources(3, [0, 0, 2]))


# In[2]:


#Program-17(1)
class SequentialFileAllocation:
    def __init__(self, num_blocks):
        self.disk = [0] * num_blocks  # 0 indicates free block, 1 indicates allocated block
        self.num_blocks = num_blocks

    def allocate_blocks(self, num_blocks):
        start_block = -1
        count = 0
        for i in range(self.num_blocks):
            if self.disk[i] == 0:
                if start_block == -1:
                    start_block = i
                count += 1
                if count == num_blocks:
                    for j in range(start_block, start_block + num_blocks):
                        self.disk[j] = 1
                    return start_block
            else:
                start_block = -1
                count = 0
        return -1  # Not enough contiguous blocks available

    def deallocate_blocks(self, start_block, num_blocks):
        for i in range(start_block, start_block + num_blocks):
            self.disk[i] = 0

    def display_disk(self):
        print("Disk Status:")
        print(" ".join(str(block) for block in self.disk))

# Example usage
sequential = SequentialFileAllocation(100)
start_block = sequential.allocate_blocks(3)
if start_block != -1:
    print(f"File allocated starting from block {start_block}")
sequential.display_disk()
sequential.deallocate_blocks(start_block, 3)
print("Blocks deallocated.")
sequential.display_disk()


# In[3]:


#Program-17(2)
class IndexedFileAllocation:
    def __init__(self, num_blocks):
        self.disk = [0] * num_blocks  # 0 indicates free block, 1 indicates allocated block
        self.index = None

    def allocate_blocks(self, num_blocks):
        index_block = []
        start_block = -1
        for i in range(len(self.disk)):
            if self.disk[i] == 0:
                self.disk[i] = 1
                index_block.append(i)
                if len(index_block) == num_blocks:
                    self.index = index_block
                    return index_block[0]
            else:
                index_block = []
        return -1  # Not enough contiguous blocks available

    def deallocate_blocks(self):
        for block in self.index:
            self.disk[block] = 0
        self.index = None

    def display_disk(self):
        print("Disk Status:")
        print(" ".join(str(block) for block in self.disk))

# Example usage
indexed = IndexedFileAllocation(100)
start_block = indexed.allocate_blocks(3)
if start_block != -1:
    print(f"File allocated starting from block {start_block}")
indexed.display_disk()
indexed.deallocate_blocks()
print("Blocks deallocated.")
indexed.display_disk()


# In[4]:


#Program-17(3)
class Node:
    def __init__(self, block_number):
        self.block_number = block_number
        self.next = None

class LinkedFileAllocation:
    def __init__(self, num_blocks):
        self.disk = [0] * num_blocks  # 0 indicates free block, 1 indicates allocated block
        self.head = None

    def allocate_block(self):
        for i in range(len(self.disk)):
            if self.disk[i] == 0:
                self.disk[i] = 1
                new_node = Node(i)
                if not self.head:
                    self.head = new_node
                else:
                    current = self.head
                    while current.next:
                        current = current.next
                    current.next = new_node
                return i
        return -1  # No free blocks available

    def deallocate_blocks(self):
        current = self.head
        while current:
            self.disk[current.block_number] = 0
            current = current.next
        self.head = None

    def display_disk(self):
        print("Disk Status:")
        print(" ".join(str(block) for block in self.disk))

# Example usage
linked = LinkedFileAllocation(100)
for _ in range(5):
    block_number = linked.allocate_block()
    if block_number != -1:
        print(f"Block {block_number} allocated.")
linked.display_disk()
linked.deallocate_blocks()
print("Blocks deallocated.")
linked.display_disk()


# In[5]:


#Program-18(1)
class SingleLevelDirectory:
    def __init__(self):
        self.files = {}

    def create_file(self, filename, start_block, num_blocks):
        self.files[filename] = {'start_block': start_block, 'num_blocks': num_blocks}

    def display_directory(self):
        print("Single Level Directory:")
        for filename, info in self.files.items():
            print(f"Filename: {filename}, Start Block: {info['start_block']}, Number of Blocks: {info['num_blocks']}")


# Example usage
single_level_dir = SingleLevelDirectory()
single_level_dir.create_file("file1.txt", 0, 3)
single_level_dir.create_file("file2.txt", 3, 2)
single_level_dir.display_directory()


# In[6]:


#Program-18(2)
class TwoLevelDirectory:
    def __init__(self):
        self.directories = {}

    def create_directory(self, dirname):
        self.directories[dirname] = {}

    def create_file(self, dirname, filename, start_block, num_blocks):
        if dirname not in self.directories:
            print("Error: Directory does not exist.")
            return
        self.directories[dirname][filename] = {'start_block': start_block, 'num_blocks': num_blocks}

    def display_directory(self, dirname):
        print(f"Directory: {dirname}")
        if dirname in self.directories:
            for filename, info in self.directories[dirname].items():
                print(f"Filename: {filename}, Start Block: {info['start_block']}, Number of Blocks: {info['num_blocks']}")
        else:
            print("Error: Directory does not exist.")


# Example usage
two_level_dir = TwoLevelDirectory()
two_level_dir.create_directory("directory1")
two_level_dir.create_file("directory1", "file1.txt", 0, 3)
two_level_dir.create_file("directory1", "file2.txt", 3, 2)
two_level_dir.display_directory("directory1")


# In[7]:


#Program-18(3)
class Directory:
    def __init__(self, dirname):
        self.dirname = dirname
        self.subdirectories = {}
        self.files = []

    def create_directory(self, dirname):
        self.subdirectories[dirname] = Directory(dirname)

    def create_file(self, filename, start_block, num_blocks):
        self.files.append({'filename': filename, 'start_block': start_block, 'num_blocks': num_blocks})

    def display_directory(self, indent=0):
        print(" " * indent + f"Directory: {self.dirname}")
        for file in self.files:
            print(" " * (indent + 2) + f"Filename: {file['filename']}, Start Block: {file['start_block']}, Number of Blocks: {file['num_blocks']}")
        for subdirectory in self.subdirectories.values():
            subdirectory.display_directory(indent + 2)


# Example usage
root_directory = Directory("root")
root_directory.create_directory("directory1")
root_directory.subdirectories["directory1"].create_file("file1.txt", 0, 3)
root_directory.subdirectories["directory1"].create_file("file2.txt", 3, 2)
root_directory.display_directory()


# In[8]:


#Program-18(4)
class Directory:
    def __init__(self, dirname):
        self.dirname = dirname
        self.subdirectories = []
        self.files = []

    def create_directory(self, dirname):
        self.subdirectories.append(Directory(dirname))

    def create_file(self, filename, start_block, num_blocks):
        self.files.append({'filename': filename, 'start_block': start_block, 'num_blocks': num_blocks})

    def display_directory(self, indent=0):
        print(" " * indent + f"Directory: {self.dirname}")
        for file in self.files:
            print(" " * (indent + 2) + f"Filename: {file['filename']}, Start Block: {file['start_block']}, Number of Blocks: {file['num_blocks']}")
        for subdirectory in self.subdirectories:
            subdirectory.display_directory(indent + 2)


# Example usage
root_directory = Directory("root")
root_directory.create_directory("directory1")
root_directory.subdirectories[0].create_file("file1.txt", 0, 3)
root_directory.subdirectories[0].create_file("file2.txt", 3, 2)
root_directory.display_directory()


# In[ ]:




