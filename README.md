# Peony----TROJAN

(update: read : https://github.com/alexa872/Peony----TROJAN/blob/main/summary.txt)

a fud trojan that targets windows 10
by *alexa872


( update: after the new update of windows the meterpreter shellcode is getting detected, if you got a custom shellcode to replace the meterpreter shell it will work for sure )

this is another trojan that targets windows 10 i found this somewhere on the internet and a downloaded and modified it, when you generate your "big" shellcode, and paste it to the code, two files will be generated, the first is loader.exe which will load payload.dll {which has the shellcode in it}. but you need to divide your shellcode into 4 peaces "when you look at the code you'll get it". so basically to open your meterpreter/ idk what shell... you need to send the target 2 files, it is easy when you have basic knowledge in steganography. although if they were dumb enough you will need nothing. i added a comment in payload.cpp that will generate the perfect shellcode


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------



happy hunting
