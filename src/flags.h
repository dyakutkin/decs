#define FCONTAINS(flag, mask) ((flag & mask) != 0)
#define FSET(flag, mask)                                                       \
    do                                                                         \
    {                                                                          \
        flag |= mask;                                                          \
    } while (0);
#define FCLEAR(flag, mask)                                                     \
    do                                                                         \
    {                                                                          \
        flag &= ~mask;                                                         \
    }
