#!/usr/bin/env bash

test_assert_equals() {
    # Test if two inputs are equal 
    if [ $1 == $2 ]; then
        return 0
    else
        return -1
    fi
}

