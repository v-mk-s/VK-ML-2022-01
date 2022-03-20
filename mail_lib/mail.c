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
    string = input_string();
    if (!string) {
        return ERROR;
    }

    bool success = parse_string_as_mail(string, new_mail);
    if (!success) {
        return ERROR;
    }

    return OK;
}

char *input_string()
{
    struct buffer
    {
        char *string;
        size_t size;
        size_t capacity;
    } buf = {NULL, 0, 0};
    char c = '\0';
    while (c = input_char(), c != EOF && c != '\n')
    {
        if (buf.size + 1 >= buf.capacity)
        {
            size_t new_capacity = !buf.capacity ? 1 : buf.capacity * 2;
            char *tmp = (char *)malloc((new_capacity + 1) * sizeof(char));
            if (!tmp)
            {
                if (buf.string)
                {
                    free(buf.string);
                }
                return NULL;
            }
            if (buf.string)
            {
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

char input_char()
{
    char c = '\0';
    int result = 0;

    int i = 0;
    do
    {
        result = scanf("%c", &c);
        ++i;
    } while ((result != 1) && (i != MAX_INPUT_CHAR_TRY));
    return c;
}

bool is_letter(char c)
{
    return ((c >= 'a') && (c <= 'z') || (c >= 'A') && (c <= 'Z'));
}

bool is_digit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

bool is_spec_symbol(char c)
{
    return ((c == '.') || (c == '_') || (c == '-'));
}

bool is_username_sym(char c)
{
    return (is_letter(c) || is_digit(c) || is_spec_symbol(c));
}

bool parse_string_as_mail(char const *const string, Mail *const mail)
{
    char *username = (char *)malloc((MAX_USERNAME_SIZE + 1) * sizeof(char));
    char *mail_service_name = (char *)malloc((MAX_MAIL_SERVICE_NAME_SIZE + 1) * sizeof(char));
    char *top_level_domain = (char *)malloc((MAX_TOP_LEVEL_DOMAIN_SIZE + 1) * sizeof(char));

    char const * string_p = string;
    size_t inx_name = 0;
    while ((*string_p != '\0') && (inx_name < MAX_USERNAME_SIZE) && (*string_p != '@') && is_username_sym(*string_p)) {
        username[inx_name] = *string_p;
        ++string_p;
        ++inx_name;
    }
    username[inx_name] = '\0';
    if (*string_p == '@') {
        mail->username = username;
    }
    else {
        return ERROR;
    }

    ++string_p;
    size_t inx_mail = 0;
    while ((*string_p != '\0') && (inx_mail < MAX_MAIL_SERVICE_NAME_SIZE) && (*string_p != '.') && is_letter(*string_p)) {
        mail_service_name[inx_mail] = *string_p;
        ++string_p;
        ++inx_mail;
    }
    mail_service_name[inx_mail] = '\0';
    if (*string_p == '.') {
        mail->mail_service_name = mail_service_name;
    }
    else {
        return ERROR;
    }

    ++string_p;
    size_t inx_tld = 0;
    while ((*string_p != '\0') && (inx_tld < MAX_TOP_LEVEL_DOMAIN_SIZE) && (*string_p != '\n') && is_letter(*string_p))
    {
        top_level_domain[inx_tld] = *string_p;
        ++string_p;
        ++inx_tld;
    }
    top_level_domain[inx_tld] = '\0';
    if ((*string_p == '\0') || (*string_p == '\n')) {
        mail->top_level_domain = top_level_domain;
    }
    else {
        return ERROR;
    }

    mail->username = username;
    mail->mail_service_name = mail_service_name;
    mail->top_level_domain = top_level_domain;

    return OK;
}

bool print_mail(const Mail * const mail, bool success) {
    if (success) {
        printf("Email address was successfully parsed:\n");
        printf("    Username: %s\n", mail->username);
        printf("    Name of the mail service: %s\n", mail->mail_service_name);
        printf("    Top-level domain: %s\n", mail->top_level_domain);
        printf("Email: %s@%s.%s\n", mail->username, mail->mail_service_name, mail->top_level_domain);
    } else {
        puts("Wrong Email!");
        puts("NULL pointer!");
    }

    return OK;
}

bool delete_mail(Mail *mail) {
    if (!mail) {
        return OK;
    }
    if (mail->username) {
        free(mail->username);
    }
    if (mail->mail_service_name) {
        free(mail->mail_service_name);
    }
    if (mail->top_level_domain) {
        free(mail->top_level_domain);
    }

    free(mail);
    return OK;
}
