#2.1 Argument Parsing and Validation
The program must begin by parsing the command-line arguments: number_of_philosophers,
time_to_die, time_to_eat, time_to_sleep, and the optional
number_of_times_each_philosopher_must_eat. Each mandatory argument must be a positive
integer. The 42 project guidelines often specify that these values should be within the range of
standard integer types (e.g., representable by int) and non-negative. Custom functions, like a
bespoke ft_atoi, may be required if standard library functions are restricted.
Robust input validation is crucial. Failure to properly validate inputs (e.g., checking for
non-numeric characters, negative values, or --values that are too large--) can lead to undefined
behavior, crashes, or incorrect simulation logic. For instance, a time_to_die of zero or a negative
number of philosophers would render the simulation meaningless. Error handling should be
implemented to inform the user of invalid input and terminate the program gracefully. This initial
step, while seemingly simple, prevents a host of downstream issues and ensures the simulation
starts with a valid and coherent state