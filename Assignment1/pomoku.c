/* 보드 크기 : 최소 10 x 10 최대 20 x 20 */

#include "pomoku.h"
unsigned int g_user_score_black = 0;
unsigned int g_user_score_white = 0;

unsigned int g_row_count = 15;
unsigned int g_column_count = 15;

typedef struct user_info {
    unsigned int is_stone;
    color_t m_color;
} user_info_t;

user_info_t g_pomoku_board[20][20] = { 0, };

void init_game(void)
{
    unsigned int i = 0;
    unsigned int j = 0;
    g_user_score_black = 0;
    g_user_score_white = 0;
    g_row_count = 15;
    g_column_count = 15;

    for (i = 0; i < g_row_count; i++) {
        for (j = 0; j < g_column_count; j++) {
            g_pomoku_board[i][j].is_stone = FALSE;
            g_pomoku_board[i][j].m_color = COLOR_DEFAULT;
        }
    }
}

unsigned int get_row_count(void)
{
    return g_row_count;
}

unsigned int get_column_count(void)
{
    return g_column_count;
}

int get_score(const color_t color)
{
    if (color == COLOR_BLACK) {
        return g_user_score_black;
    } else if (color == COLOR_WHITE) {
        return g_user_score_white;
    }
    return -1;
}

int get_color(const unsigned int row, const unsigned int col)
{
    /* 위치가 가리키는 곳에 돌이 있을때, 그 돌의 색이 무엇인지 반환 */
    /* 돌이 검정이면 0 흰새이면 1 그외의 경우 -1 반환 */
    if ((g_row_count > row) && (g_column_count > col)) {
        if (g_pomoku_board[row][col].is_stone == TRUE) {
            if (g_pomoku_board[row][col].m_color == COLOR_BLACK) {
                return 0;
            } else if (g_pomoku_board[row][col].m_color == COLOR_WHITE) {
                return 1;
            } else {
                return -1;
            }
        }
    }
    return -1;
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    /* 돌을 넣으려는 위치에 돌이 있는지 없는지 여부 반환 */
    if ((g_row_count > row) && (g_column_count > col)) {
        if (g_pomoku_board[row][col].is_stone == TRUE) {
            return FALSE;
        } else {
            return TRUE;
        }
    }
    return FALSE;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    /* 놓으려는 위치에 돌이 없을때만 돌을 넣을 수 있다 */
    /* 오목이 완성되었는지 검사 */
    /* user_score_black = 0;
    user_score_white = 0;*/

    unsigned int one_index = 1;
    unsigned int count = 0;

    if ((g_row_count > row) && (g_column_count > col)) {
        if (is_placeable(row, col) == TRUE) {
            g_pomoku_board[row][col].m_color = color;
            g_pomoku_board[row][col].is_stone = TRUE;
            /* 왼쪽 대각선 */
            /* 왼쪽부분 */
            while ((row > 0) && (col > 0) && g_pomoku_board[row - one_index][col - one_index].is_stone && (g_pomoku_board[row - one_index][col - one_index].m_color == color)) {

                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row - one_index) < 0 || (int)(col - one_index) < 0) {
                    goto label_1;
                }
            }

        label_1:
            one_index = 1;

            /* 왼쪽 대각선 */
            /* 오른쪽부분 */
            while (g_pomoku_board[row + one_index][col + one_index].is_stone && (g_pomoku_board[row + one_index][col + one_index].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row + one_index) < 0 || (int)(col + one_index) < 0) {
                    goto label_2;
                }
            }

        label_2:
            one_index = 1;
            count = 0;

            /* 오른쪽 대각선 */
            /* 왼쪽부분*/
            while ((row > 0) && g_pomoku_board[row - one_index][col + one_index].is_stone && (g_pomoku_board[row - one_index][col + one_index].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row - one_index) < 0 || (int)(col + one_index) < 0) {
                    goto label_3;
                }
            }

        label_3:
            one_index = 1;

            /* 오른쪽 대각선 */
            /* 오른쪽부분 */
            while ((col > 0) && g_pomoku_board[row + one_index][col - one_index].is_stone && (g_pomoku_board[row + one_index][col - one_index].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row + one_index) < 0 || (int)(col - one_index) < 0) {
                    goto label_4;
                }
            }

        label_4:
            one_index = 1;
            count = 0;

            /* 좌우 */
            /* 왼쪽부분 */
            while ((row > 0) && g_pomoku_board[row - one_index][col].is_stone && (g_pomoku_board[row - one_index][col].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row - one_index) < 0 || (int)(col) < 0) {
                    goto label_5;
                }
            }

        label_5:
            one_index = 1;

            /* 좌우 */
            /* 오른쪽부분 */
            while (g_pomoku_board[row + one_index][col].is_stone && (g_pomoku_board[row + one_index][col].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row + one_index) < 0 || (int)(col) < 0) {
                    goto label_6;
                }
            }

        label_6:
            one_index = 1;
            count = 0;

            /* 위아래 */
            /* 왼쪽부분 */
            while ((col > 0) && g_pomoku_board[row][col - one_index].is_stone && (g_pomoku_board[row][col - one_index].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row) < 0 || (int)(col - one_index) < 0) {
                    goto label_7;
                }
            }

        label_7:
            one_index = 1;

            /* 위아래 */
            /* 오른쪽부분 */
            while (g_pomoku_board[row][col + one_index].is_stone && (g_pomoku_board[row][col + one_index].m_color == color)) {
                ++count;
                ++one_index;

                if (count >= 4) {
                    if (color == COLOR_BLACK) {
                        ++g_user_score_black;
                    } else if (color == COLOR_WHITE) {
                        ++g_user_score_white;
                    }
                }

                if ((int)(row) < 0 || (int)(col + one_index) < 0) {
                    goto label_8;
                }
            }

        label_8:
            one_index = 1;
            count = 0;

            return TRUE;
        }
    }
    return FALSE;
}

