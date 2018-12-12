# greatest common factor
a = int(input('input a non-negative number: '))
b = int(input('input another no-negative number: '))
if a < b:
    a, b = b, a
if b == 0:
    print('the greatest common factor is ', a)
    if a == 0:
        print('no greatest common factor')
else:
    r = a % b
    while r != 0:
        a, b = b, r
        r = a % b
    print('the greatest common factor is ', b)
