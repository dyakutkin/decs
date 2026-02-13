#define OPTION(T)                                                              \
    struct                                                                     \
    {                                                                          \
        T value;                                                               \
        bool set;                                                              \
    }
#define OPTION_SET_VALUE(opt, new_value)                                       \
    opt.set = true;                                                            \
    opt.value = new_value;
#define OPTION_SET_NULL(opt) opt.set = false;
