.data
 prompt: .asciiz "Enter the height of the pattern (must be greater than 0): "
 error: .asciiz "Invalid Entry!\n"
 newline: .asciiz "\n"
 stars: .asciiz "*\t"
 otherstars: .asciiz "\t*"
 
.text
Start:        #start of loop

#Asking for user's input and taking it.
 li $v0 4            	#gets ready to print
 la $a0 prompt        	#goes to where it takes 
 syscall		#print
 
 li $v0 5            	#reads integer from user
 syscall            	#carries out
 
 move $t0 $v0        	#moves integer and stores it in t0

#checks if user's number is less than 0
 ble $t0, 0, lessthan   #if user's input is less than 0, then go to label
 j greaterthan
 
 lessthan:            	#label
 li $v0 4            	#goes find what print
 la $a0 error        	#reads what is needed to pint
 syscall            	#prints
 j Start            	#goes back to start
 
 greaterthan:
 
 mainLoop:
 bge $t1, $t0, exit	# if $t1 is greater than $t0, exit
 addi $t1, $t1, 1	# $t1 + 1 = $t1
 addi $t2, $t2, 1     	# input plus 1
 subi $t3, $t2, 1	# num of stars
 li $t4 0		# makin sure $t4 is 0
 li $t5 0		# making sure $t5 is 0
 beq $t2, 1, num	# keeping row 1 as just 1
 
 nop
 ndLoops:		# print stars ($t3 = #stars)
 li $v0 4		#tell what command 
 la $a0 stars		#tell what to print
 syscall		#prints
 addi $t4, $t4, 1	# $t4 = $t4 + 1
 blt $t4, $t3, ndLoops	#if $t4 less than $t3 go to ndLoops
 nop
 
 nop
 num:
 # print current row number
 li $v0 1		#tell what to do
 move $a0 $t2		#moves value of $t2 to $a0
 syscall		#excutes command
 beq $t2, 1, next	# if $t2 is equal to 1 go to next
 nop
 
 nop
 # print stars after numbers
 rdLoops:		
 li $v0 4		#tells what command to use
 la $a0 otherstars	#tells what to print
 syscall		#prints
 addi $t5, $t5, 1	#$t5 = $t5 +1
 blt $t5, $t3, rdLoops	#if $t5 is less than $t3, go to rdLoops
 nop
 
 next:
 li $v0 4		#gets ready to print
 la $a0 newline 	#reads line
 syscall        	#prints
 j mainLoop     	#goes to mainLoop
 
 exit:        		#stops
 li $v0 10
 syscall