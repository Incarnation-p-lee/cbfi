#ifndef SELECT_PARAMETER_H
#define SELECT_PARAMETER_H

extern void
print_usage(void);

void
select_parameter(int, char **);
static void
init_conversion_instance(void);
static inline void
set_details_option(void);
static void
set_encoding_class(char *);
static void
set_rawdata_input(char *);
static enum operation
is_input_data_float(char *arg);
static void
store_raw_data(unsigned long long);

#endif
