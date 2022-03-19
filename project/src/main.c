#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 20
#define MAX_MAIL_SERVICE_NAME_SIZE 10
#define MAX_TOP_LEVEL_DOMAIN_SIZE 10

struct mail {
    char *name;
    char *mail_service_name;
    char *top_level_domain;
};

char input_char();

/* Returns NULL on failure */
char *input_string();

bool check_string_as_mail(char const *const string, struct mail *const mail);

/* Creates new mail. Returns false on failure */
bool create(struct mail **new_mail_p);

/* Prints struct */
void print_mail(const struct mail * const mail);

/* Return pointer what was asked in the task */
char *return_pointer_to_struct(const struct mail *const mail);

void delete(struct mail *mail);

int main() {
    struct mail *new_mail = NULL;
    bool success = create(&new_mail);

    struct mail *created_mail = NULL;
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

char input_char() {
    char c = '\0';
    int result = 0;
    do {
        result = scanf("%c", &c);
    } while (result != 1);
    return c;
}

bool check_string_as_mail(char const *const string, struct mail *const mail)
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

bool create(struct mail **new_mail_p) {
    if (!new_mail_p) {
        return false;
    }
    *new_mail_p = (struct mail *)malloc(sizeof(struct mail));
    struct mail *new_mail = *new_mail_p;
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

void print_mail(const struct mail * const mail) {
    
}

char *return_pointer_to_struct(const struct mail *const mail) {
    return mail;    
}

void delete(struct mail *mail) {
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
