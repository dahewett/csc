#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "lcd_drv.h"


int s_length(char a[]) {

	for (int i = 0; a[i]; i++){
		
		return i;
	}
}

// Function reverse with char
char s_reverse[](char b[] ) {

	int l = s_length(b)-1;
	for (int i = 0; i < l; i++) {
		for (int j = l; i < j; j--) {

			int temp = b[i];
			b[i] = b[j];
			b[j] = temp;
			//print(b[j] + " ");
			//return b;
		}
	}
	return b;
}

//This is the Main function
int main (void) {
	
	char msg1[] = "Devin Hewett";
	char msg2[] = "UVic: Comp Sci";
	char msgS[] = "****************";
	char msgD[] = "................";
	
	char msg3[16];
	strcpy(msg3, msg1);
	s_reverse(msg3);
	
	char msg4[16];
	strcpy(msg4, msg2);
	s_reverse(msg4);

	lcd_init();
	lcd_blank(32);

	for( int i = 0; i <= 3; i++) {


		lcd_xy(0,0);
		lcd_puts(msg1);
		lcd_xy(0,1);
		lcd_puts(msg2);
		_delay_ms(1000);
	
		lcd_blank(32);
		lcd_xy(1,0);
		lcd_puts(msg2);
		lcd_xy(1,1);
		lcd_puts(msg3);
		_delay_ms(1000);

		lcd_blank(32);
		lcd_xy(0,0);
		lcd_puts(msg3);
		lcd_xy(0,1);
		lcd_puts(msg4);
		_delay_ms(1000);

		lcd_blank(32);
		lcd_xy(1,0);
		lcd_puts(msg4);
		lcd_xy(1,1);
		lcd_puts(msg1);
		_delay_ms(2000);
		lcd_blank(32);
		
	}

	for (;;) {

		lcd_blank(32);
		lcd_xy(0,0);
		lcd_puts(msgS);
		lcd_xy(0,1);
		lcd_puts(msgS);
		_delay_ms(1000);

		lcd_blank(32);
		lcd_xy(0,0);
		lcd_puts(msgD);
		lcd_xy(0,1);
		lcd_puts(msgD);
		_delay_ms(1000);

	}

}

