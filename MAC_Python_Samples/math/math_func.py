# Python: calc math functions
# 2025-04-10  K.OHWADA

# https://note.nkmk.me/python-gcd-lcm/#google_vignette

import  math

# constant
print( 'pi: ', math.pi ) # 3.14

print( 'e: ', math.e ) # 2.71

print( 'tau: ', math.tau ) # 6.28

# Greatest common divisor
print('gcd(6, 4) = ', math.gcd(6, 4)) # 2

# Least common multiple
print('lcm(6, 4) = ', math.lcm(6, 4)) # 12

# Angular conversion
print()
print('degrees(pi) = ', math.degrees(math.pi)) # 1180.0

print('radians(180) = ', math.radians(180)) # 3.14

# Trigonometric functions
print()
sin30 = math.sin(math.radians(30))
print('sin(30 deg) = ', sin30) # 0.5

cos30 = math.cos(math.radians(30))
print('cos(30 deg) = ', cos30 ) # 0.866

# Pythagorean theorem of trigonometric Functions
print()
print('Pythagorean theorem of trigonometric Functions')
ret30 = (sin30 * sin30) + (cos30*cos30)
print( 'sin(30 deg)**2 + cos(30 deg)**2 = ', ret30) # 1.0
