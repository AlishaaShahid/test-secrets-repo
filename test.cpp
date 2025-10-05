#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Deliberately vulnerable C program for testing

void insecure_copy(const char *input) {
    char buf[16];
    // Buffer overflow (CWE-120)
    strcpy(buf, input);
    printf("Buffer: %s\n", buf);
}

void format_issue(const char *user) {
    char out[64];
    // Unsafe sprintf (CWE-134)
    sprintf(out, "Hello %s", user);
    // Format string vulnerability if 'user' contains '%s' etc.
    printf(out);
}

void command_injection(const char *arg) {
    char cmd[128];
    strcpy(cmd, "ls ");
    strcat(cmd, arg);   // CWE-120
    system(cmd);        // CWE-78
}

int main(int argc, char **argv) {
    // Hardcoded secrets for testing secret scanner
    const char *aws_key = "AKIA1234567890EXAMPLE";
    const char *jwt = "eyJhbGciOiJIUzI1NiJ9.eyJ1c2VyIjoiYWRtaW4ifQ.fakeSignature";
    const char *password = "P@ssw0rd123456789012345"; // high-entropy secret

    if (argc > 1) {
        insecure_copy(argv[1]);
        format_issue(argv[1]);
        command_injection(argv[1]);
    } else {
        insecure_copy("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    }

    printf("Using AWS Key: %s\n", aws_key);
    printf("JWT: %s\n", jwt);
    printf("Password: %s\n", password);

    return 0;
}

