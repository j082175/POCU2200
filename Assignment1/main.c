#include <assert.h>
#include "pomoku.h"


/*#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
void game_start(void);
void goto_xy(const size_t x, const size_t y);
void goto_row_col(const size_t row, const size_t col);
void draw_board(void);
void draw_stone(const color_t color);
void update_state(const color_t color, const size_t x, const size_t y);
*/

void test_init_game(void);
void place_stone_func(color_t color);

void test_horizontal_chain(void);
void test_combined_chains(void);
void test_swap_row(void);
void test_insert_row(void);
void test_remove_row(void);
void test_copy_row(void);

void init_game_and_test(void);
void score_test(void);

int main(void)
{
    /*test_init_game();*/

    /*game_start();*/

    init_game_and_test();
    /*score_test();*/
}

void init_game_and_test(void)
{
    init_game();
 
    assert(15 == get_row_count());
    assert(15 == get_column_count());
 
    assert(0 == get_score(COLOR_BLACK));
    assert(0 == get_score(COLOR_WHITE));
}
 
void score_test(void)
{
    /* hori */
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 5);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 6);
 
    assert(6 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 1, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 4);
 
    assert(7 == get_score(COLOR_BLACK));
 
    init_game_and_test();
    place_stone(COLOR_BLACK, 0, 14);
    place_stone(COLOR_BLACK, 0, 13);
    place_stone(COLOR_BLACK, 0, 12);
    place_stone(COLOR_BLACK, 0, 11);
    place_stone(COLOR_BLACK, 0, 10);
 
    assert(1 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 9);
 
    assert(3 == get_score(COLOR_BLACK));
 
    place_stone(COLOR_BLACK, 0, 8);
 
    assert(6 == get_score(COLOR_BLACK));
 
    /* verti */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 0);
    place_stone(COLOR_WHITE, 2, 0);
    place_stone(COLOR_WHITE, 3, 0);
    place_stone(COLOR_WHITE, 4, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 0);
    place_stone(COLOR_WHITE, 12, 0);
    place_stone(COLOR_WHITE, 11, 0);
    place_stone(COLOR_WHITE, 10, 0);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 0);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 0);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* left-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 0);
    place_stone(COLOR_WHITE, 1, 1);
    place_stone(COLOR_WHITE, 2, 2);
    place_stone(COLOR_WHITE, 3, 3);
    place_stone(COLOR_WHITE, 4, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 6, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 14);
    place_stone(COLOR_WHITE, 13, 13);
    place_stone(COLOR_WHITE, 12, 12);
    place_stone(COLOR_WHITE, 11, 11);
    place_stone(COLOR_WHITE, 10, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 9);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 8);
 
    assert(6 == get_score(COLOR_WHITE));
 
    /* right-diag */
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 14, 0);
    place_stone(COLOR_WHITE, 13, 1);
    place_stone(COLOR_WHITE, 12, 2);
    place_stone(COLOR_WHITE, 11, 3);
    place_stone(COLOR_WHITE, 10, 4);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 9, 5);
 
    assert(3 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 8, 6);
 
    assert(6 == get_score(COLOR_WHITE));
 
    init_game_and_test();
 
    place_stone(COLOR_WHITE, 0, 14);
    place_stone(COLOR_WHITE, 1, 13);
    place_stone(COLOR_WHITE, 2, 12);
    place_stone(COLOR_WHITE, 3, 11);
    place_stone(COLOR_WHITE, 4, 10);
 
    assert(1 == get_score(COLOR_WHITE));
 
    place_stone(COLOR_WHITE, 5, 9);
 
    assert(3 == get_score(COLOR_WHITE));

    place_stone(COLOR_WHITE, 6, 8);
 
    assert(6 == get_score(COLOR_WHITE));
}


void test_init_game(void)
{
    init_game();

    assert(get_row_count() == 15);
    assert(get_column_count() == 15);
    assert(get_score(5) == -1);
    assert(get_score(COLOR_BLACK) == 0);
    assert(get_score(COLOR_WHITE) == 0);
}

