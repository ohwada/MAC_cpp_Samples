random src_c
===============

C Sample <br/>
generate random number / string <br/>

random header is part of the pseudo-random number generation library <br/>


### rand.h <br/>
generate random number using C rand() <br/>
- getRand()

Build  cand Run file <br/>
% gcc  test_rand.c -c -o rand <br/>
% ./rand <br/>

display as below <br/>
rand: 0 -> 999 <br/>
738 <br/>
461 <br/>

### random.h <br/>
generate random number using C random() <br/>
- getRandom() <br/>

Build and Run file <br/>
% gcc  test_random.c -o random <br/>
% ./random <br/>

display as below <br/>
random: 0 -> 999 <br/>
 676 <br/> 
 959 <br/>

### random_char.h <br/>
generate random char with rand.h <br/>
- genRandomCharMix() <br/>
- genRandomCharLower() <br/>
- genRandomCharUpper() <br/>
- genRandomCharDigit() <br/>
- genRandomCharSpecial() <br/>

Build and Run file <br/>
% gcc  test_random_char.c -o char<br/>
% ./char <br/>

display as below <br/>
 mode 1: mix lowercase upercase degit <br/>
JGMNPegUgr <br/>
VFHA5CIrPe <br/>


### gen_random_char_no_duplicate.c <br/>
generate random chars 
that not duplicate character <br/>

Build and Run file <br/>
% gcc gen_random_char_no_duplicate.c -o no_duplicate <br/>
% ./no_duplicate <br/>

display as below <br/>
 8SWATzOgcV (0) <br/>
PSdkc7BrGt (7) <br/>

### random_char.h <br/>
generate random password <br/>

Build and Run file <br/>
% gcc test_passwd.c -o passwd <br/>
% ./passwd <br/>

display as below <br/>
mvCL56?fv 
LvCf?56mv 


### mkpasswd.c <br/>
generate password like LINUX mkpasswd <br/>

Build and Run file <br/>
% gcc mkpasswd.c -DDEBUG -o mkpasswd <br/>
% ./mkpasswd <br/>

display as below <br/>
l: 9
d: 2
c: 2
C: 2
s: 1
mix: 2
yvOH52"eM 
H"eyM52vO 


### Reference <br/>
- https://www.tutorialspoint.com/c_standard_library/c_function_rand.htm <br/>

