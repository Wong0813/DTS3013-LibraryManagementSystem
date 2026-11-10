#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <limits>    // For numeric_limits
#include <algorithm> // For transform function

using namespace std;

struct Book
{
    int id;
    string title, author, genre, status;
    Book *next;
};

struct Member
{
    int id;
    string name, contact, status;
    Member *next;
};

// Structure to store borrowing information
struct BorrowRequest
{
    string userName;
    string bookID;
    string borrowTime;
    string returnTime;
};

class BookManagement
{
public:
    Book *head = NULL;
    void insertBook();
    void updateBook();
    void deleteBook();
    void searchBook();
    void showBook();
    void sortBook();
    void menu();
};

class MemberManagement
{
public:
    Member *head = NULL;
    void insertMember();
    void updateMember();
    void deleteMember();
    void searchMember();
    void sortMembers();
};

class BorrowBookManagement
{
private:
    queue<BorrowRequest> borrowQueue; // Queue for managing borrow requests
    queue<BorrowRequest> returnQueue; // Queue for managing return requests

public:
    void borrowBook();            // Add borrow request to the queue
    void processBorrowRequests(); // Process all borrow requests in the queue
    void returnBook();            // Add return request to the queue
    void processReturnRequests(); // Process all return requests in the queue
};

void BookManagement::menu()
{
    MemberManagement memberManagement;
    BorrowBookManagement borrowBookManagement;
    int choice;
    while (true)
    {
        cout << "=======================================\n";
        cout << "==     LIBRARY MANAGEMENT SYSTEM     ==\n";
        cout << "=======================================\n";
        cout << "==                                   ==\n";
        cout << "==   1.  Register New Book           ==\n";
        cout << "==   2.  Update Book Information     ==\n";
        cout << "==   3.  Delete Book Record          ==\n";
        cout << "==   4.  Search Book                 ==\n";
        cout << "==   5.  Show All Book               ==\n";
        cout << "==   6.  Sort Book                   ==\n";
        cout << "==                                   ==\n";
        cout << "=======================================\n";
        cout << "==                                   ==\n";
        cout << "==   7.  Register New Member         ==\n";
        cout << "==   8.  Update Member Information   ==\n";
        cout << "==   9.  Delete Member Record        ==\n";
        cout << "==   10. Search Member               ==\n";
        cout << "==   11. Sort Member                 ==\n";
        cout << "==                                   ==\n";
        cout << "=======================================\n";
        cout << "==                                   ==\n";
        cout << "==   12. Borrow Book                 ==\n";
        cout << "==   13. Return Book                 ==\n";
        // cout << "==   11. Show Borrow History         ==\n";
        // cout << "==   11. Update Borrow History       ==\n";
        // cout << "==   11. Delete Borrow History       ==\n";
        cout << "==                                   ==\n";
        cout << "=======================================\n";
        cout << "==                                   ==\n";
        cout << "==   14. Exit                        ==\n";
        cout << "==                                   ==\n";
        cout << "=======================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            insertBook();
            break;
        case 2:
            updateBook();
            break;
        case 3:
            deleteBook();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            showBook();
            break;
        case 6:
            sortBook();
            break;
        case 7:
            memberManagement.insertMember();
            break;
        case 8:
            memberManagement.updateMember();
            break;
        case 9:
            memberManagement.deleteMember();
            break;
        case 10:
            memberManagement.searchMember();
            break;
        case 11:
            memberManagement.sortMembers();
            break;
        case 12:
            borrowBookManagement.borrowBook();
            borrowBookManagement.processBorrowRequests(); // Process borrow requests after adding them to the queue
            break;
        case 13:
            borrowBookManagement.returnBook();
            borrowBookManagement.processReturnRequests(); // Process return requests after adding them to the queue
            break;
        case 14:
            return; // Exit the function
        default:
            cout << "Invalid Choice!" << endl;
        }
    }
}

