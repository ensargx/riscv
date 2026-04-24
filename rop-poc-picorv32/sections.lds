MEMORY {
	mem : ORIGIN = 0x00000000, LENGTH = 0x00020000
}

SECTIONS {
	.text : {
		. = 0x000000;
		*(.text*)
		*(.rodata*)
		*(.data*)
		. = ALIGN(4);
	} > mem
}
