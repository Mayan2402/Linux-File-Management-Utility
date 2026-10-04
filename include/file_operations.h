#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <sys/types.h>

// Basic file operations
void listFiles();
void createFile(const std::string& filename);
void deleteFile(const std::string& filename);
void copyFile(const std::string& source, const std::string& destination);
void moveFile(const std::string& source, const std::string& destination);
void renameFile(const std::string& oldName, const std::string& newName);

// Directory operations
void createDirectory(const std::string& dirname);
void removeDirectory(const std::string& dirname);

// Search
void searchFile(const std::string& filename);

// File information
void fileInformation(const std::string& filename);

// Read / Write / Append
void readFile(const std::string& filename);

void writeFile(
    const std::string& filename,
    const std::string& content
);

void appendFile(
    const std::string& filename,
    const std::string& content
);

// Permissions
void changePermissions(
    const std::string& filename,
    mode_t permissions
);

void checkAccess(const std::string& filename);

// lseek
void demonstrateSeek(const std::string& filename);


//File Descriptor Monitoring
void monitorFileDescriptors();


#endif