void BookManagement::insertBook()
{
    ofstream outfile;                    // declare output file
    outfile.open("books.txt", ios::app); // open output file

    Book *newBook = new Book;

    cout << "\nEnter Book ID: "; // enter book id
    cin >> newBook->id;

    cout << "Enter Book Title: "; // enter book title
    cin.ignore();
    getline(cin, newBook->title);

    cout << "Enter Book Author: "; // enter book author
    getline(cin, newBook->author);

    cout << "Enter Book Genre: "; // enter book genre
    getline(cin, newBook->genre);

    newBook->status = "available"; // set book status as available

    // input into books.txt file
    outfile << "Book ID: " << newBook->id << endl;
    outfile << "Book Title: " << newBook->title << endl;
    outfile << "Book Author: " << newBook->author << endl;
    outfile << "Book Genre: " << newBook->genre << endl;
    outfile << "Book Status: " << newBook->status << endl;

    newBook->next = NULL;

    if (head == NULL)
    {
        head = newBook;
    }
    else
    {
        Book *ptr = head;

        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newBook;
    }
    cout << "\nBook registered successfully!" << endl;
}

void BookManagement::updateBook()
{
    int id;
    cout << "\nEnter Book ID to Update: ";
    cin >> id;

    ifstream infile("books.txt");  // Open file for reading
    ofstream tempFile("temp.txt"); // Temporary file to store updated records

    if (!infile || !tempFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool bookFound = false;
    string line, updatedTitle, updatedAuthor, updatedGenre, updatedStatus;
    int currentId;
    char choose;

    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Book ID: ", 0) == 0) // Check if line starts with "Book ID: "
        {
            currentId = stoi(line.substr(9)); // Extract ID from the line

            if (currentId == id)
            {
                // Book found
                bookFound = true;

                cout << "\nBook ID: " << currentId << endl;

                // Get updated details from user
                cout << "Enter Updated Book Title: ";
                cin.ignore();
                getline(cin, updatedTitle);

                cout << "Enter Updated Book Author: ";
                getline(cin, updatedAuthor);

                cout << "Enter Updated Book Genre: ";
                getline(cin, updatedGenre);

                cout << "Enter Updated Book Status (available(A)/unavailable(U)): ";
                cin >> choose;

                if (choose == 'a' || choose == 'A')
                {
                    updatedStatus = "available";
                }
                else if (choose == 'u' || choose == 'U')
                {
                    updatedStatus = "unavailable";
                }
                else
                {
                    cout << "Invalid!" << endl;
                    return;
                }

                // Write updated book details to temp file
                tempFile << "Book ID: " << currentId << endl;
                tempFile << "Book Title: " << updatedTitle << endl;
                tempFile << "Book Author: " << updatedAuthor << endl;
                tempFile << "Book Genre: " << updatedGenre << endl;
                tempFile << "Book Status: " << updatedStatus << endl;

                // Skip the next 4 lines in the file (as they belong to the current book)
                for (int i = 0; i < 4; i++)
                    getline(infile, line);

                continue; // Skip to the next iteration
            }
        }
        // Write the current line to the temp file if it doesn't belong to the book being updated
        tempFile << line << endl;
    }

    infile.close();
    tempFile.close();

    if (bookFound)
    {
        // Replace original file with updated temp file
        remove("books.txt");
        rename("temp.txt", "books.txt");
        cout << "\nBook Record Updated Successfully!" << endl;
    }
    else
    {
        remove("temp.txt"); // Remove temp file if no update was made
        cout << "\nBook Not Found!" << endl;
    }
}

void BookManagement::deleteBook()
{
    int id;
    cout << "\nEnter Book ID to Delete: ";
    cin >> id;

    ifstream infile("books.txt");  // Open the original file for reading
    ofstream tempFile("temp.txt"); // Create a temporary file for updated content

    if (!infile || !tempFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool bookFound = false;
    string line;
    int currentId;

    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Book ID: ", 0) == 0) // Check if the line starts with "Book ID: "
        {
            currentId = stoi(line.substr(9)); // Extract the book ID

            if (currentId == id)
            {
                // Skip this book's lines (5 lines for each book)
                bookFound = true;
                for (int i = 0; i < 4; i++) // Skip the next 4 lines
                    getline(infile, line);
                continue; // Skip to the next iteration
            }
        }

        // Write all lines except the ones to be deleted
        tempFile << line << endl;
    }

    infile.close();
    tempFile.close();

    if (bookFound)
    {
        // Replace original file with the updated temporary file
        remove("books.txt");
        rename("temp.txt", "books.txt");
        cout << "\nBook Record Deleted Successfully!" << endl;
    }
    else
    {
        remove("temp.txt"); // Remove temp file if no book was found
        cout << "\nBook Not Found!" << endl;
    }
}

