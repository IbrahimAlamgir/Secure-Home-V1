# Computer Architecture Concepts & Hardware Mapping

This document contextualizes the high-level embedded code structures of SecureHome V1 by mapping them to low-level microarchitecture paradigms, matching patterns found in Intel 8086 assembly models.

##  Hardware-to-Software Low-Level Analysis

| Embedded Development Pattern | 8086 Assembly Equivalent | Computer Architecture Grounding |
| :--- | :--- | :--- |
| `attachInterrupt(0, ...)` | **Interrupt Vector Table (IVT)** | Both route asymmetric peripheral hardware requests using dedicated memory vectors, bypassing the standard operational sequence. |
| `if (currentState == ARMED)` | **CMP & JE (Jump if Equal)** | Validates runtime register data flags against local system constants to decide conditional execution tracks. |
| `analogRead(LDR_PIN)` | **IN AL, DX (I/O Port Reading)** | Extracts binary sensor strings directly from a peripheral port address configuration to feed system computational registers. |
| `void loop()` | **Unconditional JMP** | Designs an infinite boundary condition within the processor segment to ensure constant data tracking. |
| `volatile bool flag` | **Direct Memory Segments (DS)** | Forces the compilation engine to retrieve data from physical RAM cells instead of optimization caches, guaranteeing data consistency. |

##  Architectural Scaling Blueprint

To adapt this microcontroller platform for deployment within real-world environments, the implementation paths are mapped below against computer architecture specifications:

1. **4x4 Matrix Keypad Integration:** Swaps discrete input pins for matrix scanning algorithms and sequential I/O line multiplexing to reduce resource constraints across available microcontroller ports.
2. **GSM Communications (SIM800L Module):** Interfaces peripheral components via a serial Universal Asynchronous Receiver-Transmitter (UART) interface to shift system events onto cellular telecommunication layers.
3. **SPI Storage Arrays (ArduCAM Module):** Implements high-throughput Serial Peripheral Interface (SPI) operations to read, move, and store frame arrays into standalone flash partitions.
4. **Analog-to-Digital Power Monitoring:** Links a hardware resistor divider into internal ADC conversion pins to actively track power dropouts and report low backup levels directly via the LCD.
