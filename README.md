# Acceleration Computation using C and x86-64 Assembly (SIMD/Scalar)

This project implements a program to compute the acceleration of multiple cars. The computation is handled by an x86-64 assembly function (`asmfunc.asm`), while the C program (`main.c`) manages input, memory allocation, and output printing. The assembly function utilizes **scalar SIMD floating-point instructions**.

## Project Structure

* **`main.c`**: The C source file responsible for:
    * Collecting input (number of cars, initial/final velocities, time).
    * Allocating memory for the input matrix and the output array.
    * Calling the assembly function.
    * Printing the final integer acceleration results.
    * Implementing the performance timing loop.
* **`asmfunc.asm`**: The x86-64 assembly source file containing the function responsible for:
    * Converting input velocities from **KM/H to m/s**.
    * Calculating acceleration using the formula $a = (V_f - V_i) / T$.
    * Converting the result from $m/s^2$ to an **integer** for output.
    * The core logic uses **functional scalar SIMD floating-point instructions** (e.g., `movsd`, `subsd`, `divsd`, `cvttsd2si`).
* **`lbyarch_mp2.slnx`, `lbyarch_mp2.vcxproj`, `lbyarch_mp2.vcxproj.filters`**: Visual Studio project files.

## Acceleration Formula and Conversion

The formula for acceleration is:
$$\text{Acceleration} = \frac{(V_f - V_i)}{T}$$
Where:
* $V_i$ = Initial Velocity (KM/H)
* $V_f$ = Final Velocity (KM/H)
* $T$ = Time (Seconds)

The assembly function performs the necessary conversion:
$$\text{Velocity (m/s)} = \text{Velocity (KM/H)} \times \frac{1000 \text{ m/KM}}{3600 \text{ s/hour}} \approx \text{Velocity (KM/H)} \times 0.27777777...$$

The final acceleration in $m/s^2$ is then converted to an integer (truncated).

## Execution Time and Short Analysis

### Performance Results (Average over 30 runs)

| Input Size ($Y$) | Execution Time           | 
| :--------------: | :----------------------: |
| 10               |                          |
| 100              |                          |
| 1000             |                          |

### Performance Analysis


## Screenshot of Output


## Youtube Link
