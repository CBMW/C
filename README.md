# C HoneyPot 

---

### **Honeypot.c** 
A lightweight honeypot program written in C to monitor file access. The program creates a file that, when accessed, logs the event and sends an alert email with system information.

#### Features:
-  **File Monitoring**: Tracks access to a specified honeypot file.
-  **Email Alerts**: Sends an email notification when the honeypot file is accessed.
-  **System Information Logging**: Logs basic system info like the operating system and build version.
  
#### Usage:
1. **Clone the repo**:
   ```bash
   git clone https://github.com/yourusername/C-Honeypot.git
2. Run through CygWin terminal
   ```bash
   ./honeypot.exe

#### Bugs:
- **Windows only**: I'd like to have this run accross multiple OS however not sure C is the right language here.  
- **CygWin terminal**: I used CygWin and GCC compiler to build this so unless you compile differently, this must run through CygWin terminal.  
