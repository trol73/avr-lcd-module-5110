
name = 'ic-tester-display'

src = [
   'src/lib/glcd/*.c', 'src/lib/glcd/controllers/*.c', 'src/lib/glcd/devices/*.c',
   'src/lib/uart/*.c',
   'src/*.c',
   'src/asm/*.s'
]

mcu = 'atmega8'

frequency = 16*1000000

port = ''

baudrate = 1200

programmer = 'arduino'

defines = [
   'GLCD_DEVICE_AVR8', 'GLCD_CONTROLLER_PCD8544', 'GLCD_USE_AVR_DELAY', '__DELAY_BACKWARD_COMPATIBLE__', 
   'UART_RX_BUFFER_SIZE=256',
   'UART_TX_BUFFER_SIZE=64',
	'F_CPU=16000000', 'DEBUG=0'
]

compiler_options = ['-g2']

linker_options = []


configurations = {
}


for c in range(10, 100, 2):
	sc = str(c)
	cfg = {'name': 'ic-tester-c' + sc, 'defines': ['DISPLAY_CONTRAST=' + sc]}
	configurations['contrast-' + sc] = cfg
