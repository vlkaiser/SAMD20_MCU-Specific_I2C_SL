/* Add MCU-Specific Definitions in user_baord.h */


#include <asf.h>


/* Prototypes */
void i2c_clock_init(void);

static void pin_set_peripheral_function(uint32_t pinmux);
void i2c_pin_init(void);


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

/******************************************************************************************************
 * @fn					- pin_set_peripheral_function
 * @brief				- Initialize i2c pins to SERCOM-Alternate peripheral function (D)
 * @param[in]			- pinmux (MCU driver files for pin definitions)
 * @return				- void
 *
 * @note				- Assign I/O lines PA08 and PA09 to the SERCOM peripheral function.
 *						- Will switch the GPIO functionality of an I/O pin to peripheral
 *							 functionality and assigns the given peripheral function to the pin.
 ******************************************************************************************************/
static void pin_set_peripheral_function(uint32_t pinmux)
{
	uint8_t port = (uint8_t)((pinmux >> 16)/32);
	PORT->Group[port].PINCFG[((pinmux >> 16) - (port*32))].bit.PMUXEN = 1;
	PORT->Group[port].PMUX[((pinmux >> 16) - (port*32))/2].reg &= ~(0xF << (4 * ((pinmux >> 16) & 0x01u)));
	PORT->Group[port].PMUX[((pinmux >> 16) - (port*32))/2].reg |= (uint8_t)((pinmux &0x0000FFFF) << (4 * ((pinmux >> 16) & 0x01u)));

}

/******************************************************************************************************
 * @fn					- i2c_pin_init
 * @brief				- Initialize i2c pins to SERCOM-Alternate peripheral function (D)
 * @param[in]			- void
 * @return				- void
 *
 * @note				- PA08 = SDA, PA09 = SCL
 ******************************************************************************************************/
void i2c_pin_init()
{
	pin_set_peripheral_function(PINMUX_PA08D_SERCOM2_PAD0);	
	pin_set_peripheral_function(PINMUX_PA09D_SERCOM2_PAD1);
}

int main (void)
{
	system_init();
	i2c_clock_init();
	i2c_pin_init();


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
