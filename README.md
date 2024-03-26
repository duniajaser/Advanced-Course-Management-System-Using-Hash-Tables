# Course-Management-System-Using-Hash-Tables

HashAcademy is a sophisticated course management system, designed to efficiently handle and organize academic course information through the use of advanced hash table techniques. Developed with a focus on performance and ease of use, HashAcademy employs two distinct hashing methods—open addressing (linear probing) and double hashing—to offer flexibility in data storage and retrieval. This system is an ideal solution for educational institutions looking to streamline their course management processes.

## Features

- **Two Hashing Methods**: Utilizes open addressing and double hashing to manage collisions, demonstrating the strengths of each under different scenarios.
- **Dynamic Table Resizing**: Implements rehashing based on load factors to optimize storage efficiency and access times.
- **Collision Handling Insights**: Tracks and compares the number of collisions for each hashing method, providing valuable performance metrics.
- **Interactive User Menu**: Features a user-friendly menu for performing operations like inserting new courses, searching, deleting, and exporting data.
- **Persistent Data Storage**: Supports file input/output operations for reading course data from files and saving changes back, ensuring data persistence.
- **Comprehensive Course Data**: Manages detailed course information including hours, code, name, department, and topics.

## Getting Started

To run this code, ensure you have a C compiler installed on your system. Follow these steps to compile and run the program:

1. **Compilation**: Navigate to the directory containing the `HashAcademy.c` file and compile it using a C compiler. For example, using GCC:

    ```
    gcc HashAcademy.c -o HashAcademy
    ```

2. **Running the Program**: After successful compilation, run the executable:

    ```
    ./HashAcademy
    ```

3. **Using the Program**: Follow the on-screen menu to interact with the system. Choose from reading course data, inserting new records, searching, and more.

## Menu Options

1. **Print Hashed Tables**: Displays both hash tables, including empty spots.
2. **Table Size and Load Factor**: Shows the current size and load factor for each table.
3. **Hash Functions Used**: Outlines the hash functions employed by the system.
4. **Insert New Record**: Adds a new course to the hash tables.
5. **Search for a Specific Course**: Finds course information based on the course name.
6. **Delete a Specific Course**: Removes a course from the hash tables.
7. **Collision Comparison**: Compares the two hashing methods in terms of collision occurrences.
8. **Save to File**: Exports the current state of hash tables back to a file.
9. **Exit**: Closes the program.

## Acknowledgments

- **Dr. Ahmed Abusnaina**: For providing guidance and support throughout the development process.
- **Dunia Jaser**: Developer of this Hash-system project.

This project is committed to delivering a robust and user-friendly course management experience. We welcome feedback and contributions to the project to further enhance its capabilities.