void BookManagement::searchBook()
{
    int id;
    cout << "\nEnter Book ID to Search: ";
    cin >> id;
    ifstream infile("books.txt"); // Open the file for reading
    if (!infile)
    {
        cout << "Error opening file!" << endl;
        return;
    }
    bool bookFound = false;
    string line;
    int currentId;
    string title, author, genre, status;
    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Book ID: ", 0) == 0) // Check if the line starts with "Book ID: "
        {
            currentId = stoi(line.substr(9)); // Extract the book ID
            if (currentId == id)
            {
                // Book found, read its details
                bookFound = true;
                cout << "\n=======================================\n";
                cout << "==           List of Books           ==\n";
                cout << "=======================================\n";
                cout << "\nBook ID: " << currentId << endl;
                getline(infile, line);
                title = line.substr(12); // Extract title
                cout << "Book Title: " << title << endl;
                getline(infile, line);
                author = line.substr(13); // Extract author
                cout << "Book Author: " << author << endl;
                getline(infile, line);
                genre = line.substr(12); // Extract genre
                cout << "Book Genre: " << genre << endl;
                getline(infile, line);
                status = line.substr(13); // Extract status
                cout << "Book Status: " << status << endl;
                break;
            }
        }
    }
    infile.close();
    if (!bookFound)
    {
        cout << "\nBook Not Found!" << endl;
    }
}

void BookManagement::showBook()
{
    ifstream infile("books.txt"); // Open the file for reading
    if (!infile)
    {
        cout << "Error opening file or no records found!" << endl;
        return;
    }
    string line;
    bool hasBooks = false;
    cout << "\n=======================================\n";
    cout << "==           List of Books           ==\n";
    cout << "=======================================\n";
    while (getline(infile, line))
    {
        hasBooks = true;
        cout << line << endl;
        // Check for an empty line between books for better readability
        if (line.empty())
        {
            cout << "=======================================\n";
        }
    }
    infile.close();
    if (!hasBooks)
    {
        cout << "\nNo book records available.\n";
    }
}

void BookManagement::sortBook()
{
    ifstream infile("books.txt"); // Open the file for reading
    if (!infile)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<Book> books; // Vector to store all the books
    string line;
    Book temp;

    // Reading data from the file and storing it in the vector
    while (getline(infile, line))
    {
        if (line.find("Book ID:") == 0)
        {
            temp.id = stoi(line.substr(9)); // Extract ID and convert to integer
        }
        else if (line.find("Book Title:") == 0)
        {
            temp.title = line.substr(12); // Extract title
        }
        else if (line.find("Book Author:") == 0)
        {
            temp.author = line.substr(13); // Extract author
        }
        else if (line.find("Book Genre:") == 0)
        {
            temp.genre = line.substr(12); // Extract genre
        }
        else if (line.find("Book Status:") == 0)
        {
            temp.status = line.substr(13); // Extract status
            books.push_back(temp); // Add the book to the vector once all details are read
        }
    }

    infile.close(); // Close the input file

    // Sorting the vector of books based on their IDs
    sort(books.begin(), books.end(), [](const Book &a, const Book &b) {
        return a.id < b.id; // Sort by ID in ascending order
    });

    // Writing sorted books back to the file
    ofstream outfile("books.txt", ios::trunc); // Open file to overwrite its content
    for (const auto &book : books)
    {
        outfile << "Book ID: " << book.id << endl;
        outfile << "Book Title: " << book.title << endl;
        outfile << "Book Author: " << book.author << endl;
        outfile << "Book Genre: " << book.genre << endl;
        outfile << "Book Status: " << book.status << endl;
    }

    outfile.close(); // Close the output file
    cout << "\nBooks sorted by ID successfully!" << endl;
}

