#include "sir.h"

extern GLOBALS g;

void pcg_init () {
	int fd;
	unsigned long sz;
	uint64_t initstate;

	if (g.state != 0) return;

	fd = open("/dev/random", O_RDONLY);
	
	if (fd < 1) {
		fprintf(stderr, " can't open /dev/random\n");
		exit(1);
	}

	sz = read(fd, &initstate, sizeof(uint64_t));
	
	close(fd);

	if (sz < sizeof(uint64_t)) {
		fprintf(stderr, " can't read /dev/random\n");
		exit(1);
	}

	g.state = (initstate + 1442695040888963407ULL) * 6364136223846793005ULL + 1442695040888963407ULL;
}

uint32_t pcg_32 () {
	uint64_t state = g.state;
	uint32_t value, rot;

	g.state = g.state * 6364136223846793005ULL + 1442695040888963407ULL;
	value = ((state >> 18u) ^ state) >> 27u;
	rot = state >> 59u;
	return (value >> rot) | (value << ((- rot) & 31));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint32_t pcg_32_bounded (uint32_t bound) {
	uint32_t threshold = -bound % bound, r;

	for ( ; ; ) {
		r = pcg_32();
		if (r >= threshold) return r % bound;
	}
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

uint16_t pcg_16 () {
	static unsigned int exist;

	if (exist) {
		exist = 0;
		//2^(-16)する
		return g.rmem >> 16;
	}

	exist = 1;
	g.rmem = pcg_32();
    // %2^(16)
	return (uint16_t) g.rmem;

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int get_one_or_zero_randomly(double trsh){
    double my_rand = pcg_16()*(1.0)/(1.0+UINT16_MAX);
    if(my_rand < trsh) return 1;
    else return 0;
}

double get_random_double(){
    double my_rand = pcg_16()*(1.0)/(1.0+UINT16_MAX);
    return my_rand;
}



