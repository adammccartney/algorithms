#! /usr/bin/env bash

if ! [[ -x vito ]]; then
    echo "vito executable does not exist"
    exit 1
fi

../../tester/run-tests.sh $*
