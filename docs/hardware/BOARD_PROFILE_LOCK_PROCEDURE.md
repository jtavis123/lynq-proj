# Board Profile Lock Procedure

The Hub LCD, touch, backlight and Node Port ABC GPIO assignments shall not be
guessed.

## Evidence sources

1. Exact manufacturer example project for the received revision
2. Manufacturer schematic/pin definition
3. PCB revision markings
4. Bench verification on the physical unit

## Lock steps

- Record every signal name, GPIO, voltage domain and active level.
- Verify display color order and orientation.
- Verify touch axes, rotation and interrupt behavior.
- Verify backlight polarity and safe duty range.
- Verify Port A, B and C signal routing.
- Exercise each output through a current-limited test.
- Capture serial logs and photographs.
- Publish one versioned board-profile file.
- Require engineering review for future changes.
