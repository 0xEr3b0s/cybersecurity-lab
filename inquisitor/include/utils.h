#ifndef UTILS_H
# define UTILS_H

#include "inquisitor.h"
#include <stdio.h>
#include <stdlib.h>

/* String */
void usage(char *msg);
void error(char *msg, int error_code, t_config *config);

/* Memory */
void free_ressources(t_config *config);

#endif
