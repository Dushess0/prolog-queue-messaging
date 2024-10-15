#include <SWI-cpp.h>
#include "rabbitmq_wrapper.h"

extern "C" install_t install_rabbitmq() {
    PL_register_foreign("pl_rabbitmq_connect", 2, (pl_function_t)pl_rabbitmq_connect, 0);
    PL_register_foreign("pl_rabbitmq_publish", 2, (pl_function_t)pl_rabbitmq_publish, 0);
    PL_register_foreign("pl_rabbitmq_subscribe", 1, (pl_function_t)pl_rabbitmq_subscribe, 0);
    PL_register_foreign("pl_register_rabbitmq_callback", 1, (pl_function_t)pl_register_rabbitmq_callback, 0);
    PL_register_foreign("pl_rabbitmq_loop", 0, (pl_function_t)pl_rabbitmq_loop, 0);
}
