#ifndef FILEMANAGE
#define FILEMANAGE

// Allows you to edit the file
void editfile(const char* filename[]);
// Allows you to rename the fil by providing the current path and the new path
int rename_files(char __currentfile[], char __newfilename[]);
// Manages the folders and show the directories
int folders(const char* data);
// Used for managing the user choices from the input
static int choices(const int* choice);
// Show the options available
void options(void);

#endif
