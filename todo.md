# Philosophers Project - Management Tasks & Implementation Guide

## 🎯 Project Overview
**Duration**: 3 Days
**Goal**: Implement a complete dining philosophers solution with comprehensive testing
**Team Size**: 1 Developer

## 📅 Day-by-Day Breakdown

### Day 1: Foundation & Core Structure (8 hours)

#### Morning Session (4 hours)
**Task 1.1: Project Setup & Basic Structures (2 hours)**
- [ ] Create project directory structure
- [ ] Set up Makefile with proper compilation flags
- [ ] Define all data structures in `philosophers.h`
- [ ] Implement basic utility functions (`ft_atoi`, `ft_isdigit`)

**Task 1.2: Argument Parsing & Validation (2 hours)**
- [ ] Implement `init_data()` function
- [ ] Add comprehensive argument validation
- [ ] Create error handling for invalid inputs
- [ ] Write unit tests for argument parsing

**Test Requirements for Day 1:**
```bash
# Create test_args.sh
./philo                          # Should show usage
./philo 5                        # Should show error
./philo 5 800 200 200            # Should be valid
./philo 0 800 200 200            # Should show error
./philo -5 800 200 200           # Should show error
./philo abc 800 200 200          # Should show error
```

#### Afternoon Session (4 hours)
**Task 1.3: Memory Management & Initialization (2 hours)**
- [ ] Implement `init_forks()` function
- [ ] Implement `init_philo()` function
- [ ] Create `clean_data()` cleanup function
- [ ] Test memory allocation/deallocation

**Task 1.4: Time Management System (2 hours)**
- [ ] Implement `get_time()` function
- [ ] Implement `pre_sleep() - precise_sleep` function
- [ ] Create timing utility functions
- [ ] Write timing accuracy tests

**Test Requirements:**
```bash
# Create test_timing.sh
# Test timing precision
time ./test_sleep 1000  # Should sleep ~1 second
```

---

### Day 2: Threading & Synchronization (8 hours)

#### Morning Session (4 hours)
**Task 2.1: Basic Threading Infrastructure (2 hours)**
- [ ] Implement thread creation functions
- [ ] Create philosopher routine skeleton
- [ ] Implement thread synchronization (`wait_threads`)
- [ ] Basic thread lifecycle management

**Task 2.2: Mutex Implementation (2 hours)**
- [ ] Initialize all mutex types (fork, print, state, meal)
- [ ] Implement safe printing function
- [ ] Create simulation state management
- [ ] Test basic mutex functionality

**Test Requirements:**
```bash
# Create test_threads.sh
./philo 2 800 200 200    # Test with 2 philosophers
./philo 5 800 200 200    # Test with 5 philosophers
# Output should be clean and synchronized
```

#### Afternoon Session (4 hours)
**Task 2.3: Deadlock Prevention System (3 hours)**
- [ ] Implement even/odd fork ordering strategy
- [ ] Create `setup_forks()` function
- [ ] Implement philosopher staggering
- [ ] Test deadlock prevention

**Task 2.4: Action Functions (1 hour)**
- [ ] Implement basic `sleeping_process()` and `thinking_process()`
- [ ] Create status printing system
- [ ] Basic simulation flow

**Test Requirements:**
```bash
# Create test_deadlock.sh
./philo 4 800 200 200    # Run for 30 seconds, should not deadlock
./philo 10 800 200 200   # Test with more philosophers
```

---

### Day 3: Advanced Features & Testing (8 hours)

#### Morning Session (4 hours)
**Task 3.1: Complete Eating Implementation (2 hours)**
- [ ] Implement full `eating_process()` function
- [ ] Fork acquisition and release logic
- [ ] Meal counting and timing
- [ ] Handle single philosopher case

**Task 3.2: Death Detection & Monitoring (2 hours)**
- [ ] Implement monitor thread
- [ ] Death detection algorithm
- [ ] Simulation termination logic
- [ ] Meal completion detection

**Test Requirements:**
```bash
# Create test_eating.sh
./philo 1 800 200 200           # Single philosopher should die
./philo 5 400 200 200           # Should detect death
./philo 5 800 200 200 7         # Should stop after 7 meals each
```

#### Afternoon Session (4 hours)
**Task 3.3: Comprehensive Testing Suite (2 hours)**
- [ ] Create automated test scripts
- [ ] Performance testing
- [ ] Edge case testing
- [ ] Memory leak testing

**Task 3.4: Bug Fixes & Optimization (2 hours)**
- [ ] Fix any remaining issues
- [ ] Code review and cleanup
- [ ] Documentation updates
- [ ] Final validation

---

## 🧪 Unit Testing Framework

### Core Test Files to Create:

#### `tests/test_args.c`
```c
// Test argument parsing and validation
void test_valid_args(void);
void test_invalid_args(void);
void test_edge_cases(void);
```

#### `tests/test_timing.c`
```c
// Test timing accuracy
void test_get_time_accuracy(void);
void test_precise_sleep(void);
void test_time_calculations(void);
```

#### `tests/test_threading.c`
```c
// Test thread safety and synchronization
void test_thread_creation(void);
void test_mutex_safety(void);
void test_deadlock_prevention(void);
```

#### `tests/test_simulation.c`
```c
// Test complete simulation scenarios
void test_normal_operation(void);
void test_death_detection(void);
void test_meal_counting(void);
```

