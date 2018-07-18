#!/bin/bash
rm results.txt

./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 0 
./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 5 
./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 10
./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 15 
./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 20 
./simgen 1000 1219 | ./rrsim --quantum 50 --dispatch 25 

./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 0 
./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 5 
./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 10
./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 15
./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 20
./simgen 1000 1219 | ./rrsim --quantum 100 --dispatch 25

./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 0
./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 5
./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 10
./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 15
./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 20
./simgen 1000 1219 | ./rrsim --quantum 250 --dispatch 25

./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 0
./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 5
./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 10
./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 15
./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 20
./simgen 1000 1219 | ./rrsim --quantum 500 --dispatch 25