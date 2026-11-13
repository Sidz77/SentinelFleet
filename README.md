# 🚀 SentinelFleet
### Autonomous UAV–USV Patrol and Safety Simulator

**SentinelFleet** is a C++17-based simulation project that demonstrates autonomous patrolling operations of two types of unmanned vehicles: an Unmanned Aerial Vehicle (UAV) and an Unmanned Surface Vehicle (USV).

The simulator allows vehicles to follow predefined waypoints, monitor battery levels, detect geofence violations, and automatically return to their home position when a safety condition is triggered.

---

## 📌 Project Overview

The project simulates two autonomous vehicles:

| Vehicle | Type | Speed | Battery Consumption |
|---|---|---:|---:|
| Spot-1 | UAV (Drone) | 5 units/tick | 0.8 per unit |
| Sea-1 | USV (Boat) | 2 units/tick | 0.4 per unit |

Both vehicles start from the home position `(0,0)` and follow their assigned patrol routes.

## ✨ Key Features

- **Waypoint Navigation:** Vehicles follow predefined navigation points.
- **Battery Monitoring:** Tracks battery consumption during movement.
- **Geofence Monitoring:** Detects when a vehicle exceeds its permitted operating radius.
- **Return To Launch (RTL):** Automatically sends a vehicle back home when a safety condition is triggered.
- **Mission Management:** Supports patrol, return, and landing states.
- **CSV Telemetry Logging:** Stores vehicle positions, battery levels, and operating modes for analysis.
- **Multiple Vehicle Types:** Simulates both aerial and surface vehicles using a common vehicle architecture.

## 🛡️ Safety Mechanisms

### 1. Battery Failsafe
When the battery level reaches 30% or below, the vehicle switches to RTL mode.

### 2. Geofence Failsafe
Each vehicle has a permitted geofence radius of 60 units.

The simulator calculates the distance between the current position and home position. If the distance exceeds the permitted radius, RTL mode is activated.

### 3. Mission Completion
After completing its assigned waypoints, the vehicle automatically returns to its home position `(0,0)` and enters LANDED mode.

## 🔄 Vehicle Operating Modes

| Mode | Description |
|---|---|
| IDLE | Vehicle is waiting for a mission. |
| PATROL | Vehicle follows its assigned waypoints. |
| RTL | Vehicle returns to its home position. |
| LANDED | Vehicle has successfully reached home. |

## 🛠️ Technologies Used

- **Language:** C++17
- **Concepts:** Object-Oriented Programming (OOP)
- **OOP Principles:** Inheritance, Polymorphism, Abstraction, Encapsulation
- **STL:** Vector, Algorithm
- **Memory Management:** Smart Pointers (`unique_ptr`)
- **File Handling:** CSV logging using `ofstream`
- **Compiler:** GCC (g++)

## 🧠 C++ Concepts Demonstrated

- Classes and Objects
- Inheritance
- Runtime Polymorphism
- Abstract Classes and Virtual Functions
- STL Containers
- Smart Pointers
- File Handling
- Distance and movement calculations

## 📂 Project Structure

```text
SentinelFleet/
│
├── patrol_sim.cpp
├── patrol_log.csv
├── README.md
└── .gitignore
```

## ⚙️ Installation and Execution

### Prerequisites

- GCC compiler (g++)
- C++17 support
- Windows, Linux, or macOS

### Step 1: Clone the Repository

```bash
git clone https://github.com/Sidz77/SentinelFleet.git
```

### Step 2: Navigate to the Project Folder

```bash
cd SentinelFleet
```

### Step 3: Compile the Program

```bash
g++ -std=c++17 -Wall -Wextra patrol_sim.cpp -o patrol_sim
```

### Step 4: Run the Program

**Windows PowerShell:**

```powershell
.\patrol_sim.exe
```

**Linux/macOS:**

```bash
./patrol_sim
```

## 📊 Sample Output

The simulator generates a CSV file named `patrol_log.csv`.

Example:

```csv
tick,name,x,y,battery,mode
0,Spot-1,5,0,96,PATROL
0,Sea-1,1.89737,0.632456,99.2,PATROL
1,Spot-1,10,0,92,PATROL
1,Sea-1,3.79473,1.26491,98.4,PATROL
15,Spot-1,0,0,36,RTL
16,Spot-1,0,0,36,LANDED
31,Sea-1,58.0272,9.6712,74.5509,RTL
61,Sea-1,0,0,51.0198,LANDED
```

### Sample Results

- Spot-1 successfully completed its patrol and returned home.
- Sea-1 detected a geofence violation and automatically switched to RTL.
- Both vehicles successfully reached their home position.
- Vehicle telemetry was recorded in CSV format.

## 🎯 Project Objective

The objective of SentinelFleet is to understand and demonstrate fundamental concepts of autonomous vehicle navigation, mission management, and safety monitoring through a C++ simulation.

## ⚠️ Disclaimer

This is an educational software simulation. It does not control real UAVs or USVs and is not intended to replace certified navigation or safety systems.

## 👨‍💻 Author

**Sudarshan Bhosale**

B.Tech – Computer Science and Engineering (Data Science)  
R. C. Patel Institute of Technology, Shirpur

### 🔗 GitHub Repository

[https://github.com/Sidz77/SentinelFleet](https://github.com/Sidz77/SentinelFleet)

---

⭐ If you find this project interesting, feel free to explore the repository!
