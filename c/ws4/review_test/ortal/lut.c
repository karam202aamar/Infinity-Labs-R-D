#include <stdio.h>
#include <stdlib.h>

#define ESC 0x1B
#define ASCII_SIZE 256

typedef void (*lut)();

static void PrintPressedKey();
static void APress();
static void TPress();
static void ESCPress();
static void PrintNotThatKey();

int main()
{
    system("stty -icanon -echo");

    PrintPressedKey();

 
    system("stty icanon echo");

  return 0;
}

static void PrintPressedKey()
{
    char pressed_key = '\0';
    lut all_keys[ASCII_SIZE];
    int i = 0;

    for (i = 0; i < ASCII_SIZE; ++i)
    {
        all_keys[i] = PrintNotThatKey;
    }
    
    all_keys['a'] = APress;
    all_keys['A'] = APress;
    all_keys['t'] = TPress;
    all_keys['T'] = TPress;
    all_keys[ESC] = ESCPress;

    printf("Press any key (ESC to exit):\n");
        
    while (pressed_key != ESC)
  {
        scanf("%c", &pressed_key);
        all_keys[pressed_key](); 
      }
  

    return;
}


static void APress()
{
    printf("A-pressed\n");
    return;
}

static void TPress()
{
    printf("T-pressed\n");
    return;
}

static void ESCPress()
{
    printf("ESC-pressed, goodbye!\n");
    return;
}

static void PrintNotThatKey()
{
    printf("Not that key!\n");
    return;
}
