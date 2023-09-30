# Vito's Family

Online judge problem 10041

## Description

The world-known gangster Vito Deadstone is moving to New York. He has a very big
family there, all of them living in Lamafia Avenue. Since he will visit his
relatives very often, he is trying to find a house close to them.

Vito wants to minimize the total distance to all of them and has blackmailed you
to write a program that solves his problem.

Essentially we're asking which of the houses should Vito live in in order to
minimize the distance to the other houses.

## Input

The input consists of several test cases. The first line consists of the
number of test cases. For each test case you will be given the integer
number of the number of relatives (0 < r < 500) and the street numbers
(also integers) `s_1, s_2, ..., s_i, ..., s_r` where they live `(0 < s_i < 30000)`.
Note that several relatives could live in the same street number.

## Output

For each test case, your program must write a minimal sum of distances from the
optimal Vito's house to each one of his relatives. The distance between two
street numbers `s_i` and `s_j` is `d_ij = |s_i - s_j|` .

## Sample Input

2
2 2 4
3 2 4 6

## Sample Output
2
4
