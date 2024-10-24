#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <time.h>

// Function to log access attempts and send an email
void log_access(const char *filename, const char *email) {
    FILE *log_file = fopen("honeypot.log", "a");
    if (log_file == NULL) {
        perror("Unable to open log file");
        exit(1);
    }
    
    time_t current_time;
    time(&current_time);
    
    fprintf(log_file, "File '%s' accessed at %s", filename, ctime(&current_time));
    fclose(log_file);

    // Send an email using a Windows-compatible method, e.g., Blat or PowerShell
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "blat -to %s -subject \"Honeypot Alert\" -body \"File %s was accessed at %s\"", email, filename, ctime(&current_time));
    system(cmd);
}

// Function to collect system information (basic example)
void get_system_info(char *info, size_t size) {
    // Example of gathering basic system info on Windows
    OSVERSIONINFO os_info;
    os_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&os_info);

    snprintf(info, size, "Operating System: Windows %ld.%ld (Build %ld)\n", 
             os_info.dwMajorVersion, os_info.dwMinorVersion, os_info.dwBuildNumber);
}

int main() {
    char email[100];
    char honeypot_file[100];
    
    // Ask the user to input an email address
    printf("Enter the email address to receive alerts: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';  // Remove newline character from email input
    
    // Ask the user to input a name for the honeypot file
    printf("Enter a name for the honeypot file: ");
    fgets(honeypot_file, sizeof(honeypot_file), stdin);
    honeypot_file[strcspn(honeypot_file, "\n")] = '\0';  // Remove newline character from honeypot file input
    
    // Create the honeypot file if it doesn't exist
    FILE *file = fopen(honeypot_file, "a");
    if (file == NULL) {
        perror("Unable to create honeypot file");
        exit(1);
    }
    fclose(file);
    
    printf("Honeypot file '%s' created.\n", honeypot_file);
    
    // Monitor the file for access
    struct stat file_stat;
    time_t last_access_time = 0;
    
    char system_info[256];
    get_system_info(system_info, sizeof(system_info));
    printf("System Info: %s\n", system_info); // Example display of system info
    
    while (1) {
        // Check the file's access time
        if (stat(honeypot_file, &file_stat) < 0) {
            perror("Unable to stat honeypot file");
            exit(1);
        }
        
        // If the file was accessed, log it and send an email
        if (file_stat.st_atime != last_access_time) {
            printf("File '%s' accessed!\n", honeypot_file);
            log_access(honeypot_file, email);
            last_access_time = file_stat.st_atime;
        }
        
        // Sleep for 5 seconds before checking again
        Sleep(5000);  // Windows uses Sleep (in milliseconds) instead of sleep()
    }
    
    return 0;
}
