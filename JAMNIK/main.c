#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
/*****************************************************************************/
/* KONFIGURACJA TIMERA 3
 * CONFIGURATION OF TIMER 3
 *
 */
void timer(void){
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_BaseStruct.TIM_Prescaler = 840-1;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseStruct.TIM_Period = 10-1;
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3, &TIM_BaseStruct);
    TIM_Cmd(TIM3, ENABLE);
}
/*****************************************************************************/
/* "W£¥CZONE" SILNIKI - FUNKCJA SETBITS CZYLI USTAWIENIE PINÓW W STAN 1
 * W TYM TRYBIE KO£A SIÊ KRÊC¥ I MO¯EMY JECHAÆ NASZYM POJAZDEM
 * "SET UP" ENGINES - FUNCTION SETBITS SET UP PINS IN STATE 1
 * IN THIS MODE WHEELS ARE SPIN AROUND AND WE CAN DRIVE OUR MACHINE
 *
 * KONFIGURACJA: PC 6, 7, 8, 9
 * CONFIGURATION: PC 6, 7, 8, 9
 *
 */
void kanalSet(int kanal){
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    if(kanal == 1){
   		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
   		GPIO_SetBits(GPIOC, GPIO_Pin_6);
    }
    if(kanal == 2){
    	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    	GPIO_SetBits(GPIOC, GPIO_Pin_7);
    }
    if (kanal == 3){
    	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    	GPIO_SetBits(GPIOC, GPIO_Pin_8);
    }
    if(kanal == 4){
    	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    	GPIO_SetBits(GPIOC, GPIO_Pin_9);
    }
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}
/*****************************************************************************/
/* "WY£¥CZONE" SILNIKI - FUNKCJA RESETBITS CZYLI USTAWIENIE PINÓW W STAN 0
 * W TYM TRYBIE KO£A SIÊ NIE KRÊC¥ I POJAZD CZEKA NA KOMENDÊ
 * "SET DOWN" ENGINES - FUNCTION RESETBITS SET UP PINS IN STATE 0
 * IN THIS MODE WHEELS AREN'T SPIN AROUND AND MACHINE WAIT FOR COMMANDS
 *
 * KONFIGURACJA: PC 6, 7, 8, 9
 * CONFIGURATION: PC 6, 7, 8, 9
 *
 */
void kanalReset(int kanal){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	if(kanal == 1){
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	}
	if(kanal == 2){
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	}
	if(kanal == 3){
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	}
	if(kanal == 4){
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*****************************************************************************/
/* STEROWANIE POJAZDEM - KLASYCZNY WSAD:
 * W - DO PRZODU, S - DO TY£U, A - LEWO, D - PRAWO, DO TEGO ZATRZYMANIE POJAZDU - X
 * SIGNAL CONTROL - CLASSIC WSAD:
 * W - FORWARD, S - REVERSE, A - LEFT, D - RIGHT, STOP MACHINE - X
 *
 */
void jedziemy(char znak){
	if(znak == 'w'){
		kanalSet(2);
		kanalSet(4);
	}
	if(znak == 's'){
		kanalSet(1);
		kanalSet(3);
	}
	if(znak == 'a'){
		kanalSet(2);
		kanalSet(3);
	}
	if(znak == 'd'){
		kanalSet(1);
		kanalSet(4);
	}
	if(znak == 'x'){
		kanalReset(1);
		kanalReset(2);
		kanalReset(3);
		kanalReset(4);
	}
}
/*****************************************************************************/
/* USART - POD£¥CZENIE MODU£U BLUETOOTH
 * USART - CONNECTION OF BLUETOOTH MODULE
 *
 * 1 - BAUNDRATE ZGODNY Z DOKUMENTACJ¥ MODU£U HC-06
 * 1 - BAUNDRATE COMPATIBLE WITH DOCUMENTATION OF MODULE HC-06
 *
 * 2 - KONFIGURACJA PRZERWANIA DO USART
 * 2 - CONFIGURATION OF USART INTERRUPT
 *
 * POD£¥CZENIE (FORMAT: MODU£ BLUETOOTH - MIKROKONTROLER STM32):
 * TX - PC11
 * RX - PC10
 * GND - GND
 * VCC - 5V
 * STATE I EN - NIE POD£¥CZAÆ
 *
 * CONNECTION (FORMAT: BLUETOOTH MODULE - MICROCONTROLLER STM32):
 * TX - PC11
 * RX - PC10
 * GND - GND
 * VCC - 5V
 * STATE I EN - DON'T CONNECT
 *
 */
void usart(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600; //1
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);
	USART_Cmd(USART3, ENABLE);

	//2
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_EnableIRQ(USART3_IRQn);
}
/*****************************************************************************/
/* USART - PRZERWANIE, ODBIERANIE DANYCH PRZEZ MODU£
 * USART - INTERRUPT, RECEIVE DATA FROM MODULE
 *
 * 1 - ZMIENNA, DO KTÓREJ PRZYPISAWANE S¥ KOMENDY ODBIERANE PRZEZ MODU£ BLUETOOTH
 * 1 - VARIABLE FOR COMMANDS, RECEIVE FROM BLUETOOTH MODULE
 *
 * 2 - SPRAWDZENIE FLAGI ODBIERAJ¥CEJ I JEJ ZMIANA, OBOJÊTNIE CZY CO JEST W REJESTRZE CZY NIE,
 * 	   MA ON PRZYJ¥Æ WARTOSC DOSTARCZON¥ PRZEZ BLUETOOTH
 * 2 - CHECKING AND CHANGING RECEIVING FLAG, IT DOESN'T MATTER IF IN REGISTRY WE HAVE
 * 	   A VALUE OR NOT, IT MUST BE CHANGED WHEN WE RECEIVE A COMMAND FROM BLUETOOTH
 *
 * 3 - KIEDY ODBIERAMY KOMENDÊ MASZYNA SIÊ ZATRZYMUJE NA KILKA MIKROSEKUND I DOPIERO WTEDY
 * 	   JEDZIE WE W£ACIWYM KIERUNKU
 * 3 - WHEN WE RECEIVE COMMAND, MACHINE IS STOPPED FOR A FEW MS AND THEN DRIVE IN CORRECT DIRECTION
 *
 */
char znak; //1
void USART3_IRQHandler(void){
	//2
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET || USART_GetITStatus(USART3,USART_IT_RXNE)==RESET){
		znak = USART_ReceiveData(USART3);
		//3
		if(znak == 'w'){
			jedziemy('x');
			jedziemy('w');
		}
		if(znak == 's'){
			jedziemy('x');
			jedziemy('s');
		}
		if(znak == 'a'){
			jedziemy('x');
			jedziemy('a');
		}
		if(znak == 'd'){
			jedziemy('x');
			jedziemy('d');
		}
		if(znak == 'x'){
			jedziemy('x');
		}
	}
}
/*****************************************************************************/
/* FUNKCJA MAIN
 * MAIN FUNCTION
 *
 */
int main(void){
	SystemInit();
	timer();
	usart();
	while(1){}
}
