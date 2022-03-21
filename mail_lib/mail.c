#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mail.h"

bool create_mail_pointer_to_struct(FILE* file, Mail **new_mail_p) {
    if (!new_mail_p) {
        return ERROR;
    }

    *new_mail_p = (Mail *)malloc(sizeof(Mail));
    Mail *new_mail = *new_mail_p;
    if (!new_mail) {
        return ERROR;
    }

    new_mail->username = NULL;
    new_mail->mail_service_name = NULL;
    new_mail->top_level_domain = NULL;

    char *string = NULL;
    printf("Enter e-mail\n");
    string = input_string(file);
    if (!string) {
        return ERROR;
    }

    bool success = parse_string_as_mail(string, new_mail);
    if (string) {
        free(string);
    }
    if (!success) {
        return ERROR;
    }

    return OK;
}

char *input_string(FILE *file) {
    int str_len = 0;
    int capacity = 1;
    char *string = NULL;
    string = (char *)malloc(sizeof(char));
    if (!string) {
        return ERROR;
    }
    char c = '\0';
    while (((c = fgetc(file)) != EOF) && (c != '\n')) {
        string[str_len] = c;
        ++str_len;
        // printf("%s\n %c\n", string, c);

        if (str_len >= capacity) {
            capacity *= 2;
            char *tmp = NULL;
            tmp = (char *)realloc(string, capacity * sizeof(char));
            if (!tmp) {
                if (string) {
                    free(string);
                }
                return ERROR;
            }
        }
    }
    // printf("OK!");

    string[str_len] = '\0';
    ++str_len;

    return string;
}

// char *input_string(FILE* file) {
//     struct buffer {
//         char *string;
//         size_t size;
//         size_t capacity;
//     } buf = {NULL, 0, 0};
//     char c = '\0';
//     while (c = input_char(file), c != EOF && c != '\n') {
//         if (buf.size + 1 >= buf.capacity) {
//             size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
//             char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
//             if (!tmp) {
//                 if (buf.string) {
//                     free(buf.string);
//                 }
//                 return NULL;
//             }
//             if (buf.string) {
//                 tmp = strncpy(tmp, buf.string, (size_t) MAX_CHARS_IN_BUF);
//                 free(buf.string);
//             }
//             buf.string = tmp;
//             buf.capacity = new_capacity;
//         }
//         buf.string[buf.size] = c;
//         buf.string[buf.size + 1] = '\0';
//         ++buf.size;
//     }
//     return buf.string;
// }

// char input_char(FILE* file) {
//     char* check_fgets = NULL;
//     char buf[MAX_CHARS_IN_BUF] = {0};
//     check_fgets = fgets(buf, MAX_CHARS_IN_BUF, file);
//     char c = '\0';
//     int result = 0;

//     if (check_fgets) {
//         result = sscanf(buf, "%c", &c);
//     }
//     if (result) {
//         c = '\0';
//     }
//     return c;
// }

bool is_letter(char c) {
    return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')));
}

bool is_digit(char c) {
    return ((c >= '0') && (c <= '9'));
}

bool is_spec_symbol(char c) {
    return ((c == '.') || (c == '_') || (c == '-'));
}

bool is_username_sym(char c) {
    return (is_letter(c) || is_digit(c) || is_spec_symbol(c));
}

bool parse_string_as_mail(char const * string, Mail * mail) {
    char *username = (char *)malloc((MAX_USERNAME_SIZE + 1) * sizeof(char));
    char *mail_service_name = (char *)malloc((MAX_MAIL_SERVICE_NAME_SIZE + 1) * sizeof(char));
    char *top_level_domain = (char *)malloc((MAX_TOP_LEVEL_DOMAIN_SIZE + 1) * sizeof(char));

    char const *string_p = string;
    size_t inx_name = 0;
    while ((*string_p != '\0') && (inx_name < MAX_USERNAME_SIZE) &&
           (*string_p != '@') && is_username_sym(*string_p)) {
        username[inx_name] = *string_p;
        ++string_p;
        ++inx_name;
    }
    username[inx_name] = '\0';
    // printf("%s\n", username);
    if (*string_p != '@') {
        delete_parse_p(username, mail_service_name, top_level_domain);
        return ERROR;
    }

    ++string_p;
    size_t inx_mail = 0;
    while ((*string_p != '\0') && (inx_mail < MAX_MAIL_SERVICE_NAME_SIZE) &&
           (*string_p != '.') && is_letter(*string_p)) {
        mail_service_name[inx_mail] = *string_p;
        ++string_p;
        ++inx_mail;
    }
    mail_service_name[inx_mail] = '\0';
    // printf("%s\n", mail_service_name);
    if (*string_p != '.') {
        delete_parse_p(username, mail_service_name, top_level_domain);
        return ERROR;
    }

    ++string_p;
    size_t inx_tld = 0;
    while ((*string_p != '\0') && (inx_tld < MAX_TOP_LEVEL_DOMAIN_SIZE) &&
           (*string_p != '\n') && is_letter(*string_p)) {
        top_level_domain[inx_tld] = *string_p;
        ++string_p;
        ++inx_tld;
    }
    top_level_domain[inx_tld] = '\0';
    // printf("%s\n", top_level_domain);
    if ((*string_p != '\0') && (*string_p != '\n')) {
        delete_parse_p(username, mail_service_name, top_level_domain);
        return ERROR;
    }

    mail->username = username;
    mail->mail_service_name = mail_service_name;
    mail->top_level_domain = top_level_domain;

    return OK;
}

void delete_parse_p(char *p1, char *p2, char *p3) {
    if (p1) {
        free(p1);
    }
    if (p2) {
        free(p2);
    }
    if (p3) {
        free(p3);
    }
}

bool print_mail(const Mail * const mail) {
    if (!mail) {
        puts("Wrong email or pointer!");
        return ERROR;
    }

    if ((mail->username) && (mail->mail_service_name) && (mail->top_level_domain)) {
        printf("Email address was successfully parsed:\n");
        printf("    Username: %s\n", mail->username);
        printf("    Name of the mail service: %s\n", mail->mail_service_name);
        printf("    Top-level domain: %s\n", mail->top_level_domain);
        printf("Email: %s@%s.%s\n", mail->username, mail->mail_service_name, mail->top_level_domain);

        return OK;
    }

    puts("Wrong email or pointer!");
    return ERROR;
}

bool delete_mail(Mail **mail) {
    if (!mail) {
        return ERROR;
    }
    if (!(*mail)) {
        return OK;
    }
    if ((*mail)->username) {
        free((*mail)->username);
    }
    if ((*mail)->mail_service_name) {
        free((*mail)->mail_service_name);
    }
    if ((*mail)->top_level_domain) {
        free((*mail)->top_level_domain);
    }

    free(*mail);
    return OK;
}
