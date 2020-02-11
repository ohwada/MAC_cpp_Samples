tex : OpenCL-ImageFilter2D
===============

tex script for Gaussian Kernel  <br/>

### Gaussian Kernel matrix 3x3

```
\[
 \frac{1}{16}
 \left[
    \begin{array}{ccc}
      1 & 2 & 1 \\
      2 & 4 & 2 \\
      1 & 2 & 1 \\
    \end{array}
  \right]
\]
```

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-ImageFilter2D/tex/gaussian_kernel_matrix_3x3.png" width="300" /><br/>

### Gaussian Kernel matrix 5x5

```
\[
 \frac{1}{273}
 \left[
    \begin{array}{ccccc}
      1 & 4 & 7 & 4 & 1 \\
      4 & 16 & 26 & 16 & 4 \\
      7 & 26 & 42 & 26 & 7 \\
      4 & 16 & 26 & 16 & 4 \\
      1 & 4 & 7 & 4 & 1 \\
    \end{array}
  \right]
\]
```

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-ImageFilter2D/tex/gaussian_kernel_matrix_5x5.png" width="300" /><br/>

### Gaussian Kernel _formula 1D

```
G\left( x \right) = \dfrac {1}{ \sqrt { 2 \pi \sigma} } \mathrm{e}^{ - \dfrac {x^{2}}{ 2 \sigma^{2} } }
```

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-ImageFilter2D/tex/gaussian_kernel_formula_1d.png" width="300" /><br/>

### Gaussian Kernel _formula 2D

```
G\left( x \right) = \dfrac {1}{ \sqrt { 2 \pi \sigma} } \mathrm{e}^{ - \dfrac {x^{2}}{ 2 \sigma^{2} } }
```

<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/OpenCL-ImageFilter2D/tex/gaussian_kernel_formula_2d.png" width="300" /><br/>

