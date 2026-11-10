#include <iostream> 
#include <string> 
#include <fstream>
#include <algorithm>

using namespace std;

struct Member 
{ 
    int id; 
    string memberName, memberID, memberContact, memberStatus; 
    Member *next; 
}; 

class MemberManagement
{
public: 
    Member *head = NULL; 
    void updateMember();
    void insertMember(); 
};

void MemberManagement::insertMember() 
{ 
    ofstream outfile;                    // declare output file 
    outfile.open("member.txt", ios::app); // open output file 
 
    Member *newMember = new Member; 
 
    cout << "Enter Member ID: "; // enter member ID 
    cin.ignore(); 
    getline(cin, newMember->memberID); 

    cout << "\nEnter Member Name: "; // enter member name 
    cin >> newMember->memberName; 
 
    cout << "Enter Contact Number: "; // enter contact number 
    cin.ignore();
    getline(cin, newMember->memberContact); 

    cout << "Enter Updated Member Status (Aktif(A)/Unaktif(U)): ";
    char choose;
    cin >> choose;
    if (choose == 'a' || choose == 'A')
        newMember->memberStatus = "Aktif";
    else if (choose == 'u' || choose == 'U')
        newMember->memberStatus = "Unaktif";
    else
    {
        cerr << "Invalid input for status!" << endl;
        return;
    }
 
    // newMember->memberStatus = "Active Member"; // set status as available 
 
    // input into member.txt file 
    outfile << "Member ID: " << newMember->memberID << endl; 
    outfile << "Member Name: " << newMember->memberName << endl; 
    outfile << "Member Contact: " << newMember->memberContact << endl; 
    outfile << "Member Status: " << newMember->memberStatus << endl; 
 
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
    int memberID; 
    cout << "\nEnter Member ID to Update: "; 
    cin >> memberID;

    ifstream infile("member.txt");  // Open file for reading 
    ofstream tempFile("temp.txt"); // Temporary file to store updated records 

    if (!infile.is_open() || !tempFile.is_open()) 
    { 
        cerr << "Error opening file!" << endl; 
        return; 
    } 

    bool memberFound = false; 
    string line, updatedMemberName, updatedMemberContact, updatedMemberStatus; 
    int currentId; 
    char choose; 

while (getline(infile, line)) // Read each line
{
    // Check if the current line is a "Member ID" line
    if (line.rfind("Member ID: ", 0) == 0)
    {
        string idStr = line.substr(11); // Extract ID after "Member ID: "

         if (!idStr.empty() && all_of(idStr.begin(), idStr.end(), ::isdigit))
          {
              currentId = stoi(idStr);

            if (currentId == memberID)
            {
                memberFound = true;

                // Get updated details from user
                cout << "\nMember ID: " << currentId << endl;
                cout << "Enter Updated Member Name: ";
                cin.ignore();
                getline(cin, updatedMemberName);

                cout << "Enter Updated Member Contact: ";
                getline(cin, updatedMemberContact);

                cout << "Enter Updated Member Status (Aktif(A)/Unaktif(U)): ";
                cin >> choose;

                if (choose == 'a' || choose == 'A')
                    updatedMemberStatus = "Aktif";
                else if (choose == 'u' || choose == 'U')
                    updatedMemberStatus = "Unaktif";
                else
                {
                    cerr << "Invalid input for status!" << endl;
                    return;
                }

                // Write updated member details to temp file
                tempFile << "Member ID: " << currentId << endl;
                tempFile << "Member Name: " << updatedMemberName << endl;
                tempFile << "Member Contact: " << updatedMemberContact << endl;
                tempFile << "Member Status: " << updatedMemberStatus << endl;

                // Skip the remaining fields of the current record
                while (getline(infile, line) && !line.empty() && line.rfind("Member ID: ", 0) != 0)
                {
                    // Do nothing, simply skip
                }

                if (!line.empty() && line.rfind("Member ID: ", 0) == 0)
                {
                    tempFile << line << endl;
                }
                continue;
            }
         } 
        
    }
   else
        {
            cerr << "Invalid Member ID format in line: " << line << endl;
            continue;
        }
    tempFile << line << endl; // Write non-matching lines to temp file
}

    infile.close(); 
    tempFile.close(); 

if (memberFound) 
    { 
        // Replace original file with updated temp file 
        remove("member.txt"); 
        rename("temp.txt", "member.txt"); 
        cout << "\nMember Record Updated Successfully!" << endl; 
    } 
    else 
    { 
        remove("temp.txt"); // Remove temp file if no update was made 
        cout << "\nMember Not Found!" << endl; 
    } 
}

int main() 
{
   MemberManagement MemberManagement;

   cout << "Enter your choice: "; 
   int choice;
   cin >> choice; 

   switch (choice) 
   { 
       case 1:
            MemberManagement.insertMember();
            break;
       case 2: 
           MemberManagement.updateMember();
           break; 
       default: 
           cout << "Invalid choice!" << endl;
           break;
   }

   return 0; 
}

