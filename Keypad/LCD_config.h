#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define FOUR_BIT	0
#define EIGHT_bit	1
#define LCD_MODE					EIGHT_BIT

#define LCD_u8_DATA_PORT    DIO_u8_PORTA
#define LCD_u8_CTRL_PORT    DIO_u8_PORTB
#define LCD_u8_RS_PIN       DIO_u8_PIN0
#define LCD_u8_RW_PIN       DIO_u8_PIN1
#define LCD_u8_E_PIN        DIO_u8_PIN2

#define LCD_u8_FOUR_BIT_PORT	DIO_u8_PORTA
#define LCD_u8_DATA_PIN0			0
#define LCD_u8_DATA_PIN1			1
#define LCD_u8_DATA_PIN2			2
#define LCD_u8_DATA_PIN3			3
#define LCD_u8_CTRL_RS_PIN5			5
#define LCD_u8_CTRL_RW_PIN6			6
#define LCD_u8_CTRL_E_PIN7			7



#endif
