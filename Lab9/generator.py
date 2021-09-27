import sys
import random

print(10**4*2, 10**4*2, 1, 10**4*2)

a = 10**4*2
b = random.randint(1,10**4*2)
c = random.randint(1,10**9)
print(a, b, c)

for x in range(10**4*2 - 1):
    a = random.randint(1,10**4*2)
    b = random.randint(1,10**4*2)
    c = random.randint(1,10**9)
    print(a, b, c)