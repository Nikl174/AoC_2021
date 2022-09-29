#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    int i=1, inc=0;
    while (argv[i+1]) {
	int next = atoi(argv[i+1]);
	int current = atoi(argv[i]);
	std::cout << "Next: "<<next<<" Current: "<<current << std::endl;
	if (next>current) {
	    inc++;
	}
	i++;
    }
    std::cout << "Number of times, the depth increased: " <<inc<<" Length: "<<i << std::endl;
    return 0;
}
