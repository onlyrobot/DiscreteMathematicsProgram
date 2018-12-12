# least common multiple
a = int(input('input a possitive number: '))
b = int(input('input another possitive number: '))
product = a * b
if a == 0 or b == 0:
    print('input error')
    exit()
if a < b:
    a, b = b, a
r = a % b
while r != 0:
    a, b = b, r
    r = a % b
print('the least common multiple is ', product // b)
