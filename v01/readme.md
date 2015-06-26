#15.06.26 09:46
- v01 is prototype using atmega328-16pu chips for both tx/rx on personal dev board. communicationis based on uart and directly connecting the uart communication to the RF433 tx/rx module. Unlike the tutorial that I referred to, my code doesn't implement addressing since there will be only one rx.
- for each tx/rx, a blinking led is added to check if chip is running properly and transmission, reception is functioning.
- realized that atmega328-16pu chips are too overspec for this implementation. Should try a smaller, cheaper atmega chip.
- a video of demonstration should be uploaded soon.

---
#15.06.27
- demo video: https://youtu.be/1v-W5BbOYUU
