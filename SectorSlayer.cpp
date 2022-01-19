#include <windows.h>

#include <stdio.h>

void findMFT() {
    //MFT (master file table) is going to be moving around, depending if the sector that it originally resides on has a bad sector. If the data for the MFT is corrupted, Windows will think the drive is unformatted

}

int main(int argc, char** argv)
{
    int retCode = 0;
    BYTE sector[512];
    DWORD bytesRead;
    HANDLE device = NULL;
    int numSector = 5;

    struct ntfsMap {
        int jump = 0x00;
        long long oemID = 0x03;
        int bpb = 0x0B;
        int ebpb= 0x24;
        int bootstrap = 0x54;
        WORD eos = 0x01FE;
    };

    findMFT();

    device = CreateFile(L"\\\\.\\C:",    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile: %u\n", GetLastError());
        return 1;
    }

    SetFilePointer(device, numSector * 512, NULL, FILE_BEGIN);

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
    {
        printf("ReadFile: %u\n", GetLastError());
    }
    else
    {
        printf("Success!\n");
    }

    return 0;
}