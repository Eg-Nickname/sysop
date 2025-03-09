# C

Proces adoptujący osieroconde procesy:
    ├─init-systemd(Ub(2)─┬─SessionLeader(382)───Relay(384)(383)

## D

Dane Programu:
Proces macierzysty - UID: 1000, GID: 1000, PID: 39444, PPID: 39434, PGID: 39434
    Proces potomny gen 1 - UID: 1000, GID: 1000, PID: 39445, PPID: 39444, PGID: 39434
    Proces potomny gen 1 - UID: 1000, GID: 1000, PID: 39446, PPID: 39444, PGID: 39434
    Proces potomny gen 1 - UID: 1000, GID: 1000, PID: 39447, PPID: 39444, PGID: 39434
    Proces potomny gen 2 - UID: 1000, GID: 1000, PID: 39450, PPID: 39446, PGID: 39434
    Proces potomny gen 2 - UID: 1000, GID: 1000, PID: 39448, PPID: 39445, PGID: 39434
    Proces potomny gen 2 - UID: 1000, GID: 1000, PID: 39449, PPID: 39445, PGID: 39434
    Proces potomny gen 3 - UID: 1000, GID: 1000, PID: 39455, PPID: 39448, PGID: 39434

Drzewo procesów:
                                                                (PID: 39444, PPID: 39434, PGID: 39434)
                                                                /                           |       \_______________________________________
                                                                |                           |                                               \
                            (PID: 39445, PPID: 39444, PGID: 39434)                      (PID: 39446, PPID: 39444, PGID: 39434)      (PID: 39447, PPID: 39444, PGID: 39434)
                            /               \                                                           |
(PID: 39449, PPID: 39445, PGID: 39434)      (PID: 39448, PPID: 39445, PGID: 39434)      (PID: 39450, PPID: 39446, PGID: 39434)
                                                            |
                                            (PID: 39455, PPID: 39448, PGID: 39434)

## Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?

Przy n-krotnym wywołaniu funkcji fork powstanie 2^n procesów, ponieważ jej użycie w procesie tworzy nowy proces co podwaja liczbę wszystkich procesów, z każdym kolejnym jej wywołaniem.