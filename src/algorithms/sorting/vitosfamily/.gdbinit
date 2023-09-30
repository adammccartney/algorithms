# .gdbinit

# Define breakpoints
break main
break Quicksort
tui enable
display *stack@16
run < tests/2.in

# Display the contents of stack every time we hit a breakpoint
#display *stack@numrel

source scripts/debug.py
