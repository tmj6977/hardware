SECTIONS {
	.text 0 : {*(.text)}
	.rodata : {*(.rodata)}
	.data 0x30000000 : AT(0X800) 
	{
	 	data_load_adrr = LOADADDR(.data);
		data_start = . ;
		*(.data)
		data_end = . ;
	}
	bss_start = .;
	.bss : { *(.bss) *(.COMMON)}
	bss_end = .;
}