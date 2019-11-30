#include <iostream>
using namespace std;
int main (int argc, char *argv[]) {
    FILE *out;
    out = fopen(argv[1], "w");
    for (int i = 1; i < 10001; i++) {
        fprintf(out, "%d", i);
        fprintf(out, "%s", " ");
    }
    fclose(out);
    return 0;
}