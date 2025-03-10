/*
** EPITECH PROJECT, 2025
** lib
** File description:
** lib
*/

#ifndef LIB_H
    #define LIB_H
    /*    EXTERNAL LIBS    */
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdarg.h>
    #include <signal.h>

typedef enum {
    BOOL,
    INT,
    UINT,
    FLOAT,
    STRING,
    UNDEFINED
} column_type_t;

typedef struct {
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    void ***data;
} dataframe_t;

typedef struct node {
    char *name;
    int value;
    struct node *next;
} node_t;

typedef struct list {
    struct node *head;
} list_t;

/*    LIB    */
int my_strlen(char *);
char **split_str(char *, char *);
void free_list(list_t *list);
int my_strcmp(char *, char *);
int my_strncmp(char *, char *, int);
void free_array(char **);
list_t *create_list(void);
void add_node(char *, int, list_t *);
int delete_node(list_t *, char *);
void print_list(list_t *);
char **list_to_array(list_t *);
char *my_strdup(char *);
char *array_to_str(char **, char);
int my_array_len(char **);
int total_array_len(char **);
char *my_strcat(char *, char *, char *);
int mini_printf(int, char *, ...);
int free_node(node_t *node);
int my_strncpy(char *str, char *dst, int n);
int my_atoi(char *string);

#endif
