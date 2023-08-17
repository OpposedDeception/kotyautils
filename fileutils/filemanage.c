#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fileutils.h>


void editfile(const char* filename[]) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = malloc(size + 1);
    fread(content, 1, size, file);
    content[size] = '\0';

    printf("Current content:\n%s\n", content);

    printf("Enter the new content (press Ctrl+D to save and exit):\n");
    char newContent[1000];
    if (fgets(newContent, sizeof(newContent), stdin) != NULL) {
        fseek(file, 0, SEEK_SET);
        fputs(newContent, file);
        printf("File content updated successfully.\n");
    } else {
        printf("Error reading input.\n");
    }

    fclose(file);
    free(content);
}

int rename_files(char __currentfile[], char __newfilename[]) {
    if (rename(__currentfile, __newfilename) == 0) {
        printf("File renamed successfully.\n");
    }
    else {
        perror("rename");
        return -1;
    }
    printf("The task was done!");
    return 0;
}

int folders(const char* data) {
    if (data == NULL) {
        perror("data");
        return -1;
    } else {
        DIR* dir = opendir("/");
        if (dir == NULL) {
            perror("opendir");
            return -1;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }

        closedir(dir);
        return 0;
    }
}


static int choices(const int* choice) {
    switch (*choice)
    {
    case 1:
        system("ls /");
        break;
    case 2:
        char* folderchoice = (char*)malloc(100 * sizeof(char));
        while (1) {
            printf("/");
            fgets(folderchoice, 100, stdin);

            if (strlen(folderchoice) == 0) {
                printf("Empty input was given\n");
                continue;
            } else {
                folders(folderchoice);
                continue;
            }
            free(folderchoice);
    }
        break;
    case 3:
        char oldname[100];
        char newname[100];
        printf("Enter the old file path: ");
        scanf("%s", oldname);
        printf("Enter the new file name path: ");
        scanf("%s", newname);
        rename(oldname, newname);
        break; 
    case 4:
        char* nameofthefile = (char*)malloc(100 * sizeof(char));
        chdir("/home/koten");
        printf("Enter the name of the file you want to edit: ");
        fgets(nameofthefile, sizeof(nameofthefile), stdin);
        editfile(nameofthefile);
    default:
        break;
    }
    return 0;
}

void options(void) {
    printf("What do you want to do?\n1. Print contents of root folder\n2. Browse your root folder\n3. Rename files\n4. Edit the file\n");
}

int main(void) {
    int input;
    char* cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Your current directory is %s\n", cwd);
    }
    options();
    while (1) {
        scanf("%d", &input);
        if (input == 1 || input == 2 || input == 3 || input == 4) {
            choices(&input);
        }
    }
    return 0;
}
