

from RPi import GPIO
from hx711 import HX711  # import the class HX711

try:
    GPIO.setmode(GPIO.BCM)  # set GPIO pin mode to BCM numbering
    # Create an object hx which represents your real hx711 chip
    # Required input parameters are only 'dout_pin' and 'pd_sck_pin'
    hx = HX711(dout_pin=5, pd_sck_pin=6)
    # measure tare and save the value as offset for current channel
    # and gain selected. That means channel A and gain 128
    err = hx.zero()
    # check if successful
    if err:
        raise ValueError('Tare is unsuccessful.')

    reading = hx.get_raw_data_mean()
    if reading:  # always check if you get correct value or only False
        # now the value is close to 0
        print('Data subtracted by offset but still not converted to units:',
              reading)
    else:
        print('invalid data', reading)

    # In order to calculate the conversion ratio to some units, in my case I want grams,
    # you must have known weight.
    input('Put known weight on the scale and then press Enter')
    reading = hx.get_data_mean()
    if reading:
        print('Mean value from HX711 subtracted by offset:', reading)
        known_weight_grams = input(
            'Write how many grams it was and press Enter: ')
        try:
            value = float(known_weight_grams)
            print(value, 'grams')
        except ValueError:
            print('Expected integer or float and I have got:',
                  known_weight_grams)

        # set scale ratio for particular channel and gain which is
        # used to calculate the conversion to units. Required argument is only
        # scale ratio. Without arguments 'channel' and 'gain_A' it sets
        # the ratio for current channel and gain.
        ratio = reading / value  # calculate the ratio for channel A and gain 128
        hx.set_scale_ratio(ratio)  # set ratio for current channel
        print('Ratio is set.')
    else:
        raise ValueError('Cannot calculate mean value. Try debug mode. Variable reading:', reading)

    # Read data several times and return mean value
    # subtracted by offset and converted by scale ratio to
    # desired units. In my case in grams.
    print("Now, I will read data in infinite loop. To exit press 'CTRL + C'")
    input('Press Enter to begin reading')
    print('Current weight on the scale in grams is: ')
    while True:
        print(hx.get_weight_mean(20), 'g')

except (KeyboardInterrupt, SystemExit):
    print('Bye :)')

finally:
    GPIO.cleanup()


from RPi import GPIO

GPIO.setmode(GPIO.BCM)  # set GPIO pin mode to BCM numbering

sck_pin = 6
dout_pin = 5
channel_select = 'A'
channel_A_gain = 128

# init GPIO
GPIO.setup(sck_pin, GPIO.OUT)  # sck_pin is output only
GPIO.setup(dout_pin, GPIO.IN)  # dout_pin is input only

# prepare for read
GPIO.output(sck_pin, False)  # start by setting the pd_sck to 0
# check if dout pin is ready by confirming zero
for _ in range(20):
    ready = (GPIO.input(dout_pin) == 0)
    if ready:
        break

if not ready:
    print('GPIO pin not ready, quitting..')
    quit()

# for each bit in 24 bits, perform ADC read
raw_read = 0
for _ in range(24):
    # pulse sck high to request each bit
    GPIO.output(sck_pin, True)
    GPIO.output(sck_pin, False)
    # left shift by one bit then bitwise OR with the new bit
    raw_read = (raw_read << 1) | GPIO.input(dout_pin)

# set channel after read
# get number of pulses based on channel configuration
num_pulses = 2  # default 2 for channel B
if channel_select == 'A' and channel_A_gain == 128:
    num_pulses = 1
elif channel_select == 'A' and channel_A_gain == 64:
    num_pulses = 3
# pulse num_pulses
for _ in range(num_pulses):
    GPIO.output(sck_pin, True)
    GPIO.output(sck_pin, False)

print(f'Raw read (2s complement): {raw_read}')
if raw_read in [0x000000, 0x800000, 0x7FFFFF, 0xFFFFFF]:
    # invalid if value is exactly zero, exactly the min or max value, or a value of all 1's
    print(f'Invalid raw value detected')
# calculate int from 2's complement
# check if the sign bit is 1, indicating a negative number
if (raw_read & 0x800000):
    # convert from 2's complement to negative int
    signed_value = -((raw_read ^ 0xffffff) + 1)
else:  # else do not do anything the value is positive number
    signed_value = raw_read
print(f'Raw read (signed integer): {signed_value}')

GPIO.cleanup()