/*
** EPITECH PROJECT, 2025
** lib
** File description:
** lib
*/

#ifndef LIB_H
    #define LIB_H
    /*    LIB    */
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdarg.h>
    /*    PROJECT LIBS    */
    #include <stdbool.h>
    #include <errno.h>
    #include <string.h>
    #include <math.h>
    #include <stdbool.h>

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
} dataframe_shape_t;

typedef struct {
    int k;
    int nb_rows;
    int nb_columns;
    char **column_names;
    column_type_t *column_types;
    void ***data;
    char ***strings;
    char *separator;
} dataframe_t;

typedef struct node {
    char *name;
    int value;
    struct node *next;
} node_t;

typedef struct list {
    struct node *head;
} list_t;

/*    LIB STR    */
int my_strlen(const char *);
int my_strcmp(const char *, const char *);
int my_strncmp(const char *, const char *, int);
int my_tab_strcmp(const char *, const char *);
char *my_strdup(const char *);
char *array_to_str(const char **, char);
char *my_strcat(const char *, const char *, const char *);
int my_strncpy(const char *, const char *, int);
char *str_lowcase(char *);
int is_bool(const char *);
char *my_strndup(const char *, int);

/*    LIB ARRAY    */
char **split_str(const char *, const char *);
int free_array(void **);
int my_array_len(const void **);
int total_array_len(const char **);

/*    LIB NUMBER    */
int my_atoi(const char *);
int is_unsigned_int(const char *);
int is_negative_int(const char *);
int is_float(const char *str);

/*    LIB LINKED LIST    */
char **list_to_array(list_t *);
int free_node(node_t *);
int delete_node(list_t *, const char *);
list_t *create_list(void);
void free_list(list_t *);
void print_list(list_t *);
void add_node(char *, int, list_t *);

/*    OTHER LIB FUNCTIONS    */
int my_free(void *);
int mini_printf(int, const char *, ...);

/*    UTILS FUNCTIONS    */
column_type_t get_type(const char *);
char *type_value_to_str(unsigned int);
dataframe_t *init_data(void);
FILE *try_to_open(const char *, const char *);
char *strclean(const char *);
char *correct_type(char *, column_type_t);
void *convert_to_type(void *, column_type_t);
void print_value(FILE *, void *, column_type_t, char *);
column_type_t is_previous_type(column_type_t, column_type_t, int);

/*    PROJECT'S MAIN FUNCTIONS    */
dataframe_shape_t df_shape(dataframe_t *);
dataframe_t *df_tail(dataframe_t *, int);
dataframe_t *df_head(dataframe_t *, int);
dataframe_t *df_read_csv(const char *, char *);
dataframe_t *cpy_instance(dataframe_t *, int, int);
dataframe_t *df_to_type(dataframe_t *, const char *, column_type_t);
dataframe_t *df_filter(dataframe_t *, const char *, bool (*)(void *));
dataframe_t *df_apply(dataframe_t *, const char *, void *(*)(void *));
dataframe_t *df_sort(dataframe_t *, const char *, bool(*)(void *, void *));
int df_write_csv(dataframe_t *, const char *);
int update_strings(dataframe_t *, dataframe_t *, int, int);
void df_info(dataframe_t *);
void df_describe(dataframe_t *);
void *df_get_value(dataframe_t *, int, const char *);
void **df_get_values(dataframe_t *, const char *);
void **df_get_unique_values(dataframe_t *, const char *);
void df_free(dataframe_t *);

#endif
