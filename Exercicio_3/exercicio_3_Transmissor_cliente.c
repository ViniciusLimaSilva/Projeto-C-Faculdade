#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    hSerial = CreateFile("\\\\.\\COM2", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erro ao abrir a porta serial\n");
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao obter o estado da porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Taxa de baud: 9600 bps
    dcbSerialParams.ByteSize = 8;        // Bits de dados: 8 bits
    dcbSerialParams.StopBits = ONESTOPBIT; // Bit de parada: 1 bit
    dcbSerialParams.Parity = NOPARITY;     // Paridade: Nenhuma

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Erro ao configurar o estado da porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Erro ao configurar os timeouts da porta serial\n");
        CloseHandle(hSerial);
        return 1;
    }

    char mensagem[256];

    while (1) {
        printf("Digite uma mensagem para enviar ao servidor (ou 'exit' para sair):\n");
        fgets(mensagem, sizeof(mensagem), stdin);

        // Remove a quebra de linha da entrada do usuário
        mensagem[strlen(mensagem) - 1] = '\0';

        // Envia a mensagem pela porta serial
        DWORD bytesWritten;
        if (WriteFile(hSerial, mensagem, strlen(mensagem), &bytesWritten, NULL)) {
            if (strcmp(mensagem, "exit") == 0) {
                break;
            }
        }
    }

    CloseHandle(hSerial);

    return 0;
}

