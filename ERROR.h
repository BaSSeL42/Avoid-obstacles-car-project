#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED

#define COMMON_ERROR_BASE                          (0)
#define RETURN_SUCCESS                             (COMMON_ERROR_BASE)
#define RETURN_NULL_POINTER_PASSED                 (COMMON_ERROR_BASE-1)
#define RETURN_INVALID_PARAMETERS                  (COMMON_ERROR_BASE-2)
#define RETURN_MODULE_NOT_INTIALIZED               (COMMON_ERROR_BASE-3)
#define RETURN_INVALID_CRC                         (COMMON_ERROR_BASE-4)
#define RETURN_INVALID_CHECKSUM                    (COMMON_ERROR_BASE-5)
#define RETURN_INVALID_CONFIGURATION               (COMMON_ERROR_BASE-6)
#define RETURN_MODULE_ALREADY_INTIALIZED           (COMMON_ERROR_BASE-7)
#define RETURN_NOT_SUPPORTED_FEATURE               (COMMON_ERROR_BASE-8)
#define RETURN_MODULE_IS_BUSY                      (COMMON_ERROR_BASE-9)
#define RETURN_DATA_SENT_FAILURE                   (COMMON_ERROR_BASE-10)
#define RETURN_NO_ENOUGH_ROOM                      (COMMON_ERROR_BASE-11)
#define RETURN_BAUD_RATE_NOTMATCHED                (COMMON_ERROR_BASE-12)
#define RETURN_OPERATION_TIMEOUT                   (COMMON_ERROR_BASE-13)
#define RETURN_INVALID_STATE                       (COMMON_ERROR_BASE-14)
#define RETURN_INVALID_PRESCALAR_VALUE			   (COMMON_ERROR_BASE-15)



/*MOVE TO THIS EACH MODULE .h FILE*/


#define GPIO_ERROR_BASE                          (-100)
#define ADC_ERROR_BASE                           (-200)
#define TIMER_ERROR_BASE                         (-300)
#define UART_ERROR_BASE                          (-400)
#define SPI_ERROR_BASE                           (-500)
#define I2C_ERROR_BASE                           (-600)
#define LCD_ERROR_BASE                           (-700)
#define KEYPAD_ERROR_BASE                        (-800)
#define PUSH_BUTTON_ERROR_BASE                   (-900)
#define TEMP_SENSOR_ERROR_BASE                   (-1000)
#define STEPPER_MOTOR_ERROR_BASE                 (-1100)
#define DC_MOTOR_ERROR_BASE                      (-1200)
#define SERVO_MOTOR_ERROR_BASE                   (-1300)
#define RELAY_ERROR_BASE                         (-1400)
#define SEVENT_SEGEMENT_ERROR_BASE               (-1500)




#endif // ERROR_H_INCLUDED
