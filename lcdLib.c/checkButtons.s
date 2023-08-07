.data
    .align 2
    buttonPressed: .word 0  ; Declare buttonPressed variable in data section, initialized to 0

.text
    .align 2
    checkButtons:
        ; Load P2IN into a register
        mov 0x28, r12

        ; Create a jump table for button presses
        cmp #0x0001, r12
        je case1

        cmp #0x0002, r12
        je case2

        cmp #0x0004, r12
        je case3

        cmp #0x0008, r12
        je case4

        ; No button is pressed, set buttonPressed to 0
        jmp esac

    case1:
        ; Button 1 is pressed, set buttonPressed to 1
	call #growSquare
	mov #1, &buttonPressed
        jmp esac

    case2:
        ; Button 2 is pressed, set buttonPressed to 2
	call #shrinkSquare
	mov #2, &buttonPressed
        jmp esac

    case3:
        ; Button 3 is pressed, set buttonPressed to 3
	call #rotateSquare
	mov #3, &buttonPressed
        jmp esac

    case4:
        ; Button 4 is pressed, set buttonPressed to 4
	call #cycleColors
	mov #4, &buttonPressed
	jmp esac
	
    esac:
        ; Rest of the checkButtons function using the buttonPressed value
        ; ...

        ret
