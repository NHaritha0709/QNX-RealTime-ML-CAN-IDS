#include <stdio.h>
#include "../src/dt_classifier.c"

int main(void)
{
    CANFrame frame = {0};

    /* Test 1: CAN ID <= 1.5 follows the attack branch. */
    frame.can_id = 1;
    if (classify_can_frame(&frame) != ATTACK) {
        puts("Test 1 FAILED");
        return 1;
    }
    puts("Test 1 PASSED: attack branch");

    /* Test 2: data[1] > 191.5, data[6] > 0.5 => attack. */
    frame.can_id = 0x100;
    frame.data[1] = 200;
    frame.data[6] = 1;
    if (classify_can_frame(&frame) != ATTACK) {
        puts("Test 2 FAILED");
        return 1;
    }
    puts("Test 2 PASSED: attack branch");

    /* Test 3: data[1] > 191.5, data[6] == 0,
       data[7] <= 36 => normal. */
    frame.can_id = 0x100;
    frame.data[1] = 200;
    frame.data[6] = 0;
    frame.data[7] = 20;
    if (classify_can_frame(&frame) != NORMAL) {
        puts("Test 3 FAILED");
        return 1;
    }
    puts("Test 3 PASSED: normal branch");

    puts("All classifier smoke tests passed.");
    return 0;
}
