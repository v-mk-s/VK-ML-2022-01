#ifndef  PROJECT_UTILS_H_
#define  PROJECT_UTILS_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 20
#define MAX_MAIL_SERVICE_NAME_SIZE 10
#define MAX_TOP_LEVEL_DOMAIN_SIZE 10

typedef struct Mail {
    char *name;
    char *mail_service_name;
    char *top_level_domain;
} Mail;

bool create_my_struct(char** params);

bool clear_my_struct(Mail* mail);

char input_char();

/* Returns NULL on failure */
char *input_string();

bool check_string_as_mail(char const *const string, Mail *const mail);

/* Creates new mail. Returns false on failure */
bool create(Mail **new_mail_p);

/* Prints struct */
void print_mail(const Mail * const mail);

/* Return pointer what was asked in the task */
char *return_pointer_to_struct(const Mail *const mail);

void delete(Mail *mail);


#endif // PROJECT_UTILS_H_
