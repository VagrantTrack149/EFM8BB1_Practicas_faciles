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
    #pragma asm
       //Desactivar el watchdog timer
        //OBLIGATORIO
        MOV WDTCN, #0DEH;
        MOV WDTCN, #0ADH;
        MOV R0, #0FFH;
        ESPERA1:
          DJNZ R0, ESPERA1;
        //INICIALIZAR Y CONFIGURAR P1 Y P0
         ORL P1MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P1MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P1SKIP, #0FFH; //TODAS LAS TERMINALES SON IGNORADAS POR EL CROSSBAR
         ORL P0MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P0MDOUT, #0F0H; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P0SKIP, #0FFH;
         //ORL P2MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P2MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         //ORL P2SKIP, #0FFH;
         ORL XBR2, #040H;

        LCALL INILCD;
        MOV P1, #0FH;
        TECLADO:
          MOV R1,#0FFH;
          LECTURA:
            CLR P1.7;
            JNB P1.3, BOTON11;
            JNB P1.2, BOTON12;
            JNB P1.1, BOTON13;
            JNB P1.0, BOTON14;
            SETB P1.7;
            CLR P1.6;
            JNB P1.3, BOTON21;
            JNB P1.2, BOTON22;
            JNB P1.1, BOTON23;
            JNB P1.0, BOTON24;
            SETB P1.6;
            CLR P1.5;
            JNB P1.3, BOTON31;
            JNB P1.2, BOTON32;
            JNB P1.1, BOTON33;
            JNB P1.0, BOTON34;
            SETB P1.5;
            CLR P1.4;
            JNB P1.3, BOTON41;
            JNB P1.2, BOTON42;
            JNB P1.1, BOTON43;
            JNB P1.0, BOTON44;
            SETB P1.4;
            LJMP LECTURA;
        BOTON11:
          MOV R0,#031H;
          LJMP DISPLAY;
        BOTON12:
          MOV R0,#032H;
          LJMP DISPLAY;
        BOTON13:
          MOV R0,#033H;
          LJMP DISPLAY;
        BOTON14:
          MOV R0,#041H;
          LJMP DISPLAY;
        BOTON21:
          MOV R0,#034H;
          LJMP DISPLAY;
        BOTON22:
          MOV R0,#035H;
          LJMP DISPLAY;
        BOTON23:
          MOV R0,#036H;
          LJMP DISPLAY;
        BOTON24:
          MOV R0,#042H;
          LJMP DISPLAY;
        BOTON31:
          MOV R0,#037H;
          LJMP DISPLAY;
        BOTON32:
          MOV R0,#038H;
          LJMP DISPLAY;
        BOTON33:
          MOV R0,#039H;
          LJMP DISPLAY;
        BOTON34:
          MOV R0,#043H;
          LJMP DISPLAY;
        BOTON41:
          MOV R0,#02AH;
          LJMP DISPLAY;
        BOTON42:
          MOV R0,#030H;
          LJMP DISPLAY;
        BOTON43:
          MOV R0,#023H;
          LJMP DISPLAY;
        BOTON44:
          MOV R0,#044H;
          LJMP DISPLAY;
        DISPLAY:
          LCALL LCDDAT2N;
          LCALL DELAY250ms;
          LJMP TECLADO;

        INILCD:
          LCALL DELAY250ms;
          MOV R0, #030H;
          LCALL LCDINS1N;
          LCALL DELAY250ms;
          MOV R0, #030H;
          LCALL LCDINS1N;
          LCALL DELAY1ms;
          MOV R0, #030H;
          LCALL LCDINS1N;
          LCALL DELAY1ms;
          MOV R0, #020H;
          LCALL LCDINS1N;
          LCALL DELAY1ms;
          MOV R0, #028H;
          LCALL LCDINS2N;
          LCALL DELAY1ms;
          MOV R0, #08H;
          LCALL LCDINS2N;
          LCALL DELAY1ms;
          MOV R0, #01H;
          LCALL LCDINS2N;
          LCALL DELAY1ms;
          MOV R0, #06H;
          LCALL LCDINS2N;
          LCALL DELAY1ms;
          MOV R0,#0EH;
          LCALL LCDINS2N;
          LCALL DELAY1ms;
          RET;

        LCDDAT1N:
          CLR P2.0;
          LCALL DELAY1ms;
          SETB P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          LCALL DELAY1ms;
          LCALL NibbleAlto;
          LCALL DELAY1ms;
          CLR P2.0;
          LCALL DELAY1ms;
          RET;

          LCDDAT2N:
          CLR P2.0;
          LCALL DELAY1ms;
          SETB P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          LCALL DELAY1ms;
          LCALL NibbleAlto;
          LCALL DELAY1ms;
          CLR P2.0;
          LCALL DELAY1ms;
          MOV A,R0;
          SWAP A;
          MOV R0, A;
          CLR P2.0;
          LCALL DELAY1ms;
          SETB P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          LCALL DELAY1ms;
          LCALL NibbleAlto;
          LCALL DELAY1ms;
          CLR P2.0;
          LCALL DELAY1ms;
          MOV A,R0;
          SWAP A;
          MOV R0, A;
          RET;

        LCDINS1N:
          CLR P2.0;
          LCALL DELAY1ms;
          CLR P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          MOV   P2,#01H;
          LCALL DELAY1ms;
          LCALL NibbleAlto;
          LCALL DELAY1ms;
          MOV   P2,#00H;
          CLR P2.0;
          LCALL DELAY1ms;
          RET;

        LCDINS2N:
        CLR P2.0;
        LCALL DELAY1ms;
        CLR P2.1;
        LCALL DELAY1ms;
        SETB P2.0;
        MOV   P2,#01H;
        LCALL DELAY1ms;
        LCALL NibbleAlto;
        LCALL DELAY1ms;
        MOV   P2,#00H;
        CLR P2.0;
        LCALL DELAY1ms;
        MOV A,R0;
        SWAP A;
        MOV R0, A;

        SETB P2.0;
        MOV   P2,#01H;
        LCALL DELAY1ms;
        LCALL NibbleAlto;
        LCALL DELAY1ms;
        MOV   P2,#00H;
        CLR P2.0;
        LCALL DELAY1ms;
        MOV A,R0;
        SWAP A;
        MOV R0, A;
        RET;

        NibbleAlto:
          MOV A,#0F0H;
          ANL A,R0;
          MOV R1,A;
          MOV A,#0FH;
          ANL A,P0;
          ORL A,R1;
          MOV P0,A;
          RET;

        DELAY1ms:
           MOV R6, #03H;
           AQUI2: MOV R7, #0FFH;
             AQUI1:
               NOP;
               DJNZ R7, AQUI1;
               NOP;
               DJNZ R6, AQUI2;
               RET;

        DELAY250ms:
           MOV R5, #0FAH;
           AQUI3:
                LCALL DELAY1ms;
                DJNZ R5, AQUI3;
                RET;
         DELAY1s:
           MOV R4, #04H;  // Cargar R5 con 4 en decimal (250 * 4ms = 1s)
           AQUI4:
                LCALL DELAY250ms;
                DJNZ R4, AQUI4;
                RET;
         //CAD1:DB 044H,045H,04DH;
         //CAD2:DB 044H,045H,04DH;
         #pragma endasm

}
