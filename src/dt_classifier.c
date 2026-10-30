/*
 * ==================================================
 * dt_classifier.c
 * ==================================================
 * Auto-generated Decision Tree classifier
 * QNX CAN Bus Intrusion Detection System
 * SREC Batch 3EC13
 *
 * Detects:
 *   - Normal CAN traffic
 *   - Attack traffic
 *
 * Decision Tree Accuracy: 99.69%
 * Tree Depth: 8
 * Leaf Nodes: 20
 *
 * Generated automatically from Python
 * DO NOT EDIT TREE RULES MANUALLY
 * ==================================================
 */

#include <stdint.h>
#include <stddef.h>

/* Classification labels */
#define NORMAL 0
#define ATTACK 1

/*
 * CAN frame used by the ML classifier.
 *
 * IMPORTANT:
 * inter_arrival must use the same time unit
 * used during Python model training.
 */
typedef struct {
    uint32_t can_id;
    uint8_t  dlc;
    uint8_t  data[8];
    float    inter_arrival;
} CANFrame;

/*
 * classify_can_frame()
 *
 * Input:
 *     Pointer to CANFrame
 *
 * Returns:
 *     NORMAL = 0
 *     ATTACK = 1
 */
int classify_can_frame(const CANFrame *f)
{
    if (f->can_id <= 1.500000000f) {
        return ATTACK; /* samples=1, normal=0, attack=1 */
    } else {
        if (f->data[1] <= 191.500000000f) {
            if (f->can_id <= 1520.500000000f) {
                if (f->data[6] <= 209.500000000f) {
                    if (f->data[2] <= 155.500000000f) {
                        if (f->data[6] <= 15.500000000f) {
                            if (f->data[2] <= 133.000000000f) {
                                if (f->inter_arrival <= 0.000227571f) {
                                    return NORMAL; /* samples=1, normal=0, attack=0 */
                                } else {
                                    return NORMAL; /* samples=1, normal=0, attack=0 */
                                }
                            } else {
                                if (f->data[5] <= 38.500000000f) {
                                    return NORMAL; /* samples=1, normal=0, attack=0 */
                                } else {
                                    return ATTACK; /* samples=1, normal=0, attack=1 */
                                }
                            }
                        } else {
                            if (f->data[1] <= 38.500000000f) {
                                if (f->data[0] <= 100.500000000f) {
                                    return NORMAL; /* samples=1, normal=0, attack=0 */
                                } else {
                                    return ATTACK; /* samples=1, normal=0, attack=1 */
                                }
                            } else {
                                return ATTACK; /* samples=1, normal=0, attack=1 */
                            }
                        }
                    } else {
                        if (f->data[6] <= 0.500000000f) {
                            if (f->data[0] <= 25.000000000f) {
                                return NORMAL; /* samples=1, normal=1, attack=0 */
                            } else {
                                return ATTACK; /* samples=1, normal=0, attack=1 */
                            }
                        } else {
                            if (f->data[4] <= 0.500000000f) {
                                return NORMAL; /* samples=1, normal=0, attack=0 */
                            } else {
                                return ATTACK; /* samples=1, normal=0, attack=1 */
                            }
                        }
                    }
                } else {
                    return ATTACK; /* samples=1, normal=0, attack=1 */
                }
            } else {
                if (f->data[6] <= 0.500000000f) {
                    if (f->data[2] <= 1.500000000f) {
                        return NORMAL; /* samples=1, normal=1, attack=0 */
                    } else {
                        return ATTACK; /* samples=1, normal=0, attack=0 */
                    }
                } else {
                    if (f->data[6] <= 254.500000000f) {
                        return ATTACK; /* samples=1, normal=0, attack=1 */
                    } else {
                        return NORMAL; /* samples=1, normal=0, attack=0 */
                    }
                }
            }
        } else {
            if (f->data[6] <= 0.500000000f) {
                if (f->data[7] <= 36.000000000f) {
                    return NORMAL; /* samples=1, normal=1, attack=0 */
                } else {
                    return ATTACK; /* samples=1, normal=0, attack=1 */
                }
            } else {
                return ATTACK; /* samples=1, normal=0, attack=1 */
            }
        }
    }
}
