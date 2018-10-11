# rref

Reduced row echelon form calculator, written in C++. 

## Build

Make with `make`.

## Example Usage

    $ ./rref
    Input the number of rows: 3
    Input the number of columns: 4
    Input a line for row 1: 3 4 2 12
    Input a line for row 2: 6 -4 -3 5
    Input a line for row 3: 5 7 -12 5
    Your matrix:
    [ 3 4 2 12 ]
    [ 6 -4 -3 5 ]
    [ 5 7 -12 5 ]
    Showing the steps:
    [ 1 1.33333 0.666667 4 ]
    [ 0 -12 -7 -19 ]
    [ 0 0.333333 -15.3333 -15 ]

    [ 1 0 -0.111111 1.88889 ]
    [ -0 1 0.583333 1.58333 ]
    [ 0 0 -15.5278 -15.5278 ]

    [ 1 0 0 2 ]
    [ 0 1 0 1 ]
    [ -0 -0 1 1 ]

    Result:
    [ 1 0 0 2 ]
    [ 0 1 0 1 ]
    [ -0 -0 1 1 ]