//==================================Member==============================================================================
void MemberManagement::insertMember()
{
    ofstream outfile;                      // declare output file
    outfile.open("members.txt", ios::app); // open output file

    Member *newMember = new Member;

    cout << "\nEnter Member ID: "; // enter member id
    cin >> newMember->id;

    cout << "Enter Member Name: "; // enter member name
    cin.ignore();
    getline(cin, newMember->name);

    cout << "Enter Contact Detail: "; // enter contact detail
    getline(cin, newMember->contact);

    newMember->status = "active"; // set member status as valid

    // input into members.txt file
    outfile << "Member ID: " << newMember->id << endl;
    outfile << "Member Name: " << newMember->name << endl;
    outfile << "Member Contact Detail: " << newMember->contact << endl;
    outfile << "Member Status: " << newMember->status << endl;

    newMember->next = NULL;

    if (head == NULL)
    {
        head = newMember;
    }
    else
    {
        Member *ptr = head;

        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = newMember;
    }
    cout << "\nMember registered successfully!" << endl;
}

void MemberManagement::updateMember()
{
    int id;
    cout << "\nEnter Member ID to Update: ";
    cin >> id;

    ifstream infile("members.txt"); // Open file for reading
    ofstream tempFile("temp.txt");  // Temporary file to store updated records

    if (!infile || !tempFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool memberFound = false;
    string line, updatedName, updatedContact, updatedStatus;
    int currentId;
    char choose;

    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Member ID: ", 0) == 0) // Check if line starts with "Member ID: "
        {
            currentId = stoi(line.substr(11)); // Extract ID from the line

            if (currentId == id)
            {
                // Member found
                memberFound = true;

                cout << "\nMember ID: " << currentId << endl;

                // Get updated details from user
                cout << "Enter Updated Member Name: ";
                cin.ignore();
                getline(cin, updatedName);

                cout << "Enter Updated Member Contact Detail: ";
                getline(cin, updatedContact);

                cout << "Enter Updated Member Status (active(A)/unactive(U)): ";
                cin >> choose;

                if (choose == 'a' || choose == 'A')
                {
                    updatedStatus = "active";
                }
                else if (choose == 'u' || choose == 'U')
                {
                    updatedStatus = "unactive";
                }
                else
                {
                    cout << "Invalid Choice!" << endl;
                    return;
                }

                // Write updated member details to temp file
                tempFile << "Member ID: " << currentId << endl;
                tempFile << "Member Name: " << updatedName << endl;
                tempFile << "Member Contact Detail: " << updatedContact << endl;
                tempFile << "Member Status: " << updatedStatus << endl;

                // Skip the next 4 lines in the file (as they belong to the current member)
                for (int i = 0; i < 4; i++)
                    getline(infile, line);

                continue; // Skip to the next iteration
            }
        }
        // Write the current line to the temp file if it doesn't belong to the member being updated
        tempFile << line << endl;
    }

    infile.close();
    tempFile.close();

    if (memberFound)
    {
        // Replace original file with updated temp file
        remove("members.txt");
        rename("temp.txt", "members.txt");
        cout << "\nMember Record Updated Successfully!" << endl;
    }
    else
    {
        remove("temp.txt"); // Remove temp file if no update was made
        cout << "\nMember Not Found!" << endl;
    }
}

void MemberManagement::deleteMember()
{
    int id;
    cout << "\nEnter Member ID to Delete: ";
    cin >> id;

    ifstream infile("members.txt"); // Open the original file for reading
    ofstream tempFile("temp.txt");  // Create a temporary file for updated content

    if (!infile || !tempFile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool memberFound = false;
    string line;
    int currentId;

    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Member ID: ", 0) == 0) // Check if the line starts with "Member ID: "
        {
            currentId = stoi(line.substr(11)); // Extract the member ID

            if (currentId == id)
            {
                // Skip this member's lines (4 lines for each member)
                memberFound = true;
                for (int i = 0; i < 3; i++) // Skip the next 3 lines
                    getline(infile, line);
                continue; // Skip to the next iteration
            }
        }

        // Write all lines except the ones to be deleted
        tempFile << line << endl;
    }

    infile.close();
    tempFile.close();

    if (memberFound)
    {
        // Replace original file with the updated temporary file
        remove("members.txt");
        rename("temp.txt", "members.txt");
        cout << "\nMember Record Deleted Successfully!" << endl;
    }
    else
    {
        remove("temp.txt"); // Remove temp file if no member was found
        cout << "\nMember Not Found!" << endl;
    }
}

