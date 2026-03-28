📑 TECHNICAL DOCUMENTATION:
SYSTEM MONITOR V3.0 PRO
Project Developed by: Ionut Andrei Tudora Faculty: ETTI (Electronics, Telecommunications, and Information Technology)
Language: C++ (C++20 Standard)
Operating System: Windows 10/11
________________________________________
1. 🎯 Project Purpose
This project was developed to provide a real-time hardware resource monitoring solution for computing systems. The application queries the Windows Kernel to retrieve CPU utilization (CPU Load) and utilizes an algorithmic model to estimate operating temperatures, ultimately providing a "Health Status" verdict for the system.
2. 🛠️ System Architecture
The program is structured around three main pillars, following standard engineering data processing models:
•	Acquisition Layer: Utilizes the windows.h library and the GetSystemTimes function to extract processor timing data directly from the Kernel.
•	Processing Layer: Calculates the arithmetic mean of the collected samples and determines extreme values (Minimum/Maximum) to identify performance "spikes."
•	Persistence Layer: All collected data is exported to a log file (sensor_log.txt), allowing for post-session performance audits.
3. ⚙️ Implementation Details
3.1. Technology Stack
•	Compiler: GCC (via MSYS2/MinGW suite).
•	IDE: JetBrains CLion.
•	Build Management: CMake with Static Linking configuration (ensuring all dependencies are bundled within the executable).
3.2. Diagnostic Algorithm
The final health verdict is established based on two critical variables:
•	Average Load: Optimal threshold < 60%.
•	Maximum Temperature: Optimal threshold < 75°C.
•	Alert System: If either threshold is exceeded, the system triggers a hardware-level audio alert (750Hz frequency) to warn the user.
4. 📊 Results and Statistics
Upon completing the 15-sample cycle, the application generates a detailed report including:
•	Timestamps: The exact time of each individual reading.
•	Comparative Analysis: A structured table displaying Minimum, Maximum, and Average values.
•	General Status: A binary evaluation (Optimal / High Demand).
5. 🚀 Conclusions
System Monitor V3.0 Pro, developed by Ionut Andrei Tudora, successfully demonstrates the integration of System-Level Programming and Data Logging concepts. It serves as a practical tool for rapid performance diagnostics and for understanding how software tasks directly impact hardware resource consumption.

