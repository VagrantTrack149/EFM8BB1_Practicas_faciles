//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                // SFR declarations

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
//void SiLabs_Startup (void)
//{
  // Disable the watchdog here
//}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
// Note: the software watchdog timer is not disabled by default in this
// example, so a long-running program will reset periodically unless
// the timer is disabled or your program periodically writes to it.
//
// Review the "Watchdog Timer" section under the part family's datasheet
// for details. To find the datasheet, select your part in the
// Simplicity Launcher and click on "Data Sheet".
//-----------------------------------------------------------------------------
int main (void)
{
  while (1) {
    #pragma asm
       //Desactivar el watchdog timer
        //OBLIGATORIO
        MOV WDTCN, #0DEH;
        MOV WDTCN, #0ADH;
        MOV R0, #0FFH;
        ESPERA1:
          DJNZ R0, ESPERA1;
        //INICIALIZAR Y CONFIGURAR P1
         ORL P1MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P1MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P1SKIP, #0FFH; //TODAS LAS TERMINALES SON IGNORADAS POR EL CROSSBAR
         ORL P0MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P0MDOUT, #00H; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P0SKIP, #0FFH;
         ORL XBR2, #040H;

         SALIDA:
         // Verificar si el botón P0.2 está presionado
         JB P0.2, BUTTON_PRESSED;
         LJMP LED_OFF;          // Salta a la etiqueta LED_OFF si el botón no está presionado

         BUTTON_PRESSED:          // Si el botón está presionado
           //MOV P1, #00H;
           SETB P1.4;              // Apaga el LED en P1.4
           LJMP SALIDA;

         LED_OFF:
           //MOV P1, #0FFH;
           CLR P1.4;              // Enciende el LED en P1.4


           LJMP SALIDA;
         #pragma endasm

  }                             // Spin forever
}
