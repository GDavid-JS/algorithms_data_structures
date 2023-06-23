# https://habr.com/ru/companies/ruvds/articles/325522/
if g++ $1.cpp -o ./dist/$1.out
then ./dist/$1.out
fi