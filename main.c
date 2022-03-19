#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mail.h"

int main() {
    Mail *new_mail = NULL;
    bool success = create(&new_mail);

    Mail *created_mail = NULL;
    created_mail = return_pointer_to_struct(new_mail); // my hw1 function
    if (success) {
        print_mail(new_mail);
    } else {
        puts("NULL pointer!");
    }
    delete(new_mail);
    created_mail = NULL;
    return 0;
}
