The original code did not support my LD293D board.

Using the AF library we have overcome some problems with the cheap Aliexpress shield. It was similar to the shield Kevin identified in the video that was not-compatible due to missing headers. Luckily I had holes to add headers.


We use #ifdef FUNDUMOTO_SHIELD to define a real beep function (with a buzzer) and provide a no-op (empty) version if the buzzer is absent. This keeps the code simpler.
Distance is now local to loop() rather than a global variable, clarifying the code flow.
For mutually exclusive conditions, else if used, it makes code clearer that only one block will run.
The beep duration is calculated from the distance. If the distance is 0 or negative, we force it to 1 to avoid division by zero or a very large beep.
ping() is renamed to measureDistance() for no other reason than personal preference.

Kevins original code can be found here : https://github.com/kevinmcaleer/follow_me2
Kevins youtube series on bringing SMARS to life is here : https://www.youtube.com/playlist?list=PLU9tksFlQRipcp05lwirpQCswXkhOgy1J


Sheild I used : https://www.aliexpress.com/item/1005007112191522.html (I'll upload a picture)
