# RFID-based-Attendance-System-Using-Atmega32
With the pandemic ongoing personal hygiene has become the top most priority. Marking attendance by physical touch can become noxious. This technology provides a safe way to mark attendance of students and teachers without actually coming in contact.
1. Scan the RFID card with the RFID sensor.
2. RFID sends a 12byte of data to the microcontroller which is unique for every card.
3. The microcontroller(ATMega32) used here compares the data with our dataset.
4. If it matches then it displays that number on the LCD screen and the student number with a message of "ATTENDANCE REGISTERED".
5. If it does not matches it displays "INVALID USER" and the buzzer is on for 3 seconds.
