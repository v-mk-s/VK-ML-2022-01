#ifndef MAIL_LIB_MAIL_H_
#define MAIL_LIB_MAIL_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_USERNAME_SIZE 20
#define MAX_MAIL_SERVICE_NAME_SIZE 10
#define MAX_TOP_LEVEL_DOMAIN_SIZE 10

#define OK true
#define ERROR false
#define nullptr NULL

#define MAX_CHARS_IN_BUF 100

typedef struct Mail {
    char *username;
    char *mail_service_name;
    char *top_level_domain;
} Mail;

/* Creates new struct Mail. Returns pointer to struct or NULL */
bool create_mail_pointer_to_struct(FILE* file, Mail **new_mail_p);

/* Returns NULL on failure */
char *input_string(FILE* file);
// char input_char(FILE* file);

bool is_letter(char c);
bool is_digit(char c);
bool is_spec_symbol(char c);
bool is_username_sym(char c);

bool parse_string_as_mail(char const * string, Mail * mail);
void delete_parse_p(char *p1, char *p2, char *p3);
bool print_mail(const Mail * const mail);
bool delete_mail(Mail **mail);

#endif  // MAIL_LIB_MAIL_H_
