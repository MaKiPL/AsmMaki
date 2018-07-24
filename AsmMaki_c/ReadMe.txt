AsmMaki is probably the first realtime x86-32 assembler interpretor made for training and learning. Keep in mind it's only a simulator. Simulator will have real-time updated register content (just like in debuggers) but it will let you input commands without worrying about program crashing. You'll be able to train for example arithmetic operations including FPU without having to assembly the software in e.g. NASM or FASM and debug again. 



Planned assembler available features for core release:
*Memory (EAX:EDX registers + extension)
*ALU Arithmetic + logic (with FLAGS simulation)
*Conditions (debug TRUE or FALSE for CMP; Simulation for e.g. JNE, JA ... will yeld only SUCCESS or FAIL in log window)
*FPU operations
*Basic 4096 byte stack

Planned assembler available features for upcoming release that MIGHT happen:
*Allocating memory for DB; DD allocating
*Memory management with pointer from allocated memory (e.g. MOV eax, [EBX])

Planned assembler features in future that probably won't happen:
*Allocating memory for functions and assemblying user code
*Flow control
*Conditons with working flow
*Internal calling
*Syscalling + INT operations simulation (based on BIOS + DOS)
*Assemblying to machine code