void MemberManagement::searchMember()
{
    string searchName;
    cout << "\nEnter Member Name to Search: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    getline(cin, searchName);                            // Read the full name input

    ifstream infile("members.txt"); // Open the file for reading
    if (!infile)
    {
        cout << "Error opening file!" << endl;
        return;
    }

    bool memberFound = false;
    string line, prevLine;

    // Convert searchName to lowercase for case-insensitive comparison
    transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);

    while (getline(infile, line)) // Read each line
    {
        if (line.rfind("Member Name: ", 0) == 0) // Check if the line starts with "Member Name: "
        {
            string memberName = line.substr(13); // Extract the member name (starting from index 13)

            // Convert memberName to lowercase for case-insensitive comparison
            string lowercaseName = memberName;
            transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);

            if (lowercaseName == searchName) // Compare the name with the search input
            {
                memberFound = true;

                cout << "\n=======================================\n";
                cout << "==          Member Details           ==\n";
                cout << "=======================================\n";

                // Output Member ID (from the previous line)
                if (prevLine.rfind("Member ID: ", 0) == 0)
                    cout << prevLine << endl;

                // Output Member Name
                cout << line << endl;

                // Read and output Contact Detail
                getline(infile, line);
                if (line.rfind("Member Contact Detail: ", 0) == 0)
                    cout << line << endl;

                // Read and output Status
                getline(infile, line);
                if (line.rfind("Member Status: ", 0) == 0)
                    cout << line << endl;

                break; // Exit loop after finding the member
            }
        }
        prevLine = line; // Store the current line to access as the previous line in the next iteration
    }

    infile.close();

    if (!memberFound)
    {
        cout << "\nMember Not Found!" << endl;
    }
}

void MemberManagement::sortMembers()
{
    ifstream infile("members.txt"); // open file for reading
    if (!infile)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<Member> members; // to store all the members
    string line;
    Member temp;
    
    // Reading data from the file and storing in the members vector
    while (getline(infile, line))
    {
        if (line.find("Member ID:") == 0)
        {
            temp.id = stoi(line.substr(11)); // convert ID to integer
        }
        else if (line.find("Member Name:") == 0)
        {
            temp.name = line.substr(13);
        }
        else if (line.find("Member Contact Detail:") == 0)
        {
            temp.contact = line.substr(23); // adjust starting position
        }
        else if (line.find("Member Status:") == 0)
        {
            temp.status = line.substr(15); // adjust starting position
            members.push_back(temp); // store the member once all details are read
        }
    }

    infile.close(); // close the input file after reading all members

    // Sorting the members vector based on the member ID
    sort(members.begin(), members.end(), [](const Member &a, const Member &b) {
        return a.id < b.id; // sort by ID in ascending order
    });

    // Writing sorted members back to the file
    ofstream outfile("members.txt", ios::trunc); // open file to overwrite its content
    for (const auto &m : members)
    {
        outfile << "Member ID: " << m.id << endl;
        outfile << "Member Name: " << m.name << endl;
        outfile << "Member Contact Detail: " << m.contact << endl;
        outfile << "Member Status: " << m.status << endl;
    }

    outfile.close(); // close the output file
    cout << "\nMembers sorted by ID successfully!" << endl;
}



//==============================================Borrow Book============================================================================

void BorrowBookManagement::borrowBook()
{
    BorrowRequest request;

    // User input for borrowing details
    cout << "Enter User Name: ";
    cin.ignore();
    getline(cin, request.userName);

    cout << "Enter Book ID: ";
    cin >> request.bookID;

    string day, month, year;
    cout << "Enter Borrow Time (day): ";
    cin >> day;
    cout << "Enter Borrow Time (month): ";
    cin >> month;
    cout << "Enter Borrow Time (year): ";
    cin >> year;
    request.borrowTime = day + "/" + month + "/" + year;
    request.returnTime = "N/A";

    // Add the borrow request to the queue
    borrowQueue.push(request);

    cout << "Borrow request added to the queue!" << endl;
}

