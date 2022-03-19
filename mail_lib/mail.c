#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mail.h"

char input_char() {
    char c = '\0';
    int result = 0;
    do {
        result = scanf("%c", &c);
    } while (result != 1);
    return c;
}

bool check_string_as_mail(char const *const string, Mail *const mail)
{
    bool success = true;

    char *name = (char *)malloc((MAX_NAME_SIZE + 1) * sizeof(char));
    char *mail_service_name = (char *)malloc((MAX_NAME_SIZE + 1) * sizeof(char));
    char *top_level_domain = (char *)malloc((MAX_NAME_SIZE + 1) * sizeof(char));

    char const * string_p = string;
    size_t inx_name = 0;
    while ((string_p != '\0') && (inx_name < MAX_NAME_SIZE) && (string_p != '@')) {
        name[inx_name] = string_p;
        ++string_p;
        ++inx_name;
    }
    name[inx_name] = '\0';
    if (string_p == '@') {
        mail->name = name;
    }
    else {
        return false;
    }

    ++string_p;
    size_t inx_mail = 0;
    while ((string_p != '\0') && (inx_mail < MAX_NAME_SIZE) && (string_p != '.')) {
        mail_service_name[inx_mail] = string_p;
        ++string_p;
        ++inx_mail;
    }
    mail_service_name[inx_mail] = '\0';
    if (string_p == '.') {
        mail->mail_service_name = mail_service_name;
    }
    else {
        return false;
    }

    ++string_p;
    size_t inx_tld = 0;
    while ((string_p != '\0') && (inx_tld < MAX_NAME_SIZE) && (string_p != '\n'))
    {
        top_level_domain[inx_tld] = string_p;
        ++string_p;
        ++inx_tld;
    }
    top_level_domain[inx_tld] = '\0';
    if (string_p == '\0') {
        mail->top_level_domain = top_level_domain;
    }
    else {
        return false;
    }

    mail->name = name;
    mail->mail_service_name = mail_service_name;
    mail->top_level_domain = top_level_domain;

    return success;
}

char *input_string()
{
    struct buffer {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = input_char(), c != EOF && c != '\n') {
        if (buf.size + 1 >= buf.capacity) {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp) {
                if (buf.string) {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string) {
                tmp = strcpy(tmp, buf.string);
                free(buf.string);
            }
            buf.string = tmp;
            buf.capacity = new_capacity;
        }
        buf.string[buf.size] = c;
        buf.string[buf.size + 1] = '\0';
        ++buf.size;
    }
    return buf.string;
}

bool create(Mail **new_mail_p) {
    if (!new_mail_p) {
        return false;
    }
    *new_mail_p = (Mail *)malloc(sizeof(Mail));
    Mail *new_mail = *new_mail_p;
    if (!new_mail) {
        return false;
    }
    new_mail->name = NULL;
    new_mail->mail_service_name = NULL;
    new_mail->top_level_domain = NULL;

    char *name = NULL;
    char *mail_service_name = NULL;
    char *top_level_domain = NULL;

    char *string = NULL;
    printf("Enter e-mail\n");
    string = input_string();
    if (!string) {
        return false;
    }

    bool success = check_string_as_mail(string, new_mail);
    if (!success) {
        return false;
    }

    return true;
}

bool is_space(char c) {
    return c == ' ' || c == '\t';
}

void print_escaped_string(const char * const str, const char symbols_to_escape[]) {
    size_t i = 0;
    printf("\"");
    while (str[i] != '\0') {
        if (strchr(symbols_to_escape, str[i])) {
            printf("\\");
        }
        printf("%c", str[i]);
        ++i;
    }
    printf("\"");
}

char *get_url_substring_without_schema(char * str) {
    const char *pattern = "://";
    char *result = str;
    result = strstr(str, pattern);
    if (!result) {
        return str;
    }
    result += strlen(pattern);
    return result;
}

void print_mail(const Mail * const mail) {
    
}

char *return_pointer_to_struct(const Mail *const mail) {
    return mail;    
}

void delete(Mail *mail) {
    if (!mail) {
        return;
    }
    if (mail->name) {
        free(mail->name);
    }
    if (mail->mail_service_name) {
        free(mail->mail_service_name);
    }
    if (mail->top_level_domain) {
        free(mail->top_level_domain);
    }

    free(mail);
}
