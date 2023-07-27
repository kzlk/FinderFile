# File Search Application - GL BaseCamp C/C++ 2023

## Done ✓
- [x] App find file by "name"
- [x] Search  started from root "/" directory. (or Disk "C:\" on Windows OS)
- [x] App creates new **Searching Thread for each sub-directory** in root directory, but no more than 8 Execution Threads.
- [x] Thread who will find needed file has to print Full Path to the file notify all the rest threads to stop searching.
- [x] Logic "to search file" placed into **static library**.
- [x] Application just uses this library to find files in a fast way.
- [x] **Makefile** for compilation/linking instruction. 

## Prerequisites
Before using the File Search Application, ensure you have the following prerequisites:
- C++ compiler (g++)
- Make utility

## Installation
To install the File Search Application, follow these steps:

1. Clone this repository to your local machine:
```bash
git clone <repository_url> 
cd file-search-application
```

2. Build the application using the provided Makefile:
```bash
make 
```

3. Run the application:
```bash
./FileSearcher <file_name> [<search_directory>]

```
- `<file_name>`: The name of the file you want to find.
- `[<search_directory>]` (optional): The directory where the search should start. If not provided, the search begins from the root directory ("/" on Unix-like systems or "C:" on Windows OS).

4. The application will start the search process from the root directory and display the full path to the first occurrence of the file with the given name. If the file is not found, an appropriate message will be displayed.