void BorrowBookManagement::processBorrowRequests()
{
    while (!borrowQueue.empty())
    {
        BorrowRequest request = borrowQueue.front(); // Get the next borrow request
        borrowQueue.pop();                           // Remove it from the queue

        // Open the books.txt file to check the status of the book
        ifstream booksFile("books.txt");
        ofstream tempBooksFile("temp_books.txt"); // Temporary file for updating book status
        bool bookFound = false;
        bool bookAvailable = false;

        string line;
        while (getline(booksFile, line))
        {
            tempBooksFile << line << endl; // Write the current line to the temp file

            if (line.find("Book ID: " + request.bookID) != string::npos)
            {
                bookFound = true;

                // Read and copy the next lines (title, author, genre, and status)
                string title, author, genre, status;
                getline(booksFile, title);
                getline(booksFile, author);
                getline(booksFile, genre);
                getline(booksFile, status);

                tempBooksFile << title << endl;
                tempBooksFile << author << endl;
                tempBooksFile << genre << endl;

                // Check if the book is available
                if (status.find("Book Status: available") != string::npos)
                {
                    bookAvailable = true;
                    tempBooksFile << "Book Status: unavailable" << endl; // Update status to unavailable
                }
                else
                {
                    tempBooksFile << status << endl; // Keep the same status if unavailable
                }
            }
        }

        booksFile.close();
        tempBooksFile.close();

        if (bookFound && bookAvailable)
        {
            // Update books.txt with the temporary file after changing status to unavailable
            remove("books.txt");
            rename("temp_books.txt", "books.txt");

            // Process the borrowing record
            bool updated = false;
            ifstream borrowFile("borrowing.txt");
            ofstream tempBorrowFile("temp_borrowing.txt");

            while (getline(borrowFile, line))
            {
                if (line.find("User Name: " + request.userName) != string::npos)
                {
                    string bookIDLine;
                    getline(borrowFile, bookIDLine);
                    if (bookIDLine.find("Book ID: " + request.bookID) != string::npos)
                    {
                        // Found existing borrow record, update it
                        updated = true;

                        // Skip over the old Borrow Time and Return Time lines
                        getline(borrowFile, line); // Skip Borrow Time
                        getline(borrowFile, line); // Skip Return Time

                        // Write the updated borrow details
                        tempBorrowFile << "User Name: " << request.userName << endl;
                        tempBorrowFile << "Book ID: " << request.bookID << endl;
                        tempBorrowFile << "Borrow Time: " << request.borrowTime << endl;
                        tempBorrowFile << "Return Time: " << request.returnTime << endl;

                        // Skip over the old record and continue
                        continue;
                    }
                }
                tempBorrowFile << line << endl; // Copy other lines to the temp file
            }

            borrowFile.close();

            // If no existing record was updated, add a new borrow record at the end
            if (!updated)
            {
                tempBorrowFile << "User Name: " << request.userName << endl;
                tempBorrowFile << "Book ID: " << request.bookID << endl;
                tempBorrowFile << "Borrow Time: " << request.borrowTime << endl;
                tempBorrowFile << "Return Time: " << request.returnTime << endl;
            }

            tempBorrowFile.close();
            // Replace the old borrowing.txt with the updated file
            remove("borrowing.txt");
            rename("temp_borrowing.txt", "borrowing.txt");

            cout << "Book borrowed successfully!" << endl;
        }
        else if (!bookFound)
        {
            cout << "Error: Book ID not found in books records!" << endl;
        }
        else
        {
            cout << "The Book is Already Borrowed!" << endl; // If the book is unavailable
        }
    }

    if (borrowQueue.empty())
    {
        cout << "All borrow requests have been processed." << endl;
    }
}

//================================================================Return Book==============================================================================

// Add return request to the queue
void BorrowBookManagement::returnBook()
{
    BorrowRequest request;

    // User input for return details
    cout << "Enter User Name: ";
    cin.ignore();
    getline(cin, request.userName);

    cout << "Enter Book ID: ";
    cin >> request.bookID;

    string day, month, year;
    cout << "Enter Return Time (day): ";
    cin >> day;
    cout << "Enter Return Time (month): ";
    cin >> month;
    cout << "Enter Return Time (year): ";
    cin >> year;
    request.returnTime = day + "/" + month + "/" + year;

    // Add the return request to the queue
    returnQueue.push(request);

    cout << "Return request added to the queue!" << endl;
}

