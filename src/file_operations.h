#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <sys/types.h>

using std::string;

// File operations
void listFiles();
void createFile(const string& filename);
void readFile(const string& filename);
void writeFile(const string& filename, const string& content);
void appendFile(const string& filename, const string& content);

// Directory operations
void createDirectory(const string& dirname);
void removeDirectory(const string& dirname);

// File management
void deleteFile(const string& filename);
void copyFile(const string& source, const string& destination);
void moveFile(const string& source, const string& destination);
void renameFile(const string& oldName, const string& newName);

// Search and information
void searchFile(const string& filename);
void fileInformation(const string& filename);

// Permissions
void changePermissions(const std::string&filename,mode_t permissions);
void checkAccess(const string& filename);

// File descriptor / file positioning
void demonstrateSeek(const string& filename);
void monitorFileDescriptors(const std::string& filename);

#endif
