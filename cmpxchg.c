#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

atomic_int state = 0;

int f1() {
    for (int i = 0; i < 10; ++i) {
        while (1) {
            int expected = 0;
            if (atomic_compare_exchange_weak(&state, &expected, 1)) break;
        }
        printf("%d ", i);
        state = 2;
    }
    return 0;
}

int f2() {
    for (int i = 0; i < 10; ++i) {
        while (1) {
            int expected = 2;
            if (atomic_compare_exchange_weak(&state, &expected, 3)) break;
        }
        printf("%c ", 'a' + i);
        state = 0;
    }
    return 0;
}

int main()
{
    thrd_t t1, t2;

    thrd_create(&t1, f1, NULL);
    thrd_create(&t2, f2, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    printf("\n");
    return 0;
}