/* special moves */

/* insert 함수 => 1. 색상 확인. 2. 조건문 통과 */
/* 작동 방식: row_count 1 증가시키고 점수 깎고 기존 행에 있는 값들 모두 +1행씩 이동. (이때 열은 변동없음!!) */

int insert_row(const color_t color, const unsigned int row)
{
    /* 3점 소모 */
    /* 추가할 위치에 돌이 없어야함. */
    /* 20 이 최대 크기 */

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int i1 = 0;
    unsigned int j1 = 0;

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 3 && g_row_count < 20 && row < g_row_count + 1) {
            /*구현부*/
            /* 넣을 행 기준으로 그 행보다 큰 행들은 모두 +1 씩 아래로 이동 */

            ++g_row_count;
            g_user_score_black = g_user_score_black - 3;

            /* 맨 끝 열에서부터 입력받은 row 값 까지 for문을 시작하는것이 핵심 */
            /* 입력받은 row 쪽 행은 위의 작업 실행이후 추가적인 for 문으로 모두 지워준다. */
            /* row가 2일때, */

            for (i = g_row_count - 1; i > row; i--) {
                /* 아래에서부터 위로가는 for 문 */
                for (j = 0; j < g_column_count; j++) {
                    /* 각 행의 모든 열을 순차적으로 훑는 과정 */
                    if (g_pomoku_board[i - 1][j].is_stone == TRUE) {
                        /* 돌이 존재할때만 그 돌을 아래 행으로 복사하는 과정 */
                        g_pomoku_board[i][j] = g_pomoku_board[i - 1][j];
                        g_pomoku_board[i - 1][j].is_stone = FALSE; /* 옮기고 난후에 기존 돌들은 모두 초기화 */
                        g_pomoku_board[i - 1][j].m_color = COLOR_DEFAULT;
                    }
                }
            }

            /* 필요가 없어진 코드 */
            /* for (int i = 0; i < row_count; i++)
            {
                 pomoku_board[row][i].is_stone = FALSE;
                 pomoku_board[row][i].m_color = COLOR_DEFAULT;
            }*/

            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 3 && g_row_count < 20 && row < g_row_count + 1) {
            /*구현부*/

            ++g_row_count;
            g_user_score_white = g_user_score_white - 3;

            for (i1 = g_row_count - 1; i1 > row; i1--) {
                for (j1 = 0; j1 < g_column_count; j1++) {
                    if (g_pomoku_board[i1 - 1][j1].is_stone == TRUE) {
                        g_pomoku_board[i1][j1] = g_pomoku_board[i1 - 1][j1];
                        g_pomoku_board[i1 - 1][j1].is_stone = FALSE;
                        g_pomoku_board[i1 - 1][j1].m_color = COLOR_DEFAULT;
                    }
                }
            }

            /* for (int i = 0; i < row_count; i++)
             {
                 pomoku_board[row][i].is_stone = FALSE;
                 pomoku_board[row][i].m_color = COLOR_DEFAULT;
             }*/

            return TRUE;
        }
    }
    return FALSE;
}

