#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define WAIT(ms) Sleep(ms)
#else
#include <unistd.h>
#define WAIT(ms) usleep((ms) * 1000)
#endif

#define RESET  "\033[0m"
#define RED    "\033[1;31m"
#define GREEN  "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE   "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN   "\033[1;36m"
#define WHITE  "\033[1;37m"

/* Screen animation */
void clearScreen() {
    printf("\033[2J\033[H");
}

/* Fireworks animation */
void fireworks(int frame) {
    const char *colors[] = {
        RED, GREEN, YELLOW, BLUE, PURPLE, CYAN
    };

    printf("\n");

    for (int i = 0; i < 3; i++) {
        printf("       ");

        for (int j = 0; j < 8; j++) {
            printf("%s%c   ",
                colors[(i + j + frame) % 6],
                (frame + j) % 2 ? '*' : '+');
        }

        printf("%s\n", RESET);
    }
}

/* Your original ASCII artwork */
void showFace(int blink) {

    const char *art[] = {
"                                               ......",
"                                         ..:^:::::::::::::..",
"                                   ..::^^^^^:............::^^:..",
"                               .::..:::::..       ....... ..:^^^^:",
"                             .....::^^:.              ..::....^^^~^:.",
"                           .::..::::::.   ..            .::::..:^~~~~:.",
"                         .::....:...   ..:::::::....      .:^^:::^~~~~~:",
"                        .:......    .:^~!!!7!!!!~~^:::::.  .:^~~^:^~~~~~^.",
"                        :.....    .^!77???JJJ????77!~^^^^::..:^~~^^^^~~~~~:",
"                       ::...    .^!7???JJYYYYYYYJJJ??7!~^^^:..^^~!~^^~~~^~~^",
"                      .:..:.   .^!7??JJYYYYYYY5YY5YYYJJ?!~~~^::^:~!~^^~~~^~~^",
"                      :..:.   .:~!7?JJYYYY5555555555555YJ?!~~^:::.^~~^^~^~^~^^",
"                      :..:    :^~!??JJYYYYY555555555PPP55Y?!!~^:::.^!~^^^^^^^^:",
"                     .....   .^~!7??JJYYYY5555555PPPPPPP55Y?7!~^::.:~~~^^^^^^^^.",
"                     .....  .:~!!7?JJYYYY55555555PPPPPPPPP5YJ7!~:::::~~^^^^:^^^^",
"                     :...   .^~!7??JJYYYY55555P555PPPPPPPPPP5J7!^:::::~^^:::::^^:",
"                    ... .   :^~7??JJJYYYYYYY555555555PPPPP55YJ7!^::::.^^:::::.::^.",
"                    ..  .   :~!7777????JJJYYYY55555YYJJ?7777?JJ?7~^::.:::.::...:::",
"                    ..      :^~~~~~~~~~~~!7?JYYY5YYJ??777?JY5555Y?~^^:..:.......:^.",
"                   ..       :~!77?????77!!77?JJY55YYJJ?7!~~~~~!\?\?!~^^:..:.......::",
"                   ..       ^!77!!~~^^^^~!!!!7JY5P5YJ?!~!:..^!~^~!77~^^:..........^.",
"                  ...       ^!!~^::^^::^~~!?77?YPGP5P5?7??7?JYYYYYYJ?7~^:.........::",
"                  :.        ~!7!!!!77????????7J5GGPPPPP5YYY555PPPGP5YY?~^::........::",
"                 .:.        ~7777????JJJJJJ???Y5GBGGGGGGPPPPPPPGGGGGP5YJ!::........::",
"                  :..       ^7??JJJYYYYYYY???J5PGBGGGGGPPPPPPGGGBGGGGPPY?^::.......::",
"                 .:..       :7??JJYYYY5YY?7??Y5PGBBBGGGP555PPPGGGBGGGGP5J!~^    ....:",
"                  ::.       .!7??JJYYYYYJ7?J??JY5PPPPGGG55555PPPGGGGGGPPY!^.     ...:.",
"                  .::        :7???JJYYYJ?77?7!7?JJJ??J5PGGP55555PPPGGGGPY.    ..  ..^.",
"                   ::.        !????JJJJ???77777?J?J555GGGGGP5555PPPGGGPP7   ..::. .:^",
"                   :^.        ^7???????????????JYJYPGGGGGP5Y5555PPGGGGPY:  ...::. .::",
"                   .^..        ~???????7!~!!!!!!!777777?JJJY55PPPPGGPPY:   ...^: ..::",
"                    :...        ~????J???7~^^^~~~!!77?JJ5PBBGGPPPPPPPJ:    ...:. ..::",
"                    :...         :7????????7!!!77??JJYYPGBBBGGGPPP5Y!.    ...... ...:.",
"                    .....         .~7????????????JJJY5PPGGGGGGGP55YJ.     . ...  ...:.",
"                    ..  ..          .~7?????JJJYYY55PPPGGGGGGGP5YY5J.       ...    .::",
"                    .    ..           :!7???JJJY555PGGGGGGGGPYYY555J.       ...     .:.",
"                    .     .           .~!!7?JJJYYY55PPPPPP5YYY5PPP5Y^       .  .     ::",
"                   ..                 .~~!!77?JJJYYYYYYYYYY55PPPPP55!          .     .:.",
"                   .                  :~~!!!!777????JJYYY5PPPPPPPPP57...        .     .:",
"                  :.                  .~~!!!777777?JJY55PPPPPGGPPPP5~.:...             ..",
"                 ::                   .^~!!77777??JYY555PPPPGGGGPPPY:.:::...            :",
"                ..                    .^~!!77??JJJYY55PPPPPPGGGGGGP~.::::::.....         .",
"                                      .~~!!77?JYYY555PPPPPPGGGGGGP?:.::::::::::::..........",
"       ..                             .~77????J5555PPPPPPPGGGGGGGY~..:::::::::::::.....::::...",
" .........       .                 ...:!7?JJJJY5PPPPPPGGGGGGGGGGP7:..::::::::::::::........::::::...",
"....................             ......7JJJY555PGGGGGGGGPPGGGGPPY!:..:::::::::::::::.........:::::::",
"...................  .... .      ......7PP55PPGGGGGGGGPPPPGGGGGG5~..:::::::::::::::::.........::::::",
"..................  ...................~PPPPPPGGGGGGGGGGGGGGGGGG?:..::::::::::::::::::.........::::::",
"..................      ...............^5PPPGPPPGGGGGGGGGGGGGGGY~..:::::::::::::::::::.........:::::",
".............  ..........  ............:YPPPPGGPPPGGGGGGGGBGGG57^..:::::::::::::........::.......:::",
".............   ......................:.?PPPPGGGGGPYPGGGGGGGGGJ~:.:::::::::::.::::::::::::.......:::",
"  ............  ......................:.!PPPPGGGGP5Y5GGGGGGGG57^..:::::::::::::::::.:::::.......::::",
"   ...........  ........................^5PPGGG5J5P5P5GGGGGGPJ!:.:::::::::::::::::..::::........::::",
"    ...........  .......................:JGGGGGPJJYP55PGGGGG57^..:::::::::::::::.....:::.......:::::",
"    ...........  ........................7GGGGGGGG55PGGGGGGPJ!...::::::::::::::::....::........:::::",
"    ............  .......................~GGGGGGGGGGGGGGGGPY7^..:::::::::::::::::.::::.........:::::",
"    ............. .......................:5GGGGGGGGGGGGGPP5?!..:::::::::::::::::..:::........:::::::",
"     ............  .......................?BGGGGGGGGGGPPPPY7^..:::::::::::::::::..::.........:::::::",
"     .............  ......................^GGGGGGGGGPPPP5Y?~....:::::::::::..::::::.........:::::...",
"       ............  ......................JBGGGGGGPP555Y?!.....::::::::::....::::.........::::.....",
"       .............  .....................~GBGGGGPP55YY?7^ .....:::::::......:::.....:.:::::::::::.",
"          ........... ......................YBBGGGP5YYJJ7~....................::...:::::::::::::::..",
"           ..........  .....................7BBGGGP5JJ\?\?!:....................:...................."
    };

    int total = sizeof(art) / sizeof(art[0]);

    printf("%s", blink ? PURPLE : CYAN);

    for (int i = 0; i < total; i++) {

        /* Blink effect on the upper face area */
        if (blink && i >= 9 && i <= 12) {
            printf("%s\n", art[i]);
        } else {
            printf("%s\n", art[i]);
        }
    }

    printf("%s", RESET);
}

