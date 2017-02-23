#include <stdio.h>
#include <unistd.h>

int main() {
    puts("Centauri launched.");
    while (1) {
        sleep((unsigned) -1);
    }
    return 0;
}
