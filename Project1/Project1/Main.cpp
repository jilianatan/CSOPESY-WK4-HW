#include <iostream>
#include <string> 
#include <windows.h>
#include <vector> 

using namespace std;

// Function to write text at a specific position in the console
void writeConsoleOutput(HANDLE consoleHandle, int posX, int posY, const std::wstring& outputText) {
	COORD cursorPosition = { static_cast<SHORT>(posX), static_cast<SHORT>(posY) };
	DWORD charsWritten;
	WriteConsoleOutputCharacterW(consoleHandle, outputText.c_str(), static_cast<DWORD>(outputText.size()), cursorPosition, &charsWritten);
}

// Function to display the NVIDIA GPU summary and processes
COORD displayNvidiaSMI(HANDLE consoleHandle, COORD currentPosition) {
	// Display NVIDIA GPU header
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"+--------------------------------------------------------------------------------------+");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| NVIDIA-SMI 551.86              Driver Version: 551.86         CUDA Version: 12.4     |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|--------------------------------------+------------------------+----------------------|");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| GPU  Name                  TCC/WDDM  | Bus-Id         Disp. A | Volatile Uncorr. ECC |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| Fan  Temp             Pwr:Usage/Cap  |           Memory-Usage | GPU-Util  Compute M. |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|                                      |                        |               MIG M. |");

	// Display GPU info
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|======================================+========================+======================|");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0  NVIDIA GeForce GTX 1080    WDDM |   00000000:26:00.0  On |                  N/A |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| 28%   37C    P8           11W / 180W |      701MiB /  8192MiB |        0%    Default |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|                                      |                        |                  N/A |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"+--------------------------------------+------------------------+----------------------|");

	// Display processes header
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"+--------------------------------------------------------------------------------------+");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| Processes:                                                                           |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"| GPU    GI    CI      PID  Type  Process name                              GPU Memory |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|        ID    ID                                                           Usage      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|======================================================================================|");

	// Display dummy process info
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     1368   C+G  C:\\Windows\\System32\\dwm.exe                N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     2116   C+G  ...wekby3d8bbwe\\XboxGameBarWidgets.exe     N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     4224   C+G  ...on\\123.0.2420.65\\msedgewebview2.exe     N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     5684   C+G  C:\\Windows\\explorer.exe                    N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     6676   C+G  ...nt.CBS_cw5n1h2txyewy\\SearchHost.exe     N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"|   0    N/A   N/A     6700   C+G  ...2txyewy\\StartMenuExperienceHost.exe     N/A      |");
	writeConsoleOutput(consoleHandle, currentPosition.X, currentPosition.Y++, L"+--------------------------------------------------------------------------------------+");

	return currentPosition; // Return updated coordinates after printing
}

int main() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;

	std::string userInput;
	while (true) {
		std::cout << ">"; // Print command prompt
		std::getline(std::cin, userInput);
		cursorPosition.X++; // Increment cursor position for each command
		cursorPosition.Y++;

		// Check if the user typed 'nvidia-smi'
		if (userInput == "nvidia-smi") {
			COORD newCursorPosition = displayNvidiaSMI(consoleHandle, cursorPosition); // Display NVIDIA info
			cursorPosition = newCursorPosition;  // Update cursor position after displaying NVIDIA output
			cursorPosition.X = 0;     // Reset X coordinate
			SetConsoleCursorPosition(consoleHandle, cursorPosition);  // Reset cursor position to the beginning
		}
		// Exit condition for 'exit' command
		if (userInput == "exit") {
			return 0;  // Exit the loop on "exit"
		}
	}
}
