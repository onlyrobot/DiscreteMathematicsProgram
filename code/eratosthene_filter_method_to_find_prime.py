# Eratosthene filter method to find prime
prime = [2, 3, 5, 7]
for i in range(1, 4): # look up all the prime in range 1 to 10000
    for j in range(10**i, 10**(i + 1)):
        for k in prime:
            if j % k == 0:
                break
        else:
            prime.append(j)
print(prime)
