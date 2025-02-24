from machine import Pin, PWM
class rgb_led:
    pwm_r = 0
    pwm_g = 0
    pwm_b = 0
    def __init__ (self, pin_r, pin_g, pin_b, freq):
        self.pwm_r = PWM(Pin(pin_r))
        self.pwm_g = PWM(Pin(pin_g))
        self.pwm_b = PWM(Pin(pin_b))
        self.pwm_r.freq(freq)
        self.pwm_g.freq(freq)
        self.pwm_b.freq(freq)
        self.pwm_r.duty_u16(0)
        self.pwm_g.duty_u16(0)
        self.pwm_b.duty_u16(0)
    
    def rgb(self, v_r, v_g, v_b):
        self.pwm_r.duty_u16(v_r * 257);
        self.pwm_g.duty_u16(v_g * 257);
        self.pwm_b.duty_u16(v_b * 257);
    def single(self, c, v):
        if c == 'r':
            self.pwm_r.duty_u16(v * 257);
        elif c == 'g':
            self.pwm_g.duty_u16(v * 257);
        elif c == 'b':
            self.pwm_b.duty_u16(v * 257);
