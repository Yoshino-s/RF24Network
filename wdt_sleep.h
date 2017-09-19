namespace sleep {
	//
	// Sleep declarations
	//

	typedef enum { wdt_16ms = 0, wdt_32ms, wdt_64ms, wdt_128ms, wdt_250ms, wdt_500ms, wdt_1s, wdt_2s, wdt_4s, wdt_8s } wdt_prescalar_e;

	void setup_watchdog(uint8_t prescalar);
	void do_sleep(void);

	const short sleep_cycles_per_transmission = 4;
	volatile short sleep_cycles_remaining = sleep_cycles_per_transmission;

	//
	// Sleep helpers
	//

	// 0=16ms, 1=32ms,2=64ms,3=125ms,4=250ms,5=500ms
	// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec

	void setup_watchdog(uint8_t prescalar)
	{
		prescalar = min(9, prescalar);
		uint8_t wdtcsr = prescalar & 7;
		if (prescalar & 8)
			wdtcsr |= _BV(WDP3);

		MCUSR &= ~_BV(WDRF);
		WDTCSR = _BV(WDCE) | _BV(WDE);
		WDTCSR = _BV(WDCE) | wdtcsr | _BV(WDIE);
	}

	ISR(WDT_vect)
	{
		--sleep_cycles_remaining;
	}

	void do_sleep(void)
	{
		set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
		sleep_enable();

		sleep_mode();                        // System sleeps here

		sleep_disable();                     // System continues execution here when watchdog timed out
	}
}