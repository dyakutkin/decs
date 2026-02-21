#define DYNARRAY(T)                                                            \
    struct                                                                     \
    {                                                                          \
        size_t len;                                                            \
        size_t cap;                                                            \
        T *items;                                                              \
    }
#define DYNARRAY_APPEND(list, element)                                         \
    do                                                                         \
    {                                                                          \
        if ((list).len >= (list).cap)                                          \
        {                                                                      \
            (list).cap += (list).cap / 2 + 1;                                  \
            (list).items = static_cast<decltype((list).items)>(                \
                realloc((list).items, (list).cap * sizeof(*(list).items)));    \
        }                                                                      \
        (list).items[(list).len] = (element);                                  \
        (list).len++;                                                          \
    } while (0)
#define DYNARRAY_CLEAR(list)                                                   \
    do                                                                         \
    {                                                                          \
        list.len = 0;                                                          \
    } while (0)
