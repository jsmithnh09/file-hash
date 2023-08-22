#include "uuid4.h"
#include <stdio.h>

/*********************************************************
* Filename: UUID4GEN
* Description: Generate a UUID4-compliant string to STDOUT.
**********************************************************/

/*********************************************************
* UUID4GEN <NO ARGS>
**********************************************************/
int main(int argc, char *argv[]) {
    char *uuid = uuid4();
    printf("UUID4: %.36s\n", uuid);
    free(uuid);
    return 0;
}