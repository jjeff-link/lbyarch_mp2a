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

## Execution Time and Analysis

### Performance Results (Average over 30 runs, measured 10 times)
1.  **Inner Loop (Stabilization):** The C program executes the target function **30 consecutive times** within a high-resolution timing block to calculate a single, stable **Average Execution Time**.
2.  **Outer Loop (Mitigation):** This entire 30-run averaging process is itself repeated **10 times** by the user. The final performance result listed below is the **Average of these 10 Average Execution Times**.

| Input Size ($Y$) | Execution Time (in seconds)| 
| :--------------: | :------------------------: |
| 10               | 0.1133333333               |
| 100              | 0.513                      |
| 1000             | 1.384666667                |
| 5000             | 6.511                      |

### Performance Analysis
The measured data indicates that the algorithm exhibits **Linear Time Complexity**, denoted as **$O(Y)$**.

**Observations**
* The performance measurements demonstrate a clear and expected upward trend in execution time as the input size increases. Since the assembly routine processes each record in a loop without advanced optimizations, the runtime scales approximately linearly with the number of inputs (Y).
* This indicates that the program maintains consistent per-input processing cost, confirming that the function itself has O(n) time complexity.
* Because each loop iteration always performs the same amount of work, the total execution time increases directly with the number of inputs. The performance mainly depends on:
  * The memory reads and writes done per element
  * The arithmetic instructions needed to compute acceleration
  * The time spent repeating the loop for each input

## Screenshot of Output
### Confirmed Inputs
The log begins by confirming the Y x 3 input matrix of Initial Velocity (Vi in KM/H), Final Velocity (Vf in KM/H), and Time (T in Seconds) used for the run:

For this run, Y = 10.

<img width="548" height="641" alt="image" src="https://github.com/user-attachments/assets/0ae24d80-117b-4838-b13c-68d919c6320b" />

### Execution Time Measurement
The target function was executed 30 consecutive times within a high-resolution timer to obtain a stable execution time.

<img width="616" height="806" alt="image" src="https://github.com/user-attachments/assets/40b67723-43ab-4537-9f63-8433231b8e0e" />

### Correctness Verification
The final section verifies the program's output by displaying the calculated acceleration values, which are converted to integers.

To **verify correctness**:
* Manually recompute accelerations from raw data.
* Compare expected truncated values to program output.
* If mismatch is found, test intermediate values (converted m/s and raw acceleration) to locate the problem.

Example Calculation (Row 1)
**Given:**
- Initial Velocity Vi = 108.3 km/h
- Final Velocity Vf = 190.5 km/h
- Time T = 4.4 s

#### 1. Convert km/h to m/s
v(m/s) = v(km/h) × 0.27777778
- Vi = 108.3 × 0.27777778 = 30.083 m/s
- Vf = 190.5 × 0.27777778 = 52.917 m/s
#### 2. Apply the acceleration formula
a = (Vf - Vi) / T
a = (52.917 - 30.083) / 4.4  
a = 22.834 / 4.4  
a = 5.19 m/s²
#### 3. Compare With Program Output
- Program result (truncated): 5
- Computed acceleration: 5.19 m/s²

<img width="184" height="259" alt="image" src="https://github.com/user-attachments/assets/9bc1cb7c-a2e3-4212-b31e-a32a8a4e0a90" />

The output confirms that the function successfully processed the input data, calculated the acceleration using the formula Acceleration = (Vf - Vi) / T (with unit conversions from KM/H to m/s), and converted the final floating-point results to the required integer format.

<img width="928" height="914" alt="image" src="https://github.com/user-attachments/assets/957d7dbc-0ab5-4488-acd4-4a97064be50d" />


## Youtube Link
https://youtu.be/IZtEtTjuHuQ 