void place_stone_func(color_t color)
{
    place_stone(color, 0, 0);
    place_stone(color, 4, 4);
    place_stone(color, 1, 1);
    place_stone(color, 3, 3);

    place_stone(color, 2, 2);

    place_stone(color, 2, 0);
    place_stone(color, 2, 1);
    place_stone(color, 2, 3);
    place_stone(color, 2, 4);

    place_stone(color, 5, 5);
    place_stone(color, 6, 6);

    place_stone(color, 3, 1);
    place_stone(color, 4, 0);
    place_stone(color, 1, 3);
    place_stone(color, 0, 4);

    place_stone(color, 2, 5);
    place_stone(color, 2, 6);

    place_stone(color, 3, 0);
    place_stone(color, 3, 2);
    place_stone(color, 3, 4);

    /*black: 0 white : 3 */

    assert(place_stone(color, 14, 14) == TRUE);
}

void test_horizontal_chain(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 3);
    place_stone(COLOR_BLACK, 0, 4);

    assert(get_score(COLOR_BLACK) == 1);

    place_stone(COLOR_BLACK, 0, 5);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 7);
    assert(get_score(COLOR_BLACK) == 3);

    place_stone(COLOR_BLACK, 0, 6);
    assert(get_score(COLOR_BLACK) == 7);

    assert(get_score(COLOR_WHITE) == 0);
}

void test_combined_chains(void)
{
    test_init_game();

    place_stone(COLOR_BLACK, 0, 0);
    place_stone(COLOR_BLACK, 0, 1);
    place_stone(COLOR_BLACK, 0, 2);
    place_stone(COLOR_BLACK, 0, 4);
    place_stone(COLOR_BLACK, 0, 5);

    place_stone(COLOR_BLACK, 1, 3);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 3, 3);
    place_stone(COLOR_BLACK, 4, 3);

    /*assert(get_score(COLOR_BLACK) == 0);*/

    place_stone(COLOR_BLACK, 0, 3);

    /*assert(get_score(COLOR_BLACK) == 3);*/
}

void test_swap_row(void)
{
    unsigned int i;

    test_init_game();

    for (i = 0; i < 6; i++) {
        place_stone(COLOR_BLACK, 0, i);
    }

    /*assert(get_score(COLOR_BLACK) == 3);*/

    assert(swap_rows(COLOR_BLACK, 0, 4) == TRUE);
    /*assert(get_score(COLOR_BLACK) == 1);*/

    for (i = 0; i < 6; i++) {
        /*assert(is_placeable(0, i) == TRUE);*/
        /*assert(is_placeable(4, i) == FALSE);*/
    }
}

void test_insert_row(void)
{
    unsigned int i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);

    assert(insert_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);
    assert(get_row_count() == 16);

    for (i = 0; i < 6; i++) {
        assert(is_placeable(2, i) == TRUE);
        assert(is_placeable(3, i) == FALSE);
    }
}

void test_remove_row(void)
{
    unsigned int i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);

    assert(get_score(COLOR_BLACK) == 3);
    assert(remove_row(COLOR_BLACK, 2) == TRUE);
    assert(get_score(COLOR_BLACK) == 0);

    for (i = 0; i < get_column_count(); i++) {
        assert(is_placeable(2, i) == TRUE);
    }
}

void test_copy_row(void)
{
    unsigned int i;

    test_init_game();

    place_stone(COLOR_BLACK, 2, 0);
    place_stone(COLOR_BLACK, 2, 1);
    place_stone(COLOR_BLACK, 2, 2);
    place_stone(COLOR_BLACK, 2, 3);
    place_stone(COLOR_BLACK, 2, 4);
    place_stone(COLOR_BLACK, 2, 5);
    place_stone(COLOR_BLACK, 2, 6);

    place_stone(COLOR_WHITE, 2, 7);
    place_stone(COLOR_WHITE, 2, 8);

    assert(get_score(COLOR_BLACK) == 6);
    assert(copy_row(COLOR_BLACK, 2, 4) == TRUE);
    assert(get_score(COLOR_BLACK) == 2);

    for (i = 0; i < get_column_count(); i++) {
        assert(get_color(4, i) == get_color(2, i));
    }
}


/*   */


