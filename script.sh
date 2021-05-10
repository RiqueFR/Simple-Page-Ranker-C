#!/bin/bash
to=$1
test=$2

for i in $(seq 0 $to) ; do
    file="entradas/$test/pages/$i.txt"
    echo "$file"
    python3 python_bolado.py < $file > temp.txt
    cat temp.txt > $file
done

rm temp.txt