int insert_column(const color_t color, const unsigned int col)
{
    /* 3점 소모 */
    /* 추가할 위치에 돌이 없어야함. */
    /* 20 이 최대 크기 */

    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int i1;
    unsigned int j1;

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 3 && g_column_count < 20 && col < g_column_count + 1) {
            /*구현부*/
            /* 넣을 열 기준으로 그 열보다 큰 열들은 모두 +1 씩 오른쪽으로 이동 */

            ++g_column_count;
            g_user_score_black = g_user_score_black - 3;

            for (i = g_column_count - 1; i > col; i--) {
                for (j = 0; j < g_row_count; j++) {
                    if (g_pomoku_board[j][i - 1].is_stone == TRUE) {
                        g_pomoku_board[j][i] = g_pomoku_board[j][i - 1];
                        g_pomoku_board[j][i - 1].is_stone = FALSE;
                        g_pomoku_board[j][i - 1].m_color = COLOR_DEFAULT;
                    }
                }
            }

            /* for (int i = 0; i < row_count; i++)
             {
                 pomoku_board[i][col].is_stone = FALSE;
                 pomoku_board[i][col].m_color = COLOR_DEFAULT;
             }*/

            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 3 && g_column_count < 20 && col < g_column_count + 1) {
            /*구현부*/

            ++g_column_count;
            g_user_score_white = g_user_score_white - 3;

            for (i1 = g_column_count - 1; i1 > col; i1--) {
                for (j1 = 0; j1 < g_row_count; j1++) {
                    if (g_pomoku_board[j1][i1 - 1].is_stone == TRUE) {
                        g_pomoku_board[j1][i1] = g_pomoku_board[j1][i1 - 1];
                        g_pomoku_board[j1][i1 - 1].is_stone = FALSE;
                        g_pomoku_board[j1][i1 - 1].m_color = COLOR_DEFAULT;
                    }
                }
            }

            /*  for (int i = 0; i < row_count; i++)
              {
                  pomoku_board[i][col].is_stone = FALSE;
                  pomoku_board[i][col].m_color = COLOR_DEFAULT;
              }*/

            return TRUE;
        }
    }
    return FALSE;
}

int remove_row(const color_t color, const unsigned int row)
{
    /* 3점 사용 */
    unsigned int i;
    unsigned int j;
    unsigned int i1;
    unsigned int j1;

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 3 && row < g_row_count && g_row_count >= 11) {
            /*구현부*/

            for (i = row + 1; i < g_row_count; i++) {
                for (j = 0; j < g_column_count; j++) {

                    g_pomoku_board[i - 1][j].is_stone = FALSE;
                    g_pomoku_board[i - 1][j].m_color = COLOR_DEFAULT;

                    if (g_pomoku_board[i][j].is_stone == TRUE) {
                        g_pomoku_board[i - 1][j] = g_pomoku_board[i][j];
                        g_pomoku_board[i][j].is_stone = FALSE;
                        g_pomoku_board[i][j].m_color = COLOR_DEFAULT;
                    }
                }
            }

            --g_row_count;
            g_user_score_black = g_user_score_black - 3;

            /*   for (int i = 0; i < row_count; i++)
               {
                   pomoku_board[row_count - 1][i].is_stone = FALSE;
                   pomoku_board[row_count - 1][i].m_color = COLOR_DEFAULT;
               }*/

            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 3 && row < g_row_count && g_row_count >= 11) {
            /*구현부*/

            for (i1 = row + 1; i1 < g_row_count; i1++) {
                for (j1 = 0; j1 < g_column_count; j1++) {

                    g_pomoku_board[i1 - 1][j1].is_stone = FALSE;
                    g_pomoku_board[i1 - 1][j1].m_color = COLOR_DEFAULT;

                    if (g_pomoku_board[i1][j1].is_stone == TRUE) {
                        g_pomoku_board[i1 - 1][j1] = g_pomoku_board[i1][j1];
                        g_pomoku_board[i1][j1].is_stone = FALSE;
                        g_pomoku_board[i1][j1].m_color = COLOR_DEFAULT;
                    }
                }
            }

            --g_row_count;
            g_user_score_white = g_user_score_white - 3;

            /*  for (int i = 0; i < row_count; i++)
              {
                  pomoku_board[row_count - 1][i].is_stone = FALSE;
                  pomoku_board[row_count - 1][i].m_color = COLOR_DEFAULT;
              }*/

            return TRUE;
        }
    }
    return FALSE;
}