void BorrowBookManagement::processReturnRequests()
{
    ifstream borrowFile;
    ofstream tempBorrowFile;
    ifstream booksFile;
    ofstream tempBooksFile;

    while (!returnQueue.empty())
    {
        BorrowRequest request = returnQueue.front(); // Get the next return request
        returnQueue.pop();                           // Remove it from the queue

        borrowFile.open("borrowing.txt");
        tempBorrowFile.open("temp_borrowing.txt");

        booksFile.open("books.txt");
        tempBooksFile.open("temp_books.txt");

        if (!borrowFile.is_open() || !tempBorrowFile.is_open() || !booksFile.is_open() || !tempBooksFile.is_open())
        {
            cout << "Error: Unable to open files for processing." << endl;
            return;
        }

        bool borrowRecordFound = false;
        bool bookFound = false;
        bool bookUnavailable = false;
        string line;

        // Process the borrowing record
        while (getline(borrowFile, line))
        {
            if (line.find("User Name: " + request.userName) != string::npos)
            {
                tempBorrowFile << line << endl; // Copy User Name

                string bookIDLine;
                getline(borrowFile, bookIDLine);
                if (bookIDLine.find("Book ID: " + request.bookID) != string::npos)
                {
                    borrowRecordFound = true;
                    tempBorrowFile << bookIDLine << endl;

                    string borrowTime;
                    getline(borrowFile, borrowTime); // Borrow Time
                    tempBorrowFile << borrowTime << endl;

                    // Find and replace the old "Return Time:" with the new return time
                    string returnTimeLine;
                    while (getline(borrowFile, returnTimeLine))
                    {
                        // Look for the line with "Return Time:"
                        if (returnTimeLine.find("Return Time:") != string::npos)
                        {
                            tempBorrowFile << "Return Time: " << request.returnTime << endl; // Replace with new return time
                            break;                                                           // Stop processing once we find and replace Return Time
                        }
                        tempBorrowFile << returnTimeLine << endl; // Otherwise, keep the same line
                    }

                    continue; // Skip the rest of the entry after processing the return time
                }
            }
            tempBorrowFile << line << endl; // Copy other lines
        }

        borrowFile.close();
        tempBorrowFile.close();

        if (borrowRecordFound)
        {
            // Replace the old borrowing.txt with the updated one
            remove("borrowing.txt");
            rename("temp_borrowing.txt", "borrowing.txt");

            // Update the book status in books.txt
            while (getline(booksFile, line))
            {
                tempBooksFile << line << endl; // Copy the current line to the temp file

                if (line.find("Book ID: " + request.bookID) != string::npos)
                {
                    bookFound = true;

                    // Read and copy the next lines (title, author, genre, and status)
                    string title, author, genre, status;
                    getline(booksFile, title);
                    getline(booksFile, author);
                    getline(booksFile, genre);
                    getline(booksFile, status);

                    tempBooksFile << title << endl;
                    tempBooksFile << author << endl;
                    tempBooksFile << genre << endl;

                    // Check if the book is currently unavailable (borrowed)
                    if (status.find("Book Status: unavailable") != string::npos)
                    {
                        bookUnavailable = true;
                        tempBooksFile << "Book Status: available" << endl; // Update status to available
                    }
                    else
                    {
                        tempBooksFile << status << endl;
                        cout << "Error: The book is already available." << endl;
                        return;
                    }
                }
            }

            booksFile.close();
            tempBooksFile.close();

            if (bookFound && bookUnavailable)
            {
                // Replace books.txt with the updated file after changing status to available
                remove("books.txt");
                rename("temp_books.txt", "books.txt");
                cout << "Book returned and status updated to available!" << endl;
            }
            else if (!bookFound)
            {
                cout << "Error: Book ID not found in the book records!" << endl;
                remove("temp_books.txt");
            }
        }
        else
        {
            cout << "Error: No matching record for User Name and Book ID found in borrowing records!" << endl;
        }
    }

    if (returnQueue.empty())
    {
        cout << "All return requests have been processed." << endl;
    }
}

//===================================Main Body==========================================================================
int main()
{
    BookManagement bookManagement;
    MemberManagement memberManagement;
    BorrowBookManagement borrowBookManagement;
    bookManagement.menu();
    return 0;
}