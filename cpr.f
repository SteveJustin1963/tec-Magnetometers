\: charge-capacitor ( -- )
  1 \> \h
  millis \h !  \ store the start time in the heap
  512 < A0 ? until
  0 \> \h
  \h @ millis - \h !  \ update the elapsed time in the heap
;

\: discharge-capacitor ( -- )
  0 \> \h
  millis \h !  \ store the start time in the heap
  512 > A0 ? until
  \h @ millis - \h !  \ update the elapsed time in the heap
;

\: loop ( -- )
  charge-capacitor
  \h @ .  \ print the elapsed time for charging
  1000 ms sleep
  discharge-capacitor
  \h @ .  \ print the elapsed time for discharging
  1000 ms sleep
  loop
;