int remove_column(const color_t color, const unsigned int col)
{
    /* 3점 사용 */
    unsigned int i;
    unsigned int j;
    unsigned int i1;
    unsigned int j1;

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 3 && col < g_column_count && g_column_count >= 11) {
            /*구현부*/

            for (i = col + 1; i < g_column_count; i++) {
                for (j = 0; j < g_row_count; j++) {

                    g_pomoku_board[j][i - 1].is_stone = FALSE;
                    g_pomoku_board[j][i - 1].m_color = COLOR_DEFAULT;

                    if (g_pomoku_board[j][i].is_stone == TRUE) {
                        g_pomoku_board[j][i - 1] = g_pomoku_board[j][i];
                        g_pomoku_board[j][i].is_stone = FALSE;
                        g_pomoku_board[j][i].m_color = COLOR_DEFAULT;
                    }
                }
            }

            --g_column_count;
            g_user_score_black = g_user_score_black - 3;

            /*for (int i = 0; i < column_count; i++)
            {
                pomoku_board[i][column_count].is_stone = FALSE;
                pomoku_board[i][column_count].m_color = COLOR_DEFAULT;
            }*/

            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 3 && col < g_column_count && g_column_count >= 11) {
            /*구현부*/

            for (i1 = col + 1; i1 < g_column_count; i1++) {
                for (j1 = 0; j1 < g_row_count; j1++) {

                    g_pomoku_board[j1][i1 - 1].is_stone = FALSE;
                    g_pomoku_board[j1][i1 - 1].m_color = COLOR_DEFAULT;

                    if (g_pomoku_board[j1][i1].is_stone == TRUE) {
                        g_pomoku_board[j1][i1 - 1] = g_pomoku_board[j1][i1];
                        g_pomoku_board[j1][i1].is_stone = FALSE;
                        g_pomoku_board[j1][i1].m_color = COLOR_DEFAULT;
                    }
                }
            }

            --g_column_count;
            g_user_score_white = g_user_score_white - 3;

            /* for (int i = 0; i < row_count; i++)
             {
                 pomoku_board[row_count - 1][i].is_stone = FALSE;
                 pomoku_board[row_count - 1][i].m_color = COLOR_DEFAULT;
             }*/

            return TRUE;
        }
    }
    return FALSE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    /* 2점 사용 */

    user_info_t backup_info[20] = { 0, };

    user_info_t backup_info1[20] = { 0, };

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 2 && row0 < g_row_count && row1 < g_row_count) {
            g_user_score_black = g_user_score_black - 2;

            /* 먼저 row0 를 백업하는 방향으로 */
            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    backup_info[i] = g_pomoku_board[row0][i];
                }
            }

            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    g_pomoku_board[row0][i] = g_pomoku_board[row1][i];
                }
            }

            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    g_pomoku_board[row1][i] = backup_info[i];
                }
            }

            return TRUE;
            /* 범위밖 조건문*/
        } else if (row0 >= g_row_count || row1 >= g_row_count) {
            if (row0 > row1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_column_count; i++)
                    {
                        g_pomoku_board[row1][i].is_stone = FALSE;
                        g_pomoku_board[row1][i].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            } else if (row0 < row1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_column_count; i++)
                    {
                        g_pomoku_board[row0][i].is_stone = FALSE;
                        g_pomoku_board[row0][i].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            }
        }
            /* 범위밖 조건문*/
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 2 && row0 < g_row_count && row1 < g_row_count) {
            g_user_score_white = g_user_score_white - 2;

            /* 먼저 row0 를 백업하는 방향으로 */
            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    backup_info1[i] = g_pomoku_board[row0][i];
                }
            }

            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    g_pomoku_board[row0][i] = g_pomoku_board[row1][i];
                }
            }

            {
                unsigned int i;
                for (i = 0; i < g_column_count; i++) {
                    g_pomoku_board[row1][i] = backup_info1[i];
                }
            }

            return TRUE;
                /* 범위밖 조건문*/
        } else if (row0 >= g_row_count || row1 >= g_row_count) {
            if (row0 > row1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_column_count; i++)
                    {
                        g_pomoku_board[row1][i].is_stone = FALSE;
                        g_pomoku_board[row1][i].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;

                /* 범위밖 조건문*/
            } else if (row0 < row1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_column_count; i++)
                    {
                        g_pomoku_board[row0][i].is_stone = FALSE;
                        g_pomoku_board[row0][i].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            }
                /* 범위밖 조건문*/
        }
    }
    return FALSE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    /* 2점 사용 */
    unsigned int i = 0;
    user_info_t backup_info[20] = { 0, };
    user_info_t backup_info1[20] = { 0, };

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 2 && col0 < g_column_count && col1 < g_column_count) {
            g_user_score_black = g_user_score_black - 2;

            /* 먼저 col0 를 백업하는 방향으로 */
            for (i = 0; i < g_row_count; i++) {
                backup_info[i] = g_pomoku_board[i][col0];
            }

            for (i = 0; i < g_row_count; i++) {
                g_pomoku_board[i][col0] = g_pomoku_board[i][col1];
            }

            for (i = 0; i < g_column_count; i++) {
                g_pomoku_board[i][col1] = backup_info[i];
            }
            return TRUE;

            /* 범위밖 조건문*/
        } else if (col0 >= g_column_count || col1 >= g_column_count) {
            if (col0 > col1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_row_count; i++)
                    {
                        g_pomoku_board[i][col1].is_stone = FALSE;
                        g_pomoku_board[i][col1].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            } else if (col0 < col1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_row_count; i++)
                    {
                        g_pomoku_board[i][col0].is_stone = FALSE;
                        g_pomoku_board[i][col0].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            }
        }
        /* 범위밖 조건문*/
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 2 && col0 < g_column_count && col1 < g_column_count) {
            g_user_score_white = g_user_score_white - 2;

            i = 0;

            /* 먼저 col0 를 백업하는 방향으로 */
            for (i = 0; i < g_row_count; i++) {
                backup_info1[i] = g_pomoku_board[i][col0];
            }

            for (i = 0; i < g_row_count; i++) {
                g_pomoku_board[i][col0] = g_pomoku_board[i][col1];
            }

            for (i = 0; i < g_column_count; i++) {
                g_pomoku_board[i][col1] = backup_info1[i];
            }

            return TRUE;
            /* 범위밖 조건문*/
        } else if (col0 >= g_column_count || col1 >= g_column_count) {
            if (col0 > col1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_row_count; i++)
                    {
                        g_pomoku_board[i][col1].is_stone = FALSE;
                        g_pomoku_board[i][col1].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            } else if (col0 < col1) {
                {
                    unsigned int i = 0;
                    for (i = 0; i < g_row_count; i++)
                    {
                        g_pomoku_board[i][col0].is_stone = FALSE;
                        g_pomoku_board[i][col0].m_color = COLOR_DEFAULT;
                    }
                }

                return TRUE;
            }
        }
        /* 범위밖 조건문*/
    }
    return FALSE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    /* 4점 사용 */

    unsigned int i = 0;

    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 4 && src < g_row_count && dst < g_row_count) {
            g_user_score_black = g_user_score_black - 4;

            for (i = 0; i < g_column_count; i++) {
                g_pomoku_board[dst][i] = g_pomoku_board[src][i];
            }
            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 4 && src < g_row_count && dst < g_row_count) {
            g_user_score_white = g_user_score_white - 4;

            i = 0;

            for (i = 0; i < g_column_count; i++) {
                g_pomoku_board[dst][i] = g_pomoku_board[src][i];
            }
            return TRUE;
        }
    }
    return FALSE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    /* 4점 사용 */

    unsigned int i = 0;
    if (color == COLOR_BLACK) {
        if (g_user_score_black >= 4 && src < g_column_count && dst < g_column_count) {
            g_user_score_black = g_user_score_black - 4;

            for (i = 0; i < g_row_count; i++) {
                g_pomoku_board[i][dst] = g_pomoku_board[i][src];
            }
            return TRUE;
        }
    } else if (color == COLOR_WHITE) {
        if (g_user_score_white >= 4 && src < g_column_count && dst < g_column_count) {
            g_user_score_white = g_user_score_white - 4;

            for (i = 0; i < g_row_count; i++) {
                g_pomoku_board[i][dst] = g_pomoku_board[i][src];
            }

            return TRUE;
        }
    }
    return FALSE;
}
