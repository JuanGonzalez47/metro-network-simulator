C++ Metro Network Simulator

An object-oriented data model developed in C++ to simulate and manage the structure of a metro network via a command-line interface. This project was developed as the "Challenge II" for our Computer Science course.

📝 Project Description

The main objective of this project was to design a software solution capable of modeling the complex structure of a subway system. This includes managing multiple lines, stations, transfer points, and the travel times between them. The solution is centered on a robust class design and efficient management of memory and data structures.

✨ Core Features

- Network Management: Add and delete entire lines from the metro network.
- Line Management: Add and delete stations on a specific line, correctly handling their positions and connection times.

Queries and Calculations:
- Calculate the estimated travel time between two stations on the same line.
- Count the total number of lines and stations across the entire network.
- Check for the existence of a specific line or station.
 
Visualization: 
- Print a text-based representation of the entire metro network to the console, showing all lines and their respective stations.

🏛️ Design and Architecture

The solution is built on an Object-Oriented Programming (OOP) design, featuring two primary classes that model the problem domain:

- Network: Acts as the main container class. It is responsible for managing the collection of all lines and handling operations that affect the network as a whole.
- Line: Represents an individual metro line. It holds the information of its stations, their sequence, and the travel times between them.
  
🧠 Technical Challenges and Solutions

During development, we faced several significant engineering challenges. Our solutions demonstrate a deep analysis of the problem:

Memory Management and Computational Cost:
- Problem: The need to dynamically resize arrays to add new lines or stations created a high computational cost due to constant data copying.
- Solution: We researched real-world metro networks in Latin America to establish an average number of lines and stations (approx. 16 lines and 285 stations). Based on this data, we implemented memory pre-allocation for an optimistic initial size (10 lines and 15 stations for the academic context), drastically reducing the need for resizing. We also added functionality to expand capacity if this initial expectation is exceeded.

Class Design and Circular Dependency:
- Problem: In the early design stages, we encountered a critical circular dependency issue between our classes, which prevented compilation and indicated a flawed design.
- Solution: We refactored the class logic to establish a clear hierarchy (Network contains Line), which eliminated the conflicting dependencies and resulted in a more robust and maintainable design.

Data Structure Complexity:
- Problem: An initial idea to use a "triple pointer" to model the network was conceptually complex and highly error-prone.
- Solution: We simplified the model to a more intuitive two-dimensional structure, where the Network class manages an array of Line objects. This improved code readability and efficiency.
  
🛠️ Tech Stack
Language: C++
Environment: Command-line application.

🚀 How to Compile and Run

Clone the repository:
Bash: git clone https://github.com/your-username/your-repository.git
cd your-repository

Compile the source files:
Bash g++ *.cpp -o metro_simulator

Run the program:
Bash ./metro_simulator

👥 Authors

- Juan José Balvin Torres
- Juan Pablo González Blandón

📄 License

This project is licensed under the MIT License. See the LICENSE file for more details.
