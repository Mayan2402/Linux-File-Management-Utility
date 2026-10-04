#include "file_operations.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <ctime>

using namespace std;


// ============================================================
// 1. LIST FILES
// ============================================================

void listFiles()
{
    cout << "\n========== FILES AND DIRECTORIES ==========\n";

    DIR* dir = opendir(".");

    if (dir == nullptr)
    {
        perror("opendir");
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr)
    {
        string name = entry->d_name;

        if (name == "." || name == "..")
            continue;

        struct stat fileStat;

        if (stat(name.c_str(), &fileStat) == -1)
        {
            perror("stat");
            continue;
        }

        if (S_ISDIR(fileStat.st_mode))
            cout << "[DIR]  " << name << endl;
        else
            cout << "[FILE] " << name << endl;
    }

    closedir(dir);
}


// ============================================================
// 2. CREATE FILE
// ============================================================

void createFile(const string& filename)
{
    int fd = open(
        filename.c_str(),
        O_WRONLY | O_CREAT | O_EXCL,
        0644
    );

    if (fd == -1)
    {
        perror("open");
        return;
    }

    close(fd);

    cout << "File created successfully: "
         << filename << endl;
}


// ============================================================
// 3. DELETE FILE
// ============================================================

void deleteFile(const string& filename)
{
    if (unlink(filename.c_str()) == 0)
    {
        cout << "File deleted successfully: "
             << filename << endl;
    }
    else
    {
        perror("unlink");
    }
}


// ============================================================
// 4. COPY FILE
// ============================================================

void copyFile(
    const string& source,
    const string& destination
)
{
    int sourceFd = open(source.c_str(), O_RDONLY);

    if (sourceFd == -1)
    {
        perror("open source");
        return;
    }

    int destinationFd = open(
        destination.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC,
        0644
    );

    if (destinationFd == -1)
    {
        perror("open destination");
        close(sourceFd);
        return;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(
                sourceFd,
                buffer,
                sizeof(buffer))) > 0)
    {
        ssize_t totalWritten = 0;

        while (totalWritten < bytesRead)
        {
            ssize_t bytesWritten = write(
                destinationFd,
                buffer + totalWritten,
                bytesRead - totalWritten
            );

            if (bytesWritten == -1)
            {
                perror("write");
                close(sourceFd);
                close(destinationFd);
                return;
            }

            totalWritten += bytesWritten;
        }
    }

    if (bytesRead == -1)
        perror("read");

    close(sourceFd);
    close(destinationFd);

    cout << "File copied successfully.\n";
}


// ============================================================
// 5. MOVE FILE
// ============================================================

void moveFile(
    const string& source,
    const string& destination
)
{
    if (rename(source.c_str(), destination.c_str()) == 0)
    {
        cout << "File moved successfully.\n";
    }
    else
    {
        perror("rename");
    }
}


// ============================================================
// 6. RENAME FILE
// ============================================================

void renameFile(
    const string& oldName,
    const string& newName
)
{
    if (rename(oldName.c_str(), newName.c_str()) == 0)
    {
        cout << "File renamed successfully.\n";
    }
    else
    {
        perror("rename");
    }
}


// ============================================================
// 7. CREATE DIRECTORY
// ============================================================

void createDirectory(const string& dirname)
{
    if (mkdir(dirname.c_str(), 0755) == 0)
    {
        cout << "Directory created successfully: "
             << dirname << endl;
    }
    else
    {
        perror("mkdir");
    }
}


// ============================================================
// 8. REMOVE DIRECTORY
// ============================================================

void removeDirectory(const string& dirname)
{
    if (rmdir(dirname.c_str()) == 0)
    {
        cout << "Directory removed successfully: "
             << dirname << endl;
    }
    else
    {
        perror("rmdir");
    }
}


// ============================================================
// 9. RECURSIVE SEARCH
// ============================================================

void searchRecursive(
    const string& directory,
    const string& filename,
    bool& found
)
{
    DIR* dir = opendir(directory.c_str());

    if (dir == nullptr)
        return;

    struct dirent* entry;

    while ((entry = readdir(dir)) != nullptr)
    {
        string name = entry->d_name;

        if (name == "." || name == "..")
            continue;

        string fullPath = directory + "/" + name;

        struct stat fileStat;

        if (stat(fullPath.c_str(), &fileStat) == -1)
            continue;

        if (name == filename)
        {
            cout << "Found: " << fullPath << endl;
            found = true;
        }

        if (S_ISDIR(fileStat.st_mode))
        {
            searchRecursive(
                fullPath,
                filename,
                found
            );
        }
    }

    closedir(dir);
}


void searchFile(const string& filename)
{
    bool found = false;

    cout << "\nSearching for: "
         << filename << endl;

    searchRecursive(".", filename, found);

    if (!found)
        cout << "File not found.\n";
}


// ============================================================
// 10. FILE INFORMATION
// ============================================================

