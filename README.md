# SAMD20_MCU-Specific_I2C_SL
Porting the I2C Slave code from AT11628 from the xplained board to the user-board, trying to circumvent some xplained confusion with CTRLA.SPEED and CTRLA.SCLSM 

## Initial Commit
Imported defines from SAMD20 xplained board specific to the MCU -> user_board.h (src->ASF->common2->boards->user_board)
Imported inits from SAMD20 xplained board specific to the MCU -> init.c
Added GPIO via ASF wizard
Added test code: SW0 = LED0 state
Validated.  Base SAMD20J18 MCU code with GPIO initialized.

## Branch - feature i2c slave
Added i2c_clock_init function.  Compiles and working.
