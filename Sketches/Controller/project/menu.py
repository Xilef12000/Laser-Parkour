class menu:
    lcd = 0
    structure = {}
    directory = structure
    index = 0
    def __init__ (self, lcd):
        self.lcd = lcd
        self.lcd.custom_char(0, bytearray([0x00, 0x01, 0x01, 0x05, 0x09, 0x1F, 0x08, 0x04]))
    
    def add_entry(self, state, *args):
        temp = self.structure
        for arg in args[:-1]:
            if arg not in temp:
                temp[arg] = {}
            temp = temp[arg]
        temp[args[-1]] = state
        #print(self.structure)
        
    def rot_cw(self):
        if self.index < len(list(self.directory)) - 1:
            self.index += 1
            self.show()
        
    def rot_ccw(self):
        if self.index > 0:
            self.index -= 1
            self.show()
    
    def rot_go(self):
        if isinstance(self.directory[list(self.directory)[self.index]], dict):
            self.directory = self.directory[list(self.directory)[self.index]]
            self.index = 0
            self.show()
        else:
            self.directory = self.structure
            self.index = 0
            self.show()
        
    def show(self):
        self.lcd.clear()
        self.lcd.putstr(list(self.directory)[self.index])
        self.lcd.move_to(0, 1)
        if not isinstance(self.directory[list(self.directory)[self.index]], dict):
            self.lcd.putstr(self.directory[list(self.directory)[self.index]])
        else:
            self.lcd.putchar(chr(0))
