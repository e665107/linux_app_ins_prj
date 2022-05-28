#ifndef BSP_LED_H
#define BSP_LED_H




extern int led_fd;
void bsp_led_off(int fd);

void bsp_led_on(int fd);

void bsp_led_init(void);
void led_toggle(int fd);




#endif /* BSP_LED_H */
