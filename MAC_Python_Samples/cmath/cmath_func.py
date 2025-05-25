# Python: calc cmath functions
# 2025-04-10  K.OHWADA

import  cmath

# constant
print( 'pi: ', cmath.pi ) # 3.14

print( 'e: ', cmath.e ) # 2.71

print( 'tau: ', cmath.tau ) # 6.28

# square root
sqrt = cmath.sqrt(complex(-2.0, -0.0))

print()
print('sqrt(complex(-2.0, -0.0) = ', sqrt) # -1.4142135623730951j

# the phase of z
phase = cmath.phase(complex(-1.0, 0.0))

print('phase(complex(-1.0, 0.0) = ', phase) # 3.141592653589793

# Euler's Formula

# e ** jz =cos(z)+ j sin(z)

rad = (cmath.pi * 60 )/ 180  # 60 deg

cos = cmath.cos(rad) # 0.5

sin = cmath.sin(rad) # 0.866

c = complex(0, rad)

euler = cmath.e ** c # (0.5 + 0.866j)

print()

print('rad(60deg): ', rad) # 1.047

print('complex(0, rad): ',c)

print('cos(60 deg), sin(60 deg): ', cos.real, sin.real)

print()
print("Euler's Formula")
print('euler: .e ** complex(0, rad(60 deg) ): ', euler)




