.data
 buffer: .space 128
 pass: .asciiz "You entered the file:\n"
 newline: .asciiz "\n"
 error: .asciiz "Error: Invalid program argument.\n"
 mismatch: .asciiz "Error: There is a brace mismatch at index: "
 np: .asciiz "SUCCESS: There are "
 np2: .asciiz " pairs of braces. "


.text
#open file
#File name
 #pritning file name
 #check for valid name
 #check for valid length
 move $s3 $a1
 li $v0 13		#find file			
 lw $a0 ($a1)
 li $a1 0
 syscall
 move $s0 $v0

 
 lw $s1 ($s3)		# s1 contains address of the string
 add $s2 $zero $s1 	#counter
 add $t0 $s0 $s2	#address of next byte
 lb $t1 0($s1)		#load byte
 
 li $t6 65
 li $t7 90
 li $t5 96
 li $t4	123
 
 checkforvalid:
 # checks for error		
 ble $t1 64 invalid	#checks if character is less than or equal to 64 in ascii table
 beq $t1 91 invalid
 beq $t1 92 invalid
 beq $t1 93 invalid
 beq $t1 94 invalid
 beq $t1 95 invalid
 beq $t1 96 invalid
 bge $t1 123 invalid 	#checks if character is greater or equal to 123 in ascii table 
 
 #checks for passes
 blt $t1 $t6 Loop	#checks if 1st character IS valid from A to Z
 bgt $t1 $t7 Loop
 bgt $t1 $t5 Loop
 blt $t1 $t4 Loop
 
 Loop:
 addi $s1 $s1 1
 add $t0 $s0 $s1	#address next byte
 lb $t1 0($t0)		#load byte
 beq $t1 $zero cont
 bgt $t3 20 invalid	#check if length greater than 20
 addi $t3 $t3 1		#counter

 #checks for errors
 blt $t1 45 invalid	#check next byte
 beq $t1 47 invalid
 beq $t1 58 invalid
 beq $t1 59 invalid
 beq $t1 60 invalid
 beq $t1 61 invalid
 beq $t1 62 invalid
 beq $t1 63 invalid
 beq $t1 64 invalid
 beq $t1 91 invalid
 beq $t1 92 invalid
 beq $t1 93 invalid
 beq $t1 94 invalid
 beq $t1 96 invalid
 bge $t1 123 invalid

 #checks for passes
 beq $t1 46 Loop	#checks if 1st character IS valid from A to Z and _ and .
 blt $t1 $t6 Loop
 bgt $t1 $t7 Loop
 beq $t1 95 Loop
 
 bgt $t1 $t5 Loop	#checks if other character IS valid from a to z
 blt $t1 $t4 Loop
 
 j Loop
 
 cont: nop		#passses mesg
 li $t6 0		#reset registers
 li $t7 0
 li $t5 0
 li $t4	0
 li $t3 0
 
 li $v0 4
 la $a0 pass
 syscall
 
 li $v0 4
 lw $a0 ($s3)
 syscall
 
 li $v0 4
 la $a0 newline
 syscall
 j inFile
 
 invalid:		#invalid error
 li $v0 4
 la $a0 pass
 syscall
 
 li $v0 4
 lw $a0 ($s3)		# move value of $s1 to anothe register before you go into loop and then relace $s1 with that register here
 syscall
 
 li $v0 4
 la $a0 newline
 syscall
 
 li $v0 4
 la $a0 newline
 syscall
 
 li $v0 4
 la $a0 error
 syscall

 li $v0, 10
 syscall

 
 # li fileIndex 0
 li $s4 0
 Read:
 li $v0 14		#read whats in file
 move $a0 $s0
 la $a1 buffer
 la $a2 128
 syscall
 move $s7 $v0
 beqz $s7 exit
 # syscall 14 returns the number of characters read in $v0
 
 inFile: nop
 la $t3 buffer
 lb $t4 ($t3)
 # if $t4  is an open brace '(' '[' or '{'
 	# push $t4 to the stack
 open:
 addi $s4 $s4 1		# addi fileIndex fileIndex 1
 beqz $s7 Read
 subi $s7 $s7 1
 beq $s7 0 success
 beq $t4 40 push
 beq $t4 91 push
 beq $t4 123 push
 	
 # if $t4 is a closed brace ')' ']' or '}'
 	# pop a brace off the stack
 beq $t4 41 pop
 beq $t4 93 pop
 beq $t4 125 pop
 # if braces match
 	# continue
 
 match:
 addi $t3 $t3 1		#go to next character in string
 addi $t2 $t2 1		#counter to count length
 lb $t4 ($t3)
 j open
 
 pop:nop
 lw $s6 ($sp)
 addi $sp $sp 4
 beq $t4 40 checkPara
 beq $t4 91 checkSquare
 beq $t4 123 checkpointy
 j match
 
 push:nop
 addi $sp $sp -4
 sw $s5 ($sp)
 j match
 
 #compare braces
 # if $t4 == ']'
 	# if ($s6 != '[') error
 	# continue
  # if $t4 == '}'
 	# if ($s6 != '{') error
 	# continue
 	
 checkPara:
 addi $t7 $t7 1
 beq $s6 40 match
 bne $6 40 errormsg

 checkSquare:
 addi $t7 $t7 1
 beq $s6 91 match
 bne $s6 91 errormsg
 
 checkpointy:
 addi $t7 $t7 1
 beq $s6 123 match
 bne $s6 123 errormsg
 # else
 	# error message
 
 success:
 li $v0 4
 la $a0 np
 syscall
 
 li $v0 1
 la $a0 ($t7)
 syscall
 
 li $v0 4
 la $a0 np2
 syscall
 
 j exit
 
 errormsg:
 li $v0 4
 la $a0 mismatch
 syscall
 
 li $v0 1
 la $a0 ($t7)
 syscall
 j exit
 
 exit:
 li $v0 16		#close file
 move $a0 $s0
 syscall
 
 li $v0 10
 syscall
