#!/bin/bash

qmk compile -kb gmmk/pro/rev1/ansi -km nabeel
make gmmk/pro/rev1/ansi:nabeel:flash
