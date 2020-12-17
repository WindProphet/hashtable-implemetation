# Hash Table Implementation

An implementation of Hast Table by C language

## test

```bash
gcc -c hashtable.c
gcc -o test test.c hashtable.o
ruby test_generator.rb 100000 infile outfile
./test < infile | diff outfile -
```

