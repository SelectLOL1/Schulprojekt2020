import matplotlib.pyplot as plt
import numpy as np
anzahlperioden = 1

batterymah = 3450  # Theoretical max capacity at voltage 2.5V
batterymahat34v = 3000  # Actual Capacity by going down to 3.4V
batterymah = np.sort(np.arange(0, batterymah, 1))



batterymincapacity = 450  # Capacity left at batteryminvolt
batterymaxvolt = 4.2
batteryminvolt = 3.4

POINTER = 0
np.set_printoptions(precision=2)
np.set_printoptions(suppress=False)
values = np.zeros(372 * anzahlperioden, dtype=float)

for x in range(anzahlperioden):
    for i in range(120):
        values[POINTER] = 0.08
        POINTER = POINTER + 1

    for i in range(2):
        values[POINTER] = 80
        POINTER = POINTER + 1

    for i in range(120):
        values[POINTER] = 0.08
        POINTER = POINTER + 1

    for i in range(2):
        values[POINTER] = 80
        POINTER = POINTER + 1

    for i in range(120):
        values[POINTER] = 0.08
        POINTER = POINTER + 1

    for i in range(2):
        values[POINTER] = 80
        POINTER = POINTER + 1

    for i in range(6):
        values[POINTER] = 72
        POINTER = POINTER + 1


summer = np.cumsum(values)
rmscurrentdraw = np.sqrt(np.mean(np.square(values))) ##Per 360s/6min
rmscurrentdrawmah = rmscurrentdraw * 10

print(values)
print(rmscurrentdraw)
print(summer)

figure, axes = plt.subplots(nrows=2, ncols=2)
axes[0, 0].plot(values, color='red')
axes[0, 0].set_title('Periodic Current Draw')
axes[0, 0].set_xlabel('Time in s')
axes[0, 0].set_ylabel('Current in mA')

axes[0, 1].plot(summer, color='darkorange')
axes[0, 1].set_title('Cummalative Sum of currents')
axes[0, 1].set_xlabel('Time in s')
axes[0, 1].set_ylabel('Currentdraw in mAs')

axes[1, 0].plot(batterymah/rmscurrentdrawmah, batterymah, color='green')
axes[1, 0].set_title('Estimated battery life with given battery')
axes[1, 0].set_xlabel('Time in h')
axes[1, 0].set_ylabel('Capacity drawn in mAh')
axes[1, 0].axhline(batterymahat34v)
axes[1, 0].axvline(batterymahat34v/rmscurrentdrawmah)
axes[1, 0].plot(batterymahat34v/rmscurrentdrawmah, batterymahat34v, 'ro', color='red')
axes[1, 0].text(batterymahat34v/rmscurrentdrawmah-3, batterymahat34v-250, f'CurrentdrawRMS estimated= {rmscurrentdrawmah:.2f}mAh',
                fontsize=13, horizontalalignment='right')

axes[1, 0].annotate(f'{batterymahat34v/rmscurrentdrawmah:.1f} Hours estimated @ min. Voltage {batteryminvolt}V ',
                    (batterymahat34v/rmscurrentdrawmah, batterymahat34v+50), fontsize=13, horizontalalignment='right')


# axes[1, 1].plot(summer)
# axes[1, 1].set_title('Cummalative Sum')
# axes[1, 1].set_xlabel('Time in s')
# axes[1, 1].set_ylabel('Current in mAs')


figure.suptitle('Theoretical Current Consumption Project Air Quality Monitor', fontsize=25)
plt.subplots_adjust(top=0.88, bottom=0.085, left=0.11, right=0.9, hspace=0.25, wspace=0.175)
plt.show()
plt.close()
