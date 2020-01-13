//
// Created by MK on 13.01.2020.
//
#include "Solver.h"
#include <stdio.h>


typedef struct{
    AREA_SIZE_T size;
    bool *p_rows, *p_cross_up, *p_cross_down;
    AREA_SIZE_T *p_solution;

} Area_t;

static bool check(Area_t *area, AREA_SIZE_T row, AREA_SIZE_T column)
{
    //Checks if queen could be added in given position
    return !area->p_rows[row] && !area->p_cross_up[row + column] && !area->p_cross_down[row - column + area->size];
}

static void put(Area_t *area, AREA_SIZE_T row, AREA_SIZE_T column)
{
    //Puts queen in given position
    area->p_solution[column] = row;

    area->p_rows[row] = area->p_cross_up[row + column] = area->p_cross_down[row - column + area->size] = true;
}

static void rmv(Area_t *area, AREA_SIZE_T row, AREA_SIZE_T column)
{
    //Remove queen from given position
    area->p_rows[row] = area->p_cross_up[row + column] = area->p_cross_down[row - column + area->size] = false;
}

static void printSolution(Area_t *area)
{
    //Print Solution as Row Indexes
    printf("Solution: ");

    for(AREA_SIZE_T column = 0; column < area->size; column++)
    {
        printf("%u ", area->p_solution[column]);
    }

    printf("\n");
}

static void drawSolution(Area_t *area)
{
    //Draw Solution as Matrix of 'o' and 'x'
    printf("Solution:\n");

    for(AREA_SIZE_T row = 0; row < area->size; row++)
    {
        for (AREA_SIZE_T column = 0; column < area->size; column++)
        {
            if(area->p_solution[column] == row)
            {
                printf("%c ", 'x');
            }
            else
            {
                printf("%c ", 'o');
            }
        }
        printf("\n");
    }
}

static void solve(Area_t *area, AREA_SIZE_T column, bool draw)
{
    //Generates solutions - starting from given column and prints/draws them
    if(column < area->size)
    {
        for(AREA_SIZE_T row = 0; row < area->size; row++)
        {
            if(check(area, row, column))
            {
                put(area, row, column);

                solve(area, (AREA_SIZE_T) (column + 1), draw);

                rmv(area, row, column); //remove queen to simulate other solution
            }
        }
    }
    else
    {
        if(draw)
            drawSolution(area);
        else
            printSolution(area);
    }
}

void solution(int32_t area_size, bool draw)
{
    if(area_size < 4)
    {
        printf("There's no solution for size: %d\n", area_size);
        return;
    }
    if(area_size >= AREA_MAX_SIZE)
    {
        printf("Area Size exceed max value");
        return;
    }

    AREA_SIZE_T size = (AREA_SIZE_T)area_size;

    bool crs_down_arr[2 * size -1];
    bool crs_up_arr[2 * size -1];
    bool rows_arr[size];
    AREA_SIZE_T solution_arr[size];

    for(int i = 0; i < (2 * size - 1); i++)
    {
        crs_down_arr[i] = false;
        crs_up_arr[i] = false;
    }

    for(AREA_SIZE_T i = 0; i < size; i++)
    {
        rows_arr[i] = false;
    }

    Area_t area;
    area.size = size;
    area.p_cross_down = crs_down_arr;
    area.p_cross_up = crs_up_arr;
    area.p_rows = rows_arr;
    area.p_solution = solution_arr;

    solve(&area, 0, draw);
}