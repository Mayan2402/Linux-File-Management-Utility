#include <iostream>
#include <string>
#include <limits>
#include <sys/types.h>

#include "file_operations.h"

using namespace std;

void showMenu()
{
    cout << "\n";
    cout << "==================================================\n";
    cout << "          LINUX FILE MANAGEMENT UTILITY\n";
    cout << "==================================================\n";
    cout << " 1.  List Files\n";
    cout << " 2.  Create File\n";
    cout << " 3.  Read File\n";
    cout << " 4.  Write File\n";
    cout << " 5.  Append to File\n";
    cout << " 6.  Create Directory\n";
    cout << " 7.  Remove Directory\n";
    cout << " 8.  Delete File\n";
    cout << " 9.  Copy File\n";
    cout << "10.  Move File\n";
    cout << "11.  Rename File\n";
    cout << "12.  Search File\n";
    cout << "13.  File Information\n";
    cout << "14.  Change Permissions\n";
    cout << "15.  Check Permissions\n";
    cout << "16.  lseek Demonstration\n";
    cout << "17.  File Desciptor Monitoring\n";
    cout << "18.  Exit\n";
    cout << "==================================================\n";
}

int main()
{
    int choice;

    while (true)
    {
        showMenu();

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        switch (choice)
        {
            // ------------------------------------------------
            // 1. List Files
            // ------------------------------------------------
            case 1:
            {
                listFiles();
                break;
            }

            // ------------------------------------------------
            // 2. Create File
            // ------------------------------------------------
            case 2:
            {
                string filename;

                cout << "Enter file name: ";
                getline(cin, filename);

                createFile(filename);
                break;
            }

            // ------------------------------------------------
            // 3. Read File
            // ------------------------------------------------
            case 3:
            {
                string filename;

                cout << "Enter file name to read: ";
                getline(cin, filename);

                readFile(filename);
                break;
            }

            // ------------------------------------------------
            // 4. Write File
            // ------------------------------------------------
            case 4:
            {
                string filename;
                string content;

                cout << "Enter file name: ";
                getline(cin, filename);

                cout << "Enter content to write: ";
                getline(cin, content);

                writeFile(filename, content);
                break;
            }

            // ------------------------------------------------
            // 5. Append File
            // ------------------------------------------------
            case 5:
            {
                string filename;
                string content;

                cout << "Enter file name: ";
                getline(cin, filename);

                cout << "Enter content to append: ";
                getline(cin, content);

                appendFile(filename, content);
                break;
            }

            // ------------------------------------------------
            // 6. Create Directory
            // ------------------------------------------------
            case 6:
            {
                string dirname;

                cout << "Enter directory name: ";
                getline(cin, dirname);

                createDirectory(dirname);
                break;
            }

            // ------------------------------------------------
            // 7. Remove Directory
            // ------------------------------------------------
            case 7:
            {
                string dirname;

                cout << "Enter directory name to remove: ";
                getline(cin, dirname);

                removeDirectory(dirname);
                break;
            }

            // ------------------------------------------------
            // 8. Delete File
            // ------------------------------------------------
            case 8:
            {
                string filename;

                cout << "Enter file name to delete: ";
                getline(cin, filename);

                deleteFile(filename);
                break;
            }

            // ------------------------------------------------
            // 9. Copy File
            // ------------------------------------------------
            case 9:
            {
                string source;
                string destination;

                cout << "Enter source file: ";
                getline(cin, source);

                cout << "Enter destination file: ";
                getline(cin, destination);

                copyFile(source, destination);
                break;
            }

            // ------------------------------------------------
            // 10. Move File
            // ------------------------------------------------
            case 10:
            {
                string source;
                string destination;

                cout << "Enter source file/path: ";
                getline(cin, source);

                cout << "Enter destination path: ";
                getline(cin, destination);

                moveFile(source, destination);
                break;
            }

            // ------------------------------------------------
            // 11. Rename File
            // ------------------------------------------------
            case 11:
            {
                string oldName;
                string newName;

                cout << "Enter old file name: ";
                getline(cin, oldName);

                cout << "Enter new file name: ";
                getline(cin, newName);

                renameFile(oldName, newName);
                break;
            }

            // ------------------------------------------------
            // 12. Search File
            // ------------------------------------------------
            case 12:
            {
                string filename;

                cout << "Enter file name to search: ";
                getline(cin, filename);

                searchFile(filename);
                break;
            }

            // ------------------------------------------------
            // 13. File Information
            // ------------------------------------------------
            case 13:
            {
                string filename;

                cout << "Enter file name: ";
                getline(cin, filename);

                fileInformation(filename);
                break;
            }

            // ------------------------------------------------
            // 14. Change Permissions
            // ------------------------------------------------
            
            case 14:
{
    string filename;
    int permissions;

    cout << "Enter filename: ";
    cin >> filename;

    cout << "Enter permissions (e.g. 755): ";
    cin >> permissions;

    mode_t mode = static_cast<mode_t>(
        ((permissions / 100) * 64) +
        (((permissions / 10) % 10) * 8) +
        (permissions % 10)
    );

    changePermissions(filename, mode);

    break;
}

            // ------------------------------------------------
            // 15. Check Permissions
            // ------------------------------------------------
            case 15:
            {
                string filename;

                cout << "Enter file name: ";
                getline(cin, filename);

                checkAccess(filename);
 
               break;
            }

            // ------------------------------------------------
            // 16. lseek Demonstration
            // ------------------------------------------------
            case 16:
            {
                string filename;

                cout << "Enter file name: ";
                getline(cin, filename);

                demonstrateSeek(filename);
                break;
            }
               case 17:
{
    string filename;

    cout << "Enter filename: ";
    cin >> filename;

    monitorFileDescriptors(filename);

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

    break;
}


             // ------------------------------------------------
            // 18. Exit
            // ------------------------------------------------
            case 18:
            {
                cout << "\nThank you for using "
                     << "Linux File Management Utility.\n";

                return 0;
            }

            // ------------------------------------------------
            // Invalid choice
            // ------------------------------------------------
            default:
            {
                cout << "Invalid choice. "
                     << "Please enter 1-18.\n";
            }
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    }

    return 0;
}