/* New Year countdown */
void countdown() {
    for (int i = 5; i >= 1; i--) {
        clearScreen();

        printf(YELLOW);
        printf("\n\n");
        printf("       ************************\n");
        printf("             COUNTDOWN!\n");
        printf("                  %d\n", i);
        printf("       ************************\n");
        printf(RESET);

        WAIT(800);
    }
}

int main() {

    int frame;

    countdown();

    for (frame = 0; frame < 20; frame++) {

        clearScreen();

        printf(YELLOW);
        printf("\n");
        printf("  =========================================\n");
        printf("            NEW YEAR CELEBRATION!\n");
        printf("  =========================================\n");
        printf(RESET);

        fireworks(frame);

        showFace(frame % 2);

        printf("\n");

        if (frame % 2 == 0) {
            printf(GREEN);
            printf("          HAPPY NEW YEAR 2027!\n");
        } else {
            printf(CYAN);
            printf("          WELCOME TO 2027!\n");
        }

        printf(RESET);

        printf(YELLOW);
        printf("\n       * DREAM BIG! SHINE BRIGHT! *\n");
        printf(RESET);

        WAIT(500);
    }

    clearScreen();

    printf(YELLOW);
    printf("\n\n");
    printf("  ****************************************\n");
    printf("  *                                      *\n");
    printf("  *         HAPPY NEW YEAR 2027!         *\n");
    printf("  *                                      *\n");
    printf("  *       MAY YOUR DREAMS COME TRUE!     *\n");
    printf("  *                                      *\n");
    printf("  ****************************************\n");
    printf(RESET);

    showFace(0);

    printf(GREEN);
    printf("\n       THANK YOU FOR WATCHING!\n");
    printf(RESET);

    return 0;
}