void fileInformation(const string& filename)
{
    struct stat fileStat;

    if (stat(filename.c_str(), &fileStat) == -1)
    {
        perror("stat");
        return;
    }

    cout << "\n========== FILE INFORMATION ==========\n";

    cout << "File: "
         << filename << endl;

    cout << "Size: "
         << fileStat.st_size
         << " bytes" << endl;

    cout << "Inode: "
         << fileStat.st_ino << endl;

    cout << "Number of Links: "
         << fileStat.st_nlink << endl;

    cout << "User ID: "
         << fileStat.st_uid << endl;

    cout << "Group ID: "
         << fileStat.st_gid << endl;

    struct passwd* user = getpwuid(fileStat.st_uid);

    if (user != nullptr)
    {
        cout << "Owner: "
             << user->pw_name << endl;
    }

    struct group* groupInfo = getgrgid(fileStat.st_gid);

    if (groupInfo != nullptr)
    {
        cout << "Group: "
             << groupInfo->gr_name << endl;
    }

    if (S_ISREG(fileStat.st_mode))
        cout << "Type: Regular File" << endl;
    else if (S_ISDIR(fileStat.st_mode))
        cout << "Type: Directory" << endl;
    else if (S_ISLNK(fileStat.st_mode))
        cout << "Type: Symbolic Link" << endl;
    else
        cout << "Type: Other" << endl;

    cout << "Permissions: "
         << oct
         << (fileStat.st_mode & 0777)
         << dec
         << endl;

    cout << "Last Modified: "
         << ctime(&fileStat.st_mtime);
}


// ============================================================
// 11. READ FILE
// ============================================================

void readFile(const string& filename)
{
    int fd = open(filename.c_str(), O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    cout << "\n========== FILE CONTENT ==========\n";

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(
                fd,
                buffer,
                sizeof(buffer))) > 0)
    {
        cout.write(buffer, bytesRead);
    }

    if (bytesRead == -1)
        perror("read");

    cout << "\n";

    close(fd);
}


// ============================================================
// 12. WRITE FILE
// ============================================================

void writeFile(
    const string& filename,
    const string& content
)
{
    int fd = open(
        filename.c_str(),
        O_WRONLY | O_CREAT | O_TRUNC,
        0644
    );

    if (fd == -1)
    {
        perror("open");
        return;
    }

    ssize_t bytesWritten = write(
        fd,
        content.c_str(),
        content.length()
    );

    if (bytesWritten == -1)
    {
        perror("write");
    }
    else
    {
        cout << "Content written successfully.\n";
    }

    close(fd);
}


// ============================================================
// 13. APPEND FILE
// ============================================================

void appendFile(
    const string& filename,
    const string& content
)
{
    int fd = open(
        filename.c_str(),
        O_WRONLY | O_CREAT | O_APPEND,
        0644
    );

    if (fd == -1)
    {
        perror("open");
        return;
    }

    ssize_t bytesWritten = write(
        fd,
        content.c_str(),
        content.length()
    );

    if (bytesWritten == -1)
    {
        perror("write");
    }
    else
    {
        cout << "Content appended successfully.\n";
    }

    close(fd);
}


// ============================================================
// 14. CHANGE PERMISSIONS
// ============================================================

void changePermissions(
    const std::string& filename,
    mode_t permissions
)
{
    if (chmod(filename.c_str(), permissions) == -1)
	
    {
            perror("chmod");
            return;
         }
        cout << "Permissions changed successfully."<< endl;
    }


// ============================================================
// 15. CHECK ACCESS
// ============================================================

void checkAccess(const string& filename)
{
    cout << "\n========== ACCESS CHECK ==========\n";

    if (access(filename.c_str(), F_OK) == 0)
        cout << "File exists.\n";
    else
    {
        perror("access");
        return;
    }

    if (access(filename.c_str(), R_OK) == 0)
        cout << "Read permission: YES\n";
    else
        cout << "Read permission: NO\n";

    if (access(filename.c_str(), W_OK) == 0)
        cout << "Write permission: YES\n";
    else
        cout << "Write permission: NO\n";

    if (access(filename.c_str(), X_OK) == 0)
        cout << "Execute permission: YES\n";
    else
        cout << "Execute permission: NO\n";
}


// ============================================================
// 16. LSEEK DEMONSTRATION
// ============================================================

void demonstrateSeek(const string& filename)
{
    int fd = open(filename.c_str(), O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    cout << "\n========== LSEEK DEMONSTRATION ==========\n";

    off_t currentPosition = lseek(fd, 0, SEEK_CUR);

    if (currentPosition == -1)
    {
        perror("lseek");
        close(fd);
        return;
    }

    cout << "Initial file position: "
         << currentPosition << endl;

    off_t endPosition = lseek(fd, 0, SEEK_END);

    if (endPosition == -1)
    {
        perror("lseek");
        close(fd);
        return;
    }

    cout << "End position: "
         << endPosition << endl;

    off_t newPosition = lseek(fd, 0, SEEK_SET);

    if (newPosition == -1)
    {
        perror("lseek");
        close(fd);
        return;
    }

    cout << "Position after SEEK_SET: "
         << newPosition << endl;

    close(fd);
}




// ============================================================
// File Descriptor Monitoring
// ============================================================

void monitorFileDescriptors(const std::string& filename)
{
    cout << "\n========== FILE DESCRIPTOR MONITORING ==========\n";

    int fd = open(filename.c_str(), O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    cout << "File: " << filename << endl;
    cout << "File Descriptor: " << fd << endl;

    char fdPath[PATH_MAX];
    char target[PATH_MAX];

    snprintf(fdPath, sizeof(fdPath), "/proc/self/fd/%d", fd);

    ssize_t length = readlink(fdPath, target, sizeof(target) - 1);

    if (length != -1)
    {
        target[length] = '\0';
        cout << "Actual File: " << target << endl;
    }

    close(fd);

    cout << "===============================================\n";
}