/*
void game_start(void)
{
    int x = 0;
    int y = 0;
    char key_input = 0;
    int color = COLOR_BLACK;
    int skill = 0;
    int skill_position1 = -1;
    int skill_position2 = -1;
    int is_skill_successful = FALSE;
 
    init_game();
    system("cls");
    draw_board();
    update_state(COLOR_BLACK, 0, 0);
 
    while (key_input != 27) {
        key_input = _getch();
        is_skill_successful = FALSE;
        switch (key_input) {
        case 32:
            if (skill != 0) {
                if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                    goto_row_col(y, get_column_count());
                    printf(" ");
                    if ('Q' == skill || 'q' == skill) {
                        is_skill_successful = insert_row(color, y);
                    } else if ('W' == skill || 'w' == skill) {
                        is_skill_successful = remove_row(color, y);
                    }                    
                } else if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                    goto_row_col(get_row_count(), x);
                    printf(" ");
                    if ('E' == skill || 'e' == skill) {
                        is_skill_successful = insert_column(color, x);
                    } else if ('R' == skill || 'r' == skill) {
                        is_skill_successful = remove_column(color, x);
                    }                    
                } else if (-1 == skill_position2) {
                    if ('1' == skill || 'A' == skill || 'a' == skill) {
                        skill_position2 = y;
                        break;
                    } else if ('2' == skill || 'S' == skill || 's' == skill) {
                        skill_position2 = x;
                        break;
                    }
                } else if (skill_position2 != -1) {
                    if ('1' == skill || 'A' == skill || 'a' == skill) {
                        goto_row_col(skill_position1, get_column_count());
                        printf(" ");
                        goto_row_col(y, get_column_count());
                        printf(" ");
                        if ('1' == skill) {
                            is_skill_successful = swap_rows(color, skill_position1, y);
                        } else if ('A' == skill || 'a' == skill) {
                            is_skill_successful = copy_row(color, skill_position1, y);
                        }
                    } else if ('2' == skill || 'S' == skill || 's' == skill) {
                        goto_row_col(get_row_count(), skill_position1);
                        printf(" ");
                        goto_row_col(get_row_count(), x);
                        printf(" ");
                        if ('2' == skill) {
                            is_skill_successful = swap_columns(color, skill_position1, x);
                        } else if ('S' == skill || 's' == skill) {
                            is_skill_successful = copy_column(color, skill_position1, x);
                        }
                    }
                }
 
                skill_position1 = -1;
                skill_position2 = -1;
                skill = 0;                
 
                if (TRUE == is_skill_successful) {
                    if (COLOR_BLACK == color) {
                        color = COLOR_WHITE;
                    } else if (COLOR_WHITE == color) {
                        color = COLOR_BLACK;
                    }
                }
                system("cls");
                draw_board();
                update_state(color, x, y);                
                break;
            } 
            if (TRUE == is_placeable(y, x)) {
                place_stone(color, y, x);
                draw_stone(color);
 
                if (COLOR_BLACK == color) {
                    color = COLOR_WHITE;
                } else if (COLOR_WHITE == color) {
                    color = COLOR_BLACK;
                }
 
                update_state(color, x, y);
            }
            break;
        case 72:
            if (y > 0) {
                y--;
                if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                    goto_row_col(skill_position1, get_column_count());
                    printf(" ");
                    skill_position1 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                } else if('1' == skill || 'A' == skill || 'a' == skill) {
                    if (-1 == skill_position2) {
                        goto_row_col(skill_position1, get_column_count());
                        printf(" ");
                        skill_position1 = y;
                        goto_row_col(y, get_column_count());
                        printf("<");
                    } else if (skill_position2 != -1) {
                        goto_row_col(skill_position2, get_column_count());
                        printf(" ");
                        skill_position2 = y;
                        goto_row_col(y, get_column_count());
                        printf("<");
                        goto_row_col(skill_position1, get_column_count());
                        printf("<");
                    }
                }
            }
            break;
        case 80:
            y++;
            if ('Q' == skill || 'W' == skill || 'q' == skill || 'w' == skill) {
                goto_row_col(skill_position1, get_column_count());
                printf(" ");
                skill_position1 = y;
                goto_row_col(y, get_column_count());           
                printf("<");
            } else if('1' == skill || 'A' == skill || 'a' == skill) {
                if (-1 == skill_position2) {
                    goto_row_col(skill_position1, get_column_count());
                    printf(" ");
                    skill_position1 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                } else if (skill_position2 != -1) {
                    goto_row_col(skill_position2, get_column_count());
                    printf(" ");
                    skill_position2 = y;
                    goto_row_col(y, get_column_count());
                    printf("<");
                    goto_row_col(skill_position1, get_column_count());
                    printf("<");
                }
            }
            break;
        case 75:
            if (x > 0) {
                x--;
                if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                    goto_row_col(get_row_count(), skill_position1);
                    printf("  ");
                    skill_position1 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                } else if('2' == skill || 'S' == skill || 's' == skill) {
                    if (-1 == skill_position2) {
                        goto_row_col(get_row_count(), skill_position1);
                        printf("  ");
                        skill_position1 = x;
                        goto_row_col(get_row_count(), x);
                        printf("^^");
                    } else if (skill_position2 != -1) {
                        goto_row_col(get_row_count(), skill_position2);
                        printf("  ");
                        skill_position2 = x;
                        goto_row_col(get_row_count(), x);
                        printf("^^");
                        goto_row_col(get_row_count(), skill_position1);
                        printf("^^");
                    }
                }
            }
            break;
        case 77:
            x++;
            if ('E' == skill || 'R' == skill || 'e' == skill || 'r' == skill) {
                goto_row_col(get_row_count(), skill_position1);
                printf("  ");
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            } else if('2' == skill || 'S' == skill || 's' == skill) {
                if (-1 == skill_position2) {
                    goto_row_col(get_row_count(), skill_position1);
                    printf("  ");
                    skill_position1 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                } else if (skill_position2 != -1) {
                    goto_row_col(get_row_count(), skill_position2);
                    printf("  ");
                    skill_position2 = x;
                    goto_row_col(get_row_count(), x);
                    printf("^^");
                    goto_row_col(get_row_count(), skill_position1);
                    printf("^^");
                }
            }
            break;
        case 27:
            break;
        case 'Q':
        case 'q':
        case 'W':
        case 'w':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = y;
                goto_row_col(y, get_column_count());
                printf("<");
            }
            break;
        case 'E':
        case 'e':
        case 'R':
        case 'r':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            }
            break;
        case '1':
        case 'A':
        case 'a':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = y;
                goto_row_col(y, get_column_count());
                printf("<");
            }
            break;
        case '2':
        case 'S':
        case 's':
            if (0 == skill) {
                skill = key_input;
                skill_position1 = x;
                goto_row_col(get_row_count(), x);
                printf("^^");
            }
            break;
        default:
            break;
        }
        goto_xy(x, y);
    }
    system("cls");
}
 
void goto_xy(const size_t x, const size_t y)
{
    COORD XY;
    XY.X = x * 2;
    XY.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}
 
void goto_row_col(const size_t row, size_t col)
{
    COORD XY;
    XY.X = col * 2;
    XY.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), XY);
}
 
void draw_board(void)
{
    size_t row = 0;
    size_t col = 0;
 
    for (row = 0; row < get_row_count(); ++row) {        
        for (col = 0; col < get_column_count(); ++col) {
            goto_row_col(row, col);
            draw_stone(get_color(row, col));
        }
    }
}
 
void draw_stone(const color_t color)
{
    if (COLOR_BLACK == color) {
        printf("()");
    } else if (COLOR_WHITE == color) {
        printf("[]");
    } else {
        printf("--");
    }
}
 
void update_state(const color_t color, const size_t x, const size_t y)
{
    char stone[3] = "()";
 
    goto_xy(21, 2);
    printf("place stone / use skill : spacebar");
    goto_xy(21, 3);
    printf("exit : ESC");
 
    if (COLOR_BLACK == color) {
        strcpy_s(stone, 3, "()");
    }
    else if (COLOR_WHITE == color) {
        strcpy_s(stone, 3, "[]");
    }
 
    goto_xy(21, 5);
    printf("Turn : %s    Score : () %d [] %d", stone, get_score(COLOR_BLACK), get_score(COLOR_WHITE));
 
          goto_xy(21, 8);
    printf("[2 points]  swap rows : 1");  
    goto_xy(21, 9);
    printf("[2 points]  swap columns : 2");
    goto_xy(21, 10);
    printf("[3 points]  insert row : Q");
    goto_xy(21, 11);
    printf("[3 points]  remove row : W");
    goto_xy(21, 12);
    printf("[3 points]  insert column : E");
    goto_xy(21, 13);
    printf("[3 points]  remove column : R");
    goto_xy(21, 14);
    printf("[4 points]  copy row : A");
    goto_xy(21, 15);
    printf("[4 points]  copy column : S");
 
    goto_xy(x, y);
}
*/
