#!/bin/bash
cmake -Bbuild && cmake --build build

cp build/cg-engine cg-engine
cp build/cg-generator cg-generator