# Operating Systems | Jagiellonian University

**winter semester 2024/2025**

# Tech

**Language:** C99  
**Environment:** Unix/Linux

This repository contains a collection of programs developed for the Operating Systems course, focusing on process management, signals, inter-process communication (IPC), and thread synchronization. Each task has it's own README.md in polish wiht more details and specific running instructions.

## Project Overview

### Project Structure

Codebase is documented in English but the README's are written in Polish. Each task (`cwX/`) follows a layout:

```text
.
├── src/                # C source code
├── Makefile            # Makefile for compilation and running
├── README.md           # Task description and exectuion instructions in polish
└── test_files.txt      # Example files needed for working program showcase

```

### [Task 1 (cw2)] Process Management & Hierarchy

- **Focus:** Understanding PID, PPID, UID, GID, and the `fork()` system call.
- **Programs:**
  - **A:** Displays process credentials (UID, GID, PID, PPID, PGID).
  - **B:** Creates child processes and prints their information.
  - **C:** Demonstrates process orphaning to observe adoption by the system init process.
  - **D:** Uses `sleep()` to force a specific printing order from the oldest to the youngest generation.
  - **E:** Implements process group modification using `setpgid()`.

### [Task 2 (cw2)] Executing External Programs

- **Focus:** Creating processes with `fork()` and replacing the process image with `execl()`.
- **Description:** A master program creates 3 child processes that execute an external program (`process_info.c`) to display their metadata.

### [Task 3 (cw3)] Signal Handling

- **Focus:** Handling and sending Unix signals.
- **Programs:**
  - **3a:** Sets various signal handling methods (default, ignore, custom handler).
  - **3b:** A parent process creates a child and sends a specific signal to it.
  - **3c:** A master program spawns a "spawner" process which acts as a group leader and broadcasts signals to all its children.

### [Task 4 (cw4)] Anonymous Pipes

- **Focus:** Basic IPC using unnamed pipes (`pipe`).
- **Description:** Implements a producer-consumer model where data is read from a file, passed through a pipe to a child process, and then saved to a destination file.

### [Task 5 (cw5)] Named Pipes (FIFOs)

- **Focus:** Inter-process communication using FIFO files.
- **Description:** A manager program creates a named pipe and spawns two independent processes (Producer and Consumer) that communicate through it.

### [Task 6 (cw6)] Mutex with Semaphores

- **Focus:** Solving the critical section problem using semaphores.
- **Description:** A set of programs using a custom semaphore library to ensure mutual exclusion between processes accessing shared resources.

### [Task 7 (cw7)] Shared Memory & Circular Buffer

- **Focus:** High-performance IPC using Shared Memory and Semaphores.
- **Description:** Implements a producer-consumer system with a circular buffer located in shared memory. Synchronization is managed via semaphores to prevent race conditions.

### [Task 8 (cw8)] Message Queues

- **Focus:** Client-Server architecture using Message Queues.
- **Description:** Clients send mathematical data to a server via a request queue. The server processes the data and sends the result back to a specific client-owned response queue.

### [Task 9 (cw9)] Thread Synchronization (Mutex)

- **Focus:** POSIX threads (`pthreads`) and mutual exclusion locks.
- **Description:** Multiple threads increment a global counter within a critical section protected by a mutex to ensure data integrity.

### [Task 10 (cw10)] Bakery Algorithm

- **Focus:** Software-based mutual exclusion.
- **Description:** Implementation of Lamport's Bakery Algorithm. Threads assign themselves numbers to enter the critical section in a specific order, simulating a ticket system in a bakery.

## Usage & Automation

Each project directory contains a `Makefile` to simplify compilation and execution.

### Compilation

To compile the programs:

```bash
make all
```

# Author

**Jakub Kurek** Jagiellonian University, Faculty of Physics, Astronomy and Applied Computer Science (FAIS)
