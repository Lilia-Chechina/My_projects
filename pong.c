#include <math.h>
#include <stdio.h>

void print_field(int x, int y, int racket_1, int racket_2, int goal_counter_1, int goal_counter_2);
void print_prize(int goal_counter_1, int goal_counter_2);
int move_ball_y(int direction, int ball_y);
int move_ball_x(int direction, int ball_x);
int move_racket_2(int position, int flag_m, int flag_k);
int move_racket_1(int position, int flag_a, int flag_z);
int definition_movemet(int direction, int ball_x, int ball_y, int racket_1, int racket_2);

// 0 - вправо-вверх; 1 - вправо-вниз; 2 - влево-вверх; 3 - влево-вниз

int main() {
    char c;
    int flag_a = 0, flag_z = 0, flag_m = 0, flag_k = 0, flag_space = 0, flag_goal = 0;
    int ball_x = 40, ball_y = 12, racket_1 = 12, racket_2 = 12;
    int direction_movement = 0, goal_counter_1 = 0, goal_counter_2 = 0;
    print_field(ball_x, ball_y, racket_1, racket_2, goal_counter_1, goal_counter_2);
    while (goal_counter_1 != 21 && goal_counter_2 != 21) {
        while ((c = getchar()) != '\n' && flag_space == 0) {
            if (c == 'a' || c == 'A') {
                flag_a = 1;
            } else if (c == 'z' || c == 'Z') {
                flag_z = 1;
            } else if (c == 'm' || c == 'M') {
                flag_m = 1;
            } else if (c == 'k' || c == 'K') {
                flag_k = 1;
            } else if (c == ' ') {
                flag_space = 1;
            }
        }
        if (flag_goal == 1) {
            printf("\e[1;1H\e[2J");
            print_field(ball_x, ball_y, racket_1, racket_2, goal_counter_1, goal_counter_2);
            flag_a = 0, flag_z = 0, flag_m = 0, flag_k = 0, flag_space = 0, flag_goal = 0;
        } else if (flag_space == 0) {
            flag_a = 0, flag_z = 0, flag_m = 0, flag_k = 0;
        } else {
            racket_1 = move_racket_1(racket_1, flag_a, flag_z);
            racket_2 = move_racket_2(racket_2, flag_m, flag_k);
            direction_movement = definition_movemet(direction_movement, ball_x, ball_y, racket_1, racket_2);
            ball_x = move_ball_x(direction_movement, ball_x);
            ball_y = move_ball_y(direction_movement, ball_y);
            printf("\e[1;1H\e[2J");
            print_field(ball_x, ball_y, racket_1, racket_2, goal_counter_1, goal_counter_2);
            if (ball_x == 0) {
                goal_counter_2++;
                ball_x = 40, ball_y = 12, racket_1 = 12, racket_2 = 12;
                flag_goal = 1;
            } else if (ball_x == 79) {
                goal_counter_1++;
                ball_x = 40, ball_y = 12, racket_1 = 12, racket_2 = 12;
                flag_goal = 1;
            }
            flag_a = 0, flag_z = 0, flag_m = 0, flag_k = 0, flag_space = 0;
        }
    }
    printf("\e[1;1H\e[2J");
    print_prize(goal_counter_1, goal_counter_2);
}

int definition_movemet(int direction, int ball_x, int ball_y, int racket_1, int racket_2) {
    if ((ball_x == 2 && ball_y == 1 && (racket_1 == 2 || racket_1 == 3)) ||
        (ball_x == 77 && ball_y == 1 && (racket_2 == 2 || racket_2 == 3)) ||
        (ball_x == 2 && ball_y == 23 && (racket_1 == 22 || racket_1 == 21)) ||
        (ball_x == 77 && ball_y == 23 && (racket_2 == 22 || racket_2 == 21)) ||
        (ball_x == 77 &&
         ((racket_2 - 2 == ball_y && direction == 1) || (racket_2 + 2 == ball_y && direction == 0))) ||
        (ball_x == 2 &&
         ((racket_1 - 2 == ball_y && direction == 3) || (racket_1 + 2 == ball_y && direction == 2)))) {
        if (direction == 0) {
            direction = 3;
        } else if (direction == 1) {
            direction = 2;
        } else if (direction == 3) {
            direction = 0;
        } else if (direction == 2) {
            direction = 1;
        }
    } else if (ball_y == 1 || ball_y == 23) {
        if (direction == 0) {
            direction = 1;
        } else if (direction == 1) {
            direction = 0;
        } else if (direction == 3) {
            direction = 2;
        } else if (direction == 2) {
            direction = 3;
        }
    } else if ((ball_x == 2 && (racket_1 == ball_y || racket_1 + 1 == ball_y || racket_1 - 1 == ball_y)) ||
               (ball_x == 77 && (racket_2 == ball_y || racket_2 + 1 == ball_y || racket_2 - 1 == ball_y))) {
        if (direction == 1) {
            direction = 3;
        } else if (direction == 3) {
            direction = 1;
        } else if (direction == 0) {
            direction = 2;
        } else if (direction == 2) {
            direction = 0;
        }
    }
    return direction;
}

int move_racket_1(int position, int flag_a, int flag_z) {
    if (flag_a == 1 && position != 2) {
        position--;
    } else if (flag_z == 1 && position != 22) {
        position++;
    }
    return position;
}

int move_racket_2(int position, int flag_m, int flag_k) {
    if (flag_k == 1 && position != 2) {
        position--;
    } else if (flag_m == 1 && position != 22) {
        position++;
    }
    return position;
}

int move_ball_x(int direction, int ball_x) {
    if (direction == 0) {
        ball_x++;
    } else if (direction == 1) {
        ball_x++;
    } else if (direction == 2) {
        ball_x--;
    } else if (direction == 3) {
        ball_x--;
    }

    return ball_x;
}

int move_ball_y(int direction, int ball_y) {
    if (direction == 0) {
        ball_y--;
    } else if (direction == 1) {
        ball_y++;
    } else if (direction == 2) {
        ball_y--;
    } else if (direction == 3) {
        ball_y++;
    }

    return ball_y;
}

void print_field(int x, int y, int racket_1, int racket_2, int goal_counter_1, int goal_counter_2) {
    printf("Player_1                              %d    %d                            Player_2\n",
           goal_counter_1, goal_counter_2);
    for (int i = 0; i <= 24; i++) {
        if (i == 0 || i == 24) {
            printf("################################################################################\n");
        } else if (racket_1 != i && racket_1 + 1 != i && racket_1 - 1 != i && racket_2 != i &&
                   racket_2 + 1 != i && racket_2 - 1 != i && y != i) {
            printf("#                                                                              #\n");
        } else {
            for (int j = 0; j <= 79; j++) {
                if (j == x && i == y) {
                    printf("O");
                } else if (j == 0 || j == 79) {
                    printf("#");
                } else if ((i == racket_1 || i == racket_1 + 1 || i == racket_1 - 1) && j == 1) {
                    printf("]");
                } else if ((i == racket_2 || i == racket_2 + 1 || i == racket_2 - 1) && j == 78) {
                    printf("[");
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}

void print_prize(int goal_counter_1, int goal_counter_2) {
    for (int i = 0; i <= 24; i++) {
        if (i == 12) {
            if (goal_counter_1 == 21) {
                printf("                      Player_1 win! AI congratulates you)                      \n");
            } else if (goal_counter_2 == 21) {
                printf("                      Player_2 win! AI congratulates you)                      \n");
            }
        } else {
            printf("\n");
        }
    }
}