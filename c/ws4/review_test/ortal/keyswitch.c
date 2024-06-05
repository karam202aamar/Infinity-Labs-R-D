#include <stdio.h>
#include <stdlib.h>

#define ESC 0x1B

static void PrintPressedKey();

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
    printf("Press one of the magic keys (ESC to exit):\n");
    
    while (pressed_key != ESC)
  {
      scanf("%c", &pressed_key);

      if (pressed_key == 'A'|| pressed_key == 'a')
      {
          printf("A-pressed\n");
      }
      
      if (pressed_key == 'T' || pressed_key == 't')
      {
          printf("T-pressed\n");
      }
  }

    return;
}
