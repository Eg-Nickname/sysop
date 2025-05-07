/*
====================================================================
Makro CheckError: wskazuj lokalizacje bledu, wypisuje nazwe
przekazywanego argumentu (#Arg) i konczy program.
====================================================================
*/

#define CheckError(Arg)                                                        \
    if (!(Arg)) {                                                              \
        fprintf(stderr, "[ERROR] %s:%d (%s) -> CheckError argument: %s\n",     \
                __FILE__, __LINE__, __func__, #Arg);                           \
        exit(EXIT_FAILURE);                                                    \
    }
/*
====================================================================
Makro ChecChildkError: wskazuj lokalizacje bledu, wypisuje nazwe
przekazywanego argumentu (#Arg) i konczy proces potomny.
====================================================================
*/
#define ChildCheckError(Arg)                                                   \
    if (!(Arg)) {                                                              \
        fprintf(stderr, "[ERROR] %s:%d (%s) -> CheckError argument: %s\n",     \
                __FILE__, __LINE__, __func__, #Arg);                           \
        _exit(EXIT_FAILURE);                                                   \
    }
