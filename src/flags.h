#define FCONTAINS(flag, mask) ((flag & mask) != 0)
#define FSET(flag, mask)                                                       \
    do                                                                         \
    {                                                                          \
        flag = static_cast<entity_flag>(flag | mask);                          \
    } while (0);
#define FCLEAR(flag, mask)                                                     \
    do                                                                         \
    {                                                                          \
        flag &= ~mask;                                                         \
    }
