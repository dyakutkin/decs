#define OPT(T)                                                                 \
    struct                                                                     \
    {                                                                          \
        T value;                                                               \
        bool set;                                                              \
    }
#define OPTSET(opt, new_value)                                                 \
    opt.set = true;                                                            \
    opt.value = new_value;
#define OPTUNSET(opt) opt.set = false;
