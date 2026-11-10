# Library Management System

> **Course:** DTS3013 Pengaturcaraan Berstruktur / Structured Programming  
> **Project:** Group Assignment - Library Management System (Sistem Pengurusan Perpustakaan)  
> **Language:** C++  

---

## 📖 Introduction
This Library Management System is a console-based C++ application developed for the **DTS3013 Structured Programming** course group assignment. The system provides complete management features for books, members, and borrowing transactions, persisting all records into text files.

---

## ✨ Features

### 1. 📚 Book Management
- **Add New Book**: Insert book ID, title, author, genre, and status.
- **Update Book Information**: Modify book details by ID.
- **Delete Book**: Remove a book record from the system.
- **Search Book**: Search books by ID or title.
- **Display Books**: View the list of all registered books.
- **Sort Books**: Sort books in ascending or descending order by title or ID.

### 2. 👥 Member Management
- **Add New Member**: Register a member with Member ID, name, contact details, and status (active/inactive).
- **Update Member Details**: Edit member information.
- **Delete Member**: Remove member records.
- **Search Member**: Find member information by ID.
- **Sort Members**: Sort member records.

### 3. 🔄 Borrow & Return System
- **Borrow Book**: Queue-based borrowing system linking member and book records.
- **Return Book**: Process book returns and update availability status automatically in real-time.
- **Transaction History**: Keeps track of borrowing records.

---

## 📁 File Structure

```text
├── mainFunction.cpp       # Main program containing all module implementations and menu logic
├── books.txt              # Database file for book records
├── members.txt            # Database file for member records
├── borrowing.txt          # Database file for borrowing transaction logs
├── .gitignore             # Git ignore file excluding binaries and temporary files
└── README.md              # Project documentation
```

---

## 🛠️ How to Compile & Run

### Using GCC / MinGW (Command Line / Terminal)
```bash
g++ mainFunction.cpp -o mainFunction.exe
./mainFunction.exe
```

### Using Microsoft Visual C++ (MSVC / cl)
```cmd
cl /EHsc mainFunction.cpp
mainFunction.exe
```

### Using Visual Studio / VS Code
1. Open the project folder in VS Code or Visual Studio.
2. Ensure C++ compiler configuration is set up properly.
3. Build and run `mainFunction.cpp`.

---

## 👥 Contributors
- **Course**: DTS3013 Pengaturcaraan Berstruktur / Structured Programming
- Group Members (Refer to project submission report)
