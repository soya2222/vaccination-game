# SIR with vaccination
Original code:
https://github.com/pholme/sir

To get it running you need:

1. Make dictionary o (for complier object files)
2. Compile it by make (it has some generic optimization flags now)
3. Run it like

usage: ./sir [nwk file] [beta] [coverage] <seed>

The third argument is the vaccination coverage. This argument should be between 0 to 1, where 1 denotes that every node gets vaccinated against the infection.

I removed fourth argument (efficacy). 
