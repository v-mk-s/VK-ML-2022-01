#include <stdio.h>
#include <stdbool.h>

#include "mail_lib/mail.h"  // "mail" doesn't work

int main(void) {
    FILE* file = stdin;
    Mail* new_mail = NULL;

    create_mail_pointer_to_struct(file, &new_mail);
    print_mail(new_mail);
    delete_mail(&new_mail);

    return 0;
}
