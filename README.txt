================================================================================
                    LIBRARY BOOK MANAGEMENT & OPERATION SYSTEM
================================================================================

PROJECT INFORMATION:
-------------------
Project Name    : Library Book Management & Operation System
Developer       : H.M.Ashis Rahman
Student ID      : 242-35-407
Program         : B.Sc in Software Engineering (SWE)
Department      : Department of Software Engineering
University      : Daffodil International University (DIU)
Course Teacher  : Rantu Das
Project Type    : Semester Short Project
Language        : C Programming
Date            : August 2025

================================================================================

PROJECT OVERVIEW:
----------------
This project implements a comprehensive Library Book Management System using 
four fundamental data structures in C programming language. The system provides
efficient book management operations including addition, deletion, searching,
and organization of library resources. Each data structure offers unique
advantages for different operational requirements of a library management system.

================================================================================

DATA STRUCTURES IMPLEMENTED:
----------------------------

1. ARRAY DATA STRUCTURE (Array.h & Array.c)
   - Fixed-size book storage implementation
   - Fast random access to book records
   - Efficient for small to medium-sized libraries
   - Functions: Insert, Delete, Search, Display, Sort

2. LINKED LIST DATA STRUCTURE (Linked_List.h & Linked_List.c)
   - Dynamic memory allocation for book records
   - Efficient insertion and deletion operations
   - Suitable for frequently changing book inventories
   - Functions: Add Node, Delete Node, Search, Traverse, Update

3. STACK DATA STRUCTURE (Stack.h & Stack.c)
   - LIFO (Last In, First Out) implementation
   - Useful for tracking recently added/accessed books
   - Undo operations for book transactions
   - Functions: Push, Pop, Peek, IsEmpty, IsFull, Display

4. QUEUE DATA STRUCTURE (Queue.h & Queue.c)
   - FIFO (First In, First Out) implementation
   - Manages book reservation and waiting lists
   - Handles book request processing in order
   - Functions: Enqueue, Dequeue, Front, Rear, IsEmpty, IsFull

================================================================================

SYSTEM FEATURES:
---------------

CORE FUNCTIONALITIES:
- Add new books to the library system
- Remove books from the inventory
- Search books by various criteria (ID, Title, Author, ISBN)
- Display all books in organized format
- Update book information
- Sort books by different parameters

ADVANCED OPERATIONS:
- Book reservation system using Queue
- Recently accessed books tracking using Stack
- Efficient search and retrieval using Arrays and Linked Lists
- Memory management optimization
- Data validation and error handling

================================================================================

FILE STRUCTURE:
--------------

Main.c          - Main program file with user interface and menu system
Array.h         - Header file for Array data structure declarations
Array.c         - Implementation of Array-based book management functions
Linked_List.h   - Header file for Linked List data structure declarations
Linked_List.c   - Implementation of Linked List-based operations
Stack.h         - Header file for Stack data structure declarations
Stack.c         - Implementation of Stack-based operations
Queue.h         - Header file for Queue data structure declarations
Queue.c         - Implementation of Queue-based operations
README.txt      - Project documentation (this file)

================================================================================

COMPILATION AND EXECUTION:
-------------------------

COMPILATION:
To compile the project, use the following command in terminal/command prompt:

gcc Main.c Array.c Linked_List.c Stack.c Queue.c -o LibrarySystem

EXECUTION:
To run the compiled program:
./LibrarySystem (Linux/Mac)
LibrarySystem.exe (Windows)

REQUIREMENTS:
- GCC Compiler or any C compiler
- Operating System: Windows/Linux/Mac
- Minimum RAM: 512 MB
- Storage: 10 MB free space

================================================================================

PROGRAM FLOW:
------------

1. INITIALIZATION
   - Initialize all data structures
   - Allocate memory for dynamic structures
   - Set up default configurations

2. MAIN MENU
   - Display available operations
   - Accept user input for operation selection
   - Route to appropriate data structure functions

3. OPERATIONS
   - Perform selected operations on chosen data structure
   - Validate input data
   - Display results and status messages

4. TERMINATION
   - Clean up allocated memory
   - Save data if persistence is implemented
   - Exit gracefull

================================================================================

LEARNING OUTCOMES:
-----------------
- Understanding of fundamental data structures
- Implementation of abstract data types in C
- Memory management and pointer manipulation
- Algorithm analysis and efficiency comparison
- Real-world application of theoretical concepts
- Software development best practices
- Problem-solving using appropriate data structures

================================================================================

ACKNOWLEDGMENTS:
---------------
- Course Teacher: Rantu Das (for guidance and project assignment)
- Daffodil International University (for academic support)
- Department of Software Engineering (for curriculum and resources)
- C Programming Community (for references and best practices)

================================================================================

PROJECT STATUS:
--------------
Status:Completed
Version: 1.0
Last Updated: August 12, 2025

For any queries or suggestions regarding this project, please contact:
H.M. Ashis Rahman
Email: ashis242-35-407@diu.edu.bd
Department of Software Engineering
Daffodil International University

================================================================================

Copyright © 2025 H.M. Ashis Rahman. All rights reserved.
This project is submitted as academic work for educational purposes.

================================================================================
