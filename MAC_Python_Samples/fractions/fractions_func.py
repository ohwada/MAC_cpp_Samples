# Python:  fractions function
# 2025-04-10  K.OHWADA


from fractions import Fraction
from decimal import Decimal


f1 = Fraction(1, 2)
print('Fraction(1, 2) : ', f1) # 1/2

f2 = Fraction(1, 3)
print('Fraction(1, 3) : ', f2) # 1/3

f3 = f1 + f2
print('Fraction(1, 2) + Fraction(1, 3) = ', f3) # 5/6

d1 = Decimal('1.1')
print()
print("Decimal('1.1') : ", d1)

f4 = Fraction(Decimal('1.1'))
print( "Fraction(Decimal('1.1')) : ", f4)
