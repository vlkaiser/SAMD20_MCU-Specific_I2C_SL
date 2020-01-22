/* Add MCU-Specific Definitions in user_baord.h */


#include <asf.h>


/* Prototypes */
void i2c_clock_init(void);


/******************************************************************************************************
 * @fn					- i2c_clock_init
 * @brief				- Configure peripheral bus clock (APB) and generic clock for i2c SERCOM module
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void i2c_clock_init()
{
	struct system_gclk_chan_config gclk_chan_conf;		//struct to configure generic clock for SERCOM
	uint32_t gclk_index = SERCOM2_GCLK_ID_CORE;

	system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBC, PM_APBCMASK_SERCOM2);	//Turn on module in Power Manager - peripheral bus C
	system_gclk_chan_get_config_defaults((&gclk_chan_conf));				//Turn on generic clock for i2c: Default is generator0
	system_gclk_chan_set_config(gclk_index, &gclk_chan_conf);				//Write defaults to SERCOM2
	system_gclk_chan_enable(gclk_index);									//Enable
}


int main (void)
{
	system_init();
	i2c_clock_init();



	while (1) {
		/* Is button pressed? */
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
			} else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}

}