### Test Automation Script:
```bash
#!/bin/bash
# tests/run_all_tests.sh

echo "Running Philosophers Test Suite..."

# Compilation test
make re || exit 1

# Basic functionality tests
echo "Testing argument parsing..."
bash tests/test_args.sh

echo "Testing timing functions..."
bash tests/test_timing.sh

echo "Testing threading..."
bash tests/test_threading.sh

echo "Testing simulation scenarios..."
bash tests/test_simulation.sh

echo "Testing for memory leaks..."
valgrind --leak-check=full ./philo 5 800 200 200 7

echo "All tests completed!"
```

---

## 🚨 Common Problems & Solutions

### Problem 1: Data Races
**Symptoms**: Inconsistent output, program crashes, undefined behavior
**Detection**:
```bash
gcc -fsanitize=thread -g philosopher.c
./philo 5 800 200 200
```
**Solutions**:
- Always protect shared data with mutexes
- Use proper locking order
- Avoid holding multiple locks simultaneously when possible

### Problem 2: Deadlocks
**Symptoms**: Program hangs, no output after initial messages
**Detection**:
- Program runs >10 seconds without progress
- All philosophers stuck in "has taken a fork" state
**Solutions**:
- Implement even/odd fork ordering
- Add timeout mechanisms
- Use philosopher staggering

### Problem 3: Race Conditions in Death Detection
**Symptoms**: Multiple death messages, death detection delays
**Detection**:
```bash
./philo 5 400 200 200  # Should show exactly one death
```
**Solutions**:
- Protect death checking with mutexes
- Use atomic flags for simulation stop
- Ensure monitor thread has proper synchronization

### Problem 4: Memory Leaks
**Symptoms**: Memory usage grows over time
**Detection**:
```bash
valgrind --leak-check=full ./philo 5 800 200 200 7
```
**Solutions**:
- Always free allocated memory
- Properly destroy mutexes
- Clean up on all exit paths

### Problem 5: Timing Issues
**Symptoms**: Philosophers die when they shouldn't, inaccurate sleep times
**Detection**:
```bash
# Test timing precision
time ./philo 5 1000 100 100
```
**Solutions**:
- Use precise timing functions
- Account for execution overhead
- Test timing accuracy regularly

---

## 📊 Performance Benchmarks

### Target Performance Metrics:
- **No deadlocks**: Program should run indefinitely without hanging
- **Accurate timing**: ±10ms precision for sleep/eat times
- **Fair scheduling**: No philosopher should eat >2x more than others
- **Memory efficiency**: <1MB total memory usage
- **CPU efficiency**: <50% CPU usage for 5 philosophers

### Benchmark Tests:
```bash
# Performance test script
#!/bin/bash

echo "Performance Benchmarking..."

# Test 1: Deadlock resistance
timeout 30s ./philo 10 800 200 200 && echo "✓ No deadlock in 30s"

# Test 2: Memory usage
valgrind --tool=massif ./philo 5 800 200 200 7
ms_print massif.out.* | grep "peak"

# Test 3: CPU usage
timeout 10s perf stat ./philo 20 800 200 200

# Test 4: Timing accuracy
for i in {1..5}; do
    time ./philo 3 1000 500 500 2
done
```

---

## 🔍 Code Review Checklist

### Day 1 Review:
- [ ] All structures properly defined
- [ ] Argument validation covers edge cases
- [ ] Memory allocation has error checking
- [ ] Basic functions compile without warnings

### Day 2 Review:
- [ ] All mutexes properly initialized/destroyed
- [ ] Thread creation/joining handled correctly
- [ ] Deadlock prevention strategy implemented
- [ ] Basic simulation runs without hanging

### Day 3 Review:
- [ ] Death detection works accurately
- [ ] Meal counting is thread-safe
- [ ] Single philosopher case handled
- [ ] All test cases pass
- [ ] No memory leaks detected
- [ ] Code follows 42 norm

---

## 📝 Final Deliverables

### Required Files:
```
philosophers/
├── Makefile
├── philosophers.h
├── main.c
├── initialization.c
├── philo_actions.c
├── routine.c
├── monitor.c
├── time_management.c
├── string_operations.c
├── utils.c
└── tests/
    ├── run_all_tests.sh
    ├── test_args.sh
    ├── test_timing.sh
    ├── test_threading.sh
    └── test_simulation.sh
```

### Documentation:
- [ ] Project README with usage instructions
- [ ] Test results documentation
- [ ] Performance benchmark results
- [ ] Known issues and limitations
- [ ] Code comments and explanations

---

## 🎯 Success Criteria

### Minimum Viable Product (MVP):
- [ ] Compiles without warnings
- [ ] Handles basic test cases
- [ ] No obvious deadlocks
- [ ] Basic death detection works

### Full Success:
- [ ] All test cases pass
- [ ] No memory leaks
- [ ] Performance meets benchmarks
- [ ] Code follows all standards
- [ ] Comprehensive documentation

### Excellence:
- [ ] Advanced testing suite
- [ ] Performance optimizations
- [ ] Error handling edge cases
- [ ] Clean, maintainable code
- [ ] Detailed problem analysis

---

**Remember**: Focus on getting a working solution first, then optimize. Test frequently, commit often, and document everything!
