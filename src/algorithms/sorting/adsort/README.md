adsort
======

Adsort is a solution to the proposed to the opening question from 5.2 of Knuth. 
The reader is asked to construct a program in the following way:

    Memory locations R+1, R+2, R+3, R+4, and R+5 contain five numbers. Write a
    computer program that rearranges these numbers, if necessary, so that they
    are in ascending order.

The solutions `adsort` proposes a very naive and very inefficient form of
minimum-insertion sort.

A.1 Find min 
A.2 Push min to S
A.3 R empty? Goto A.1
A.4 Return S
