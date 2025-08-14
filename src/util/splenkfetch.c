//this shit is so scuffed
//1000% the least efficent way
//He is silli
//if a .exe file pops up from this it is cause of my running this incorrectly
#include <stdio.h>

int main(void) {
    const char *splenk_logo =
    "@@@@@%&%@@@@@@@@@@@@@@&&@@@@@@   Splenkfetch v0.0.0.0.0.1\n"
    "@@@@-. =@@@@@@@@@@@@&.  &@@@@@   OS: SplenkOS (Super awesome Dev Edition)\n"
    "@@@@*+*%%%&**++++++&&*+-+@@@@@   Host: Placeholder Machine\n"
    "@@%@*+=---:::::::---=++*%@@@@@   Kernel: splenk-kern 0.0.1\n"
    "@@@+::-------------------&@@@@   Uptime: 0d 00h 00m\n"
    "@@%-------=---------*+----+@@@   Packages: 000 (splpkg)\n"
    "@@*:------@*:------=@*----=@@@   Shell: idkwhat we are calling this shell 0.1\n"
    "@@&:------&@=------+@=----&@@@   Resolution: 0000x0000 (This isnt a mistake im just running it a real machine that has resolution)\n"
    "@@@--------*%*=---=%%-----%@@@   DE: like we are getting a DE\n"
    "@@@---------=*%%%%&*------+%@@   WM: never in a balatrillion years will WM work\n"
    "@@%-:-------=--=++=:---==---*@   WM Theme: Default\n"
    "@+==+*=--*%@@@@@@@@*===%@%@@@@   Terminal: spookterm\n"
    "@@@@@@--+@@@@@@@@@@@@@@@@@@@@@   CPU: Add smth to find this out\n"
    "@@@@@@&%@@@@@@@@@@@@@@@@@@@@@@   GPU: Idfk\n"
    "                                RAM: We dont need ram anyway\n";

    print("%s", splenk_logo);
    return 0;
}
// idk how to get the actual values for the placeholders
//spook dont do it please tell me how to get the values so I can learn
//If you are reading this and you are spook, please tell me how to get the values for the placeholders
//If you are reading this and you are not spook, who are you cause you arent me or spook
//This ISNT a neofetch clone, neofetch is a clone of splenkfetch (Trust me bro)) 

// hi plenorf
// look in driver.c, at the bottom in the findDriver function.
// the pci tells us the vendor id and deviceId, which we can use
// to figure out the exact type of device you have installed
// look for a vendor and device id lookup online, it'll help you
// on boot the PCI code prints out all the hardware on the machine