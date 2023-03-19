#! /usr/bin/env bash

if ! [[ -x compoundwords ]]; then
    echo "scanner executable does not exist"
    exit 1
fi

../tester/run-tests.sh $*
